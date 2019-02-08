#include "timestamp_edit.h"
#include <sensor_msgs/PointCloud2.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "timestamp_edit_odom");

    TimestampEdit<sensor_msgs::PointCloud2> te;
    
    ros::spin();

    return 0;
}