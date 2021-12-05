/* 
    Programmer: Sam Pickell
    Date: 12/2/21
    Filename: Day1a.cpp
    Description: Count how many times a depth measurement
                 increases from a file.
*/

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    // Variables
    std::ifstream in_file("Depths.txt");
    int count = 0, last_num = -1, curr_num = -1;
    bool is_first_loop = true;
    std::string my_str;

    // Make sure file opens
    if (in_file.is_open())
    {
        // While there are still lines in the file
        while (!in_file.eof())
        {
            // Get the next line of the file
            std::getline(in_file, my_str);
            
            // If this is the first loop, set
            // last_num to the first line in the file.
            // Otherwise set last_num to prev curr_num
            if (is_first_loop)
            {
                last_num = std::stoi(my_str);
                is_first_loop = false;
            }
            else
            {
                last_num = curr_num;
            }

            // Set curr_num to the number at
            // the current line in the file
            // we are at
            curr_num = std::stoi(my_str);

            // If the current number is larger
            // than the last number, track it
            if (curr_num > last_num)
            {
                count++;
            }
        }
    }

    in_file.close();

    std::cout << "Total times there was an increase: " << count << std::endl;

    return 0;

}
