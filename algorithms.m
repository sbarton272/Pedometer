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

% Work with data normalized and with gravity removed
normData = sqrt(sum(data.^2, 2)) - 1;

%% Simple threshold - really bad

THRESHOLD = .25;
steps = normData > THRESHOLD;

plotDetectedSteps(normData, steps, Fs);

%% Simple threshold with lpf

b = fir1(16, .3, 'low');
lpData = filter(b,1,normData);

THRESHOLD = .24; % Calculated in other script
steps = lpData > THRESHOLD;

plotDetectedSteps(lpData, steps, Fs);

%% Simple threshold with bpf

b = fir1(64, [.1 .3]);
bpData = filter(b,1,normData);

steps = bpData > .2; % theshold found in other script

plotDetectedSteps(bpData, steps, Fs);

end

function [] = plotDetectedSteps(data, steps, Fs)

nSamples = size(data,1);
time = linspace(0, nSamples / Fs, nSamples);

nFft = 1024; % padding
w = unwrap(fftshift(2*pi * (0:(nFft-1)) / nFft) - 2*pi) / pi;

% Get DTFT
freqData = abs(fftshift(fft(data, nFft)));

% Count number of steps
stepCount = sum(diff(steps) > 0);

figure;
subplot(3,1,1); plot(w, freqData); title('Data Freq');
xlabel('rad/pi'); ylabel('mag');
subplot(3,1,2); plot(time, data); title('Data');
xlabel('sec'); ylabel('mag');
subplot(3,1,3); plot(time, steps); title(['Steps ', int2str(stepCount)]);
xlabel('sec'); ylabel('step = 1'); ylim([0 1.5]);

end
