# Installation 

## MVS sdk
Download the SDK according to your platform architecture. 
https://www.hikrobotics.com/cn/machinevision/service/download

For x86 platform
```
dpkg -i MVS-2.1.0_x86_64_20201228.deb
```
For aarch64 platform like Jeston Nano or NX
```
dpkg -i MVS-2.1.0_aarch64_20201228.deb
```
After install the sdk
```
source ~/.bashrc
```

## hikrobot_camera
```
cd ~/catkin_ws/src
git clone https://github.com/tianb03/hikrobot_camera
cd .. && catkin_make
```


# launch
Indoor, outdoor launch files take in different params.
```
roslaunch hikrobot_camera hikrobot_camera.launch
rosrun image_view image_view image:=/hikrobot_camera/rgb
```

or launch RVIZ to show the image
```
roslaunch hikrobot_camera hikrobot_camera_rviz.launch
```