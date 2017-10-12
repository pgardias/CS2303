// Organism.h -- Eric Arthur (etarthur) & Przemek Gardias (pmgardias)

#ifndef ORGANISM_H_
#define ORGANISM_H_
#include<stdlib.h>
#include "main.h"
class Organism {
public:
	int x,y;
	int age;
	bool isPrey;
	bool canMove;
	virtual int getTime() = 0;
	virtual Organism* breed() = 0;
	virtual void move() = 0;
	virtual bool isMove(int x, int y) = 0;
	virtual void action() = 0;
	virtual ~Organism(){}
	Organism(){
		x = -1;
		y = -1;
		age = 0;
		isPrey = NULL;
		canMove = false;
	}

};

#endif /* ORGANISM_H_ */
