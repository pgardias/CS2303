// event.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include "event.h"

void EventQueue::getNext() { // Remove event and execute action even which is appropriate for that event
	Event *temp_event = eq.front(); // Set pointer to first element
	eq.pop_front(); // Remove first element
	temp_event->action_single_line();
}

void EventQueue::getNextMultipleLines() { // Remove event and execute action even which is appropriate for that event
	Event *temp_event = eq.front(); // Set pointer to first element
	eq.pop_front(); // Remove first element
	temp_event->action_multiple_lines();
}

Event* EventQueue::front() {
	return eq.front(); // get first element
}

void EventQueue::remove() {
	eq.pop_front(); // remove first element
}

void EventQueue::add(Event *a) {
	eq.push_back(a); // add element to end of queue
}
