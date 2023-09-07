#include <iostream>
#include "opencv2/opencv.hpp"
#include <vector>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <camera_info_manager/camera_info_manager.h>
#include "hikrobot_camera.hpp"

// 剪裁掉照片和雷达没有重合的视角，去除多余像素可以使rosbag包变小
#define FIT_LIDAR_CUT_IMAGE false
#if FIT_LIDAR_CUT_IMAGE
    #define FIT_min_x 420
    #define FIT_min_y 70
    #define FIT_max_x 2450
    #define FIT_max_y 2000
#endif 

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    //********** variables    **********/
    cv::Mat src;
    //string src = "",image_pub = "";
    //********** rosnode init **********/
    ros::init(argc, argv, "hikrobot_camera");
    ros::NodeHandle hikrobot_camera;
    camera::Camera MVS_cap(hikrobot_camera);
    //********** rosnode init **********/
    image_transport::ImageTransport main_cam_image(hikrobot_camera);
    std::string TopicName;
    std::string calib_config_file;
    std::string distortion_model;

    vector<double> camera_matrix;
    vector<double> dist_coeffs;

    hikrobot_camera.param<string>("distortion_model", distortion_model, "plumb_bob");
    hikrobot_camera.param<vector<double>>("camera_matrix", camera_matrix,
                           vector<double>());
    hikrobot_camera.param<vector<double>>("dist_coeffs", dist_coeffs, vector<double>());
    hikrobot_camera.getParam("TopicName", TopicName);
    image_transport::CameraPublisher image_pub = main_cam_image.advertiseCamera(TopicName, 1000);

    sensor_msgs::Image image_msg;
    sensor_msgs::CameraInfo camera_info_msg;
    cv_bridge::CvImagePtr cv_ptr = boost::make_shared<cv_bridge::CvImage>();
    cv_ptr->encoding = sensor_msgs::image_encodings::BGR8;  // 就是rgb格式 
    
    //********** 10 Hz        **********/
    ros::Rate loop_rate(10);

    while (ros::ok())
    {

        loop_rate.sleep();
        ros::spinOnce();

        MVS_cap.ReadImg(src);
        if (src.empty())
        {
            continue;
        }
#if FIT_LIDAR_CUT_IMAGE
        cv::Rect area(FIT_min_x,FIT_min_y,FIT_max_x-FIT_min_x,FIT_max_y-FIT_min_y); // cut区域：从左上角像素坐标x，y，宽，高
        cv::Mat src_new = src(area);
        cv_ptr->image = src_new;
#else
        cv_ptr->image = src;
#endif
        image_msg = *(cv_ptr->toImageMsg());
        constexpr uint64_t k1e9 = 1000000000;
        image_msg.header.stamp = ros::Time().fromSec(camera::stImageInfo.nHostTimeStamp / k1e9);  // ros发出的时间不是快门时间
        image_msg.header.frame_id = "hikrobot_camera";

        camera_info_msg.width = camera::stImageInfo.nWidth;
        camera_info_msg.height = camera::stImageInfo.nHeight;
        camera_info_msg.distortion_model = distortion_model;
        for (int i = 0; i < 9; i++) {
          camera_info_msg.K[i] = camera_matrix[i];
        }
        for (int i = 0; i < 5; i++) {
          camera_info_msg.D[i] = dist_coeffs[i];
        }

        image_pub.publish(image_msg, camera_info_msg);
        //*******************************************************************************************************************/
    }
    return 0;
}
