/*
    Programmer: Sam Pickell
    Date: 4/23/22
    Filename: Day8b.cpp
    Description: Fix the seven segment display part two
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

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
	int total_sum = 0;
	std::string my_chunk;
	bool is_past_bar = false;
	
	if (my_file.is_open())
	{
		// Read in each string, space separated
		while(std::getline(my_file, my_chunk))
		{
			std::stringstream my_stream(my_chunk);
			std::unordered_map<std::string, int> wiring_string_int;
			std::unordered_map<int, std::string> wiring_int_string;
			std::vector<std::string> five_segment, six_segment;
			std::string string_num;

			while(std::getline(my_stream, my_chunk, ' '))
			{
				// Sort the chunk (will make map lookup easier)
				std::sort(my_chunk.begin(), my_chunk.end());

				// If past the bar, start calculating numbers. If before the bar, organize
				// strings based on unique length, or put into vector if non-unique length
				if(is_past_bar)
				{
					// Retrieve the number associated with this string
					int int_string = wiring_string_int.at(my_chunk);

					// Convert to a char and add to our string representation of 
					// the display face
					string_num.push_back('0' + int_string);
				}
				else
				{
					// Organize the strings
					if (my_chunk.length() == 5)
					{
						five_segment.push_back(my_chunk);
					}
					else if (my_chunk.length() == 6)
   					{
						six_segment.push_back(my_chunk);
					}
					else
					{
						// It is a unique string
						switch (my_chunk.length())
						{
							case 2:
								wiring_string_int[my_chunk] = 1;
								wiring_int_string[1] = my_chunk;
								break;
							case 3:
								wiring_string_int[my_chunk] = 7;
								wiring_int_string[7] = my_chunk;
								break;
							case 4:
								wiring_string_int[my_chunk] = 4;
								wiring_int_string[4] = my_chunk;
								break;
							case 7:
								wiring_string_int[my_chunk] = 8;
								wiring_int_string[8] = my_chunk;
								break;
							default:
								break;
						}
					}

				}

				// If the current string is a bar, update check
				if (my_chunk == "|")
				{
					// Determine the remaining string/number pairs 
					
					// For the six length strings
					for (unsigned int i = 0; i < six_segment.size(); i++)
					{
						// Can you fit a 1 and 4 in it?
						std::string probe_1 = wiring_int_string.at(1);
						std::string probe_4 = wiring_int_string.at(4);
	
						if ((six_segment.at(i).find(probe_1.at(0)) != std::string::npos
						   && six_segment.at(i).find(probe_1.at(1)) != std::string::npos)
						&& (six_segment.at(i).find(probe_4.at(0)) != std::string::npos
						   && six_segment.at(i).find(probe_4.at(1)) != std::string::npos
						   && six_segment.at(i).find(probe_4.at(2)) != std::string::npos
						   && six_segment.at(i).find(probe_4.at(3)) != std::string::npos))
						{
							// yes: It's a 9
							wiring_string_int[six_segment.at(i)] = 9;
							wiring_int_string[9] = six_segment.at(i);
						}
						else
						{
							// no: It's a 0 or 6
							// Can you fit a 7 in it?
							std::string probe_7 = wiring_int_string.at(7);
 
                                                 	if (six_segment.at(i).find(probe_7.at(0)) 
									!= std::string::npos
                                                 	&& six_segment.at(i).find(probe_7.at(1)) 
									!= std::string::npos
                                                 	&& six_segment.at(i).find(probe_7.at(2)) 
									!= std::string::npos)
                                                 	{

								// yes: It's a 0
								wiring_string_int[six_segment.at(i)] = 0;
								wiring_int_string[0] = six_segment.at(i);
							}
							else
							{
								// no: It's a 6
								wiring_string_int[six_segment.at(i)] = 6;
								wiring_int_string[6] = six_segment.at(i);
							}
						}
					}

					
					// For the five length strings
					for (unsigned int i = 0; i < five_segment.size(); i++)
					{
						// Can you fit a 7 in it?
						std::string probe_7 = wiring_int_string.at(7);

						if (five_segment.at(i).find(probe_7.at(0)) != std::string::npos
						&& five_segment.at(i).find(probe_7.at(1)) != std::string::npos
						&& five_segment.at(i).find(probe_7.at(2)) != std::string::npos)
						{
							// yes: It's a 3
							wiring_string_int[five_segment.at(i)] = 3;
							wiring_int_string[3] = five_segment.at(i);
						}
						else
						{
							// no: It's a 2 or 5
							// Is it a substring of 6?
							std::string probe_6 = wiring_int_string.at(6);

							if (probe_6.find(five_segment.at(i).at(0)) 
									!= std::string::npos
							&& probe_6.find(five_segment.at(i).at(1)) 
									!= std::string::npos
		   					&& probe_6.find(five_segment.at(i).at(2)) 
									!= std::string::npos
					   		&& probe_6.find(five_segment.at(i).at(3))
                                                                        != std::string::npos
                                                        && probe_6.find(five_segment.at(i).at(4))
                                                                        != std::string::npos)

							{


								// yes: It's a 5
								wiring_string_int[five_segment.at(i)] = 5;
       								wiring_int_string[5] = five_segment.at(i);

							}
							else
							{
								// no: It's a 2
								wiring_string_int[five_segment.at(i)] = 2;
       								wiring_int_string[2] = five_segment.at(i);
							}
						}

					}
					
					// Indicate we're onto the second part of the line
					is_past_bar = true;
				}
			}	
			
			// Reset bar check
			is_past_bar = false;

			// Convert our string to an int and add it to the total
			total_sum += stoi(string_num);
		}

	}

	my_file.close();

	return total_sum;
}

