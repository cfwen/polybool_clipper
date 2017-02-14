function inp = isinpolygon(polygon, xy)
%function inp = isinpolygon(polygon, xy)
%
% isinpolygon :  checks if any of a set of points
%                is inside a polygon.
%
% polygon :  Mx2 array of polygon vertices.
% xy :       Mx2 array of N points, one point per row.
% inp :      a logical array of length M. inp(k) == 1 if 
%            xy(k,:) is inside the polygon.

% Initial version, Ulf Griesmann, NIST, June 2013
%
