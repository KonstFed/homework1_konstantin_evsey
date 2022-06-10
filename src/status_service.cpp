#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_srvs/Empty.h>
#include <string>


class TurtleCallbacks {
    bool turtleInfo[4];
public:
    TurtleCallbacks() {
        for (int i = 0; i < 4; i++) {
            turtleInfo[i] = false;
        }
    }
    void turtle1Callback(const std_msgs::Bool::ConstPtr& msg);
    void turtle2Callback(const std_msgs::Bool::ConstPtr& msg);
    void turtle3Callback(const std_msgs::Bool::ConstPtr& msg);
    void turtle4Callback(const std_msgs::Bool::ConstPtr& msg);
    bool statusServiceCallback(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res);
};

void TurtleCallbacks::turtle1Callback(const std_msgs::Bool::ConstPtr& msg) {
    turtleInfo[0] = msg->data;
}

void TurtleCallbacks::turtle2Callback(const std_msgs::Bool::ConstPtr& msg) {
    turtleInfo[1] = msg->data;
}

void TurtleCallbacks::turtle3Callback(const std_msgs::Bool::ConstPtr& msg) {
    turtleInfo[2] = msg->data;
}

void TurtleCallbacks::turtle4Callback(const std_msgs::Bool::ConstPtr& msg) {
    turtleInfo[3] = msg->data;
}

bool TurtleCallbacks::statusServiceCallback(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res) {
    std::string turtleStatus[4];
    for (int i = 0; i < 4; i++) {
        turtleStatus[i] = turtleInfo[i] ? "done" : "not done";
    }
    ROS_INFO("Turtle status: Turtle 1 - %s, Turtle 2 - %s, Turtle 3 - %s, Turtle 4 - %s", turtleStatus[0].c_str(), turtleStatus[1].c_str(), turtleStatus[2].c_str(), turtleStatus[3].c_str());
    return true;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "status_server");
    ros::NodeHandle n;
    TurtleCallbacks callbacks;
    ros::Subscriber turtle1Sub = n.subscribe("/turtle1_done", 10, &TurtleCallbacks::turtle1Callback, &callbacks);
    ros::Subscriber turtle2Sub = n.subscribe("/turtle2_done", 10, &TurtleCallbacks::turtle2Callback, &callbacks);
    ros::Subscriber turtle3Sub = n.subscribe("/turtle3_done", 10, &TurtleCallbacks::turtle3Callback, &callbacks);
    ros::Subscriber turtle4Sub = n.subscribe("/turtle4_done", 10, &TurtleCallbacks::turtle4Callback, &callbacks);
    ros::ServiceServer statusServer = n.advertiseService("status", &TurtleCallbacks::statusServiceCallback, &callbacks);
    ros::spin();
}