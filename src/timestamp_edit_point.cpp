#include "timestamp_edit.h"
#include <geometry_msgs/PointStamped.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "timestamp_edit_point");

    TimestampEdit<geometry_msgs::PointStamped> te;
    
    ros::spin();

    return 0;
}