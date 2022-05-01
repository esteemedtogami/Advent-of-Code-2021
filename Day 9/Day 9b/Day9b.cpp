/************************************
 * Programmer: Sam Pickell
 * Date: May 1, 2022
 * 
 * Filename: Day9b.cpp
 * Description: Multiply the sizes of
 *  		the three largest
 *  		basins
 *
 ***********************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

// Reads input from a file, stores in a vector<vector<int>> heightmap
void get_and_store_input(std::vector<std::vector<int>>& my_heightmap);

// Calculates largest basins based on heightmap
int calculate_largest_basins(std::vector<std::vector<int>> my_heightmap);

// Comparator between two numbers in the matrix
// matrix = vector<vector<int>>
// i = row number
// j = column number
// x = number to compare to
bool is_the_lesser_number(std::vector<std::vector<int>> matrix, int i, int j, int x);

// Trace the basin path *recursively*
// matrix = vector<vector<int>>
// coords = vector<tuple<int, int>>
// old_num = int
int trace_basin(std::vector<std::vector<int>> matrix, std::vector<std::tuple<int, int>>coords, int old_num);

// Check to see if the two heights are offset by 1, and add to the vector of tuples if so
void check_offset(std::vector<std::vector<int>> matrix, std::vector<std::tuple<int, int>>& my_tuples,
	          unsigned int i, unsigned int j, int x);


int main()
{
	std::vector<std::vector<int>> my_heightmap;

	get_and_store_input(my_heightmap);

	std::cout << calculate_largest_basins(my_heightmap) << std::endl;

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

int calculate_largest_basins(std::vector<std::vector<int>> my_heightmap)
{
	// Variables
	int total = 0;
	int curr_num = 0;
	int new_basin = 0;
	bool up_bound = false;
	bool down_bound = false;
	bool left_bound = false;
	bool right_bound = false;
	bool is_smallest = true;
	std::vector<int> my_basins{1, 1, 1};

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
			std::vector<std::tuple<int, int>> my_tuples;
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
				check_offset(my_heightmap, my_tuples, i-1, j, curr_num);
			}

			// Compare below
			if (!down_bound && is_smallest)
			{
				is_smallest = is_the_lesser_number(my_heightmap, i+1, j, curr_num);
				check_offset(my_heightmap, my_tuples, i+1, j, curr_num);
			}

			// Compare left
			if (!left_bound && is_smallest)
			{
				is_smallest = is_the_lesser_number(my_heightmap, i, j-1, curr_num);
				check_offset(my_heightmap, my_tuples, i, j-1, curr_num);
			}

			// Compare right
			if (!right_bound && is_smallest)
			{
				is_smallest = is_the_lesser_number(my_heightmap, i, j+1, curr_num);
				check_offset(my_heightmap, my_tuples, i, j+1, curr_num);
			}

			// If after all that the current number is still smallest,
			// calculate basin size
			if (is_smallest)
			{
				new_basin = 1 + trace_basin(my_heightmap, my_tuples, curr_num);
				// Add to largest basin if bigger than one of the three current
				// large basins
				if (new_basin > my_basins.at(2))
				{
					my_basins.at(0) = my_basins.at(1);
					my_basins.at(1) = my_basins.at(2);
					my_basins.at(2) = new_basin;
				}
				else if (new_basin > my_basins.at(1) && new_basin <= my_basins.at(2))
				{
					my_basins.at(0) = my_basins.at(1);
					my_basins.at(1) = new_basin;
				}
				else if (new_basin > my_basins.at(0) && new_basin <= my_basins.at(1))
				{
					my_basins.at(0) = new_basin;
				}

				// Reset basin size
				new_basin = 0;
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

	std::cout << my_basins.at(0) << ", " << my_basins.at(1) << ", " << my_basins.at(2) << std::endl;
	
	total = (my_basins.at(0) * my_basins.at(1) * my_basins.at(2));
	return total;
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

int trace_basin(std::vector<std::vector<int>> matrix, std::vector<std::tuple<int, int>> coords, int old_num)
{
	int sum = 0;
	int new_num = old_num + 1;
	unsigned int coords_og_size = coords.size();
	bool up_bound = false;
	bool down_bound = false;
	bool left_bound = false;
 	bool right_bound = false;
	std::vector<std::tuple<int, int>> new_coords;
	
	// If the current examined number is less than 9 and there are coords to 
	// evaluate, trace it
	if (new_num < 9 && coords.size() > 0)
	{
		// Go through the vector of tuples
		for (unsigned int i = 0; i < coords_og_size; i++)
		{
			sum++;

			std::cout << new_num << " ";

			// Check if we are on the top or bottom rows
			if (static_cast<unsigned int>(std::get<0>(coords.at(i))) == 0)
			{
				up_bound = true;
			}

			if (static_cast<unsigned int>(std::get<0>(coords.at(i))) == matrix.size()-1)
			{
				down_bound = true;
			}

			// Check if we are at the left or right most column
			if (static_cast<unsigned int>(std::get<1>(coords.at(i))) == 0)
			{
				left_bound = true;
			}

			if (static_cast<unsigned int>(std::get<0>(coords.at(i))) == matrix.at(0).size() - 1)
			{
				right_bound = true;
			}


			// Examine this int compared to its neighbors 
			// Compare above
			if (!up_bound)
			{
				check_offset(matrix, new_coords, std::get<0>(coords.at(i)) - 1, 
				     	     std::get<1>(coords.at(i)), new_num);
			}	

			// Compare below
			if (!down_bound)
			{
				check_offset(matrix, new_coords, std::get<0>(coords.at(i)) + 1, 
				     	     std::get<1>(coords.at(i)), new_num);
			}

			// Compare left
			if (!left_bound)
			{
				check_offset(matrix, new_coords, std::get<0>(coords.at(i)), 
				     	     std::get<1>(coords.at(i)) - 1, new_num);
			}

			// Compare right
			if (!right_bound)
			{
				check_offset(matrix, new_coords, std::get<0>(coords.at(i)), 
				 	     std::get<1>(coords.at(i)) + 1, new_num);
			}

		}
	}
	
	if (new_coords.size() > 0)
	{
		sum += trace_basin(matrix, new_coords, new_num);
	}
	
	return sum;
}

void check_offset(std::vector<std::vector<int>> matrix, std::vector<std::tuple<int, int>>& my_tuples,
                  unsigned int i, unsigned int j, int x)
{
	if (i >= 0 && i < matrix.size() && j >=0 && j < matrix.at(i).size())
	{
		if (matrix.at(i).at(j) == x + 1)
		{
			// Check to see if coord already exists
			bool is_in_vector = false;
			for (unsigned int k = 0; k < my_tuples.size(); k++)
			{
				if (static_cast<unsigned int>(std::get<0>(my_tuples.at(k))) == i 
				    && static_cast<unsigned int>(std::get<1>(my_tuples.at(k))) == j)
				{
					is_in_vector = true;
					break;
				}
			}

			if (!is_in_vector)
			{
				my_tuples.push_back(std::make_tuple(i, j));
			}
		}
	}
}
