hfile = 'snap.wav';

[x, Sound] = audioread(hfile);
Ssize = size(x,1);
%fft of only one column (one ear) of audio
y= fft(x(:,1)); 

ifSnap = 0;
if abs(max(y))>40 %40 is proper threshold for sound
    ifSnap = 1;
end

if ifSnap == 0
    disp('snap sound detected');
else
    disp('clap sound detected');
end
