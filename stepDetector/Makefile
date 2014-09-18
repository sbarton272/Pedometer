pedometer: pedometer.o stepDetector.o fixedPt.o
	gcc -Wall -o pedometer pedometer.o stepDetector.o fixedPt.o

pedometer.o: pedometer.c stepDetector.h fixedPt.h
	gcc -c pedometer.c stepDetector.c fixedPt.c

stepDetector.o: stepDetector.c stepDetector.h fixedPt.h
	gcc -c stepDetector.c fixedPt.c

fixedPt.o: fixedPt.c fixedPt.h
	gcc -c fixedPt.c