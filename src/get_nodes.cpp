#include <ros/ros.h>
#include <ros/datatypes.h>//V_stringが定義されている

int main(int argc, char ** argv){
    ros::init(argc, argv, "get_nodes");

    //ノード名のリストを取得
    std::vector <std::string> nodeList;
    ros::master::getNodes(nodeList);

    ros::V_string nodeList2;
    ros::master::getNodes(nodeList2);

    for(int i=0;i<nodeList.size();i++){
        std::cout << "node[" << i << "] : " << nodeList[i] << std::endl;
    }

    for(int i=0;i<nodeList2.size();i++){
        std::cout << "node2[" << i << "] : " << nodeList2[i] << std::endl;
    }

    //トピック名のリストを取得
    ros::master::V_TopicInfo topicList;
    ros::master::getTopics(topicList);

    for(int i=0;i<topicList.size();i++){
        std::cout << "topic[" << i << "] << {name : " << topicList[i].name << "} , {type : " << topicList[i].datatype << "}" << std::endl;
    }


    return 0;
}