%
% test the inpolygon function
%

P = [1,1; -1,1; -1,-1; 1,-1]; % a square
xy = [ 0,   0; ...     % in
       2,   2; ...     % out
       0,   0.5; ...   % in
       0,   -4; ...    % out
      -0.5,-0.5; ...   % in
       0.5, 0.1];      % in

isinpolygon(P, xy)
