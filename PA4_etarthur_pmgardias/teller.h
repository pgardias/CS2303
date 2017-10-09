// teller.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef TELLER_H_
#define TELLER_H_

#include "event.h"
#include "eventqueue.h"

class Teller: public Event {
public:
	int idle_time;
	int time;
	Teller() {
	}
	Teller(int idle_t) {
		time = 0;
		idle_time = idle_t;
	}

	Event* add();
	int getTime();
	int getIdle();
	void action_single_line();
	void action_multiple_lines();
	void add_time(int transaction_time);
	void process_transaction(int line_number);
	virtual ~Teller() {
	}
private:
};

class TellerQueue: public EventQueue {
public:
	TellerQueue() {
	}
private:
};

#endif /* TELLER_H_ */
