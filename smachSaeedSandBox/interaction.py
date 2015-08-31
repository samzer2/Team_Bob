import rospy
import random

def intFun():

    # psuedo Interaction
    waitTime = random.randint(1,5)
    rospy.loginfo( 'Interaction for %s' % waitTime + ' seconds')
    rate = rospy.Rate(1./waitTime) #hz
    rate.sleep()
    
    success = random.randint(0,4) # 80% chance of success
    if success:
        rospy.loginfo( 'Interaction succeeded' )
        return 'success'
    elif not(success):
        rospy.loginfo( 'Interaction failed' )
        return 'failure'

