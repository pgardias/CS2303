// teller.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "sim.h"
#include "teller.h"
#include "event.h"

using namespace std;

//extern const int min_idle_time; // units in sec
//extern const int max_idle_time; // units in sec
extern float simulation_time;
extern float avg_service_time;
extern int total_time, total_idle_time, times_idle, total_transaction_time,
		tellers;
extern int* customers_in_line;
extern TellerQueue teller_queue;
extern TellerQueue* teller_queues;
extern EventQueue *event_queue;

Event* Teller::add() {
	int idle_time = min_idle_time + rand() % max_idle_time;
	Event* new_event = new Teller(idle_time);
	return new_event;
}

int Teller::getTime() {
	return time;
}

int Teller::getIdle() {
	return idle_time;
}

void Teller::action_single_line() {
	teller_queue.eq.push_back(this); // Add to end of teller queue
}

void Teller::action_multiple_lines() {
	if (customers_in_line[lineNumber] > 0) { // If there are customers in the teller's line
		process_transaction(lineNumber);
	} else { // No customers in the teller's line
		bool customers_in_other_lines = false;
		for (int i = 0; i < tellers; i++) {
			if (customers_in_line[i] != 0) {
				customers_in_other_lines = true;
			}
		}

		if (customers_in_other_lines == true) { // There are customers in other lines to serve
			int longest_line = 0;
			int num_of_longest_lines = 0;

			// Determine which line has maximum number of customers to take the next customer from
			for (int i = 0; i < tellers; i++) {
				if (customers_in_line[longest_line] < customers_in_line[i]) {
					longest_line = i;
				}
			}

			for (int i = 0; i < tellers; i++) {
				if (customers_in_line[longest_line] == customers_in_line[i]) {
					num_of_longest_lines++;
				}
			}

			int random_line = rand() % num_of_longest_lines; // Choose a random line for the customer to go to

			for (int i = 0; i < tellers; i++) {
				if (customers_in_line[longest_line] == customers_in_line[i]) {
					if (random_line != 0) {
						random_line--;
					} else {
						process_transaction(i); // Process transaction at that line
						break;
					}
				}
			}
		} else { // No customers in other lines to serve
			this->add_time(this->getIdle()); // Teller goes idle
			total_idle_time += this->getIdle(); // Increment idle time counter by time idle
			times_idle++; // Increment idle counter

			if (this->getTime() <= simulation_time) {
				event_queue->add(this);
			}
		}
	}
}

void Teller::add_time(int transaction_time) { // Add transaction time to total time of teller
	this->time += transaction_time;
}

void Teller::process_transaction(int line_number) {
	Event* temp_event = teller_queues[line_number].front(); // Get next event as a temp event before removing it
	teller_queues[line_number].remove(); // Remove event from queue
	customers_in_line[line_number]--; // Decrease num of customers in line by 1

	float service_time = 2 * avg_service_time * rand() / float(RAND_MAX); // Random service times
	add_time(service_time);

	total_time += (getTime() - temp_event->getTime());
	total_transaction_time += service_time;

	event_queue->add(this);
}
