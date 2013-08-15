
def generatePublisherDeclaration(robotInfo):
    publisherDeclaration="""
    //Publishers for {0}
ros::Publisher {0}_StageOdom_pub;//To Sheep
ros::Publisher {0}_StageLaser_pub; //To Sheep
ros::Publisher {0}_cmd_vel_pub; //To stage

    """
    
    one=publisherDeclaration.format(robotInfo[1])
    return one

def generateRegisterPublishers(robotInfo):
    RegisterPublisher="""
    //Advertisments for {0}
    {0}_StageOdom_pub = n.advertise<nav_msgs::Odometry>("{0}/odom", 1000); //To {0}
    {0}_StageLaser_pub= n.advertise<sensor_msgs::LaserScan>("{0}/base_scan", 1000); //To {0}
    {0}_cmd_vel_pub=n.advertise<geometry_msgs::Twist>("{1}/cmd_vel", 1000); //To stage
    
    """
    
    two= RegisterPublisher.format(robotInfo[1],robotInfo[0])
    return two
    
def generateSubscriberCallBacksMethods(robotInfo):
    subscriberCallBacksMethods="""
//Callbacks for {0}
void {0}_StageOdom_callback(nav_msgs::Odometry msg){ {0}_StageOdom_pub.publish(msg);}
void {0}_StageLaser_callback(sensor_msgs::LaserScan msg){{0}_StageLaser_pub.publish(msg);}
void {0}_cmd_vel_callback (geometry_msgs::Twist msg){{0}_cmd_vel_pub.publish(msg);}

    """
    
    four= subscriberCallBacksMethods.replace('{0}',robotInfo[1])
    return four

def generateSetupSubscribers(robotInfo):
    SetupSubscribers="""
    //Subscriber for {0}
    ros::Subscriber {0}_StageOdo_sub = n.subscribe<nav_msgs::Odometry>("{1}/odom", 1000, {0}_StageOdom_callback);
    ros::Subscriber {0}_StageLaser_sub = n.subscribe<sensor_msgs::LaserScan>("{1}/base_scan", 1000, {0}_StageLaser_callback);
    ros::Subscriber {0}_cmd_vel = n.subscribe<geometry_msgs::Twist>("{0}/cmd_vel", 1000,{0}_cmd_vel_callback);
    
    """
    
    three= SetupSubscribers.format(robotInfo[1],robotInfo[0])
    return three





print('Starting Creation of God')
##PublisherDeclaration

#{0} Robot Node
#{1} e.g robot_0}
print('Reading config file....')
configFile = open('NodeConfiguration.txt')

Nodes=[]
for line in configFile:
    if len(line)==1:
        continue
    
  
    param = line.strip().split(',')
    #print "This is the param "
    #print param
    tuple1=(param[0],param[1])
    Nodes.append(tuple1)
    
print 'Nodes:...'
print Nodes


template= open('GodNodeTemplate.cpp','r')
#print(f)

contents = template.read()
#print contents

#set up publisher declaration. 
## for each tuple

PublisherDeclaration =""
RegisterPublisher= ""
SetupSubscribers = ""
subscriberCallBacksMethods= ""

for robot in Nodes:
    PublisherDeclaration = PublisherDeclaration+ generatePublisherDeclaration(robot)
    RegisterPublisher= RegisterPublisher+ generateRegisterPublishers(robot)
    SetupSubscribers = SetupSubscribers+ generateSetupSubscribers(robot)
    subscriberCallBacksMethods= subscriberCallBacksMethods+ generateSubscriberCallBacksMethods(robot)



#result=contents.format(PublisherDeclaration=one,RegisterPublisher=two,SetupSubscribers=three,subscriberCallBacksMethods='s')
result=contents

result=result.replace('//PublisherDeclaration',PublisherDeclaration)
result=result.replace('//RegisterPublisher',RegisterPublisher)
result=result.replace('//SetupSubscribers',SetupSubscribers)
result=result.replace('//subscriberCallBacksMethods',subscriberCallBacksMethods)



out = open ('GodNode.cpp','w')

out.write(result) 
out.flush()
 
print 'Modifications over. Written changes to GodNode.cpp'

   

        