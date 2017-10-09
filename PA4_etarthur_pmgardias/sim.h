// sim.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef SIM_H_
#define SIM_H_

extern const int min_idle_time;
extern const int max_idle_time;
extern const int min_idle_time_back_in_queue;
extern const int max_idle_time_back_in_queue;

void sim_single_line();
void sim_multiple_lines();
void print();

#endif /* SIM_H_ */
