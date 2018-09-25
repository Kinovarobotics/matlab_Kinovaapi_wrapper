% COMPILEMEXINTERFACE
%  Copyright 2017 The MathWorks, Inc.



% Compile Mex file
ipath1 = '-IC:\Users\mblouin\Desktop\JACO2Communicator\JACO2SDK';
ipath2 = '-IC:\Users\mblouin\Desktop\JACO2Communicator\Source';
lpath = '-LC:\Users\mblouin\Desktop\JACO2Communicator\JACO2SDK';
mexInterfaceFile = 'C:\Users\mblouin\Desktop\JACO2Communicator\JACO2SDK\JacoMexInterface.cpp';
wrapperFile = 'C:\Users\mblouin\Desktop\JACO2Communicator\JACO2SDK\JacoSDKWrapper.cpp';
cd 'C:\Users\mblouin\Desktop\JACO2Communicator\Source';
mex('-v',ipath1,ipath2,lpath,mexInterfaceFile,wrapperFile); 
