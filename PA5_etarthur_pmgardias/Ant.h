// Ant.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef ANT_H_
#define ANT_H_

#include "Organism.h"

class Ant: public Organism {
public:
	Ant();
	Ant(int x, int y);
	virtual ~Ant();
	int getTime();
	void move();
	Ant* breed();
	bool isMove(int x, int y);
	void action();
};

#endif /* ANT_H_ */
