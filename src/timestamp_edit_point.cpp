#include "timestamp_edit.h"
#include <sensor_msgs/Joy.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "timestamp_edit_point");

    TimestampEdit<sensor_msgs::Joy> te;
    
    ros::spin();

    return 0;
}