#ifndef TOPIC_SUBSCRIBER_H
#define TOPIC_SUBSCRIBER_H

#include "synchronizer.h"
#include "std_msgs/String.h"


class TopicSubscriber{
private:
    Synchronizer *_synchronizer;

    void _heartbeat_in(const std_msgs::String::ConstPtr& msg);

public:
    TopicSubscriber(Synchronizer *synchronizer);
    ~TopicSubscriber();
    void run();

};


#endif

