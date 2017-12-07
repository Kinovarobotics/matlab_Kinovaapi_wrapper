#ifndef JACO_SDK_WRAPPER_H_
#define JACO_SDK_WRAPPER_H_

#include <Windows.h>
#include "CommunicationLayerWindows.h"
#include "CommandLayer.h"
#include <conio.h>
#include "KinovaTypes.h"

#include <iostream>


#define NUM_JOINTS  6
#define NUM_FINGERS 3
#define JACO_SDK_WRAPPER_TINY_NUMBER 0.00001

#define JACO_SDK_WRAPPER_PI 3.14159265358979323846f
const float kDeg2rad = JACO_SDK_WRAPPER_PI / 180.0f;
const float kRad2deg = 180.0f/JACO_SDK_WRAPPER_PI;


enum class FunctionIndices
{
    kOpenLibrary = 0,
    kCloseLibrary = 1,
    kGetJointsPosition = 2,
    kGetJointsVelocity = 3,
    kGetJointsTorque = 4,
    kGetJointsTemperature = 5,
    kGetEndEffectorPose = 6,
    kGetEndEffectorWrench = 7,
    kMoveToHomePosition = 8,
    kSetPositionControlMode = 9,
    kSetDirectTorqueControlMode = 10,
    kRunGravityCalibration = 11,
    kInitializeFingers = 12,
    kSendJointPositions = 13,
    kSendJointAndFingerPositions = 14,
    kSendJointVelocities = 15,
    kSendJointTorques = 16,
    kSendFingerPositions = 17,
};

/* Load library */
extern "C" bool openKinovaLibrary();

/* Close library */
extern "C" bool closeKinovaLibrary();

/* Get joints position in rad */ 
extern "C" bool getJointsPosition(double *pos);

/* Get joints velocity in rad/s */ 
extern "C" bool getJointsVelocity(double *vel);

/* Get joints torque in N*m */ 
extern "C" bool getJointsTorque(double *torque);

/* Get actuator temperature in C */ 
extern "C" bool getJointsTemperature(double *temp);

/* Get end effector pose [px py pz ex ey ez] */
/* The orientation is defined by Euler angles (convention XYZ) */
extern "C" bool getEndEffectorPose(double *pose);

/* Get end effector wrench [fx fy fz tx ty tz] */
extern "C" bool getEndEffectorWrench(double *wrench);


/* Send robot to home position */
extern "C" bool moveToHomePosition(void);

/* Set position control mode */
extern "C" bool setPositionControlMode(void);

/* Set torque control mode */
extern "C" bool setDirectTorqueControlMode(void);

/* Do gravity calibration sequence, be sure to have 1.5 meters of free space*/
extern "C" bool runGravityCalibration(void); 
    
/* Initialize gripper */
extern "C" bool initializeFingers(void);

/* Send Joint positions in [rad] */
extern "C" bool sendJointPositions(double *pos);

/* Send joint and finger positions (fingers in [rad]) */
extern "C" bool sendJointAndFingerPositions(double *jpos, double *fpos);

/* Send joint velocities in [rad/s]*/
extern "C" bool sendJointVelocities(double *vel);

/* Send joint torques*/
extern "C" bool sendJointTorques(double *torque);

/* Send finger positions*/
extern "C" bool sendFingerPositions(double *pos);
    
    

#endif
