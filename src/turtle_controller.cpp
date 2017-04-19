#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/Twist.h>

double goal_position = 1.0;
double forward_control = 0.0;
double k_P = 1.0;

void poseCallback(const turtlesim::Pose::ConstPtr& pose_msg) {
  double x_error = goal_position - pose_msg->x;

  forward_control = k_P * x_error;
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "turtle_controller");
  ros::NodeHandle nh;

  ros::Publisher control_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
  ros::Subscriber pose_sub = nh.subscribe("/turtle1/pose", 10, &poseCallback);

  ros::Rate rate(100.0);

  while (ros::ok()) {
    ros::spinOnce();

    geometry_msgs::Twist controls;
    controls.linear.x = forward_control;
    controls.angular.z = 0.0;

    control_pub.publish(controls);

    rate.sleep();
  }

  return 0;
}
