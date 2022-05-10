%% LAB03 EX2

%%% File info 
%
% ************************************************************************
%
%  @file     LAB03/zbiornik_fuzzy_zad2_InitFcn.m
%  @author   Adrian Wojcik
%  @version  1.0
%  @date     12-Mar-2019 10:41:10
%  @brief    Water tank fuzzy controller
%
% ************************************************************************
%
clear all; close all; clc;
%% Create FIS structure

    fis_name = 'Fuzzy Tank Controller';
    FuzzyTankController = mamfis('Name', fis_name);
   
    FuzzyTankController.andMethod = 'min';
    FuzzyTankController.orMethod = 'max';
    FuzzyTankController.defuzzMethod = 'centroid';
    FuzzyTankController.impMethod = 'min';
    FuzzyTankController.aggMethod = 'max';
    
%% Add inputs

    m = 2; % number of inputs

    % Input #1: level error
    levelError.name = 'levelError';
    levelError.number = 1;
    levelError.range = [-2 2];
    levelError.accuracy = 0.01; % [m] % 0.01 * (levelError.range(end)); % 1% static error
    levelError.mfNumber = 5;
    levelError.mfVortex = logspace(0, log10(levelError.range(end)+1), ...
                                      floor(levelError.mfNumber/2)+2)-1;
    levelError.types = {@trimf, @trimf, @trapmf};

    FuzzyTankController = addInput(FuzzyTankController, levelError.range, 'Name', levelError.name);
    
     % Level error = big negative
    FuzzyTankController = addMF(FuzzyTankController, levelError.name, levelError.types{3}, ...
                -[levelError.range(end) levelError.mfVortex(4) levelError.mfVortex(3) levelError.mfVortex(2)], ...
                 'Name', 'NB');
            
    % Level error = small negative          
    FuzzyTankController = addMF(FuzzyTankController, levelError.name, levelError.types{2}, ...
                -[levelError.mfVortex(2) mean([levelError.mfVortex(2) levelError.accuracy]) levelError.accuracy], ...
                 'Name', 'NS');
    
    % Level error = zero
    FuzzyTankController = addMF(FuzzyTankController, levelError.name, levelError.types{1}, ...
                [-levelError.accuracy 0 levelError.accuracy], ...
                 'Name', 'Z');
                        
    % Level error = small positive
    FuzzyTankController = addMF(FuzzyTankController, levelError.name, levelError.types{2}, ...
                [levelError.accuracy mean([levelError.accuracy levelError.mfVortex(2)]) levelError.mfVortex(2)], ...
                 'Name', 'PS');

    % Level error = big positive
    FuzzyTankController = addMF(FuzzyTankController, levelError.name, levelError.types{3}, ...
                [levelError.mfVortex(2) levelError.mfVortex(3) levelError.mfVortex(4) levelError.range(end)], ...
                 'Name', 'PB');

    plotmf(FuzzyTankController, 'input', levelError.number, 1001);
    waitforbuttonpress;
                
    % Input #2: temperature error
    tempError.name = 'tempError';
    tempError.number = 2;
    tempError.range = [-80 80];
    tempError.accuracy = 0.1; % [deg C] %0.005 * (tempError.range(end)); % 0.5% static error
    tempError.mfNumber = 5;
    tempError.mfVortex = logspace(0, log10(tempError.range(end)+1), ...
                                   floor(tempError.mfNumber/2)+2)-1;
    tempError.types = {@trimf, @trimf, @trapmf};

    FuzzyTankController = addInput(FuzzyTankController, tempError.range, 'Name', tempError.name);
    
    % Temperature error = big negative 
    FuzzyTankController = addMF(FuzzyTankController, tempError.name, tempError.types{3}, ...
                -[tempError.range(end) tempError.mfVortex(4) tempError.mfVortex(3) tempError.mfVortex(2)], ...
                 'Name', 'NB');
                    
    % Temperature error = small negative 
    FuzzyTankController = addMF(FuzzyTankController, tempError.name, tempError.types{2}, ...
                -[tempError.mfVortex(2) mean([tempError.mfVortex(2) tempError.accuracy]) tempError.accuracy], ...
                 'Name', 'NS');
    
    % Temperature error = zero
    FuzzyTankController = addMF(FuzzyTankController, tempError.name, tempError.types{1}, ...
                [-tempError.accuracy 0 tempError.accuracy], ...
                 'Name', 'Z');
                                       
    % Temperature error = small positive 
    FuzzyTankController = addMF(FuzzyTankController, tempError.name, tempError.types{2}, ...
                [tempError.accuracy mean([tempError.accuracy tempError.mfVortex(2)]) tempError.mfVortex(2)], ...
                 'Name', 'PS');

    % Temperature error = big positive
    FuzzyTankController = addMF(FuzzyTankController, tempError.name, tempError.types{3}, ...
                [tempError.mfVortex(2) tempError.mfVortex(3) tempError.mfVortex(4) tempError.range(end)], ...
                 'Name', 'PB');

    plotmf(FuzzyTankController, 'input', tempError.number, 1001);
    waitforbuttonpress;
    
%% Add outputs

    n = 2; % number of outputs
    
    % Output #1: cold water
    waterCold.name = 'waterCold';
    waterCold.number = 1;
    waterCold.range = [0 1];
    
    % saturation function
    sat = @(s) min(max(s, waterCold.range(1)), waterCold.range(end)); 
    
    waterCold.mfName = {'0.0', '0.2', '0.5', '0.8', '1.0'};
    waterCold.mfWidth = 0.05;
    
    for i = 1 : length(waterCold.mfName)
        waterCold.mfParams{i} = [sat(str2double(waterCold.mfName{i})-waterCold.mfWidth), ... 
                                sat(str2double(waterCold.mfName{i})), sat(str2double(waterCold.mfName{i})+waterCold.mfWidth)];  
    end
    
    FuzzyTankController = addOutput(FuzzyTankController, waterCold.range, 'Name', waterCold.name);
    
    for i = 1 : length(waterCold.mfName)
        FuzzyTankController = addMF(FuzzyTankController, waterCold.name, @trimf, ...
                waterCold.mfParams{i}, 'Name', waterCold.mfName{i});
    end
    
    plotmf(FuzzyTankController, 'output', waterCold.number, 1001);
    waitforbuttonpress;

    % Output #1: hot water
    waterHot.name = 'waterHot';
    waterHot.number = 2;
    waterHot.range = [0 1];
    
    % saturation function
    sat = @(s) min(max(s, waterHot.range(1)), waterHot.range(end)); 
    
    waterHot.mfName = {'0.0', '0.2', '0.5', '0.8', '1.0'};
    waterHot.mfWidth = 0.05;
    
    for i = 1 : length(waterHot.mfName)
        waterHot.mfParams{i} = [sat(str2double(waterHot.mfName{i})-waterHot.mfWidth), ... 
                                sat(str2double(waterHot.mfName{i})), sat(str2double(waterHot.mfName{i})+waterHot.mfWidth)];  
    end
    
    FuzzyTankController = addOutput(FuzzyTankController, waterHot.range, 'Name', waterHot.name);
    
    for i = 1 : length(waterHot.mfName)
        FuzzyTankController = addMF(FuzzyTankController, waterHot.name, @trimf, ...
                waterHot.mfParams{i}, 'Name', waterHot.mfName{i});
    end
    
    plotmf(FuzzyTankController, 'output', waterHot.number, 1001);
    waitforbuttonpress;  close all;

    
%% Rules array
     
% TEMP ERROR:      NB              NS             Z              PS             PB         % LEVEL ERROR:
    TABLE = { {'0.0','0.0'}, {'0.0','0.0'}, {'0.0','0.0'}, {'0.0','0.0'}, {'0.0','0.0'};   % NB
              {'0.2','0.0'}, {'0.0','0.0'}, {'0.0','0.0'}, {'0.0','0.0'}, {'0.0','0.2'};   % NS
              {'0.5','0.0'}, {'0.2','0.0'}, {'0.0','0.0'}, {'0.0','0.2'}, {'0.0','0.5'};   % Z
              {'1.0','0.0'}, {'0.8','0.2'}, {'0.5','0.5'}, {'0.2','0.8'}, {'0.0','1.0'};   % PS
              {'1.0','0.5'}, {'1.0','0.8'}, {'1.0','1.0'}, {'0.8','1.0'}, {'0.5','1.0'} }; % PB

%% Add rules

    % index functions
    getWaterColdIndex = @(str)(find(strcmp(waterCold.mfName, str)));
    getWaterHotIndex =  @(str)(find(strcmp(waterHot.mfName, str)));
          
    % fuzzy logic system structure
    fs.levelError = 1;   % 1st input
    fs.tempError  = 2;   % 2nd input
    fs.waterCold  = m+1; % 1st output
    fs.waterHot   = m+2; % 2nd output
    fs.op      = m+n+2; % AND/OR selectionhel

    rule = cell(numel(TABLE),1);
   
    [I,J] = size(TABLE); k = 1;
    for i = 1 : I
        for j = 1 : J
        
        rule{k} = ones(1, fs.op);
        
        % IF
        rule{k}(fs.levelError) = i; 
        rule{k}(fs.op)      = 1; % AND    
        rule{k}(fs.tempError)    = j; 
        % THEN
        rule{k}(fs.waterCold) =  getWaterColdIndex(TABLE{i,j}{1});
        rule{k}(fs.waterHot) = getWaterHotIndex(TABLE{i,j}{2});
        
        FuzzyTankController = addrule(FuzzyTankController,rule{k});
        k = k+1;
        end
    end
         
%% Clear variables

    clearvars -except FuzzyTankController 
    