function [] = algorithms()
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

% Work with data normalized and with gravity removed
normData = sqrt(sum(data.^2, 2)) - 1;

%% Simple threshold

figure; hist(normData, 100);

THRESHOLD = .25; % TODO calculating threshold
steps = normData > THRESHOLD;

plotDetectedSteps(normData, steps, Fs);

%% Simple threshold with lpf

%% Two threasholds with hysteresis and lpf


end

function [] = plotDetectedSteps(data, steps, Fs)

nSamples = size(data,1);
time = linspace(0, nSamples / Fs, nSamples);

nFft = 1024; % padding
w = unwrap(fftshift(2*pi * (0:(nFft-1)) / nFft) - 2*pi) / pi;

% Get DTFT
freqData = abs(fftshift(fft(data, nFft)));

figure;
subplot(3,1,1); plot(w, freqData); title('Data Freq');
xlabel('rad/pi'); ylabel('mag');
subplot(3,1,2); plot(time, data); title('Data');
xlabel('sec'); ylabel('mag');
subplot(3,1,3); plot(time, steps); title('Steps');
xlabel('sec'); ylabel('step = 1');

end