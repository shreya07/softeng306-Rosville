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

# God
godPreVal = "?"
godCurVal = "!"
godNewLine = False

# Grass
grassPreVal = "?"
grassCurVal = "!"
grassNewLine = False

# Poison Grass
poisonPreVal = "?"
poisonCurVal = "!"
poisonNewLine = True

# Farmer
farmerPreVal = "?"
farmerCurVal = "!"
farmerNewLine = False

sys.stdout.write("==================================================\n\n")

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
			
			# Check the node name as 'GodNode'
			if ("GodNode" == m.group(1)):
				re6='((?:[a-z][a-z]+))'	# Word 2
				rgGod = re.compile(re1+re2+re3+re4+re5+re6,re.IGNORECASE|re.DOTALL)
				mGod = rgGod.search(txt)
				
				if mGod:
					godCurVal = mGod.group(2)
			
					# Check if the current value is different to the previous value
					if (godCurVal != godPreVal):
						
						# Start weather in a new line
						if (godNewLine):
							sys.stdout.write("\n")
							sys.stdout.flush()
							time.sleep(1)
							
							grassNewLine = False # Grass turn
							poisonNewLine = True
							godNewLine = False
							farmerNewLine = False
						else:
							sys.stdout.write("\rWeather: " + godCurVal)
							sys.stdout.flush()
							time.sleep(1)
							godPreVal = godCurVal	


			# Check the node name as 'GrassOne'
			elif ("GrassOne" == m.group(1)):
				re7='([+-]?\\d*\\.\\d+)(?![-+0-9\\.])'	# Float 2
				rgGrass = re.compile(re1+re2+re3+re4+re5+re7,re.IGNORECASE|re.DOTALL)
				mGrass = rgGrass.search(txt)
				
				if mGrass:						
					grassCurVal = mGrass.group(2)
			
					# Check if the current value is different to the previous value
					if (grassCurVal != grassPreVal):
						
						# Print Grass info on a new line
						if (grassNewLine):
							sys.stdout.write("\n")
							sys.stdout.flush()
							time.sleep(1)
							
							grassNewLine = False
							poisonNewLine = False
							farmerNewLine = True 			
							godNewLine = False				
							
						# Grass is already on a new line
						else:
							sys.stdout.write("\rGrass height = " + grassCurVal)
							sys.stdout.flush()
							time.sleep(1)
							grassPreVal = grassCurVal
							
			
			# Check the node name as 'PoisonGrassOne'
			elif ("PoisonGrassOne" == m.group(1)):
				re7='([+-]?\\d*\\.\\d+)(?![-+0-9\\.])'	# Float 2
				rgPoison = re.compile(re1+re2+re3+re4+re5+re7,re.IGNORECASE|re.DOTALL)
				mPoison = rgPoison.search(txt)
				
				if mPoison:						
					poisonCurVal = mPoison.group(2)
			
					# Check if the current value is different to the previous value
					if (poisonCurVal != poisonPreVal):
						
						# Print PoisonGrass on a new line
						if (poisonNewLine):
							sys.stdout.write("\n")
							sys.stdout.flush()
							time.sleep(1)
							
							grassNewLine = True 
							poisonNewLine = False
							farmerNewLine = False # Farmer turn
							godNewLine = False
							
						# PoisonGrass is already on a new line
						else:
							sys.stdout.write("\rPoison Grass height = " + poisonCurVal)
							sys.stdout.flush()
							time.sleep(1)
							poisonPreVal = poisonCurVal


			# Check the node name as 'Farmer'
			elif ("Farmer" == m.group(1)):
				re7='([+-]?\\d*\\.\\d+)(?![-+0-9\\.])'	# Float 2
				rgFarmer = re.compile(re1+re2+re3+re4+re5+re7,re.IGNORECASE|re.DOTALL)
				mFarmer = rgFarmer.search(txt)
				
				if mFarmer:						
					farmerCurVal = mFarmer.group(2)
			
					# Check if the current value is different to the previous value
					if (farmerCurVal != farmerPreVal):
						
						# Print Farmer on a new line
						if (farmerNewLine):
							sys.stdout.write("\n")
							sys.stdout.flush()
							time.sleep(1)
							
							grassNewLine = False # Grass turn
							poisonNewLine = False
							farmerNewLine = False
							godNewLine = True # God turn
							
						# Farmer is already on a new line
						else:
							sys.stdout.write("\rFarmer's money = " + farmerCurVal)
							sys.stdout.flush()
							time.sleep(1)
							farmerPreVal = farmerCurVal
			
	except KeyboardInterrupt:
		break
	
	if not txt:
		break
