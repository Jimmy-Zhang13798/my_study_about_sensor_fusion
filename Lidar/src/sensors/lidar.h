#ifndef LIDAR_H
#define LIDAR_H
#include "../render/render.h"
#include <ctime>
#include <chrono>

const double pi = 3.1415;


// this Ray struct is only directly used by the struct Lidar in this same lidar.h 
// Lidar will use these rays to sense its surrounding by doing ray casting. 
// in this Ray struct, a ray is more like a point that moves forword step by step, so one step means its resolution
// Done!
struct Ray
{
	
	Vect3 origin;
	double resolution;
	Vect3 direction;
	Vect3 castPosition;
	double castDistance;

	// parameters:
	// setOrigin: the starting position from where the ray is cast
	// horizontalAngle: the angle of direction the ray travels on the xy plane
	// verticalAngle: the angle of direction between xy plane and ray 
	// 				  for example 0 radians is along xy plane and pi/2 radians is stright up
	// resoultion: the magnitude of the ray's step, used for ray casting, the smaller the more accurate but the more expensive
	Ray(Vect3 setOrigin, double horizontalAngle, double verticalAngle, double setResolution)
		: origin(setOrigin), resolution(setResolution), 
		direction(resolution*cos(verticalAngle)*cos(horizontalAngle), resolution*cos(verticalAngle)*sin(horizontalAngle),resolution*sin(verticalAngle)),
		castPosition(origin), castDistance(0)
	{}

	// call this function once, it will cast one ray, and when collision happens or when it reachs the maxdistance
	// then it will put the final point into a cloud
	void rayCast(const std::vector<Car>& cars, double minDistance, double maxDistance, 
				 pcl::PointCloud<pcl::PointXYZ>::Ptr& cloud, double slopeAngle, double sderr)

	{
		// reset ray
		castPosition = origin;
		castDistance = 0;

		bool collision = false;

		while(!collision && castDistance < maxDistance)
		{

			castPosition = castPosition + direction;
			castDistance += resolution;

			// check if there is any collisions with ground slope
			collision = (castPosition.z <= castPosition.x * tan(slopeAngle));

			// check if there is any collisions with cars
			if(!collision && castDistance < maxDistance)
			{
				for(Car car : cars)
				{
					collision |= car.checkCollision(castPosition);//|= means :a=a|b
					if(collision)
						break;
				}
			}
		}

 
		if((castDistance >= minDistance)&&(castDistance<=maxDistance))
		{
			// add noise based on standard deviation error
			double rx = ((double) rand() / (RAND_MAX));
			double ry = ((double) rand() / (RAND_MAX));
			double rz = ((double) rand() / (RAND_MAX));
			cloud->points.push_back(pcl::PointXYZ(castPosition.x+rx*sderr, castPosition.y+ry*sderr, castPosition.z+rz*sderr));
		}
			
	}

};



// Done!
struct Lidar
{

	std::vector<Ray> rays;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	std::vector<Car> cars;
	Vect3 position;
	double groundSlope;
	double minDistance;
	double maxDistance;
	double resoultion;
	double sderr;

	Lidar(std::vector<Car> setCars, double setGroundSlope)
		: cloud(new pcl::PointCloud<pcl::PointXYZ>()), position(0,0,2.6)
	{
		// TODO:: set minDistance to 5 to remove points from roof of ego car
		minDistance = 5;
		maxDistance = 50;
		resoultion = 0.2;
		// TODO:: set sderr to 0.2 to get more interesting pcd files
		sderr = 0.2;
		cars = setCars;
		groundSlope = setGroundSlope;

		// TODO:: increase number of layers to 8 to get higher resoultion pcd
		int numLayers = 8;
		// the steepest vertical angle
		double steepestAngle =  30.0*(-pi/180);
		double angleRange = 26.0*(pi/180);
		// TODO:: set to pi/64 to get higher resoultion pcd
		double horizontalAngleInc = pi/64;

		double angleIncrement = angleRange/numLayers;
		// the outside for loop is for vertical angle 
		for(double angleVertical = steepestAngle; angleVertical < steepestAngle+angleRange; angleVertical+=angleIncrement)
		{	
			// the outside for loop is for horizontal angle
			for(double angle = 0; angle <= 2*pi; angle+=horizontalAngleInc)
			{
				Ray ray(position,angle,angleVertical,resoultion);
				rays.push_back(ray);
			}
		}
	}

	~Lidar()
	{
		// pcl uses boost smart pointers for cloud pointer so we don't have to worry about manually freeing the memory
	}

	pcl::PointCloud<pcl::PointXYZ>::Ptr scan()
	{
		cloud->points.clear();
		auto startTime = std::chrono::steady_clock::now();
		for(Ray ray : rays)
			ray.rayCast(cars, minDistance, maxDistance, cloud, groundSlope, sderr);
		auto endTime = std::chrono::steady_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
		cout << "ray casting took " << elapsedTime.count() << " milliseconds" << endl;
		cloud->width = cloud->points.size();
		cloud->height = 1; // one dimensional unorganized point cloud dataset
		return cloud;
	}

};

#endif