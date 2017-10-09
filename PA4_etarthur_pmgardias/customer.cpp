// customer.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <list>
#include "sim.h"
#include "customer.h"
#include "teller.h"
#include "event.h"
#include "eventqueue.h"

using namespace std;

extern float simulation_time, avg_service_time;
extern int total_time, total_idle_time, times_idle, total_transaction_time,
		tellers;
extern double max_time_until_service;
extern int* customers_in_line;
extern list<int> time_in_bank;
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
	float service_time = 2 * avg_service_time * rand() / float(RAND_MAX);

	while (teller_queue.front()->getTime() < this->time) {
		Event* temp_customer = new Event();
		temp_customer = (teller_queue.front()); // Set next customer as temp event and remove him from queue
		teller_queue.remove();
		temp_customer->add_time(temp_customer->getIdle()); // Add idle time to the customers time
		teller_queue.add(temp_customer); // Push it back to the priority queue

		total_idle_time += temp_customer->getIdle(); // Add idle time to total idle time
		time_in_bank.push_back(temp_customer->getIdle());
		times_idle++; // Increment number of times idle
	}
	Event* temp_event = new Event();
	temp_event = teller_queue.front();
	teller_queue.remove();

	double wait_time = temp_event->getTime() - this->time;
	temp_event->add_time(service_time);

	if (wait_time > max_time_until_service) {
		max_time_until_service = wait_time;
	}
	total_time += temp_event->getTime() - this->time;
	total_transaction_time += service_time;

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

	int random_shortest_line = rand() % shortest_line_count;

	for (int i = 0; i < tellers; i++) {
		if (customers_in_line[shortest_line] == customers_in_line[i]) {
			if (random_shortest_line != 0) {
				random_shortest_line--;
			} else {
				customers_in_line[i]++;
				teller_queues[i].add(this);
				break;
			}
		}
	}
}
