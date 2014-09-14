%% Nest Interview
% Spencer Barton
% 9/13/14

clear all;
close all;

FILENAME = 'accel.csv';
Fs = 20; % Hz
STEPS = 20;

%% Basic peek at the data - plot x, y, z
% It appears that the data is normalized to 1 for gravity

data = csvread(FILENAME); % x,y,z

nSamples = size(data,1);
time = linspace(0, nSamples / Fs, nSamples);

figure;
subplot(3,1,1); plot(time, data(:,1)); title('X'); xlabel('sec');
subplot(3,1,2); plot(time, data(:,2)); title('Y'); xlabel('sec');
subplot(3,1,3); plot(time, data(:,3)); title('Z'); xlabel('sec');

%% Plot 2-norm of x,y,z
% This will likely be a much more useful measurment because the
% accelermeter can be rotated.

normData = sqrt(sum(data.^2, 2));
figure; plot(time, normData); title('2-norm'); xlabel('sec')

%% Plot freq to get a sense of frequencies in play
% Very string DC value - expected because gravity is always constant
% May want to remove effects of gravity

nFft = 1024; % padding
w = unwrap(fftshift(2*pi * (0:(nFft-1)) / nFft) - 2*pi) / pi;
freqNormData = abs(fftshift(fft(normData, nFft)));
figure; plot(w, freqNormData); 
title('Freq');
xlabel('rad/pi'); ylabel('mag');

%% Subtract effects of gravity and replot freq
% This is nicer to look at

nFft = 1024; % padding
w = unwrap(fftshift(2*pi * (0:(nFft-1)) / nFft) - 2*pi) / pi;

% Subtract gavity
gravNormData = normData-1;
freqGravNormData = abs(fftshift(fft(gravNormData, nFft)));

figure; plot(w, freqGravNormData); 
title('Freq - with gravity removed');
xlabel('rad/pi'); ylabel('mag');

%% LPF

b = fir1(16, .4, 'low');
lpData = filter(b,1,gravNormData);

figure; plot(time, lpData); 
title('Low pass data');
xlabel('sec'); ylabel('mag');


%% Spectrogram alongside time plot
% insight into important frequencies?
% Know about 20 steps in about 15 sec (2s-17s) -> about .67 sec per step
% Freq about 1.5 Hz

stepTime = .67;
windowSize = floor(stepTime*Fs);
window = hamming(windowSize);
nOverlap = floor(windowSize / 2);

figure;
spectrogram(gravNormData, window, nOverlap, nFft, Fs, 'yaxis');

%% BPF
% Thinking about the fundamental step frequency
% Around .17*2*pi
% About 1.3 m/s walking speed, .67/.76 m step size (women/men)
% About 1.9 step/sec (women) or 1.7 step/sec (men)
% Since sampled at 20Hz, -> looking for about 1.7 - 1.9 Hz

b = fir1(64, [.1, .2]);
bpData = filter(b,1,gravNormData);

nFft = 1024; % padding
w = unwrap(fftshift(2*pi * (0:(nFft-1)) / nFft) - 2*pi) / pi;

% Subtract gavity
freqBpData = abs(fftshift(fft(bpData, nFft)));

figure;
subplot(3,1,1); plot(b); title('Filter');
subplot(3,1,2); plot(time, bpData); title('Band pass data');
xlabel('sec'); ylabel('mag');
subplot(3,1,3); plot(w, freqBpData); title('Freq');
xlabel('rad/pi'); ylabel('mag');




