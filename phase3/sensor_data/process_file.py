#!/usr/bin/python

import os
import sys
import subprocess

if len(sys.argv) != 2:
	print 'Usage: process_file.py <filename>'

filename = sys.argv[1]

# Convert to hex
subprocess.Popen(['./scripts/hex2bin.py', filename]).wait()

# Get distributions
subprocess.Popen(['./scripts/distribution_per_bit.py', filename.replace(".dat", "_binary_x.dat")]).wait()
subprocess.Popen(['./scripts/distribution_per_bit.py', filename.replace(".dat", "_binary_y.dat")]).wait()
subprocess.Popen(['./scripts/distribution_per_bit.py', filename.replace(".dat", "_binary_z.dat")]).wait()

# Generate plots
os.environ['FILENAME'] = filename.replace('.dat', '_processed_x.dat')
os.environ['OUTPUT'] = filename.replace('.dat', '_x.png').replace('data', 'graphs')
os.environ['TITLE'] = "Distribution of 0's and 1's for file\n" + filename.replace('data/', '').replace('.dat', '_processed_x.dat')
subprocess.Popen(['./scripts/plot.p']).wait()

os.environ['FILENAME'] = filename.replace('.dat', '_processed_y.dat')
os.environ['OUTPUT'] = filename.replace('.dat', '_y.png').replace('data', 'graphs')
os.environ['TITLE'] = "Distribution of 0's and 1's for file\n" + filename.replace('data/', '').replace('.dat', '_processed_y.dat')
subprocess.Popen(['./scripts/plot.p']).wait()

os.environ['FILENAME'] = filename.replace('.dat', '_processed_z.dat')
os.environ['OUTPUT'] = filename.replace('.dat', '_z.png').replace('data', 'graphs')
os.environ['TITLE'] = "Distribution of 0's and 1's for file\n" + filename.replace('data/', '').replace('.dat', '_processed_z.dat')
subprocess.Popen(['./scripts/plot.p']).wait()

#Cleanup
os.remove(filename.replace('.dat', '_binary_x.dat'))
os.remove(filename.replace('.dat', '_binary_y.dat'))
os.remove(filename.replace('.dat', '_binary_z.dat'))
os.remove(filename.replace('.dat', '_processed_x.dat'))
os.remove(filename.replace('.dat', '_processed_y.dat'))
os.remove(filename.replace('.dat', '_processed_z.dat'))
