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


%% Peak detection with band pass filtered data
% Goals: 
% - determine threshold for peak distances
% - determine window size for min-max pairs

b = fir1(32, [.1 .3]);
bpData = filter(b,1,gravNormData);

% Find max peaks
minPeakDist = floor(.67 * Fs / 2); % half of estimated step time distance
[maxPeaks, maxLocations] = findpeaks(bpData, 'MINPEAKHEIGHT', 0, ...
    'MINPEAKDISTANCE', minPeakDist);

% Find min peaks
[minPeaks, minLocations] = findpeaks(-bpData, 'MINPEAKHEIGHT', 0, ...
    'MINPEAKDISTANCE', minPeakDist);

% Find max-min pair distances
len = min(length(maxPeaks), length(minPeaks));
peakDist = maxPeaks(1:len) + minPeaks(1:len);

% Actual steps
stepPeakDist = peakDist .* (peakDist > .3);
stepPeakDist(stepPeakDist==0) = []; % remove 0's

% Non-steps
nonStepPeak = peakDist .* (peakDist < .3);
nonStepPeak(nonStepPeak==0) = []; % remove 0's

% Theshold is distance between two distributions
% Simply take midpoint between two groupings
% Comes out to about .3 anyway so I'll use that
threshold = (mean(stepPeakDist) - mean(nonStepPeak)) / 2

% Find min-max pair time distance
len = min(length(maxLocations), length(minLocations));
peakDist = maxLocations(1:len) + minLocations(1:len);


% Plot peak distance
figure; subplot(2,1,1);
stem(maxLocations(1:len), peakDist);
title('min-max peak pair distance'); xlabel('sec');
subplot(2,1,2);
hist(peakDist); title('step peak dists, note seperation in distributions'); 

figure; plot(time, bpData); 
hold on
plot(time(maxLocations), maxPeaks, 'ro');
plot(time(minLocations), -minPeaks, 'go');
title('Band pass peaks data');
xlabel('sec'); ylabel('mag');