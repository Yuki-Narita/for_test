#include <ros/ros.h>

#include <dynamic_reconfigure/server.h>
#include <for_test/dynamic_testConfig.h>

class DynamicTest
{
private:
    ros::NodeHandle test_param;

    double initPoseX;



    void paramReset(void);

public:
    DynamicTest();
    ~DynamicTest(){};

    void callback(for_test::dynamic_testConfig &config, uint32_t level);
};

DynamicTest::DynamicTest()
:test_param("~")
{
    test_param.getParam("init_pose_x", initPoseX);
    ROS_INFO("initial Parameter: %f", initPoseX);
}

void DynamicTest::callback(for_test::dynamic_testConfig &config, uint32_t level) {
    static int count = 0;
    ROS_INFO("before Parameter: %f", initPoseX);
    ROS_INFO("Reconfigure Request: %f", config.init_pose_x);
    initPoseX = config.init_pose_x;
    ROS_INFO("after Parameter: %f", initPoseX);
    ROS_INFO("count: %d", count);
    if(count%5 == 0)
    {
        paramReset();
        ROS_INFO("reset Parameter: %f", initPoseX);
    }
    count++;
}

void DynamicTest::paramReset(void)
{
    ROS_INFO("reset Parameter");
    test_param.setParam("init_pose_x" , 0);
    sleep(5);
    test_param.getParam("init_pose_x", initPoseX);
}

int main (int argc, char** argv)
{
    ros::init(argc, argv, "dynamic_test");

    DynamicTest dt;

    dynamic_reconfigure::Server<for_test::dynamic_testConfig> server;
    dynamic_reconfigure::Server<for_test::dynamic_testConfig>::CallbackType f;

    f = boost::bind(&DynamicTest::callback,&dt, _1, _2);
    server.setCallback(f);

    while(ros::ok())
    {
        ROS_INFO("Spinning node");
        sleep(5);
        ros::spinOnce();
        ROS_INFO("after Spinning node");
        sleep(5);
    }
    
    return 0;
}