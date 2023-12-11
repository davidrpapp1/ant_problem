/* 
Solution to Q2 of the ant problem. An analytical solution alongside a computational implementation is given in this file.


Question:

An ant leaves its anthill in order to forage for food. 
It moves with the speed of 10cm per second, but it doesn’t know where to go. 
Every second it moves randomly 10cm directly north, south, east or west with equal probability.

What is the average time the ant will reach food 
if it is located only on a diagonal line passing through (10cm, 0cm) and (0cm, 10cm) points?


Analytic solution:

Consider a 5 x 5 grid with each point being discretely mapped, with the origin marked by *, food points by o, 
																					cardinal points by c, and diagonal points by d
      .          .          .
       .         .         .
		  .        .        .
			d - d - c - d - d
			|   |   |   |   |
			d - d - o - d - d
			|   |   |   |   |
	. . .	c - c - * - o - c . . .
			|   |   |   |   |
			d - d - c - d - d
			|   |   |   |   |
			d - d - c - d - d
		  .		  .		  .
	    .			  .		   .
	   .			  .			 .

Unlike q1, it is no longer possible to calculate a finite set of possible move combinations that could occur, as the ant
is effectively unbound. Below are a set of rules the the ant must follow, before finding food:

1. Starting from the origin, it is possible to move one tile to immediately get food [*, o]

2. The ant wanders around, and finds itself on a [d] point nearest to [*] and 1 move away from [o] - [..., d, o]

3. The ant wanders around, and comes back to the origin eventually, which then leads to food [..., *, o]

4. The ant wanders around, and goes to a [c] point 1 move away from the origin [..., c, d, o] OR [..., c, *, o]

The problem is, an infinite amount of these can be listed, as the coordinate space is no longer closed into a box as per Q1.
Therefore, it is possible to generate an infinite number of these possibilities, and thus to get the expectation value given by:
E = \sum (p * x), one would have sum an infinite series of numbers which therefore means n (expected number of seconds):

n = inf
*/


// Computational solution:
// If this file is ran with 1000000 iterations, the iterations never complete, meaning that it is an infinite result.
// If a capacity to number of steps is applied (artificial barrier for the ant at a prohibitively large x and y), the
// mean and S.D scale according to this number, further reinforcing the answer.

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

		// Reset to origin if food is found, or if steps have diverged from origin. Increment number of datapoints
		if((x == 10 && y == 0) || (x == 0 && y == 10) || n == 100000){

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