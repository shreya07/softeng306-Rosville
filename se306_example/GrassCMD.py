#!/usr/bin/python
# Created on:   29/08/2013
# Author: 		george
# Credits to txt2re.com for regular expression code section
""" Usage:
Open up terminal and run roscore
Open another terminal and go to the se306_example folder
'binary file' is the name of the executable in your 'bin' folder

Individual Piping:
$ rosrun se306_example 'binary file' | python 'name'.py

Multiple Piping:
$ rosrun se306_example 'binary file' |
  rosrun se306_example 'binary file' |
  python 'name'.py

Weather:
$ rosrun se306_example GodNode |
  rosrun se306_example GrassOne |
  python GrassCMD.py 
"""

import re
import sys
import time


firstLoop = True

while True:
	try:
		# Read line from console and get rid of trash parts, 
		# assign ROS_INFO value to curVal
		txt = sys.stdin.readline()
		
		# Regular expressions section starts --------------------------
		re1='.*?'	# Non-greedy match on filler
		re2='[+-]?\\d*\\.\\d+(?![-+0-9\\.])'	# Uninteresting: float
		re3='.*?'	# Non-greedy match on filler
		re4='([+-]?\\d*\\.\\d+)(?![-+0-9\\.])'	# Float 1

		rg = re.compile(re1+re2+re3+re4,re.IGNORECASE|re.DOTALL)
		m = rg.search(txt)
		
		if m:
			curVal = m.group(1) # This is a string
		# ---------------------------- Regular expressions section ends
		
		# Ensure the first round go through
		if (firstLoop):
			preVal = "-1.000000" # This is a string
			firstLoop = False
			
		# Check if the current value is different to the previous value
		if (curVal != preVal):
			# Print to the console
			sys.stdout.write("\rGrass height = " + curVal)
			sys.stdout.flush()
			# Give time for value to stay still
			time.sleep(0.9)
			# Set previous value to current value
			preVal = curVal
			
	except KeyboardInterrupt:
		break
	
	if not txt:
		break
