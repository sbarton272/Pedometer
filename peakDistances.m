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

% Normalize
data = sqrt(sum(data.^2, 2)) - 1;


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
b = fir1(32, [.1 .3]);
bpData = filter(b,1,data);

%% Find peaks
% Find max peaks
[maxPeaks, maxLocations] = findpeaks(bpData);

% Find min peaks
[minPeaks, minLocations] = findpeaks(-bpData)

%% Find peak height/time distances
% Find max-min pair distances
len = min(length(maxPeaks), length(minPeaks));
peakDist = maxPeaks(1:len) + minPeaks(1:len);

% Find min-max pair time distance
locDist = maxLocations(1:len) - minLocations(1:len);

%% Find good threshold for distances
% Actual steps
stepIndeces = (peakDist > .3);
stepPeakDist = peakDist .* stepIndeces;
stepPeakDist(stepPeakDist==0) = []; % remove 0's

% Non-steps
nonStepPeak = peakDist .* (1-stepIndeces);
nonStepPeak(nonStepPeak==0) = []; % remove 0's

% Theshold is distance between two distributions
% Simply take midpoint between two groupings
% Comes out to about .3 anyway so I'll use that
threshold = (mean(stepPeakDist) - mean(nonStepPeak)) / 2;

%% Find good window size to search for min/max pairs

% update with only step pairs
locDist(stepIndeces==0) = [];

lowerWindowBound = 3 % see comments earlier
upperWindowBound = max(locDist)

%% Plots

% Plot peak distance
figure; subplot(2,1,1);
stem(time(maxLocations(1:len)), peakDist);
hold on; plot(time, threshold);
title(['min-max peak pair distance, ', num2str(threshold)]); xlabel('sec');
subplot(2,1,2);
hist(peakDist); title('step peak dists, note seperation in distributions'); 

% plot peak distances
figure;
hist(locDist); title('Time distance in peak pairs');

% Plot time data with min/max marked
figure; plot(time, bpData); 
hold on
plot(time(maxLocations), maxPeaks, 'ro');
plot(time(minLocations), -minPeaks, 'go');
title('Band pass peaks data');
xlabel('sec'); ylabel('mag');