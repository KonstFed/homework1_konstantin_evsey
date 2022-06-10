#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_srvs/Empty.h>


class StartStopCallbacksWithPub {
    ros::Publisher& pub;
public:
    StartStopCallbacksWithPub(ros::Publisher pub) : pub(pub) {};
    bool start(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res);
    bool stop(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res);

};

bool StartStopCallbacksWithPub::start(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res) {
    std_msgs::Bool msg;
    msg.data = true;
    pub.publish(msg);
    return true;
}


bool StartStopCallbacksWithPub::stop(std_srvs::Empty::Request& req, std_srvs::Empty::Response& res) {
    std_msgs::Bool msg;
    msg.data = false;
    pub.publish(msg);
    return true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv,"turtles_spawner");
    ros::NodeHandle n;
    ros::Publisher pub_start = n.advertise<std_msgs::Bool>("/start_topic",1);

    StartStopCallbacksWithPub callbacks(pub_start);
    ros::ServiceServer startService = n.advertiseService("/start", &StartStopCallbacksWithPub::start, &callbacks);
    ros::ServiceServer stopService = n.advertiseService("/stop", &StartStopCallbacksWithPub::stop, &callbacks);
    ros::spin();
}