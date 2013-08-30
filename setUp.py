#!usr/bin/env python

import subprocess
import time
import os
import signal
import sys

pids = []

def callRoscore():
    terminal1 = ['gnome-terminal']
    terminal1.extend(['-x', 'sh', '-c', '"roscore"'])
    pid1 = subprocess.call(terminal1, stdout=subprocess.PIPE)
    time.sleep(3)
    print "roscore is running..."
    pids.append(pid1)
    # terminal3 = ['gnome-terminal']
    os.system('cd se306_example/src/ && python GodNodeCreator.py')
    print "Ran GodNodeCreator"
    # pid3 = subprocess.call(terminal3)
    # pids.append(pid3)
    wd = os.getcwd()
    callStage(wd)
    callLaunch(wd)
    callTeleop()

def callStage(wd):
    terminal2 = ['gnome-terminal']
    terminal2.extend(['-x', 'sh', '-c', 'rosrun stage stageros '+ wd+'/world/myworld.world'])
    pid2 = subprocess.call(terminal2)
    time.sleep(3)
    print "stage is running..."
    pids.append(pid2)

def callLaunch(wd):
    terminal4 = ['gnome-terminal']
    terminal4.extend(['-x', 'sh', '-c', 'roslaunch '+ wd+'/se306_example/nodeLaunch.launch'])
    pid4 = subprocess.call(terminal4)
    pids.append(pid4)
    print "launch file is running..."

def callTeleop():
    terminal5 = ['gnome-terminal']
    terminal5.extend(['-x', 'sh', '-c', 'roslaunch pr2_teleop teleop_keyboard.launch'])
    pid4 = subprocess.call(terminal5)
    pids.append(pid4)
    print "teleop is running.."

callRoscore()


