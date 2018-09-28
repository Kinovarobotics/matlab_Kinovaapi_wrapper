close all; clc;
Rad2Deg = 180/pi;

% We load the matrix where de joint position are stored
JntPos = load ('JntPos.mat');

% We assign each row to a joint
Q1 = Rad2Deg.*JntPos.ans(2,:);
Q2 = Rad2Deg.*JntPos.ans(3,:);
Q3 = Rad2Deg.*JntPos.ans(4,:);
Q4 = Rad2Deg.*JntPos.ans(5,:);
Q5 = Rad2Deg.*JntPos.ans(6,:);
Q6 = Rad2Deg.*JntPos.ans(7,:);



for index = 1:length(JntPos.ans(1,:))
   % We call the function that takes angular positions and return
   % cartesian position of each articulation. 
   coordinates = fowardKinematicsJaco6DOFS(Q1(index), Q2(index), Q3(index), Q4(index), Q5(index), Q6(index)); 
   
   % We store the position of the end effector in EndEffector
   EndEffector(index,:)=coordinates(:,5);
   
   % We create the figure where the robot will be shown
   figure(1)
   
   % We plot the position of each articulation
   plot3(coordinates(1,:),coordinates(2,:),coordinates(3,:))
   
   hold on
   
   % We set the display settings
   view(150,40) 
   set(gcf, 'Units', 'Normalized', 'OuterPosition', [0 0 1 1]);
   axis equal
   grid on
   set(findall(gca, 'Type', 'Line'),'LineWidth',5);
   xlabel('X')
   ylabel('Y')
   xlim([-1 1])
   ylim([-1 1])
   zlim([0 1.3])
   
   % We mark the base with a red *
   plot3(coordinates(1,1),coordinates(2,1),coordinates(3,1), '-r*')
   
   % We show the trajectory for the whole simulation
   plot3(EndEffector(1:index,1),EndEffector(1:index,2),EndEffector(1:index,3))
   hold off

end