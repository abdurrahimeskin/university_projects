File = 'mike.wav';
[x, Fs] = audioread(File); 

SNRS = zeros(101,1);

%a values from 0 to 1 and plot SNR of mike.wav and recovered signal
for i=0:100
    
    drop = n_tap(i/100,5,100,x,Fs);
    Top=0;
    last=0;
    for j=1:length(x)
        Top = Top+ x(j)^2;
        last = last + (drop(j)-x(j))^2;
    end
    
    SNRS(i+1)= 10*log(Top/last);      

end

plot(1:101,SNRS);
ylabel('SNR Values');
xlabel('*10^2 a value');
xlim([0 100]);
title('SNR values with changing a value');


figure;

SNRS =zeros(50,1);

%N from 1 to 50 and plot SNR of mike.wav and recovered signal
for i=1:50
    
    drop = n_tap(0.7,i,100,x,Fs);
    Top=0;
    last=0;
    for j=1:length(x)
        Top = Top+ x(j)^2;
        last = last + (drop(j)-x(j))^2;
    end
    
    SNRS(i)= 10*log(Top/last);      

end

plot(1:50,SNRS);
ylabel('SNR Values');
xlabel('N value');
xlim([0 50]);
title('SNR values with changing N value');

figure;
SNRS =zeros(4,1);
%K between 100,200,300,400 miliseconds and plot SNR of mike.wav and recovered signal
for i=1:4
    
    drop = n_tap(0.7,5,100*i,x,Fs);
    Top=0;
    last=0;
    for j=1:length(x)
        Top = Top+ x(j)^2;
        last = last + (drop(j)-x(j))^2;
    end
    
    SNRS(i)= 10*log(Top/last);      

end

plot(1:4,SNRS);
ylabel('SNR Values');
xlabel('K value');
xlim([0 4]);
title('SNR values with changing K value');

%Delay function

function y = n_tap(a,N,K,input,Freq)
Delay = Freq*K/1000;
L=length(input);
y=input;

for i=1:N
    for j=1:L
        if i*Delay+j <= L
            y(j+i*Delay)=y(j+i*Delay) + ((-a)^i)*input(j);
        end
    end
end
    

end