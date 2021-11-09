mikeFile = 'mike.wav';
streetFile = 'street.wav';

%y1 for mike, y2 for street, y3 for combined
[y1,Fs1] = audioread(mikeFile);
[y2,Fs2] = audioread(streetFile);
%combined sound of Mike and street
y3 = y1 + y2; 

%Lengths of these three sounds
L1 = size(y1,1);
L2 = size(y2,1);
L = size(y3,1); 

%Half length
f = Fs1*(0:(L/2))/L; 
%Full length
f2 = Fs1*(0:L-1)/L;  
f3 = Fs1*(1:L)/L;

%fft of mike
fftMike = fft(y1,L);
p1_full = (fftMike./L); 
p1_half = p1_full(1:L/2+1);
p1_half(2:end-1) = 2*p1_half(2:end-1); 

%fft of street sound
fftStreet = fft(y2,L);
p2_full = (fftStreet./L);
p2_half = p2_full(1:L/2+1);
p2_half(2:end-1) = 2*p2_half(2:end-1); 

% fft of combined sounds
fftCombined = fft(y3,L);
p3_full = fftCombined./L;
p3_half = p3_full(1:L/2+1);
p3_half(2:end-1) = 2*p3_half(2:end-1); 

%Frequency domain representations of mike,street and combined sounds
figure(1)
subplot(3,1,1);
plot(f2,abs(p1_full));
title('Frequency Domain Representation Of Mike')
subplot(3,1,2);
plot(f2,abs(p2_full));
title('Frequency Domain Representation Of Street')
subplot(3,1,3);
plot(f2,abs(p3_full));
title('Frequency Domain Representation Of Combined Sounds')


%Time domain representations of Mike Street and Combined sounds

%Time domain representation of Mike
figure(2)
subplot(3,1,1);
t1=[1:L1]./Fs1; 
plot(t1,y1);
title('Time Domain Representation Of Mike')
subplot(3,1,2);
%Time domain representation of Street
t2=[1:L2]./Fs2; 
plot(t2,y2);
title('Time Domain Representation Of Street')
subplot(3,1,3);
%Time domain representations of Combiend sounds
t3=[1:L]./Fs1; 
plot(t3,y3);
title('Time Domain Representation Of Combined Sounds')


%calculations for filtering

p4_half = p3_half; %(half)
p4_full = p3_full; %(full) this will be filtered

%Human voice is between 300-3000 Hz. frequency

%I am filtering symmetrically
for i = 1:L
    if ~(f3(1,i) > 300 && f3(1,i) < 3000)
        if ~(f3(1,i) < Fs1-300 && f3(1,i) > Fs1-3000 )
            p4_full(i) = 0;
        end
    end  
end

%Frequency Domain representation of Mike and filtered combined sounds:

figure(3)
%Frequency Domain representation of Mike
subplot(2,1,1);
plot(f2,abs(p1_full));
title('Frequency Domain Representation Of Mike')

%Frequency Domain representation of filtered combined sounds
subplot(2,1,2);
plot(f3,abs(p4_full));
title('Frequency Domain Representations Of Filtered Combined Sounds')



%Time domain representations of Mike and filtered combined sounds:
p4_full = p4_full*L;
TimeDomFilt = ifft(p4_full,L);
p1_full = p1_full*L;
TimeDomMike = ifft(p1_full,L);
figure(4)
%Time domain representation Of Mike
subplot(2,1,1);
plot(real(TimeDomMike));
title('Time Domain Representation Of Mike')
%Time domain representation of filtered combined sounds
subplot(2,1,2);
plot(real(TimeDomFilt));
title('Time Domain Representation Of Filtered Combined Sounds')

%Calculating the SNR value
y1square = y1.^2;
EiIisquare = (real(TimeDomFilt)-y1).^2;
up = sum(y1square);
down = sum(EiIisquare);
SNR = 10*log(up/down)/log(10)
disp(SNR);
