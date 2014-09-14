Nest
====

Nest interview

The task for you is to implement a C implementation for a pedometer that counts and then prints the number of steps taken. I have attached the x,y,z acceleration from a walk. The accelerometer was sampled at 20Hz and the log below corresponds to around 20 steps.  Feel free to visualize the data with Matlab/Python (extra points for sending in the Matlab/Python code)

You can choose any algorithm, so long as it is reasonably accurate (e.g. +- 3 steps). Also the solution you implement should be self contained and compilable (i.e. I should be able to run it locally to verify the step count and it can only rely on the standard C library). Also stick to integer math (no floats, doubles)


Ideas
=====

- Filtering will probably be necessary
- Will need to normalize data and combine to one vector
- Bandpass can remove effects of gravity
- 

Algorithms
==========

