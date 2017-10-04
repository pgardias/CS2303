// event.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef EVENT_H_
#define EVENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <list>

using namespace std;

// Abstract class for teller and customer
class Event {
public:
	int lineNumber;
	Event() {
	}
	virtual Event* add() {
		return NULL;
	}
	virtual int getTime() {
		return (0);
	}
	virtual int getIdle() {
		return (0);
	}
	virtual void action_single_line() {
		return;
	}
	virtual void action_multiple_lines() {
		return;
	}
	virtual void add_time(int transaction_time) {
		return;
	}
	virtual ~Event() {
	}
};

class EventQueue {
public:
	std::list<Event *> eq;
	//std::queue<Event *, std::list<Event *>, cmp> thequeue;
	EventQueue() {
	}
	void getNext();
	void getNextMultipleLines();
	Event* front();
	void remove();
	void add(Event *a);
};

struct compareEvents {
	bool operator()(Event *a, Event *b) {
		return (a->getTime() > b->getTime());
	}
};

#endif /* EVENT_H_ */
