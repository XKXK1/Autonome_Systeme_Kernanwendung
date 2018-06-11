#ifndef TOPIC_SUBSCRIBER_H
#define TOPIC_SUBSCRIBER_H

#include "synchronizer.h"
#include "std_msgs/Int32.h"


class TopicSubscriber{
private:
    Synchronizer *_synchronizer; //* pointer to the synchronizer object

    /**
        Callback event being called when a message has been published onto the heartbeat_in topic
        It is used for adding the HEARTBEAT_EVENT to the synchronizer event queue
        
        @param msg the message published onto the topic
    
    */
    void _heartbeat_in(const std_msgs::Int32::ConstPtr& msg);
    void _id_in(const std_msgs::Int32::ConstPtr& msg);

public:
    TopicSubscriber(Synchronizer *synchronizer);
    ~TopicSubscriber();
    void run();
};


#endif

