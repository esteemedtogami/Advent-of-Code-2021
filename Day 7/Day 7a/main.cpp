/*
    Programmer: Sam Pickell
    Date: 4/22/22
    Filename: main.cpp (for Day7a)
    Description: Blast away the floor part 1
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

// Read position data in from file and return a vector of ints
std::vector<int> read_positions_from_file();

// Takes a vector of positions and determines the minimum amount of fuel needed
// to align the crabs
int calculate_fuel(std::vector<int> hor_pos);


int main()
{
	// Create a vector of initial positions
	std::vector<int> my_hor_pos = read_positions_from_file();
	
	// Calculate the minimum amount of fuel needed for alignment
	int min_fuel = calculate_fuel(my_hor_pos);

	std::cout << min_fuel << std::endl;

	return 0;

}

std::vector<int> read_positions_from_file()
{
	// Variables
	std::ifstream my_file("input.txt");
	std::vector<int> hor_pos;
	std::string my_line;
	
	if (my_file.is_open())
	{
		std::getline(my_file, my_line);

		// Ignore commas
		std::stringstream my_stream(my_line);

		for (int i = 0; my_stream>>i;)
		{
			hor_pos.push_back(i);
			if (my_stream.peek() == ',')
			{
				my_stream.ignore();
			}
		}
	}

	my_file.close();

	return hor_pos;
}

int calculate_fuel(std::vector<int> hor_pos)
{
	// Variables
	
	// Set the initial fuel value to something negative to help properly set min 
	// fuel value
	int fuel = -1;
	// Current element in the vector to try using as the common point
	int cur_pos = -1;
	
	// Sort the vector
	std::sort(hor_pos.begin(), hor_pos.end());

	// Iterate through the vector, using the current element as a meeting point
	for (unsigned int i = 0; i < hor_pos.size(); i++)
	{
		// Check to see if this current horizontal position has already been 
		// considered
		if (cur_pos != hor_pos.at(i))
		{
			cur_pos = hor_pos.at(i);
			
			// Determine the fuel required for each crab to get to this position, and 
			// add it to the total fuel cost
			int this_pos_fuel_cost = 0;

			for (unsigned int j = 0; j < hor_pos.size(); j++)
			{
				this_pos_fuel_cost += std::abs(cur_pos - hor_pos.at(j));
			}
			
			// See if this is the smallest fuel cost so far
			if (fuel == -1 || this_pos_fuel_cost < fuel)
			{
				fuel = this_pos_fuel_cost;
			}
		}
	}

	return fuel;
}
