// eventqueue.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include "event.h"

struct CompareEvents {
	bool operator()(Event *a, Event *b) {
		return (a->getTime() > b->getTime());
	}
};

class EventQueue {
public:
	std::priority_queue<Event *, std::vector<Event *>, CompareEvents> eq;
	EventQueue() {
	}
	void getNext();
	void getNextMultipleLines();
	Event* front();
	void remove();
	void add(Event *a);
};

#endif /* EVENTQUEUE_H_ */
