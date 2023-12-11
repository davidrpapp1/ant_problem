/* 
Solution to Q3 of the ant problem. A computational implementation is given in this file.


Question:

An ant leaves its anthill in order to forage for food. 
It moves with the speed of 10cm per second, but it doesn’t know where to go. 
Every second it moves randomly 10cm directly north, south, east or west with equal probability.

Can you write a program that comes up with an estimate of average time to find food, 
for any closed boundary around the anthill? What would be the answer if food is located outside an area defined by
((x – 2.5cm) / 30cm)^2 + ((y – 2.5cm) / 40cm)^2 < 1,
in coordinate system where the anthill is located at (x = 0cm, y = 0cm)?
*/


// Computational solution:
// If this file is ran with 1000000 iterations, a result of 14.00s with S.D 9.67s.

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

	// Boolean to check if within food boundary or not
	double coords = 0;

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

		// Equation of food boundary
		coords = ( ((x-2.5)/30) * ((x-2.5)/30) ) + ( ((y-2.5)/40) * ((y-2.5)/40) );

		// Reset to origin if the boundaries have been reached. Increment number of datapoints
		if(coords >= 1){

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