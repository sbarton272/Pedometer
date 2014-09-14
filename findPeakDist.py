# Nest interview

import csv

def findPeakDist(data):

	N = 1; # num of terms to look at on either side of value
	minInd = -1 # -1 signals not seen
	maxInd = -1
	T = .01

	# Iter through looking for min, max pair
	for i in xrange(N, len(data) - N):

		# Find min by comparing to surounding few values
		if (data[i] < data[i-N]) and (data[i] < data[i+N]):
			minInd = i;

		if (minInd != -1) and (data[i] > data[i-N]) and (data[i] > data[i+N]):
			maxInd = i

			# Determine if this is a valid pair, values calculated from matlab
			timeDif = (maxInd - minInd)
			heightDif = (data[maxInd] - data[minInd]) 
			if (3 <= timeDif) and (timeDif <= 10) and (heightDif > .3):
				print minInd, maxInd


data = []
with open('filteredData.csv', 'r') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        data.append(float(row[0]))

findPeakDist(data)
