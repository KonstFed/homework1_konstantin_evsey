#include <ros/ros.h>
#include <turtlesim/Kill.h>
#include <turtlesim/Spawn.h>
#include <math.h>

const char* SERVICE_KILL_TURTLE = "/kill";
const char* SERVICE_SPAWN_TURTLE = "/spawn";


void deleteTurtle(ros::NodeHandle n)
{
    ros::ServiceClient client = n.serviceClient<turtlesim::Kill>("/kill");
    turtlesim::Kill srv;
    srv.request.name = "turtle1";
    if (client.call(srv))
    {
        ROS_INFO("Deleted first turtle succesfully");
    }
    else
    {
        ROS_ERROR("Deleted first turtle unsuccesfully. Service turtlesim/Kill is not responding");
    }
}

void spawnTurtle(ros::NodeHandle n, ros::ServiceClient client, int x, int y, float theta, std::string name)
{
    turtlesim::Spawn srv;
    srv.request.name = name;
    srv.request.x = x;
    srv.request.y = y;
    srv.request.theta = theta;

    if (client.call(srv))
    {
        ROS_INFO("Spawned turtle: '%s' successfully.",name.c_str());
    }
    else
    {
        ROS_ERROR("Error while spawning turtle: '%s'.",name.c_str());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv,"turtles_spawner");
    ros::NodeHandle n;
    ros::Duration(0.5).sleep();
    deleteTurtle(n);

    ros::ServiceClient client = n.serviceClient<turtlesim::Spawn>(SERVICE_SPAWN_TURTLE);
    spawnTurtle(n,client, 1, 1, M_PI/2.0, "turtle1");
    spawnTurtle(n,client, 8, 5, M_PI/2.0, "turtle2");
    spawnTurtle(n,client, 9.25, 5, M_PI, "turtle3");
    spawnTurtle(n,client, 9.25, 5, 0.0, "turtle4");
    
}