
/*
#include <Windows.h>
#include "CommunicationLayerWindows.h"
#include "CommandLayer.h"
#include <conio.h>
#include "KinovaTypes.h"
#include <iostream>
*/

//using namespace std;
// Copyright 2017 The MathWorks, Inc.



#include "mex.h"
#include "JacoSDKWrapper.h"


/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    /* Inputs */
    int functionIndex;              /* input scalar */
    double *inJntPos;
    double *inJntVel;
    double *inJntTorque;
    double *inFingerPos;
    
    //size_t ncols;                   /* size of matrix */
    
    
    double *outPos;              /* output matrix */
    double *outVel;              /* output matrix */
    double *outTorque;           /* output matrix */
    double *outTemp;             /* output matrix */
    double *outPose;             /* output matrix */
    double *outWrench;           /* output matrix */


    /* check for proper number of arguments */
    if(nrhs!=5) { // (fcnIndex, jntPos, jntVel, jntTorque, fingerPos)
        mexErrMsgIdAndTxt("MyToolbox:nrhs","5 inputs required.");
    }
    if(nlhs!=7) { //[status, pos, vel, torque, temp, ee_pose,ee_wrench]
        mexErrMsgIdAndTxt("MyToolbox:nlhs","7 outputs required.");
    }
    
    /* Check first input: make sure the first input argument is scalar */
    if( !mxIsDouble(prhs[0]) || 
        mxIsComplex(prhs[0]) ||
        mxGetNumberOfElements(prhs[0])!=1 ) {
        mexErrMsgIdAndTxt("MyToolbox:notScalar","Input multiplier must be a scalar.");
    }
    
    /* Check second to fifth (inJntPos->inFingerPos) inputs are real */
    for(int i = 1; i <= 4;i++)
    {
        if( !mxIsDouble(prhs[i]) || mxIsComplex(prhs[i])) 
        {
            mexErrMsgIdAndTxt("MyToolbox:notDouble",
                "Input matrix must be type double.");
        }
    }
    
    /* Second Input: jntPos: Check that number of rows and cols */
    if(mxGetM(prhs[1]) != NUM_JOINTS || mxGetN(prhs[1]) != 1) {
        mexErrMsgIdAndTxt("MyToolbox:notColVector",
                      "Joint Pos Input must be a Col vector of num joint elements.");
    }
    /* Third Input: jntVel: Check that number of rows and cols */
    if(mxGetM(prhs[2]) != NUM_JOINTS || mxGetN(prhs[2]) != 1) {
        mexErrMsgIdAndTxt("MyToolbox:notColVector",
                      "Joint Vel Input must be a Col vector of num joint elements.");
    }
    /* Fourth Input: jntTorque: Check that number of rows and cols */
    if(mxGetM(prhs[3]) != NUM_JOINTS || mxGetN(prhs[3]) != 1) {
        mexErrMsgIdAndTxt("MyToolbox:notColVector",
                      "Joint Torque Input must be a Col vector of num joint elements.");
    }
    /* Fifth Input: fingerPos: Check that number of rows and cols */
    if(mxGetM(prhs[4]) != NUM_FINGERS || mxGetN(prhs[4]) != 1) {
        mexErrMsgIdAndTxt("MyToolbox:notColVector",
                      "Finger Pos Input must be a Col vector of num finger elements.");
    }    

   
    /* Read input data */
    /* get scalar to function index */
    functionIndex = (int) round(mxGetScalar(prhs[0]));
    
    /* create pointers to the real data in the input matrices  */
    inJntPos = mxGetPr(prhs[1]);   
    inJntVel = mxGetPr(prhs[2]);
    inJntTorque = mxGetPr(prhs[3]);
    inFingerPos = mxGetPr(prhs[4]);
    

    /* OUTPUTS */
    /* create the output value for init status */
    plhs[0] = mxCreateLogicalMatrix(1, 1);
    *mxGetLogicals(plhs[0]) = 0;
    
    /* create the output matrix for joint positions */
    plhs[1] = mxCreateDoubleMatrix(NUM_JOINTS+NUM_FINGERS,1,mxREAL);
    outPos = mxGetPr(plhs[1]);
    
    /* create the output matrix for joints velocitie */
    plhs[2] = mxCreateDoubleMatrix(NUM_JOINTS+NUM_FINGERS,1,mxREAL);
    outVel = mxGetPr(plhs[2]);
    
    /* create the output matrix for joints torque */
    plhs[3] = mxCreateDoubleMatrix(NUM_JOINTS+NUM_FINGERS,1,mxREAL);
    outTorque = mxGetPr(plhs[3]);
    
    /* create the output matrix for joints temperature */
    plhs[4] = mxCreateDoubleMatrix(NUM_JOINTS+NUM_FINGERS,1,mxREAL);
    outTemp = mxGetPr(plhs[4]);
    
    /* create the output matrix for end effector pose */
    plhs[5] = mxCreateDoubleMatrix(6,1,mxREAL);
    outPose = mxGetPr(plhs[5]);
    
    /* create the output matrix for end effector wrench */
    plhs[6] = mxCreateDoubleMatrix(6,1,mxREAL);
    outWrench = mxGetPr(plhs[6]);
    

    switch(functionIndex)
    {
        case FunctionIndices::kOpenLibrary:
            *mxGetLogicals(plhs[0]) = openKinovaLibrary();
            break;
        case FunctionIndices::kCloseLibrary:
            *mxGetLogicals(plhs[0]) = closeKinovaLibrary();
            break;
        case FunctionIndices::kGetJointsPosition:
            *mxGetLogicals(plhs[0]) = getJointsPosition(outPos);
            break;   
        case FunctionIndices::kGetJointsVelocity:
            *mxGetLogicals(plhs[0]) = getJointsVelocity(outVel);
            break; 
        case FunctionIndices::kGetJointsTorque:
            *mxGetLogicals(plhs[0]) = getJointsTorque(outTorque);
            break;
        case FunctionIndices::kGetJointsTemperature:
            *mxGetLogicals(plhs[0]) = getJointsTemperature(outTemp);
            break; 
        case FunctionIndices::kGetEndEffectorPose:
            *mxGetLogicals(plhs[0]) = getEndEffectorPose(outPose);
            break;   
        case FunctionIndices::kGetEndEffectorWrench:
            *mxGetLogicals(plhs[0]) = getEndEffectorWrench(outWrench);
            break;
        case FunctionIndices::kMoveToHomePosition:
            *mxGetLogicals(plhs[0]) = moveToHomePosition();
            break;
        case FunctionIndices::kSetPositionControlMode:
            *mxGetLogicals(plhs[0]) = setPositionControlMode();
            break;
        case FunctionIndices::kSetDirectTorqueControlMode:
            *mxGetLogicals(plhs[0]) = setDirectTorqueControlMode();
            break; 
        case FunctionIndices::kRunGravityCalibration:
            *mxGetLogicals(plhs[0]) = runGravityCalibration();
            break;  
        case FunctionIndices::kInitializeFingers:
            *mxGetLogicals(plhs[0]) = initializeFingers();
            break;
        case FunctionIndices::kSendJointPositions:
            *mxGetLogicals(plhs[0]) = sendJointPositions(inJntPos);
            break;
        case FunctionIndices::kSendJointAndFingerPositions:
            *mxGetLogicals(plhs[0]) = sendJointAndFingerPositions(inJntPos,inFingerPos);
            break;            
        case FunctionIndices::kSendJointVelocities:
            *mxGetLogicals(plhs[0]) = sendJointVelocities(inJntVel);
            break;
        case FunctionIndices::kSendJointTorques:
            *mxGetLogicals(plhs[0]) = sendJointTorques(inJntTorque);
            break;
        case FunctionIndices::kSendFingerPositions:
            *mxGetLogicals(plhs[0]) = sendFingerPositions(inFingerPos);
            break;     
    }

}
