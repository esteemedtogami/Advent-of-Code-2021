/*
    Programmer: Sam Pickell
    Date: 12/2/21
    Filename: Day1b.cpp
    Description: Count how many times a depth measurement
                 increases from a file based on two sets
                 of sliding windows.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    // Variables
    std::ifstream in_file("Depths.txt");
    std::vector<int> window_1, window_2;
    int incr_counter = 0, window_counter = 0;
    std::string my_str;

    // Make sure file opens
    if (in_file.is_open())
    {
        // While there are still lines in the file
        while (!in_file.eof())
        {
            // Get the number from the current line in the file
            std::getline(in_file, my_str);
            window_counter++;

            // Set up the two windows
            if (window_counter < 4)
            {
                window_1.push_back(std::stoi(my_str));
                
                if (window_counter > 1)
                {
                    window_2.push_back(std::stoi(my_str));
                }
            }
            else
            {
                window_2.push_back(std::stoi(my_str));

                // Sum the values and compare
                if ((window_2.at(0) + window_2.at(1) + window_2.at(2)) > (window_1.at(0) + window_1.at(1) + window_1.at(2)))
                {
                    incr_counter++;
                }

                // Clean up and get ready for the next compare
                window_1 = window_2;
                window_2.pop_back();
                window_2.pop_back();
                window_2.pop_back();
                window_2.push_back(window_1.at(1));
                window_2.push_back(window_1.at(2));
                window_counter = 3;
            }
        }
    }

    in_file.close();

    std::cout << "Total times there was an increase: " << incr_counter << std::endl;

    return 0;

}
