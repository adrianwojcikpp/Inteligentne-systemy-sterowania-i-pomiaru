function [u, hpid] = pid_controller(hpid, yref, y)

e = yref - y; % control error

% PID algorithm based on MATLAB doc
% Parallel Form:
%   u = Kp*e + Ki*e/s + Kd*N / (1 + N/s)
% Forward Euler:
%   1/s = Ts/(z - 1)

% Integral
hpid.e_int = hpid.e_int + (hpid.Ki*hpid.Ts)*e;

% Derivative 
hpid.d_prev = (hpid.Kd*hpid.N)*(e - hpid.e_prev) + (1.0 - hpid.N*hpid.Ts)*hpid.d_prev;
hpid.e_prev = e;

% Output 
u = (hpid.Kp * e) + hpid.e_int + hpid.d_prev;

% Saturation 
if u > hpid.Limit 
	 u_sat = hpid.Limit;
elseif u < -hpid.Limit
    u_sat = -hpid.Limit;
else
    u_sat = u;
end

% Anti wind-up 
if u ~= u_sat
    hpid.e_int = hpid.e_int - (hpid.Ki*hpid.Ts)*e;
end

u = u_sat;