/**
 * @file      motion_planning.cpp
 * @brief     Main motion planning node
 * @author    Alejandro Bordallo <alex.bordallo@ed.ac.uk>
 * @date      2015-06-08
 * @copyright (MIT) 2015 Edinferno
 */


#ifndef MONITORED_NAV_WRAPPER_HPP
#define MONITORED_NAV_WRAPPER_HPP

#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include <navigation/StartHumanApproach.h>
#include <navigation/NavigateToWaypoint.h>

#include <geometry_msgs/PoseStamped.h>

#include <strands_navigation_msgs/MonitoredNavigationAction.h>
#include <strands_navigation_msgs/MonitoredNavigationActionGoal.h>
#include <strands_navigation_msgs/MonitoredNavigationActionFeedback.h>

#include <topological_navigation/GotoNodeAction.h>
#include <topological_navigation/GotoNodeGoal.h>

// typedef actionlib::SimpleActionClient<strands_navigation_msgs::MonitoredNavigationAction>
// Client;

class MonitoredNavWrapper {
 public:
  MonitoredNavWrapper(ros::NodeHandle* nh);
  ~MonitoredNavWrapper();

  void loadParams();
  void init();
  void rosSetup();

  void personPoseCB(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void feedbackCB(const strands_navigation_msgs::
                  MonitoredNavigationActionFeedback::ConstPtr& msg);
  bool navigateToWaypoint(
    navigation::NavigateToWaypoint::Request& req,
    navigation::NavigateToWaypoint::Response& res);
  bool startHumanApproach(
    navigation::StartHumanApproach::Request& req,
    navigation::StartHumanApproach::Response& res);

 private:
  // Flags

  // Constants
  float personal_space_;
  float approach_timeout_;
  float node_nav_timeout_;

  // Variables
  std::string waypoint;
  geometry_msgs::PoseStamped person_pose_;
  geometry_msgs::PoseStamped safe_pose_;

  // ROS
  ros::NodeHandle* nh_;
  ros::ServiceServer navigate_to_waypoint_;
  ros::ServiceServer start_human_approach_;
  ros::Subscriber person_pose_sub_;
  ros::Subscriber monitored_feedback_sub_;
  actionlib::SimpleActionClient<topological_navigation::GotoNodeAction>
  topological_nav_ac;
  actionlib::SimpleActionClient<strands_navigation_msgs::MonitoredNavigationAction>
  monitored_nav_ac;

};

#endif  /* MONITORED_NAV_WRAPPER_HPP */
