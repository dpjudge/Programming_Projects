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

# Calculate the distance between two points in the 3D space
# Given two points in the Cartesian space:
# P1 = (43.64, 30.72, 88.95) P2 = (45.83, 31.11, 92.04)
# Use Python to calculate their distance
# Use variables for the parameters
# Print the distance to the screen
# The formula for calculating the distance is:
# d = SQRT((x2 -x1)**2 + (y2 - y1)**2 + (z2 - z1))**2)

x1, y1, z1 = 43.64, 30.72, 88.95
x2, y2, z2 = 45.83, 31.11, 92.04
xd, yd, zd = x2 - x1, y2 - y1, z2 - z1
d = math.sqrt(xd**2 + yd**2 + zd**2)

print "The distance between P1 (", x1, y1, z1,")"
print "and P2 (", x2, y2, z2,") is ", d, "unspecified units."

print "\n\n"

print "Challenge 04"
print "============\n"

# Find cysteine bonds in the Insulin structure
# Data in 2OMH.pdb
# Lines containing 'SG'
# x, y, z coordinates
# Use what you learnt from Task 2

def 
