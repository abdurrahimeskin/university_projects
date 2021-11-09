%read wave file
wfile=('exampleSignal.csv');
M=csvread(wfile, 1, 0);


[pks0,locs]=findpeaks(M, 10, 'MinPeakProminence', 1.10)
a0=numel(pks0);

%LOWPASS FILTER IMPLEMENTATION
%conform the lowpass with different limit frequencies and kept number of 
%peaks according to changing filter frequencies


lpFilt1 = designfilt('lowpassiir','FilterOrder',8, ...
         'PassbandFrequency',1e3,'PassbandRipple',0.2, ...
         'SampleRate',200e3);

dataIn = M;
dataOut = filter(lpFilt1,dataIn);

[pks1,locs]=findpeaks(dataOut, 10, 'MinPeakProminence', 1.10);

a1 = numel(pks1);


lpFilt2 = designfilt('lowpassiir','FilterOrder',8, ...
         'PassbandFrequency',2e3,'PassbandRipple',0.2, ...
         'SampleRate',200e3);

dataIn = M;
dataOut = filter(lpFilt2,dataIn);
[pks2,locs]=findpeaks(dataOut, 10, 'MinPeakProminence', 1.10);

b = numel(pks2);




lpFilt3 = designfilt('lowpassiir','FilterOrder',8, ...
         'PassbandFrequency',3e3,'PassbandRipple',0.2, ...
         'SampleRate',200e3);

dataIn = M;
dataOut = filter(lpFilt3,dataIn);
[pks3,locs]=findpeaks(dataOut, 10, 'MinPeakProminence', 1.10);

c = numel(pks3);



lpFilt4 = designfilt('lowpassiir','FilterOrder',8, ...
         'PassbandFrequency',4e3,'PassbandRipple',0.2, ...
         'SampleRate',200e3);

dataIn = M;
dataOut = filter(lpFilt4,dataIn);
[pks4,locs]=findpeaks(dataOut, 10, 'MinPeakProminence', 1.10);

d = numel(pks4);

x = [a0 a1  b  c  d] ;
y = [0 1000 2000 3000 4000];

figure;
plot(y,x);
title('Plot Number Of Peaks Versus Changing Cutoff Frequencies');
ylabel('Number Of Peaks');
xlabel('Cutoff Frequencies');



%MOVING AVERAGE FILTER IMPLEMANTATION
%I have created moving average filter to show chancing N number I used for 
%loop and I plotted number of peaks versus changing N in the figure



a = 1;
dataIn = M;
pkse = 1:29 ;
counter1 = 1:29;
for n  = 2:30
    h = ones(1,n)/ n;
    yma = filter(h, a, dataIn);
    [pks6,locs]=findpeaks(yma, 10, 'MinPeakProminence', 1.10);
    pkse(n-1) = numel(pks6);
end

for n = 2:30
    counter(n-1)= n;
end

figure;
plot (counter,pkse);
title('Peaks vs Changing Number of Samples Taken into Average')
ylabel('Number Of Peaks')
xlabel('Number Of Samples Taken into Average (N)')



