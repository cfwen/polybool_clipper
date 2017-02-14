%
% tests the polybool function
%
pa = [0,1; -1,-1; 1,-1];      % triangle with tip pointing north
pb = [2,2; 0,2; 0,-2; 2,-2];  % square

disp('AND');
pc = polybool(pa, pb, 'and');
