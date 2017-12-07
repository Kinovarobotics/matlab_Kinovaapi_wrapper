classdef JacoCommandModes < int32
    %JacoCommandModes Enumeration that provides command mode number when
    %  System object is designed using Simulink
    %  Copyright 2017 The MathWorks, Inc.

    
    enumeration
        IDLE (0)
        DIRECT_INPUT (1)
        SEND_POSITION_CMD (2)
        SEND_TORQUE_CMD (3)
        SEND_FINGER_CMD (4)
    end
    
    methods
    end
    
end

