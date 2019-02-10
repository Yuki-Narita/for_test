#include <ros/ros.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <voronoi_planner/planner_core.h>
#include <geometry_msgs/PoseStamped.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "costmap_node");
  tf::TransformListener tf(ros::Duration(10));
  costmap_2d::Costmap2DROS lcr("costmap", tf);

  std::string name = "test_map";

  voronoi_planner::VoronoiPlanner vp;

  vp.initialize(name, &lcr);

  geometry_msgs::PoseStamped start;
  geometry_msgs::PoseStamped goal;
  std::vector<geometry_msgs::PoseStamped> plan;

  start.header.frame_id = "robot1/map";
  goal.header.frame_id = "robot1/map";

  goal.pose.position.x = 5.0;

  //vp.makePlan(start,goal,plan);

  //std::cout << "frame_id :: " << lcr.getGlobalFrameID() << std::endl;
  ros::spinOnce();

  //makePlan no ato ni costmap no kousin ga hairuto error

  //voronoi_planner no cmakelist kaikikae dynamic_voronoi no tokoro

  while(ros::ok()){
    //ros::spinOnce();
    vp.makePlan(start,goal,plan);
    ros::spinOnce();
  }

  return (0);
}