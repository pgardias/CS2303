To run:
	./PA5 gridSize #doodlebugs #ants #time_steps seed pause

All parameters are optional:
gridSize: integer which is theh number of cells along one dimension of the grid(default: 20)
#doodlebugs: integer, number of doodlebugs to start with(default: 5)
#ants: integer, number of ants to start with(default: 100)
#time_steps: integer, number of steps to simulate(default:1000)
seed: integer used to set random number generator to values known(default:1)
pause: integer, 0 means do not pause, a non negative value means to pause and print every nth step, where n=pause, and a character is inputted to continue(default: 0)

How it Works:
Our implementation of this assignment runs from the top left corner down to the bottom right by first going left to right then up to down. This is the simplest implementation, the grid is looped through
three times, one time to set the movement boolean for all organisms which allows them to move, then it loops through and all the doodlebugs move, as specified in the instructions, doodlebugs move before
ants. Finally the last loop goes and all the ants act. 

Organisms move before they breed, and doodlebugs starve before any other action if applicable. 

Classes:

Organism: An abstract class that defines certain functions and fields for derived classes to have, the prototype of Ant and Doodlebug. The functions are utility functions that are necessary to run
the simulation such as move and breed. The fields are ones that all organisms must have such as age, location in x and y, a boolean isPrey and a boolean canMove.

Ant::Organism: A derived class that implements the abstract organism class, assigns certain fields, such as isPrey to true, and implements functions such as move and breed for the ant specific
polymorphic method. Ants breed every 3 turns, then get reset to age 0 so they can't continually breed.

Doodlebug::Organism: A derived class of organism that implements the abstract functions similar to ant, however doodlebugs can also kill ants. This function is nested in the move function, doodlebugs breed
every 8 turns, and starve every 3 turns they havent eaten. 

Principal Functions:
update(), runs the process described above in how it works, allows every organism to complete it's action if applicable. Works with three groupings of for loops to navigate the 2d array

action(), runs the action process for an organism, for ant, it moves and checks if it can breed if so it attempts to breed.
For doodlebugs, actions first checks if the doodlebug will starve, if so it gets deleted, otherwise it follows the same implementation as ant. 

move(), for ants, moves the ant in a random direction. For doodlebugs, checks if it can kill anything if so it does, otherwise it follows the same as ant.

printBoard(), prints out the board using " " for NULL, "x" for doodlebugs and "o" for ants.

Notes:
In certain simulations such as theh default ones, when all the base ants turn 3, there is an explosion of new ants, and by the time theh doodlebugs can breed, the board is full, therefore they never can,
so to have a simulation that can actually track doodlebugs, try starting with 20 doodlebugs. 

LOOP INVARIANTS:

