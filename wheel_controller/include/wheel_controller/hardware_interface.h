#pragma once
#include <ros/ros.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <joint_limits_interface/joint_limits_interface.h>
#include <joint_limits_interface/joint_limits.h>
#include <joint_limits_interface/joint_limits_urdf.h>
#include <joint_limits_interface/joint_limits_rosparam.h>
#include "mobile_base_msgs/msg/MotorCmds.h"
#include "mobile_base_msgs/msg/MotorStates.h"
#include "wheel_controller/joint_data.h"


namespace hardware_interface
{
  
class SwerveDriveInterface : public hardware_interface::RobotHW
{
public:
  SwerveDriveInterface(ros::NodeHandle& nodeHandle, std::vector<JointData*>& joint_data, float sample_rate, std::string control_mode);
  ~SwerveDriveInterface();
  bool read();
  void writeVelocity(ros::Duration period);
  float sample_rate;

private:
  template <typename JointInterface>
  void initJointInterface(JointInterface& jnt_interface);
  void checkCmdLimit(int cmd_indx);
  void motorStatesCallback(const mobile_base_msgs::msg::MotorStates::SharedPtr msg);
  hardware_interface::JointStateInterface jnt_state_interface;
  hardware_interface::PositionJointInterface jnt_pos_interface;
  hardware_interface::VelocityJointInterface jnt_vel_interface;
  joint_limits_interface::PositionJointSaturationInterface jnt_pos_limits_interface;
  joint_limits_interface::VelocityJointSaturationInterface jnt_vel_limits_interface;
  joint_limits_interface::PositionJointSaturationHandle* pos_limit_handle;
  joint_limits_interface::VelocityJointSaturationHandle* vel_limit_handle;
 
  std::vector<JointData*> jd_ptr;
  int control_mode;
  ros::NodeHandle& nodeHandle_;

  ros::Publisher motor_cmds_pub_;
  ros::Subscriber motor_states_sub_;
  bool received_states;
};

} // namespace name