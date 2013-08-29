#!/usr/bin/python
# Created on:   29/08/2013
# Author: 		george
# Credits to txt2re.com for regular expression code section
""" Usage:
Open up terminal and run roscore
Open another terminal and go to the se306_example folder

$ roslaunch se306_example nodeLaunch.launch | python poisonGrassCMD.py
"""

import re
import sys
import time


#firstLoop = True

while True:
	try:
		# Read line from console and get rid of trash parts, 
		# assign ROS_INFO value to curVal
		txt = sys.stdin.readline()
		# first input is weather
		# second input is poison grass
		
		# Regular expressions section starts --------------------------
		re1='.*?'	# Non-greedy match on filler
		re2='(?:[a-z][a-z]+)'	# Uninteresting: word
		re3='.*?'	# Non-greedy match on filler
		re4='((?:[a-z][a-z]+))'	# Word 1
		re5='.*?'	# Non-greedy match on filler
		re6='((?:[a-z][a-z]+))'	# Word 2

		rg1 = re.compile(re1+re2+re3+re4+re5+re6,re.IGNORECASE|re.DOTALL)
		m1 = rg1.search(txt)
		
		if m1:
			if ("Weather" == m1.group(1)):
				print "Weather: " + m1.group(2)
			elif ("PoisonGrass" == m1.group(1)):
				re7='([+-]?\\d*\\.\\d+)(?![-+0-9\\.])'	# Float 2
				rg2 = re.compile(re1+re2+re3+re4+re5+re7,re.IGNORECASE|re.DOTALL)
				m2 = rg2.search(txt)
				print "Poison Grass Height = " + m2.group(2)
#		else:
#			try:
#				sys.stdout.close()
#			except:
#				pass
#			try:
#				sys.stderr.close()
#			except:
#				pass
		#if m:
			#word1=m.group(1)
			#word2=m.group(2)
			#print "("+word1+")"+"("+word2+")"+"\n"	

		#rg = re.compile(re1+re2+re3+re4+re5+re6,re.IGNORECASE|re.DOTALL)
		#m = rg.search(txt)
		#if m:
		#	word1=m.group(1)
		#	float1=m.group(2)
		#	print "("+word1+")"+"("+float1+")"+"\n"
		#	time.sleep(0.9)
			
		#re1='.*?'	# Non-greedy match on filler
		#re2='(?:[a-z][a-z]+)'	# Uninteresting: word
		#re3='.*?'	# Non-greedy match on filler
		#re4='((?:[a-z][a-z]+))'	# Word 1
		#re5='.*?'	# Non-greedy match on filler
		# ---------------------------- Regular expressions section ends
		
		# Ensure the first round go through
		#if (firstLoop):
		#	preVal = "-1.000000" # This is a string
		#	firstLoop = False
			
		# Check if the current value is different to the previous value
		#if (curVal != preVal):
			# Print to the console
			#sys.stdout.write("\rPoison Grass height = " + curVal)
			#sys.stdout.flush()
			# Give time for value to stay still
			#time.sleep(0.9)
			# Set previous value to current value
			#preVal = curVal
			
	except KeyboardInterrupt:
		break
	
	if not txt:
		break
