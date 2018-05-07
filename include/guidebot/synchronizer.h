#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include "ringQueue.h"
#include "heartbeat.h"
#include "driver.h"
#include "topicPublisher.h"

enum class Synchronizer_State{
	IDLE,READY,ERROR,DRIVING
};

enum class Synchronizer_Event_Type{
	STOP, HEARTBEAT_IN, HEARTBEAT_TRIGGER
};

struct Synchronizer_Event{
	Synchronizer_Event_Type event_type;
	int argument;
};

class Heartbeat;
class Driver;

class Synchronizer{
private:
	static const int _max_buffer_size = 200;

	Synchronizer_State _state;
	RingQueue<Synchronizer_Event> _buffer;

	Heartbeat *_heartbeat;
	Driver *_driver;
	TopicPublisher *_publisher;

	void _heartbeat_in_event(); //triggers a heart beat when incoming message is heartbeat_in
	void _heartbeat_out_event();
public:
	Synchronizer();
	~Synchronizer();

	void run();
	void addEvent(struct Synchronizer_Event new_event); // add incoming event 
	void stop();
	void setup(Heartbeat *heartbeat, Driver* driver, TopicPublisher* publisher); 
};


#endif
