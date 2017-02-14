%
% script to make .mex files
%

% don't run on Linux
if isunix
    fprintf('\n>>>\n');
    fprintf('>>> Use makemex-octave shell script to compile mex functions in Linux\n');
    fprintf('>>>\n\n');
    return;
end

% check if we are running on MATLAB
if ~(exist('OCTAVE_VERSION')==5)

    fprintf('\n>>>\n');
    fprintf('>>> Compiling mex functions for MATLAB on Windows\n');
    fprintf('>>>\n\n');

    mex -O polyboolmex.cpp clipper.cpp
    mex -O iscwmex.c
    mex -O isinpolygon.c
    mex -O polyarea.c
    mex -O polycentr.c
    
else % we are on Octave with gcc

    fprintf('\n>>>\n');
    fprintf('>>> Compiling mex functions for Octave on Windows\n');
    fprintf('>>>\n\n');

    setenv('CFLAGS', '-O3 -fomit-frame-pointer -march=native -mtune=native');
    setenv('CXXFLAGS', '-O3 -fomit-frame-pointer -march=native -mtune=native');

    mex polyboolmex.cpp clipper.cpp
    mex iscwmex.c
    mex isinpolygon.c
    mex polyarea.c
    mex polycentr.c
    system('del *.o');

end


