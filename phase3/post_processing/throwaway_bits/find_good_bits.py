#!/usr/bin/python2.7

import sys
import os

if len(sys.argv) != 2:
	print 'Usage: find_good_bits.py <PollSensors datafile>'
	sys.exit(1)

infile = open(sys.argv[1])


