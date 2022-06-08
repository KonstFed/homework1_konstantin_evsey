#include <ros/ros.h>
#include <std_msgs/Bool.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv,"turtles_spawner");
    ros::NodeHandle n;
    ros::Duration(0.5).sleep();
    
    ros::Publisher pub_start = n.advertise<std_msgs::Bool>("/start_topic",1);
    std_msgs::Bool msg;
    msg.data = true;
    ros::Rate rate(1);
    while (ros::ok())
    {
        pub_start.publish(msg);
        ros::spinOnce();
        rate.sleep();
    }
}