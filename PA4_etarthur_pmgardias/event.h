// event.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef EVENT_H_
#define EVENT_H_

#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Abstract class for teller and customer
class Event {
public:
	int line;
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

#endif /* EVENT_H_ */
