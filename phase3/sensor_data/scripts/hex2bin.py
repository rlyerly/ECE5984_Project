#!/usr/bin/python

import sys

if len(sys.argv) != 2:
	print "Usage: hex2bin.py <input file>"
	sys.exit(1)

infile = open(sys.argv[1], 'r')
outfile1 = open(sys.argv[1].replace(".dat", "_binary_x.dat"), 'w')
outfile2 = open(sys.argv[1].replace(".dat", "_binary_y.dat"), 'w')
outfile3 = open(sys.argv[1].replace(".dat", "_binary_z.dat"), 'w')

base = 16
numBits = 32
for line in infile:
	parts = line.strip().split()
	outfile1.write(bin(int(parts[0], base))[2:].zfill(numBits) + '\n')
	outfile2.write(bin(int(parts[1], base))[2:].zfill(numBits) + '\n')
	outfile3.write(bin(int(parts[2], base))[2:].zfill(numBits) + '\n')

infile.close()
outfile1.close()
outfile2.close()
outfile3.close()
