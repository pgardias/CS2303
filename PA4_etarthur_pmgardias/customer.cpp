// customer.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include "sim.h"
#include "customer.h"
#include "teller.h"
#include "event.h"

using namespace std;

extern float simulation_time;
extern int total_time, total_idle_time, times_idle, total_transaction_time,
		tellers;
extern int* customers_in_line;
//extern const int min_transaction_time; // Units in seconds
//extern const int max_transaction_time; // Units in seconds
extern TellerQueue teller_queue;
extern TellerQueue* teller_queues;

Event* Customer::add() {
	float arrival_time = simulation_time * rand() / float(RAND_MAX); // Generate random arrival time
	Event* new_event = new Customer(arrival_time);
	return new_event;
}

int Customer::getTime() {
	return time;
}

void Customer::action_single_line() {
	while (teller_queue.front()->getTime() < this->time) { //TODO: SEG FAULT
		Event* temp_customer = new Event();
		temp_customer = (teller_queue.front()); // Set next customer as temp event and remove him from queue
		teller_queue.remove();
		temp_customer->add_time(temp_customer->getIdle()); // Add idle time to the customers time
		teller_queue.add(temp_customer); // Push it back to the priority queue

		total_idle_time += temp_customer->getIdle(); // Add idle time to total idle time
		times_idle++; // Increment number of times idle
	}
	Event* temp_event = new Event();
	temp_event = teller_queue.front();
	teller_queue.remove();

	int transaction_time = min_transaction_time + rand() % max_transaction_time; // transaction time from 1 second to 500

	temp_event->add_time(transaction_time);

	total_time += (temp_event->getTime() - this->time);
	total_transaction_time += transaction_time;

	teller_queue.add(temp_event);
}

void Customer::action_multiple_lines() {
	int shortest_line = 0; // Index of the shortest line
	int shortest_line_count = 0; // Number of shortest lines

	// Find the index of the smallest line
	for (int i = 0; i < tellers; i++) {
		if (customers_in_line[shortest_line] > customers_in_line[i]) { // find the index of the line
			shortest_line = i;
		}
	}

	// Find how many lines that are shortest
	for (int i = 0; i < tellers; i++) {
		if (customers_in_line[shortest_line] == customers_in_line[i]) {
			shortest_line_count++;
		}
	}

	int random_line = rand() % shortest_line_count;

	for (int i = 0; i < tellers; i++) {
		if (customers_in_line[shortest_line] == customers_in_line[i]) {
			if (random_line != 0) {
				random_line--;
			} else {
				customers_in_line[i]++;
				teller_queues[i].add(this);
				break;
			}
		}
	}
}
