# Nest Interview windowed max, min peak distances

def findPeakDist(data):
	
	Fs = 20 # Hz
	stepDurations = .67 # sec, approx calculated in explorations.m
	WINDOW_LEN = 10; 

	window = [0] *