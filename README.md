SoftEng306-ROSVILLE
=================
## User Guide

This page will provide all the steps for getting this project setup and running

## Prerequisites

### 1. Ubuntu 12.04.3 LTS

This project was created and tested using Ubuntu 12.04.3 LTS, other versions may work but there is no guarantee

The .iso can be found here: http://releases.ubuntu.com/12.04/

### 2. ROS Groovy

For installing ROS from the ROS server, visit: http://www.ros.org/wiki/groovy/Installation.

Follow the guide and make sure you install the `desktop-full package`, i.e run   
`sudo apt-get install ros-groovy-desktop-full python-rosinstall ros-groovy-rqt`

## Setup

1. Open an instance of the terminal (`Ctrl` + `Alt` + `t`)

1. Navigate to the directory of your choice and clone the repository onto your local machine    
`git clone https://github.com/shreya07/softeng306-Rosville.git`   

1. Open .bashrc    
`gedit .bashrc`
or
`vim .bashrc`    
1. Append the following lines to .bashrc    
`source /opt/ros/groovy/setup.bash`    
`export ROS_PACKAGE_PATH=PATH_TO_YOUR_REPO/ros/stacks:$ROS_PACKAGE_PATH`    
**NOTE:** `PATH_TO_YOUR_REPO` must be replaced by the path of the directory in which the repository was cloned in step 1 of the setup process.    
1. Save changes to .bashrc file and close it.   
1. Restart the terminal

While it is not necessary to be appending `source /opt/ros/groovy/setup.bash` to the ".bashrc" file, it is recommended. Alternatively, with every instance of the terminal, the "setup.bash" file must be sourced to use any ROS commands.

## Compilation

1. Open an instance of the terminal (`Ctrl` + `Alt` + `t`)

1. Navigate to the se306_example directory   
`roscd se306_example`

1. Compile se306_example    
`rosmake se306_example`

## Running the project

1. Open an instance of the terminal (`Ctrl` + `Alt` + `t`)

1. Navigate to the se306_example directory   
`roscd se306_example`

1. Run the launcher script
`python setUp.py`

This should start the project in the Stage simulator
