#include <ros/ros.h>
#include <costmap_2d/costmap_2d_ros.h>
#include <voronoi_planner/planner_core.h>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "costmap_node");
  tf::TransformListener tf(ros::Duration(10));
  costmap_2d::Costmap2DROS lcr("costmap", tf);

  VoronoiPlanner vp("test_map", &lcr, "map");

  while(ros::ok()){
    ros::spinOnce();
  }

  return (0);
}