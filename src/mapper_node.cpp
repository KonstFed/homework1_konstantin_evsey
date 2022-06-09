#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <homework1_konstantin_evsey/TwistArray.h>
#include <string>

class ListenerWithPub {
    ros::Publisher* pubArray[4];
public:
    ListenerWithPub(ros::Publisher* pubArr[]);
    void callback(const homework1_konstantin_evsey::TwistArray::ConstPtr& msgPtr);
};

ListenerWithPub::ListenerWithPub(ros::Publisher* pubArr[]) {
    pubArray[0] = pubArr[0];
    pubArray[1] = pubArr[1];
    pubArray[2] = pubArr[2];
    pubArray[3] = pubArr[3];
}


void ListenerWithPub::callback(const homework1_konstantin_evsey::TwistArray::ConstPtr& msgPtr) {
    geometry_msgs::Twist msgs[4];
    msgs[0] = msgPtr->turtle1;
    msgs[1] = msgPtr->turtle2;
    msgs[2] = msgPtr->turtle3;
    msgs[3] = msgPtr->turtle4;
    for (int i = 0; i < 4; i++) {
        pubArray[i]->publish(msgs[i]);
    }
}

int main(int argn, char** argc) {
    ros::init(argn, argc, "mapper_node");
    ros::NodeHandle n;
    ros::Publisher pubArray[4];
    for (int i = 0; i < 4; i++) {
        const std::string topicStr = "/turtle" + std::to_string(i + 1) + "/cmd_vel";        
        pubArray[i] = n.advertise<geometry_msgs::Twist>(topicStr, 10);
    }
    ros::Publisher* pubPointerArray[4];
    for (int i = 0; i < 4; i++) {
        pubPointerArray[i] = &pubArray[i];
    }
    ListenerWithPub listener(pubPointerArray);
    ros::Subscriber sub = n.subscribe("/turtles_cmd", 10, &ListenerWithPub::callback, &listener);
    ros::spin();
    return 0;
}