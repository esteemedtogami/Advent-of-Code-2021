/*
    Programmer: Sam Pickell
    Date: 12/4/21
    Filename: Day3b.cpp
    Description: Verify the life support rating
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    // Variables
    int oxygen = 0, c02 = 0, curr_bit = 0;
    std::ifstream my_file("PowerData.txt");
    std::string oxygen_string, c02_string, line_in;
    std::vector<std::string> oxygen_candidates, c02_candidates;

    // Make sure the file opens correctly
    if (my_file.is_open())
    {
        while (!my_file.eof())
        {
            // Get the current line in the file
            std::getline(my_file, line_in);

            // Save off the line in both candidate vectors
            oxygen_candidates.push_back(line_in);
            c02_candidates.push_back(line_in);
        }
    }

    // Filter out oxygen candidates

    // Set a counter
    int oxygen_counter = oxygen_candidates.at(0).length();

    for (int i = 0; i < oxygen_counter; i++)
    {
        if (oxygen_candidates.size() == 1)
        {
            break;
        }

        std::vector<std::string> temp;
        curr_bit = 0;

        for (int j = 0; j < oxygen_candidates.size(); j++)
        {
            if (oxygen_candidates.at(j).at(i) == '1')
            {
                curr_bit++;
            }
            else
            {
                curr_bit--;
            }
        }

        if (curr_bit >= 0)
        {
            for (int j = 0; j < oxygen_candidates.size(); j++)
            {
                if (oxygen_candidates.at(j).at(i) == '1')
                {
                    temp.push_back(oxygen_candidates.at(j));
                }
            }
        }
        else
        {
            for (int j = 0; j < oxygen_candidates.size(); j++)
            {
                if (oxygen_candidates.at(j).at(i) == '0')
                {
                    temp.push_back(oxygen_candidates.at(j));
                }
            }
        }

        oxygen_candidates = temp;
    }

    // Filter out c02 candidates

    // Set a counter
    int c02_counter = c02_candidates.at(0).length();

    for (int i = 0; i < c02_counter; i++)
    {
        if (c02_candidates.size() == 1)
        {
            break;
        }

        std::vector<std::string> temp;
        curr_bit = 0;

        for (int j = 0; j < c02_candidates.size(); j++)
        {
            if (c02_candidates.at(j).at(i) == '0')
            {
                curr_bit--;
            }
            else
            {
                curr_bit++;
            }
        }

        if (curr_bit >= 0)
        {
            for (int j = 0; j < c02_candidates.size(); j++)
            {
                if (c02_candidates.at(j).at(i) == '0')
                {
                    temp.push_back(c02_candidates.at(j));
                }
            }
        }
        else
        {
            for (int j = 0; j < c02_candidates.size(); j++)
            {
                if (c02_candidates.at(j).at(i) == '1')
                {
                    temp.push_back(c02_candidates.at(j));
                }
            }
        }

        c02_candidates = temp;
    }
    

    // Set the winning candidates
    oxygen_string = oxygen_candidates.at(0);
    c02_string = c02_candidates.at(0);

    // Convert string of bits to decimal

    // Create a power of 2 multiplier
    int power_of_two = 1;
    for (int i = oxygen_string.length() - 1; i >= 0; i--)
    {
        // Gamma rate
        oxygen += power_of_two * int(oxygen_string.at(i) - '0');

        // Epsilon rate
        c02 += power_of_two * int(c02_string.at(i) - '0');

        // Update the current power of 2 multiplier
        power_of_two *= 2;
    }

    std::cout << "Life support rating: " << oxygen * c02 << std::endl;

    my_file.close();

    return 0;
}
