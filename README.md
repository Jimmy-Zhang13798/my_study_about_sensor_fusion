# My personal learning notes diary about sensor fusion 

### -- a learning diary for udacity sensor fusion course
Some of the notes are based on the this [repo](https://github.com/fanweng/Udacity-Sensor-Fusion-Nanodegree).

lecture notes: you can check this [repo](https://github.com/fanweng/Udacity-Sensor-Fusion-Nanodegree).


I recorded the detailed knowledges that I learned, into these 4 markdown files:



[Notes of Lidar ](01Lidar.md)

[Notes of Camera ](02Camera.md)  

[Notes of Radar ](03Radar.md)  

[Notes of Sensor fusion ](04Sensor_fusion.md)  




And for the code and project parts, there are four folders, just check them. I finished my code and added more detailed comments into the officail code.



## Basic introduction

All sensors have their own different types of strengths and weeknesses. And Lidar, Radar,Camera,are the three most impotant ones for self driving.

Before doing sensor fusion, we need to know how to process raw lidar/radar/camera data separately. Then we will learn sensor fusion.

So ,we have four parts in this learning diary

- #### Lidar
- #### Camera
- #### Radar
- #### Sensor fusion



<br/><br/>
## To sum up, this is what I learned

#### Lidar


1. Learn the basic logic of Liadr  and build a simulated lidar and environment, to get pointcloud to help me understand  pointcloud better.
2. Segmentation:
    - follow the teacher's instruction  to use the the RANSAC from PCL library to segment planes.
    - understand and write my own RANSAC algorithm, and run it successfully.
3. Clustering Obstacles:
    - follow the teacher's instruction to use the the KD_tree , Euclidean Clustering algorithm from PCL library to cluster obstacles.
    - understand and write my own KD_tree and Euclidean Clustering algorithm, and run it successfully to cluster obstacles.
4. Other stuff:
    - Get more familiar with PCL library,like downsampling, Voxel grid filtering,Region of interest (ROI) filtering, stream PCD, add bounding boxes around the clusters, etc
    - download real PCD files to play and try my own algorithm, and see a lot of difference in real situation.


#### Camera

please wait, it will come soon

#### Radar

please wait, it will come soon

#### Sensor fusion

please wait, it will come soon


