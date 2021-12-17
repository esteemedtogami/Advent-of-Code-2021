/*
    Programmer: Sam Pickell
    Date: 12/7/21
    Filename: Day6a.cpp
    Description: Model lanturnfish repopulatioon
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#define TOTAL_DAYS 80

int main()
{
    // Variables
    std::ifstream my_file("Fish.txt");
    std::vector<int> fish_pop;
    std::string my_line;

    if (my_file.is_open())
    {
        std::getline(my_file, my_line);

        // Ignore commas
        std::stringstream my_stream(my_line);

        for (int i = 0; my_stream >> i;)
        {
            fish_pop.push_back(i);
            if (my_stream.peek() == ',')
            {
                my_stream.ignore();
            }
        }
    }

    my_file.close();

    for (int i = 0; i < TOTAL_DAYS; i++)
    {
        // Store all the baby fish
        std::vector<int> baby_fish;

        // Iterate over the list of fish
        for (int j = 0; j < fish_pop.size(); j++)
        {
            if (fish_pop.at(j) == 0)
            {
                // Reset fertility
                fish_pop.at(j) = 6;

                // Add a baby
                baby_fish.push_back(8);

            }
            else
            {
                // Decrement fertility
                fish_pop.at(j)--;
            }
        }

        // Append babies to list
        for (int j = 0; j < baby_fish.size(); j++)
        {
            fish_pop.push_back(baby_fish.at(j));
        }
    }

    std::cout << fish_pop.size() << std::endl;

    return 0;
}

