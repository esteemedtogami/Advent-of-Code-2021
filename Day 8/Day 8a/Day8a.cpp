/*
    Programmer: Sam Pickell
    Date: 4/23/22
    Filename: Day8a.cpp
    Description: Fix the seven segment display
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Read signal data in from file and return total number of 1s, 4s, 7s, and 8s
int read_nums_from_file();

int main()
{
	int num_digits = read_nums_from_file();
	std::cout << num_digits << std::endl;

	return 0;

}

int read_nums_from_file()
{
	// Variables
	std::ifstream my_file("input.txt");
	int num_digits = 0;
	std::string my_chunk;
	bool is_past_bar = false;
	
	if (my_file.is_open())
	{
		// Read in each string, space separated
		while(std::getline(my_file, my_chunk))
		{
			std::stringstream my_stream(my_chunk);

			while(std::getline(my_stream, my_chunk, ' '))
			{
				// For part one, we only care about the strings past the bar
				if(is_past_bar)
				{
					// We only care about incrementing if the string length is:
					// 2 (indicates a 1)
					// 4 (indicates a 4)
					// 3 (indicates a 7)
					// 7 (indicates an 8)
					if (my_chunk.length() == 2 || my_chunk.length() == 4 ||
				    	my_chunk.length() == 3 || my_chunk.length() == 7)
					{
						num_digits++;
						std::cout << my_chunk << " ";
					}

				}

				// If the current string is a bar, update check
				if (my_chunk == "|")
				{
					is_past_bar = true;
				}
			}	
			
			// Reset bar check
			is_past_bar = false;
			std::cout << std::endl;
		}

	}

	my_file.close();

	return num_digits;
}

