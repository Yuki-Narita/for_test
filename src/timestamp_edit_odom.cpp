#include "timestamp_edit.h"
#include <nav_msgs/Odometry.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "timestamp_edit_odom");

    TimestampEdit<nav_msgs::Odometry> te;
    
    ros::spin();

    return 0;
}