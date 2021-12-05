/*
    Programmer: Sam Pickell
    Date: 12/3/21
    Filename: Day2b.cpp
    Description: Find out where the submarine is
                 going based on multiplying position
                 and depth while factoring in aim.
*/

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    // Variables
    int hor_pos = 0, depth = 0, aim = 0;
    std::string my_dir;
    std::string my_val;
    std::ifstream my_file("SubPath.txt");

    if (my_file.is_open())
    {
        // Iterate over each word in the file
        while (my_file >> my_dir)
        {
            my_file >> my_val;

            // Update approriate var based on direction
            if (my_dir == "forward")
            {
                hor_pos += std::stoi(my_val);
                depth += aim * std::stoi(my_val);
            }
            else if (my_dir == "up")
            {
                aim -= std::stoi(my_val);
            }
            else if (my_dir == "down")
            {
                aim += std::stoi(my_val);
            }
        }
    }

    my_file.close();

    std::cout << "Final position: " << hor_pos * depth << std::endl;

    return 0;
}
