#!/usr/bin/python

import sys

if len(sys.argv) != 2:
	print 'Usage: distribution_per_bit.py <filename>'
	sys.exit(1)

if "_binary_" not in sys.argv[1]:
	print 'Must use a file created by hex2bin.py'
	sys.exit(1)
infile = open(sys.argv[1], 'r')

distribution = [[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0],[0,0,0]]

for line in infile:
	for i in range(32):
		distribution[i][2] = distribution[i][2] + 1
		if line[i] == '0':
			distribution[i][0] = distribution[i][0] + 1
		else:
			distribution[i][1] = distribution[i][1] + 1
infile.close()

outfile = open(sys.argv[1].replace('_binary_', '_processed_'), 'w')
for i in range(32):
	outfile.write(str(distribution[i][0]) + ' '
		+ str(distribution[i][1]) + ' '	+ str(distribution[i][2])
		+ '\n')
outfile.close
