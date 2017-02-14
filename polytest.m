%
% tests the polybool function
%

clear all

pa = [0,1; -1,-1; 1,-1; 0,1];           % triangle with tip pointing north
pb = [0,-1.5;  1,0.5; -1,0.5; 0,-1.5];  % triangle with tip pointing south

disp('AND');
pc_and = polybool(pa, pb, 'and');
disp('OR');
pc_or = polybool(pa, pb, 'or');
disp('NOTB');
pc_notb = polybool(pa, pb, 'notb');
disp('XOR');
pc_xor = polybool(pa, pb, 'xor');

