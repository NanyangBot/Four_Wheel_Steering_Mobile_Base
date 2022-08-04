#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
#include <sensor_msgs/JointState.h>
#include <controller_manager/controller_manager.h>
#include "mobile_base_msgs/msg/WheelDirection.h"
#include "wheel_controller/hardware_interface.h"
#include "wheel_controller/joint_data.h"


#define DOF 2
#define WHEEL_DIAMETER 0.15
#define WHEEL_RADIUS 0.075

enum WheelState {Idle, Busy, Error, Disable};

class WheelController
{
private:
    void jointDataInit(int swerve_id, int wheel_id, double swerve_gear_ratio, double wheel_gear_ratio);
    /* data */
    WheelState wheel_state;
    hardware_interface::SwerveDriveInterface* swerve_drive_interface;
    controller_manager::ControllerManager* wheel_cm;
    double metersToRads(const double &meters);
    double radsTometers(const double &rads);
    ros::NodeHandle& nodeHandle_;

    ros::Subscriber wheel_cmd_sub_;
    ros::Subscriber joint_state_sub_;
    ros::Publisher  wheel_state_pub_;
    ros::Publisher  swerve_joint_pub_;
    ros::Publisher  wheel_joint_pub_;
    std::string wheel_name_;
    bool wheel_reverse_;
    bool sim_;

public:
    WheelController(ros::NodeHandle& nodeHandle);
    ~WheelController();
    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg);
    void wheelCmdCallback(const mobile_base_msgs::msg::WheelDirection::SharedPtr msg);
    void statePublish();
    void process(ros::Rate& loop_rate);
    std::vector<JointData*> joint_data;
    float sample_rate;
    std::string control_mode;
};
