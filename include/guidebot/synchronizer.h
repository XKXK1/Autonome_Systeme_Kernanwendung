#ifndef SYNCHRONIZER_H
#define SYNCHRONIZER_H

#include "ringQueue.h"
#include "heartbeat.h"

enum class Synchronizer_State{
	Idle,Ready,Error,Driving
};

enum class Synchronizer_Event_Type{
	STOP, HEARTBEAT_IN, HEARTBEAT_OUT
};

struct Synchronizer_Event{
	Synchronizer_Event_Type event_type;
	int argument;
};

class Heartbeat;

class Synchronizer{
private:
	static const int _max_buffer_size = 200;

	Synchronizer_State _state;
	RingQueue<Synchronizer_Event> _buffer;

	Heartbeat *_heartbeat;

	void _heartbeat_in_event();
	void _heartbeat_out_event();
public:
	Synchronizer();
	~Synchronizer();

	void run();
	void addEvent(struct Synchronizer_Event new_event);
	void stop();
	void setup(Heartbeat *heartbeat); 
};


#endif
