#include "timestamp_edit.h"
#include <sensor_msgs/Image.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "timestamp_edit");

    TimestampEdit<sensor_msgs::Image> te;
    
    ros::spin();

    return 0;
}