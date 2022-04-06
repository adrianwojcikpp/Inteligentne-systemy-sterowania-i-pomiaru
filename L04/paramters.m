clear all
%%
%Dane do wahadla
Tsym=30;
Ts=0.1;
N=Tsym/Ts;  % Maximum number of time steps
m=0.36; %masa wahadla
l=0.06; %dlugosc wahadla
d=0.03; %odleglosc osi od srodka
c=0.0076; %tarcie wiskotyczne 
J=0.0106; %moment bezwladnosci
g=9.81; %przyspieszenie grawitacyjne

%%
%uklad napedowy
%%rownanie opisujace napiecie do moementu
%%T(s)=Km*V(s)
%Dane ukladu napedowego
U=24; %napiecie wej silnika
P=30; %moc silnika
dp=0.15; %d³ugosc smigla
ne=0.9; %sprawnosc silnika
np=0.85; %sprawnosc smigla
p=1.225; %gestosc powietrza
T=((P^2)*(np^2)*(ne^2)*pi*(dp^2)/2*p)^(1/3);
Km=T/U;

%%
%zadana pozycja
teta=90; %pozycja katowa w stopniach

%macierze stanu
A=[0 1; -m*l*g*d/J -c/J];
B=[0; Km/J];
C=[1 0];

%symulacja
sim('aero_pendulum_state_space');

%%
% plotting/animation of results 
for i=1:N
    X(i)=l*sin(tetasim(i));
    Y(i)=-l*cos(tetasim(i));
    figure(1)
    plot(X(i),Y(i),'.','markersize',65); 
    axis([-0.07 0.07  -0.07 0.07]);
    line([0 X(i)], [0 Y(i)],'Linewidth',2);
    xlabel('X'); 
    ylabel('Y'); 
    titlestring = ['pendulum motion at t =',num2str(i*(20/500)), 'seconds'];
    title(titlestring ,'fontsize',14);                            
    
    Yr=getframe;
end
%.........................................................................