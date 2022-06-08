#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <homework1_konstantin_evsey/TwistArray.h>
#include <math.h>

const char* SERVICE_KILL_TURTLE = "/kill";
const char* SERVICE_SPAWN_TURTLE = "/spawn";

homework1_konstantin_evsey::TwistArray mymsg;
bool listened[] = {false,false,false,false};

ros::Publisher pub_turtles_cmd;

void send_turtles_cmd()
{
    pub_turtles_cmd.publish(mymsg);
    ROS_INFO("send_turtles_cmd is called!!!!");
    listened[0] = false;
    listened[1] = false;
    listened[2] = false;
    listened[3] = false;
}

void callback_turtle1_cmd(geometry_msgs::Twist msg)
{
    mymsg.turtle1.linear = msg.linear;
    mymsg.turtle1.angular = msg.angular;
    listened[0] = true;
    if (listened[0] && listened[1] && listened[2] && listened[3])
    {
        send_turtles_cmd();
    }
}

void callback_turtle2_cmd(geometry_msgs::Twist msg)
{
    mymsg.turtle2.linear = msg.linear;
    mymsg.turtle2.angular = msg.angular;
    listened[1] = true;
    if (listened[0] && listened[1] && listened[2] && listened[3])
    {
        send_turtles_cmd();
    }
}

void callback_turtle3_cmd(geometry_msgs::Twist msg)
{
    mymsg.turtle3.linear = msg.linear;
    mymsg.turtle3.angular = msg.angular;
    listened[2] = true;
    if (listened[0] && listened[1] && listened[2] && listened[3])
    {
        send_turtles_cmd();
    }
}

void callback_turtle4_cmd(geometry_msgs::Twist msg)
{
    mymsg.turtle4.linear = msg.linear;
    mymsg.turtle4.angular = msg.angular;
    listened[3] = true;
    if (listened[0] && listened[1] && listened[2] && listened[3])
    {
        send_turtles_cmd();
    }
}

int main(int argc, char **argv)
{

    ros::init(argc, argv,"turtles_spawner");
    ros::NodeHandle n;
    
    ros::Subscriber sub_turtle1_cmd = n.subscribe("/turtle1_cmd",10,callback_turtle1_cmd);
    ros::Subscriber sub_turtle2_cmd = n.subscribe("/turtle1_cmd",10,callback_turtle2_cmd);
    ros::Subscriber sub_turtle3_cmd = n.subscribe("/turtle1_cmd",10,callback_turtle3_cmd);
    ros::Subscriber sub_turtle4_cmd = n.subscribe("/turtle1_cmd",10,callback_turtle4_cmd);

    // pub_turtles_cmd = n.advertise("/turtles_cmd",1,)
    
    ros::spin();
}