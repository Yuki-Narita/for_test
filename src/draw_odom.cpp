#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <std_msgs/ColorRGBA.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>

class DrawOdom
{
private:
    ros::NodeHandle s;
    ros::NodeHandle p;
    ros::NodeHandle pm;

    ros::Subscriber sub;
    ros::Publisher pub;

    std_msgs::ColorRGBA markColor;

    visualization_msgs::Marker odomMark;

    std::string odomFrameId;

    void odomCB(const nav_msgs::Odometry::ConstPtr& msg);

public:
    DrawOdom();
    ~DrawOdom(){};
};

DrawOdom::DrawOdom(){
    sub = s.subscribe("odom",1,&DrawOdom::odomCB,this);
    pub = p.advertise<visualization_msgs::Marker>("odom_marker", 1);

    odomFrameId = "/odom";
    odomMark.header.frame_id = odomFrameId;
    odomMark.pose.orientation.w = 1.0;
    odomMark.scale.x = 0.1;
    odomMark.type = visualization_msgs::Marker::LINE_STRIP;
    odomMark.action = visualization_msgs::Marker::ADD;
    odomMark.lifetime = ros::Duration(0);
    odomMark.ns = "odometry";
    odomMark.id = 0;

    markColor.r = 1.0f;
    markColor.g = 0.0f;
    markColor.b = 0.0f;
    markColor.a = 1.0f;
}

void DrawOdom::odomCB(const nav_msgs::Odometry::ConstPtr& msg){
    geometry_msgs::Point input;

    input.x = msg -> pose.pose.position.x;
    input.y = msg -> pose.pose.position.y;
    input.z = msg -> pose.pose.position.z;

    odomMark.points.push_back(input);
    odomMark.colors.push_back(markColor);

    odomMark.header.stamp = ros::Time::now();

    pub.publish(odomMark);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "draw_odom");

    DrawOdom dr;
    
    ros::Rate rate(1);
    
    while(ros::ok()){
        ros::spinOnce();
        rate.sleep();
    }


    return 0;
}