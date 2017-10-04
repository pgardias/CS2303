// sim.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef SIM_H_
#define SIM_H_

extern const int min_idle_time;
extern const int max_idle_time;
extern const int min_transaction_time;
extern const int max_transaction_time;

void sim_single_line(int customers, int tellers);
void sim_multiple_lines(int customers, int tellers);
void print();

#endif /* SIM_H_ */
