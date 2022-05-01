/************************************
 * Programmer: Sam Pickell
 * Date: May 1, 2022
 * 
 * Filename: Day9.cpp
 * Description: Sum the risk levels
 *  		of all low points
 *
 ***********************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Reads input from a file, stores in a vector<vector<int>> heightmap
void get_and_store_input(std::vector<std::vector<int>>& my_heightmap);

// Calculates risk level based on heightmap
int calculate_risk_level(std::vector<std::vector<int>> my_heightmap);

// Comparator between two numbers in the matrix
// matrix = vector<vector<int>>
// i = row number
// j = column number
// x = number to compare to
bool is_the_lesser_number(std::vector<std::vector<int>> matrix, int i, int j, int x);


int main()
{
	std::vector<std::vector<int>> my_heightmap;

	get_and_store_input(my_heightmap);

	std::cout << calculate_risk_level(my_heightmap) << std::endl;

	return 0;
}

void get_and_store_input(std::vector<std::vector<int>>& my_heightmap)
{
	// Read in each line from file
	std::ifstream my_input("input.txt");
	std::string my_line;

	if(my_input.is_open())
	{
		while(std::getline(my_input, my_line))
		{
			// Convert the chars to ints and store in a vector
			std::vector<int> my_line_of_ints;

			for (unsigned int i = 0; i < my_line.length(); i++)
			{
				my_line_of_ints.push_back((my_line.at(i)) - '0');
			
			}
	
			// Add that vector to the vector of vectors
			my_heightmap.push_back(my_line_of_ints);
		}
	}
	
	my_input.close();
}

int calculate_risk_level(std::vector<std::vector<int>> my_heightmap)
{
	// Variables
	int sum = 0;
	int curr_num = 0;
	bool up_bound = false;
	bool down_bound = false;
	bool left_bound = false;
	bool right_bound = false;
	bool is_smallest = true;

	// Examine each int and its adjacent ints to determine if this int is the
	// smallest of the group
	
	for (unsigned int i = 0; i < my_heightmap.size(); i++)
	{
		// Check if we are on the top or bottom rows
		if (i == 0)
		{
			up_bound = true;
		}

		if (i == my_heightmap.size()-1)
		{
			down_bound = true;
		}

		for (unsigned int j = 0; j < my_heightmap.at(i).size(); j++)
		{
			curr_num = my_heightmap.at(i).at(j);

			// Check if we are at the left or right most column
			if (j == 0)
			{
				left_bound = true;
			}

			if (j == my_heightmap.at(i).size() - 1)
			{
				right_bound = true;
			}

			// Examine this int compared to its neighbors 
			
			// Compare above
			if (!up_bound && is_smallest)
			{
				is_smallest = is_the_lesser_number(my_heightmap, i-1, j, curr_num);
			}

			// Compare below
			if (!down_bound && is_smallest)
			{
				is_smallest = is_the_lesser_number(my_heightmap, i+1, j, curr_num);
			}

			// Compare left
			if (!left_bound && is_smallest)
			{
				is_smallest = is_the_lesser_number(my_heightmap, i, j-1, curr_num);
			}

			// Compare right
			if (!right_bound && is_smallest)
			{
				is_smallest = is_the_lesser_number(my_heightmap, i, j+1, curr_num);
			}

			// If after all that the current number is still smallest,
			// add it PLUS its height (i + 1) to the sum
			if (is_smallest)
			{
				sum += (curr_num + 1);
			}


			// Reset left and right bounds and smallest flag
			left_bound = false;
			right_bound = false;
			is_smallest = true;
		}

		// Reset up and down bounds
		up_bound = false;
		down_bound = false;

	}

	return sum;
}

bool is_the_lesser_number(std::vector<std::vector<int>> matrix, int i, int j, int x)
{
	bool is_x_smaller = true;

	
	if (x >= matrix.at(i).at(j))
	{
		is_x_smaller = false;
	}

	return is_x_smaller;
}
