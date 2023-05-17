cmake_minimum_required(VERSION 2.8.3)

project(hikrobot_camera)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  camera_info_manager
)

catkin_package(
 
)

find_package(OpenCV REQUIRED)

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
  include
  /opt/MVS/include/
)

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "aarch64")
  LINK_DIRECTORIES(
  /opt/MVS/lib/aarch64/
  )
elseif(${CMAKE_SYSTEM_PROCESSOR} MATCHES "x86_64")
  LINK_DIRECTORIES(
  /opt/MVS/lib/64/
  )
endif()

add_executable(${PROJECT_NAME}
src/hikrobot_camera.cpp)

 target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES}
   ${OpenCV_LIBRARIES}
   MvCameraControl
   # GCBase_gcc421_v3_0
   # GenApi_gcc421_v3_0
   # MVGigEVisionSDK
   # log4cpp_gcc421_v3_0
   # MVRender
   # Log_gcc421_v3_0
   # MvUsb3vTL
   # MathParser_gcc421_v3_0
   # NodeMapData_gcc421_v3_0
   # MediaProcess
   # XmlParser_gcc421_v3_0
   # X11
 )
