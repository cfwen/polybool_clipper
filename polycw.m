function po = polycw(pin);
%function po = polycw(pin);
%
% polycw :  change all polygons with CCW orientation to 
%           polygons with CW orientation.
%
% pin : Nx2 matrix of polygon vertices or cell array of polygons.
% po :  output polygons.
%

% Initial version, Ulf Griesmann, NIST, November 2012

% check arguments
if ~iscell(pin), pin = {pin}; end

% determine orientation
cw = iscw(pin);

% re-orient the ones with CCW orientation
po = pin;
for k=find(cw==0)
   % po{k} = po{k}(end:-1:1,:); % Sigh, this works only in Octave ...
   T = po{k};
   T = T(end:-1:1,:);
   po{k} = T;
end

% return result
if length(po) == 1
   po = po{1};
end

return
