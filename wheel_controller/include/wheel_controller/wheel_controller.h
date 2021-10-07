#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <controller_manager/controller_manager.h>

#include "wheel_controller/hardware_interface.h"
#include "wheel_controller/joint_data.h"


#define DOF 2

enum WheelState {Idle, Busy, Error, Disable};

class WheelController
{
private:
    void jointDataInit(int swerve_id, int wheel_id, double swerve_gear_ratio, double wheel_gear_ratio);
    /* data */
    WheelState wheel_state;
    hardware_interface::SwerveDriveInterface* swerve_drive_interface;
    controller_manager::ControllerManager* wheel_cm;

    ros::NodeHandle& nodeHandle_;

    ros::Subscriber wheel_cmds_sub_;
    ros::Publisher  swerve_joint_pub_;
    ros::Publisher  wheel_joint_pub_;

public:
    WheelController(ros::NodeHandle& nodeHandle);
    ~WheelController();
    void wheelCmdsCallback(const std_msgs::Float64MultiArray::ConstPtr& msg);
    void process(ros::Rate& loop_rate);
    std::vector<JointData*> joint_data;
    float sample_rate;
    std::string control_mode;
};
