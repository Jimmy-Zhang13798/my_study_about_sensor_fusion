#ifndef BOX_H
#define BOX_H
#include <Eigen/Geometry> 

struct BoxQ
{
	Eigen::Vector3f bboxTransform;//=Eigen::Matrix<float, 3, 1> ,means 3 rows 1 column of floats
	Eigen::Quaternionf bboxQuaternion;// Quaternion with float (single precision ),may need to study about Quaternionf
	float cube_length;
    float cube_width;
    float cube_height;
};
struct Box
{
	float x_min;
	float y_min;
	float z_min;
	float x_max;
	float y_max;
	float z_max;
};
#endif