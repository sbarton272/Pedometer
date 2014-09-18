%% Nest Interview
% Spencer Barton
% 9/13/14

clear all;
close all;

FILENAME = 'accel.csv';
Fs = 20; % Hz
STEPS = 20;

data = csvread(FILENAME); % x,y,z

nSamples = size(data,1);
time = linspace(0, nSamples / Fs, nSamples);

figure; plot(time, data);

% Normalize - note no sqrt because won't have that in final implentation
data = sum(data.^2, 2) - 1;


%% Peak detection with band pass filtered data
% Goals: 
% - determine threshold for peak distances
% - determine window size for min-max peak pairs
%
% Based off of bpf we have lower limit of 1Hz to upper lim of 3Hz for step
% freq. This means when looking for peaks know that there will be no peaks
% appearing in less than Fs/3Hz ~= 6 samples and nothing greater than
% Fs/1Hz ~= 20 samples. Since I am looking for max/min pairs the min
% distance is 3 samples. The greater limit will likely be contrained by
% step dynamics.

%% Filter
b = [0.00244140625, 0.00390625, 0.00390625, 0.001953125, -0.001953125, -0.00439453125, 0.0, 0.00830078125, 0.0078125, -0.0146484375, -0.05908203125, -0.1025390625, -0.107421875, -0.04931640625, 0.056640625, 0.15966796875, 0.20263671875, 0.15966796875, 0.056640625, -0.04931640625, -0.107421875, -0.1025390625, -0.05908203125, -0.0146484375, 0.0078125, 0.00830078125, 0.0, -0.00439453125, -0.001953125, 0.001953125, 0.00390625, 0.00390625, 0.00244140625];
b2 = fir1(32, [.1 .3]);

quantizationError = sum((b - b2).^2)

% Just trying out filter implementation
buff = zeros(1,33);
bp2Data = zeros(1,length(data));
for i = 1:length(data)
   buff = circshift(buff,[0 1]);
   buff(1) = data(i);
   bp2Data(i) = sum(b.*buff);
end

bpData = filter(b2,1,data);
figure; plot(time, bpData, time, bp2Data);

%% Find peaks
% Find max peaks
[maxPeaks, maxLocations] = findpeaks(bpData);

% Find min peaks
[minPeaks, minLocations] = findpeaks(-bpData);

%% Find peak height/time distances
% Find min-max pair distances
len = min(length(maxPeaks), length(minPeaks));
peakDist = maxPeaks(1:len) + minPeaks(1:len);

% Find min-max pair time distance
locDist = maxLocations(1:len) - minLocations(1:len);

%% Find good threshold for distances
% Actual steps
stepIndeces = (peakDist > .3);
stepPeakDist = peakDist .* stepIndeces;
stepPeakDist(stepIndeces==0) = []; % remove 0's

% Non-steps
nonStepPeak = peakDist .* (1-stepIndeces);
nonStepPeak(nonStepPeak==0) = []; % remove 0's

% Theshold is distance between two distributions
% Simply take midpoint between two wieghted groupings
probStepPeak = sum(stepIndeces) / length(stepIndeces)
probNonStepPeak = 1-probStepPeak
threshold = (mean(stepPeakDist)*probStepPeak - mean(nonStepPeak)*probNonStepPeak) / 2

%% Find good window size to search for min/max pairs

% update with only step pairs
locDist(stepIndeces==0) = [];

lowerWindowBound = 3 % see comments earlier
upperWindowBound = max(locDist)

%% Plots

% Plot peak distance
figure; subplot(2,1,1);
stem(time(maxLocations(stepIndeces==1)), peakDist(stepIndeces==1), 'bo'); % steps
hold on;
stem(time(maxLocations(stepIndeces==0)), peakDist(stepIndeces==0), 'ro'); % non-steps
hold on; plot(time, threshold);
title(['min-max peak pair distance, ', num2str(threshold)]); xlabel('sec');
subplot(2,1,2);
hist(peakDist); title('step peak dists, note seperation in distributions'); 

% plot peak distances
figure;
hist(locDist); title('Time distance in peak pairs (between min and max)');

% Plot time data with min/max marked
figure; plot(time, bpData); 
hold on
plot(time(maxLocations), maxPeaks, 'ro');
plot(time(minLocations), -minPeaks, 'go');
title('Band pass peaks data');
xlabel('sec'); ylabel('mag');