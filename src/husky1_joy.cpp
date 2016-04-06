#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>
#include <iostream>
#include <sensor_msgs/Joy.h>

using namespace std;
class TeleopJoy{
public:
TeleopJoy();
private:
void callBack(const sensor_msgs::Joy::ConstPtr& joy);
ros::NodeHandle n;
ros::Publisher pub;
ros::Subscriber sub;
int i_velLinear, i_velAngular;
};
TeleopJoy::TeleopJoy()
{
n.param("axis_linear",i_velLinear,i_velLinear);
n.param("axis_angular",i_velAngular,i_velAngular);
pub = n.advertise<geometry_msgs::Twist>("husky_velocity_controller/cmd_vel", 100);
sub = n.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopJoy::callBack,
this);
}
void TeleopJoy::callBack(const sensor_msgs::Joy::ConstPtr& joy)
{
geometry_msgs::Twist twist;
twist.angular.z = joy->axes[i_velAngular];
twist.linear.x = joy->axes[i_velLinear];
pub.publish(twist);
}

int main(int argc, char **argv) {
ros::init(argc, argv, "joy_husky_commands");
TeleopJoy teleop_husky;
ros::spin();
}
