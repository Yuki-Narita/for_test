#include <ros/ros.h>

template<typename T>
class TimestampEdit
{
private:
    ros::NodeHandle s;
    ros::NodeHandle p;
    ros::NodeHandle pm;

    ros::Subscriber sub;
    ros::Publisher pub;

    std::string subTopic;
    std::string pubTopic;

    void subCB(const typename T::ConstPtr& msg);

public:
    TimestampEdit();
    ~TimestampEdit(){};
};

template<typename T>
TimestampEdit<T>::TimestampEdit()
:pm("~")
{
    pm.getParam("sub_topic", subTopic);
    pm.getParam("pub_topic", pubTopic);

    sub = s.subscribe(subTopic,1,&TimestampEdit::subCB,this);
    pub = p.advertise<T>(pubTopic, 1);

}

template<typename T>
void TimestampEdit<T>::subCB(const typename T::ConstPtr& msg){
    T input;

    input = *msg;

    input.header.stamp = ros::Time::now();

    pub.publish(input);
}