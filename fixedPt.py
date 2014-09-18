# Determine the best fixed point representation

import csv, math

FIXED_LOC = 11

def convert(f):
	# When read in truncate 4 palces after decimal pt.
	a = int(math.floor(f*10000))
	return (a << FIXED_LOC) / 10000

def fixedPtMult(a,b):
	return a*b >> FIXED_LOC

# print convert(.0025) # 20

data = []
with open('accel.csv', 'r') as csvfile:
    reader = csv.reader(csvfile, delimiter=',')
    for row in reader:
    	x = convert(float(row[0]))
    	y = convert(float(row[1]))
    	z = convert(float(row[2]))
    	data.append(x)
        data.append(y)
        data.append(z)

        # Also check what happens once normalize
        data.append(fixedPtMult(x,x) + fixedPtMult(y,y) + fixedPtMult(z,z))


print "Max int: ", 2**15 - 1, " vs ", max(data)
print "Min int: ", -2**15, " vs ", min(data)

# Many filter coef require .0001 precision
# Input values go to about 1.5 in mag
#  and peak distances to about 3
# Raw data values [-1.5,3]
# Want precision of ~.0001 and up to about 3 in value
# Therefore 2^(-13) = .00012 leaving 2 bits for
# interger up to 4 'sign' bit (still use 2's comp)
# This is for int16

filterCoef = [0.0025, 0.0038, 0.0041, 0.0020, -0.0021, -0.0042, 0.0000, 0.0081, 0.0079, -0.0145, -0.0592, -0.1025, -0.1072, -0.0495, 0.0565, 0.1597, 0.2024, 0.1597, 0.0565, -0.0495, -0.1072, -0.1025, -0.0592, -0.0145, 0.0079, 0.0081, 0.0000, -0.0042, -0.0021, 0.0020, 0.0041, 0.0038, 0.0025] 

b = 2**(-FIXED_LOC)
fixedPtRep = [ int(round(x/b)) for x in filterCoef ]

# Calc quantization error
err = 0
for i in xrange(0, len(filterCoef)):
	err += (filterCoef[i] - fixedPtRep[i]*b)**2

print b, err
print fixedPtRep
print [ x*b for x in fixedPtRep ]