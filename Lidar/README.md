# Lidar Obstacle Detection Project

I studied this project on my own ubuntu. 
For the preparation section,some of them are based on the official [github](https://github.com/udacity/SFND_Lidar_Obstacle_Detection).



## I. Preparation on Ubuntu
<img src="media/ObstacleDetectionFPS.gif" width="700" height="400" />

1. Clone my github repo into your own computer:

   ```sh
   cd ~
   git clone https://github.com/WOZIJI!!!!/SFND_Lidar_Obstacle_Detection.git
   ```

2.  Edit [CMakeLists.txt](https://github.com/udacity/SFND_Lidar_Obstacle_Detection/blob/master/CMakeLists.txt) as follows:

   ```cmake
   cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
   
   add_definitions(-std=c++14)
   
   set(CXX_FLAGS "-Wall")
   set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
   
   project(playback)
   
   find_package(PCL 1.11 REQUIRED)
   
   include_directories(${PCL_INCLUDE_DIRS})
   link_directories(${PCL_LIBRARY_DIRS})
   add_definitions(${PCL_DEFINITIONS})
   list(REMOVE_ITEM PCL_LIBRARIES "vtkproj4")
   
   
   add_executable (environment src/environment.cpp src/render/render.cpp src/processPointClouds.cpp)
   target_link_libraries (environment ${PCL_LIBRARIES})
   ```

3. Execute the following commands in a terminal

   ```shell
   sudo apt install libpcl-dev
    ```
   This should install the latest version of PCL.

<br/>

**Note:** The library version of PCL being distributed by the apt repository for 18.04 and 20.04 are both older than v1.11. The following links have the information regarding the versions-

[Bionic 18.04](https://www.ubuntuupdates.org/package/core/bionic/universe/updates/libpcl-dev)
[Focal 20.04](https://www.ubuntuupdates.org/package/core/focal/universe/base/libpcl-dev)

You can either build PCL from source (for v1.11) or use the older version.

**Build PCL from Source:**

[PCL Source Github](https://github.com/PointCloudLibrary/pcl)




## II. Run my code
Then, cmake this project to run it.


   ```sh
   cd ~/SFND_Lidar_Obstacle_Detection
   mkdir build && cd build
   cmake ..
   make
   ./environment
   ```
In the environment.cpp, you can choose different to render!

   




## III. Explanation about my code


#### Lidar and Point Clouds
