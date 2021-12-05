/*
    Programmer: Sam Pickell
    Date: 12/4/21
    Filename: Day3a.cpp
    Description: Find the power consumption of
                 of the submarine.
                   
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    // Variables
    int gamma_rate = 0, epsilon_rate = 0, curr_bit = 0;
    std::ifstream my_file("PowerData.txt");
    std::string gamma_rate_string, epsilon_rate_string, line_in;
    std::vector<int> my_bits;
    bool is_first_loop = true;

    // Make sure the file opens correctly
    if (my_file.is_open())
    {
        while (!my_file.eof())
        {
            // Get the current line in the file
            std::getline(my_file, line_in);

            // Iterate through the bits in the line
            for (int i = 0; i < line_in.length(); i++)
            {
                // If it's the first loop, push a 0 back to
                // allocate a space for the bit in the vector
                if (is_first_loop)
                {
                    my_bits.push_back(0);
                }

                // Get the currnt bit in the current line.
                // Increase the bit in storage by 1 if the
                // bit is 1, and decrease by 1 if the bit
                // is 0. That way we'll know how to set
                // gamma and epsilon later.
                if (line_in.at(i) == '1')
                {
                    my_bits.at(i)++;
                }
                else
                {
                    my_bits.at(i)--;
                }
            }

            // If it was the first loop, turn it off
            if (is_first_loop)
            {
                is_first_loop = false;
            }
        }
    }

    // Setup gamma and epsilon strings
    for (int i = 0; i < my_bits.size(); i++)
    {
        if (my_bits.at(i) > 0)
        {
            gamma_rate_string.push_back('1');
            epsilon_rate_string.push_back('0');
        }
        else
        {
            gamma_rate_string.push_back('0');
            epsilon_rate_string.push_back('1');
        }
    }

    // Convert string of bits to decimal

    // Create a power of 2 multiplier
    int power_of_two = 1;
    for (int i = gamma_rate_string.length()-1; i >= 0; i--)
    {
        // Gamma rate
        gamma_rate += power_of_two * int(gamma_rate_string.at(i) - '0');

        // Epsilon rate
        epsilon_rate += power_of_two * int(epsilon_rate_string.at(i) - '0');

        // Update the current power of 2 multiplier
        power_of_two *= 2;
    }

    std::cout << "Power consumption: " << gamma_rate * epsilon_rate << std::endl;

    my_file.close();

    return 0;
}
