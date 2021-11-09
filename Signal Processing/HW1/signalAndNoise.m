%PROBLEM 3

x=linspace(-100,100,2001); %x is vector of real numbers (-100:100)
y1=sin(x); 
y2=sin(50*x);
y3=50*sin(x);
y4=sin(x)+50;
y5=sin(x+50);
y6=50*sin(50*x);
y7=x.*sin(x); 
y8=sin(x)./x;
figure %made a figure and subplots on it
subplot(4,2,1); 
plot(x,y1);
subplot(4,2,2); 
plot(x,y2);
subplot(4,2,3); 
plot(x,y3);
subplot(4,2,4); 
plot(x,y4);
subplot(4,2,5); 
plot(x,y5);
subplot(4,2,6); 
plot(x,y6);
subplot(4,2,7); 
plot(x,y7);
subplot(4,2,8); 
plot(x,y8);

%PROBLEM 4

x=linspace(-20,20,401); %Let x is vector of real numbers (-20:20)
y1 = sin(x); 
y2=sin(50*x);
y3=50*sin(x); 
y4= sin(x)+50;
y5= sin(x+50); 
y6= 50*sin(50*x);
y7= x.*sin(x); 
y8=sin(x)./x;
y9= y1+y2+y3+y4+y5+y6+y7+y8;
figure %made a figure and subplots on it
subplot(5,2,1); 
plot(x,y1);
subplot(5,2,2); 
plot(x,y2);
subplot(5,2,3); 
plot(x,y3);
subplot(5,2,4); 
plot(x,y4);
subplot(5,2,5); 
plot(x,y5);
subplot(5,2,6); 
plot(x,y6);
subplot(5,2,7); 
plot(x,y7);
subplot(5,2,8); 
plot(x,y8);
subplot(5,2,9); 
plot(x,y9);

%PROBLEM 5

x=linspace(-20,20,41); %unit variance Gaussian distributed random number in (-,)
z=randn([1 41]); %Generate 41
                 %random numbers following Gaussian distributed random numbers
y10= z; 
y11= z+x ;
y12= z+sin(x); 
y13= z.*sin(x);
y14=x.*sin(z); 
y15= sin(x+z);
y16= z.*sin(50*x); 
y17=sin(x+50*z);
y18=sin(x)./z; 
y19= y11+y12+y13+y14+y15+y16+y17+y18;
figure %made a figure and subplots on it
subplot(5,2,1); 
plot(x,y10)
subplot(5,2,2); 
plot(x,y11)
subplot(5,2,3); 
plot(x,y12)
subplot(5,2,4); 
plot(x,y13)
subplot(5,2,5); 
plot(x,y14)
subplot(5,2,6); 
plot(x,y15)
subplot(5,2,7); 
plot(x,y16)
subplot(5,2,8); 
plot(x,y17)
subplot(5,2,9); 
plot(x,y18)
subplot(5,2,10); 
plot(x,y19)

%PROBLEM 6

z=rand([1 41]); %rand generates uniformly distributed random number in [0,1]
%Generated 41 random numbers following
%uniformly distributed random numbers.

y20= z; 
y21 = z+x ;
y22= z+sin(x); 
y23= z.*sin(x);
y24=x.*sin(z); 
y25= sin(x+z);
y26= z.*sin(50*x); 
y27=sin(x+50*z);
y28=sin(x)./z; 
y29= y21+y22+y23+y24+y25+y26+y27+y28;
figure %made a figure and subplots on it
subplot(5,2,1);plot(x,y20)
subplot(5,2,2);plot(x,y21)
subplot(5,2,3);plot(x,y22)
subplot(5,2,4);plot(x,y23)
subplot(5,2,5);plot(x,y24)
subplot(5,2,6);plot(x,y25)
subplot(5,2,7);plot(x,y26)
subplot(5,2,8);plot(x,y27)
subplot(5,2,9);plot(x,y28)
subplot(5,2,10);plot(x,y29)

%PROBLEM 7

z=randn([1 10000]); %Starting with z (0,1) Gaussian(Normal) Random variable.
%Generate 10000 random variables with mean 0, variance 1,4,16,256
r1=z*1+0;
r2=z*2+0;
r3=z*4+0;
r4=z*16+0;
figure
subplot(2,2,1);hist(r1)
subplot(2,2,2);hist(r2)
subplot(2,2,3);hist(r3)
subplot(2,2,4);hist(r4)

%PROBLEM 8

%Starting with z (0,1) Gaussian Random variable
%Generate 10000 random variables with mean 10, variance 1
%Generate 10000 random variables with mean 20, variance 4
%Generate 10000 random variables with mean -10, variance 1
%Generate 10000 random variables with mean -20, variance 4
r6=z*1+10;
r7=z*2+20;
r8=z*1-10;
r9=z*2-20;
figure
subplot(2,2,1);hist(r6)
subplot(2,2,2);hist(r7)
subplot(2,2,3);hist(r8)
subplot(2,2,4);hist(r9)


%PROBLEM 9

%Starting with z (0,1) uniformly distributed random variable
z=rand([1 10000]);
%Generate 10000 random variables with mean 0, variance 1
%Generate 10000 random variables with mean 0, variance 4
%Generate 10000 random variables with mean 0, variance 16
%Generate 10000 random variables with mean 0, variance 256
r11=(z-1/2)*2*3^(1/2)*1+0;
r21=(z-1/2)*2*3^(1/2)*2+0;
r31=(z-1/2)*2*3^(1/2)*4+0;
r41=(z-1/2)*2*3^(1/2)*16+0;
figure
subplot(2,2,1);hist(r11)
subplot(2,2,2);hist(r21)
subplot(2,2,3);hist(r31)
subplot(2,2,4);hist(r41)

%PROBLEM 10

%Starting with z (0,1) uniformly distributed random variable
%Generate 10000 random variables with mean 10, variance 1
%Generate 10000 random variables with mean 20, variance 4
%Generate 10000 random variables with mean -10, variance 1
%Generate 10000 random variables with mean -20, variance 4
r61=(z-1/2)*2*3^(1/2)*1+10;
r71=(z-1/2)*2*3^(1/2)*2+20;
r81=(z-1/2)*2*3^(1/2)*1-10;
r91=(z-1/2)*2*3^(1/2)*2-20;
figure
subplot(2,2,1); hist(r61)
subplot(2,2,2); hist(r71)
subplot(2,2,3); hist(r81)
subplot(2,2,4); hist(r91)




















