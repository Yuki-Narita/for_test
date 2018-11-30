#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

void moveToGoal(double goalX,double goalY,std::string mapFrame,std::string movebaseNode ){

	std::cout << "＊＊＊＊＊＊＊＊＊＊目標座標を受信＊＊＊＊＊＊＊＊＊＊" << std::endl;

	//define a client for to send goal requests to the move_base server through a SimpleActionClient

	//actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("robot1/move_base", true);
	actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac(movebaseNode, true);

	//wait for the action server to come up//5.0秒まで待つ
	while(!ac.waitForServer(ros::Duration(5.0)) && ros::ok()){
		std::cout << "＊＊＊＊＊＊＊＊＊＊待機中＊＊＊＊＊＊＊＊＊＊" << std::endl;;
	}

	move_base_msgs::MoveBaseGoal goal;

	//set up the frame parameters
	goal.target_pose.header.frame_id = mapFrame;

	goal.target_pose.header.stamp = ros::Time::now();

	/* moving towards the goal*/

	goal.target_pose.pose.position.x =  goalX;
	goal.target_pose.pose.position.y =  goalY;
	goal.target_pose.pose.position.z =  0.0;
	goal.target_pose.pose.orientation.x = 0.0;
	goal.target_pose.pose.orientation.y = 0.0;
	goal.target_pose.pose.orientation.z = 0.0;
	goal.target_pose.pose.orientation.w = 1.0;

	std::cout << "＊＊＊＊＊＊＊＊＊＊目標座標セット(" << goalX << "," << goalY << ")＊＊＊＊＊＊＊＊＊＊" << std::endl;

	std::cout << "＊＊＊＊＊＊＊＊＊＊経路を作成中＊＊＊＊＊＊＊＊＊＊" << std::endl;
	ac.sendGoal(goal);
	std::cout << "＊＊＊＊＊＊＊＊＊＊sendend＊＊＊＊＊＊＊＊＊＊" << std::endl;
	ac.waitForResult();
	std::cout << "＊＊＊＊＊＊＊＊＊＊waitend＊＊＊＊＊＊＊＊＊＊" << std::endl;
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
		std::cout << "＊＊＊＊＊＊＊＊＊＊目標座標に到着＊＊＊＊＊＊＊＊＊＊" << std::endl;
	}
	else{
		std::cout << "＊＊＊＊＊＊＊＊＊＊目標座標への移動不可＊＊＊＊＊＊＊＊＊＊" << std::endl;
		//return res.result;
	}
}


int main(int argc, char** argv){
	ros::init(argc, argv, "action_voronoi_test");

    double x,y;
	std::string mapFrame;
	std::string movebaseNode;

	ros::NodeHandle param("~");

	param.getParam("map_frame", mapFrame);
	param.getParam("movebaseNode", movebaseNode);


    while(ros::ok())
    {
        std::cout << "x : ";
        std::cin >> x;
        std::cout << "y : ";
        std::cin >> y;
        moveToGoal(x,y,mapFrame,movebaseNode);
    }

	return 0;
}