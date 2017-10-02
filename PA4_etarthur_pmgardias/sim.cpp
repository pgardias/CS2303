// sim.cpp -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include "sim.h"
#include "event.h"
#include "customer.h"
#include "teller.h"

using namespace std;

const int min_idle_time = 1; // units in sec
const int max_idle_time = 600; // units in sec

int customers, tellers;
int total_time, total_idle_time, times_idle, total_transaction_time;
int* customers_in_line;
float simulation_time, avg_service_time;
unsigned int seed;

Teller t;
Customer c;
Event* sample_teller = &t;
Event* sample_customer = &c;
Event** all_tellers;
Event** all_customers;
TellerQueue teller_queue;
TellerQueue* teller_queues;
EventQueue *event_queue;

int main(int argc, char *argv[]) {
	//ofstream output;
	//output.open("output.txt", ios::out);
	//freopen("a.out", "w", stdout); // TODO
	customers = atoi(argv[1]);
	tellers = atoi(argv[2]);
	simulation_time = atoi(argv[3]); // units in min
	avg_service_time = atoi(argv[4]);

	if (argc == 6) { // seed is provided
		seed = atof(argv[5]);
	} else { // no seed provided
		seed = time(NULL);
	}
	srand(seed);

	////////////////////
	float arrival_time = simulation_time * rand() / float(RAND_MAX); // random arrival times

	//////////////////////////

	printf("Simulation started with following parameters:\n");
	printf("Simulation time - %d\n", simulation_time);
	printf("Transaction time between %5d - %d\n", 1, 500);
	printf("Idle time between %5d - %d\n", min_idle_time, max_idle_time);
	printf("Number of Customers: %5dn", customers);
	printf("Number of Tellers: %d\n", tellers);
	cout << endl << endl << endl << endl << endl;

	sim_single_line(customers, tellers);
	print();

	cout << "Simulation for one line." << endl << endl;

	sim_single_line(customers, tellers);
	print(); // print results for single line sim

	total_time = total_idle_time = times_idle = total_transaction_time = 0;

	cout << endl << endl << endl;
	cout << "Simulation for multiple lines." << endl << endl;

	sim_multiple_lines(customers, tellers);
	print(); // print results for multiple lines sim

	return 0;
} // int main(int argc, char *argv[]);

void sim_single_line(int customers, int tellers) {
	event_queue = new EventQueue();

	all_customers = new Event*[customers];
	all_tellers = new Event*[tellers];

	for (int i = 0; i < customers; i++) { // Generate and initiate new customers
		all_customers[i] = sample_customer->add();
		event_queue->eq.push_back(all_customers[i]); // Insert element at the end of queue
	}

	for (int i = 0; i < tellers; i++) { // Generate and initiate tellers
		all_tellers[i] = sample_teller->add();
		event_queue->eq.push_back(all_tellers[i]); // Insert element at the end of queue
	}

	while (!event_queue->eq.empty()) { // Process the event queue
		event_queue->getNext();
	}

	for (int i = 0; i < customers; i++) {
		delete (all_customers[i]);
	}
	delete (all_customers);
	for (int i = 0; i < tellers; i++) {
		delete (all_tellers[i]);
	}
	delete (all_tellers);

	delete (event_queue);
} // void sim_single_line(int customers, int tellers);

void sim_multiple_lines(int customers, int tellers) {
	teller_queues = new TellerQueue[tellers];
	event_queue = new EventQueue();

	all_customers = new Event*[customers];
	all_tellers = new Event*[tellers];

	for (int i = 0; i < customers; i++) { // Generate and initiate new customers
		all_customers[i] = sample_customer->add();
		event_queue->eq.push_back(all_customers[i]); // Insert element at the end of queue
	}

	for (int i = 0; i < tellers; i++) {  // Generate and initiate tellers
		all_tellers[i] = sample_teller->add();
		all_tellers[i]->lineNumber = i;
		event_queue->eq.push_back(all_tellers[i]); // Insert element at the end of queue
	}
	customers_in_line = new int[tellers];
	for (int i = 0; i < tellers; i++)
		customers_in_line[i] = 0;

	while (!event_queue->eq.empty()) { // Process the event queue
		event_queue->getNextMultipleLines();
	}

	for (int i = 0; i < customers; i++) {
		delete (all_customers[i]);
	}
	delete (all_customers);

	for (int i = 0; i < tellers; i++) {
		delete (all_tellers[i]);
	}

	delete (all_tellers);
} // void sim_multiple_lines(int customers, int tellers);

void print() {
	printf("Average transaction time %7.2f\n",
			double(total_transaction_time) / double(customers));
	printf("Total idle time & times_idle %7d %d\n", total_idle_time,
			times_idle);
	printf("Total time & Average waiting time %7d %.2f\n", total_time,
			double(total_time) / double(customers));
} // void print();
