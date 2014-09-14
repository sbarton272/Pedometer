# Nest interview

import csv

def findPeakDist(data):

	N = 2; # num of terms to look at on either side of value
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


		# look at a moving window of 5
		# TODO play with window 4 vs 5

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
