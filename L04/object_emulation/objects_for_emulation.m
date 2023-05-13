%% Generate test object for closed-loop control emulation 

Ts = 50e-3; % [s]

s = tf('s'); % complex frequency

% Secon order systems
T1 = 30; % [s]
T2 = 0.5;  % [s]
K1 = 0.5; % [-]

G1 = K1 / ((T1*s + 1)*(T2*s + 1));

T0 = 50;   % [s]
dmp = 0.5; % [-]
w0 = (2*pi/T0); % [rad/s]
K2 = 0.5; % [-]

G2 = K2 / ((s^2 / w0^2) + (2*dmp*s / w0) + 1);

H = c2d(G1, Ts, 'tustin');

conv = floatingPointConverter('DOUBLE', 'ROWS');

% Discrete SOS coefficients
coeffs = conv.print_csv_hex_data(                    ...
         [ -H.den{1}(2), -H.den{1}(3),               ...
            H.num{1}(1),  H.num{1}(2), H.num{1}(3) ] );
coeffs = coeffs(1:end-1);
disp("Discrete second-order-system coefficients:")
disp(coeffs);

%% Compare with C implementation
N = 10000;

y1 = lsim(H, ones(N,1));

src = readlines('object_emulation.c');
src(35) = "  " + convertCharsToStrings(coeffs);
%writelines(src, 'object_emulation.c');
fid = fopen('object_emulation.c','w'); 
for s = src
    fprintf(fid, '%s\n', s);
end
fclose(fid);%close file
system('gcc object_emulation.c dsos.c -o object_emulation.exe');
system('object_emulation.exe');
y2 = load("y.csv");

t = 0 : Ts : Ts*(N-1);

hold on;
plot(t, y1, "DisplayName", "MATLAB")
plot(t, y2, "DisplayName", "C18")
grid on;
legend();
xlabel("Time [s]")
ylabel("System response [-]"); 