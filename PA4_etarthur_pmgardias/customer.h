// customer.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include "event.h"

class Customer: public Event {
public:
	int time;
	Customer() {
	}
	Customer(int t) {
		time = t;
	}
	Event* add();
	int getTime();
	void action_single_line();
	void action_multiple_lines();
	virtual ~Customer() {
	}
private:
};

#endif /* CUSTOMER_H_ */
