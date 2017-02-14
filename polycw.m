function po = polycw(pin, ori);
%function po = polycw(pin, ori);
%
% polycw :  change all polygons with CCW orientation to 
%           polygons with CW orientation or vice versa.
%
% INPUT
% pin : Nx2 matrix of polygon vertices or cell array of polygons.
% ori : (Optional) a string describing the orientation of the output
%       polygons. Either 'cw' or 'ccw'. Default is 'cw'.
%
% OUTPUT
% po :  output polygons.
%

% Initial version, Ulf Griesmann, NIST, November 2012

    % check arguments
    if nargin < 2, ori = 'cw'; end
    if ~iscell(pin), pin = {pin}; end

    % determine orientation of input
    switch lower(ori)
        
      case 'cw'
          reor = iscw(pin);
          
      case 'ccw'
          reor = ~iscw(pin);
          
      otherwise
          error('unknown polygon orientation argument.');
    end

    % re-orient the ones with CCW orientation
    po = pin;
    for k = find(reor == 0)
        % po{k} = po{k}(end:-1:1,:); % Sigh, this works only in Octave ...
        P = po{k};
        P = P(end:-1:1,:);
        po{k} = P;
    end
    
    % return result
    if length(po) == 1
        po = po{1};
    end

end
