# Nest interview

import csv

def findPeakDist(data):

	# 3Hz is fastest -> peaks no closer than 1/3 sec
	# 1/3 sec, @ 20Hz sampling rate -> 6-7 samples is closest
	# distance between peaks

	N = 6; # num of terms to look at on either side of value
	minInd = -1 # -1 signals not seen
	maxInd = -1
	T = .01
	tMin = 3
	tMax = 10
	hMin = .3

	# Iter through looking for min, max pair
	priorPeak = False
	stepCount = 0
	for i in xrange(N, len(data) - N):

		if ((max(data[i:i+N]) - min(data[i-N:i])) > hMin):
			if (not priorPeak):
				print i
				stepCount += 1
			priorPeak = True
		else:
			priorPeak = False

	print "STEPS FOUND: ", stepCount

data = []
with open('filteredData.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        data.append(float(row[0]))

findPeakDist(data)
