// eventqueue.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "eventqueue.h"
#include "event.h"

void EventQueue::getNext() { // Remove event and execute action even which is appropriate for that event
	Event* temp_event = eq.top();
	eq.pop();
	temp_event->action_single_line();
}

void EventQueue::getNextMultipleLines() { // Remove event and execute action even which is appropriate for that event
	Event* temp_event = eq.top();
	eq.pop();
	temp_event->action_multiple_lines();
}

Event* EventQueue::front() {
	return eq.top(); // get first element
}

void EventQueue::remove() {
	eq.pop(); // remove first element
}

void EventQueue::add(Event *event) {
	eq.push(event); // add element to end of queue
}

