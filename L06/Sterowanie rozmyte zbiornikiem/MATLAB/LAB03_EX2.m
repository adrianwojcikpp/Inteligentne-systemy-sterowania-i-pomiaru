%% Create FIS structure
zbiornik_fuzzy_InitFcn;  

%% Run simulation 
fis = FuzzyTankController;
modelname = 'zbiornik_fuzzy_viewer_data_log';
load_system(modelname);
sim(modelname);
close_system(modelname);

%% Plot results
level = results.Data(:,1);
levelRef = 0.7*ones(size(level));

temp = results.Data(:,2);
tempRef = 60*ones(size(temp));

t = results.Time;

subplot(2,1,1);
    plot(t, level, 'r'); hold on; grid on;
    plot(t, levelRef, 'k');
    xlabel('Time [s]');
    ylabel('Level [m]');
    legend('Tank level value','Reference value');
    title('Water level control');
    axis([t(1) t(end) 0.5 1.0]);
    hold off;
subplot(2,1,2);
    plot(t, temp, 'r'); hold on; grid on;
    plot(t, tempRef, 'k');
    xlabel('Time [s]');
    ylabel('Temperature [^oC]');
    legend('Tank temperature value','Reference value');
    title('Water temperature control');
    axis([t(1) t(end) 30 70]);
    hold off;

