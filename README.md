This is a modified ros sdk of hikvision industrial camera, supporting multi-cam. If one cam is used, plz modify right_camera.yaml

If usb-cam is used, line 133 in hikrobot_camera.hpp must be changed to use usb struct. Detailed api can be found in camera_info.h in official MVS.
# HIKROBOT-MVS-CAMERA-ROS
The ros driver package of Hikvision Industrial Camera SDK. Support configuration parameters, the parameters have been optimized, and the photos have been transcoded to rgb format.
Please install mvs, https://blog.csdn.net/weixin_41965898/article/details/116801491

# Install
```
mkdir -p ~/ws_hikrobot_camera/src
git clone https://github.com/Mikehuntisbald/HIKVISION-ROS-SDK
cd ~/ws_hikrobot_camera
catkin_make
```
# launch run
```
source ./devel/setup.bash 
roslaunch hikrobot_camera right.launch
```
