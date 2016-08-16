#! /usr/bin/python

import math

Number_1 = 6
Number_2 = 4
Number_3 = 5
Number_4 = 3
Number_5 = 5.0
Number_6 = 99

print "Challenge 01"
print "============\n"
print "Number_1 = ", Number_1
print "Number_2 = ", Number_2
print "Number_1 + Number_2 = ", Number_1 + Number_2
print "Number_1 - Number_2 = ", Number_1 - Number_2
print "\n"
print "Number_3 = ", Number_3
print "Number_4 = ", Number_4
print "Number_5 = ", Number_5
print "Number_3 / Number_4 = ", Number_3 / Number_4
print "Number_5 / Number_4 = ", Number_5 / Number_4
print "Number_4 * Number_3 = ", Number_4 * Number_3
print "\n"
print "Number_6 = ", Number_6
print "2 to the power Number_1 = ", math.pow(2,Number_1)
print "2 to the power Number_2 = ", math.pow(2,Number_2)
print "2 to the power Number_3 = ", math.pow(2,Number_3)
print "2 to the power Number_4 = ", math.pow(2,Number_4)
print "2 to the power Number_5 = ", math.pow(2,Number_5)
print "2 to the power Number_6 = ", math.pow(2,Number_6)

print "\n\n"

print "Challenge 02"
print "============\n"

# The diameter of a cell is 10 things.
# What volume does that cell have given it is a perfect sphere?
# Use Python to do the calculation.
# Use variables for the parameters.
# Print the volume to the screen.

# V = (4/3)*Pi*r*r*r

C  = 4.0 / 3.0
d  = 10.0
r  = d / 2.0
# r3 = math.pow(r,3)
r3 = r ** 3
Pi = math.pi

V = C * Pi *r3

print "Volume of a cell with diameter 10 things is", V, "things cubed."

print "\n\n"

print "Challenge 03"
print "============\n"


