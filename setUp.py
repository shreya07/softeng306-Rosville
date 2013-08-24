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
    print "success1"
    pids.append(pid1)
    callStage()
    callTeleop()

def callStage():
    terminal2 = ['gnome-terminal']
    terminal2.extend(['-x', 'sh', '-c', 'rosrun stage stageros ~/groovy_workspace/sandbox/world/myworld.world'])
    pid2 = subprocess.call(terminal2)
    time.sleep(3)
    print "success2"
    pids.append(pid2)
    callLaunch()
     
def callLaunch():
    terminal3 = ['gnome-terminal']
    terminal3.extend(['-x', 'sh', '-c', 'roslaunch ~/groovy_workspace/sandbox/se306_example/nodeLaunch.launch'])
    pid3 = subprocess.call(terminal3)
    pids.append(pid3)
    print "success3"

def callTeleop():
    terminal4 = ['gnome-terminal']
    terminal4.extend(['-x', 'sh', '-c', 'roslaunch pr2_teleop teleop_keyboard.launch'])
    pid4 = subprocess.call(terminal4)
    pids.append(pid4)
    print "teleop is running.."

callRoscore()


