#!/usr/bin/python
# Created on:   29/08/2013
# Author: 		george
# Credits to txt2re.com for regular expression code section
""" Usage:
Open up terminal and run roscore
Open another terminal and go to the se306_example folder
$ roslaunch se306_example nodeLaunch.launch | python CMD.py
"""

import re
import sys
import time
import subprocess

# Poison Grass
poisonPreVal = "1"
poisonCurVal = "2"

# God
godPreVal = "3"
godCurVal = "4"

while True:
	try:
		# Read line from console and get rid of trash parts, 
		# print important values to console
		txt = sys.stdin.readline()
		
		# Regular expressions section starts --------------------------
		re1='.*?'	# Non-greedy match on filler
		re2='(?:[a-z][a-z]+)'	# Uninteresting: word
		re3='.*?'	# Non-greedy match on filler
		re4='((?:[a-z][a-z]+))'	# Word 1
		re5='.*?'	# Non-greedy match on filler
#		re6='((?:[a-z][a-z]+))'	# Word 2
#		re7='([+-]?\\d*\\.\\d+)(?![-+0-9\\.])'	# Float 2
		# ---------------------------- Regular expressions section ends
		
		rg = re.compile(re1+re2+re3+re4+re5,re.IGNORECASE|re.DOTALL)
		m = rg.search(txt)
		
		if m:
			print "Who is in m.1 value:" + m.group(1)
			if ("PoisonGrassOne" == m.group(1)):
				re7='([+-]?\\d*\\.\\d+)(?![-+0-9\\.])'	# Float 2
				rgPoison = re.compile(re1+re2+re3+re4+re5+re7,re.IGNORECASE|re.DOTALL)
				mPoison = rgPoison.search(txt)
				
				if mPoison:						
					poisonCurVal = mPoison.group(2)
			
					# Check if the current value is different to the previous value
					if (poisonCurVal != poisonPreVal):
						# Print to the console
						sys.stdout.write("\rPoison Grass height = " + poisonCurVal)
						sys.stdout.flush()
						# Give time for value to stay still
						time.sleep(0.9)
						# Set previous value to current value
						poisonPreVal = poisonCurVal
			
			elif ("God" == m.group(1)):
				#print "God is: " + m.group(1)
				re6='((?:[a-z][a-z]+))'	# Word 2
				rgGod = re.compile(re1+re2+re3+re4+re5+re6,re.IGNORECASE|re.DOTALL)
				mGod = rgGod.search(txt)
				
				if mGod:
					# Ensure the first round go through
					if (godLoop):
						preVal = "hello"
						godLoop = False
						
					curVal = mGod.group(2)
			
					# Check if the current value is different to the previous value
					if (curVal != preVal):
						# Print to the console
						sys.stdout.write("\rWeather: " + curVal)
						sys.stdout.flush()
						# Give time for value to stay still
						time.sleep(0.9)
						# Set previous value to current value
						preVal = curVal				
#		if m1:
#			if ("Weather" == m1.group(1)):
#				print "Weather: " + m1.group(2)
#			elif ("PoisonGrass" == m1.group(1)):
#				re7='([+-]?\\d*\\.\\d+)(?![-+0-9\\.])'	# Float 2
#				rg2 = re.compile(re1+re2+re3+re4+re5+re7,re.IGNORECASE|re.DOTALL)
#				m2 = rg2.search(txt)
#				print "Poison Grass Height = " + m2.group(2)
#
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
