/* 
Solution to Q1 of the ant problem. An analytical solution alongside a computational implementation is given in this file.


Question:

An ant leaves its anthill in order to forage for food. 
It moves with the speed of 10cm per second, but it doesn’t know where to go. 
Every second it moves randomly 10cm directly north, south, east or west with equal probability.

If the food is located on east-west lines 20cm to the north and 20cm to the south, 
as well as on north-south lines 20cm to the east and 20cm to the west from the anthill, 
how long will it take the ant to reach it on average?


Analytic solution:

Consider a 5 x 5 grid with each point being discretely mapped, with the origin marked by *, food points by o, 
																					cardinal points by c, and diagonal points by d

o - o - o - o - o
|   |   |   |   |
o - d - c - d - o
|   |   |   |   |
o - c - * - c - o
|   |   |   |   |
o - d - c - d - o
|   |   |   |   |
o - o - o - o - o

Starting from the origin, there exists a finite combination of moves puts the ant on a food point, namely:

1. From the start of the simulation, moving two points in the same direction in a row (marked as [*, c, o] on the grid)

2. The ant wanders around for n seconds, and ends up at the origin once again, and commits to a [..., *, c, o] move

3. The ant wanders around for n seconds, and ends up on a [c] point from which it moves to the nearest food line [..., c, o]

4. The ant wanders around for n seconds, and ends up at a [d] point, from where it always has 2 choices to meet with the food line.
	It can also be deduced, that no matter what, it will always take the ant 1 extra second to position itself on any of the [d] points,
	as compared to landing on point [c] - [..., c, d, o]

From this, an equation of expected number of steps can be constructed, where the expected number of seconds is the summation
of the above 3 possibilities. Thus, using n as the number of seconds:

Using E = \sum (p * x) where p is the probability of said outcome occuring, and x is the value associated with that outcome,

n = 2 * (1/4) + (n+2) * (1/4) + (n+1) * (1/4) + (n+2) * (1/4)

Rearranging and solving for n yields: n = 4.5
*/


// Computational solution:
// If this file is ran with 1000000 iterations, a result of 4.50s with S.D 2.87s.

// Included libraries
#include <iostream>
#include <random>

int main(){

	// Store 2 ints x and y that represent the ant's current coordinates. If either x or y reaches 20 or -20, the ant has
	// reached a food tile and is reset to the origin (0, 0)
	int x, y = 0;

	// Number of iterations to average accross - number of times the ant will be required to reach food
	int it = 1000000;

	// Action RNG
	std::random_device rd;
   std::mt19937 generator(rd());
   std::uniform_int_distribution<int> distribution(1, 4);
	int RNG;

	// Number of seconds taken per run, each run is stored in a vector
	int n = 0;
	std::vector <int> n_v;

	// Main loop
	do{

		// Add or subtract 10 from either x or y randomly. RNG=1: x-10, RNG=2: x+10, RNG=3: y-10, RNG=4: y+10
		RNG = distribution(generator);
		switch (RNG){
		case 1:
			x -= 10;
			break;

		case 2:
			x += 10;
			break;

		case 3:
			y -= 10;
			break;

		case 4:
			y += 10;
			break;	
		}

		// Record step count
		n++;

		// Reset to origin if the boundaries have been reached. Increment number of datapoints
		if(x <= -20 || x >= 20 || y <= -20 || y >= 20){

			x = 0;
			y = 0;

			n_v.push_back(n);
			n = 0;

			it--;
		}

	} while(it != 0); // Break once number of iterations has reached required amount

	// Output mean seconds
	double m = 0;
	for(int i=0; i<n_v.size(); i++){

		m += n_v[i];

	}
	std::cout << "Mean number of seconds: " << m/n_v.size() << "s" << std::endl;

	// Output standard deviation for number of seconds taken
	double var_sum = 0;
	for(int i=0; i<n_v.size(); i++){

		var_sum += (n_v[i] - (m/n_v.size())) * (n_v[i] - (m/n_v.size()));

	}
	std::cout << "Standard deviation: " << sqrt(var_sum/n_v.size()) << "s" << std::endl;

}