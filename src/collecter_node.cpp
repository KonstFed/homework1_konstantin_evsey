#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <homework1_konstantin_evsey/TwistArray.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <math.h>

const char* SERVICE_KILL_TURTLE = "/kill";
const char* SERVICE_SPAWN_TURTLE = "/spawn";

homework1_konstantin_evsey::TwistArray msg_cmd;
geometry_msgs::PoseArray msg_poses;

bool listened[] = {false,false,false,false};

ros::Publisher pub_turtles_cmd;

void send_turtles_cmd()
{
    ROS_INFO("send_turtles_cmd is called.");
    pub_turtles_cmd.publish(msg_cmd);
    listened[0] = false;
    listened[1] = false;
    listened[2] = false;
    listened[3] = false;
}

template<int turtleNum>
void callback_turtle_cmd(geometry_msgs::Twist msg)
{
    switch(turtleNum)
    {
        case 1:
            msg_cmd.turtle1.linear = msg.linear;
            msg_cmd.turtle1.angular = msg.angular;
            break;
        case 2:
            msg_cmd.turtle2.linear = msg.linear;
            msg_cmd.turtle2.angular = msg.angular;
            break;
        case 3:
            msg_cmd.turtle3.linear = msg.linear;
            msg_cmd.turtle3.angular = msg.angular;
            break;
        case 4:
            msg_cmd.turtle4.linear = msg.linear;
            msg_cmd.turtle4.angular = msg.angular;
            break;
    }
    listened[turtleNum-1] = true;
}

template<int turtleNum>
void callback_turtles_pose(turtlesim::Pose msg)
{
    // TODO: understand transition between turtlesim::Pose to geometry_msgs::Pose
    
    // switch(turtleNum)
    //     {
    //         case 1:
    //             msg_poses.poses.position.x = msg.x;
    //             msg_poses.poses.position.y = msg.y;
                

    //             break;
    //         case 2:
    //             msg_cmd.turtle2.linear = msg.linear;
    //             msg_cmd.turtle2.angular = msg.angular;
    //             break;
    //         case 3:
    //             msg_cmd.turtle3.linear = msg.linear;
    //             msg_cmd.turtle3.angular = msg.angular;
    //             break;
    //         case 4:
    //             msg_cmd.turtle4.linear = msg.linear;
    //             msg_cmd.turtle4.angular = msg.angular;
    //             break;
    //     }
}

int main(int argc, char **argv)
{

    ros::init(argc, argv,"turtles_spawner");
    ros::NodeHandle n;
    
    ros::Subscriber sub_turtle1_cmd = n.subscribe("/turtle1_cmd",10,callback_turtle_cmd<1>);
    ros::Subscriber sub_turtle2_cmd = n.subscribe("/turtle2_cmd",10,callback_turtle_cmd<2>);
    ros::Subscriber sub_turtle3_cmd = n.subscribe("/turtle3_cmd",10,callback_turtle_cmd<3>);
    ros::Subscriber sub_turtle4_cmd = n.subscribe("/turtle4_cmd",10,callback_turtle_cmd<4>);

    // ros::Subscriber sub_turtle1_pose = n.subscribe("/turtle2/pose",10,callback_turtle1_cmd);
    // ros::Subscriber sub_turtle2_pose = n.subscribe("/turtle3/pose",10,callback_turtle2_cmd);
    // ros::Subscriber sub_turtle3_pose = n.subscribe("/turtle4/pose",10,callback_turtle3_cmd);
    // ros::Subscriber sub_turtle4_pose = n.subscribe("/turtle5/pose",10,callback_turtle4_cmd);

    pub_turtles_cmd = n.advertise<homework1_konstantin_evsey::TwistArray>("/turtles_cmd",1);


    ros::Rate rate(1);
    while (ros::ok())
    {
        if (listened[0] && listened[1] && listened[2] && listened[3])
        {
            send_turtles_cmd();
        }
        ros::spinOnce();
        rate.sleep();
    }
}