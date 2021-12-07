/*
    Programmers: Sam Pickell and Abby Luo
    Date: 12/6/21
    Filename: Day5a.cpp
    Description: Counting vertical and horizonal
                 line segments. Report how many
                 spaces are used > twice.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
    // Variables
    int result = 0, biggest_number = 0;
    std::ifstream my_file("Lines.txt");
    std::vector<std::vector<int>> my_grid;
    std::vector<std::vector<int>> my_input;
    std::string my_line;

    // Make sure the file reads in
    if (my_file.is_open())
    {
        while (!my_file.eof())
        {
            // Use "peek" to check for and filter out stuff we don't want
        /* https://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring */
            std::getline(my_file, my_line);
            std::stringstream my_stringstream(my_line);
            std::vector<int> my_line_of_nums;

            for (int i = 0; my_stringstream >> i;)
            {
                my_line_of_nums.push_back(i);
                if (i > biggest_number)
                {
                    biggest_number = i;
                }
                if (my_stringstream.peek() == ',')
                {
                    my_stringstream.ignore();
                }
                else if (my_stringstream.peek() == ' ')
                {
                    my_stringstream.ignore();
                    my_stringstream.ignore();
                    my_stringstream.ignore();
                    my_stringstream.ignore();
                }
            }

            my_input.push_back(my_line_of_nums);
        }
    }

    my_file.close();

    // Make grid of zeros
    for (int i = 0; i <= biggest_number; i++)
    {
        std::vector<int> my_zeros;
        for (int j = 0; j <= biggest_number; j++)
        {
            my_zeros.push_back(0);
        }

        my_grid.push_back(my_zeros);
    }

    // Update grid based on lines
    for (int i = 0; i < my_input.size(); i++)
    {
        // Remember to consider ONLY horizontal and
        // vertical lines
        if (my_input.at(i).at(0) == my_input.at(i).at(2))
        {
            // Horizontal
            
            if (my_input.at(i).at(1) < my_input.at(i).at(3))
            {
                // y is ascending
                for (int j = my_input.at(i).at(1); j <= my_input.at(i).at(3); j++)
                {
                    // my_input.at(i).at(0) and my_input.at(i).at(2)
                    // are the SAME value (y value) 
                    my_grid.at(j).at(my_input.at(i).at(0))++;
                }
            }
            else
            {
                // y is decending
                for (int j = my_input.at(i).at(1); j >= my_input.at(i).at(3); j--)
                {
                    // my_input.at(i).at(0) and my_input.at(i).at(2)
                    // are the SAME value (y value) 
                    my_grid.at(j).at(my_input.at(i).at(0))++;
                }
            }
        }
        else if (my_input.at(i).at(1) == my_input.at(i).at(3))
        {
            // Vertical case

            if (my_input.at(i).at(0) < my_input.at(i).at(2))
            {
                // x is ascending
                for (int j = my_input.at(i).at(0); j <= my_input.at(i).at(2); j++)
                {
                    // my_input.at(i).at(1) and my_input.at(i).at(3)
                    // are the SAME value (x value)
                    my_grid.at(my_input.at(i).at(1)).at(j)++;
                }
            }
            else
            {
                // x is decending
                for (int j = my_input.at(i).at(0); j >= my_input.at(i).at(2); j--)
                {
                    // my_input.at(i).at(1) and my_input.at(i).at(3)
                    // are the SAME value (x value) 
                    my_grid.at(my_input.at(i).at(1)).at(j)++;
                }
            }
        }
        else
        {
            // Diagonal case, igonre for now
        }
    }

    for (int i = 0; i < my_grid.size(); i++)
    {
        for (int j = 0; j < my_grid.at(i).size(); j++)
        {
            if (my_grid.at(i).at(j) >= 2)
            {
                result++;
            }
        }
    }

    std::cout << result << std::endl;

    return 0;
}
