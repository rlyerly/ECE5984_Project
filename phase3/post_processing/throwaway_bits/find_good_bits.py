#!/usr/bin/python2.7

import sys
import os
import subprocess

if len(sys.argv) != 2:
	print 'Usage: find_good_bits.py <PollSensors datafile>'
	sys.exit(1)

infile = sys.argv[1]

# Make sure utilities have been built
if not os.path.isfile('./hex_2_bin') or not os.path.isfile('./throwaway_bits_static'):
	print 'Building utilities...'
	subprocess.Popen(['make']).wait()

# Call utilities on file
print 'Converting hex to a binary file...'
subprocess.Popen(['./hex_2_bin', '-i', sys.argv[1], '-o', infile.replace('.dat', '_bin.dat')]).wait()

# Binary search to find largest number of acceptable LSB
# TODO

# Cleanup
os.remove(infile.replace('.dat', '_bin.dat'))
