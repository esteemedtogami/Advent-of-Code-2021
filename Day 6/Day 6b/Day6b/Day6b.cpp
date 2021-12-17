/*
    Programmer: Sam Pickell and Abby Luo
    Date: 12/7/21
    Filename: Day6b.cpp
    Description: Model lanturnfish repopulatioon
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#define TOTAL_DAYS 256

int main()
{
    // Variables
    long long result = 0;
    std::ifstream my_file("Fish.txt");
    std::vector<int> fish_pop; 
    std::vector<long long> pop_list;
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

    for (int k = 0; k < 7; k++)
    {
        std::vector<int> this_fish_pop;
        this_fish_pop.push_back(k);
        long long this_pop_size = 1;
        for (int i = 0; i < TOTAL_DAYS; i++)
        {
            // Store all the baby fish
            std::vector<int> baby_fish;

            // Iterate over the list of fish
            for (int j = 0; j < this_fish_pop.size(); j++)
            {
                if (this_fish_pop.at(j) == 0)
                {
                    // Reset fertility
                    this_fish_pop.at(j) = 6;

                    // Add a baby
                    baby_fish.push_back(8);
                    this_pop_size++;

                }
                else
                {
                    // Decrement fertility
                    this_fish_pop.at(j)--;
                }
            }

            // Append babies to list
            for (int j = 0; j < baby_fish.size(); j++)
            {
                this_fish_pop.push_back(baby_fish.at(j));
            }
        }
        pop_list.push_back(this_pop_size);

        std::cout << k << ": " << pop_list.at(k) << std::endl;
    }

    std::cout << std::endl;
    
    for (int k = 0; k < fish_pop.size(); k++)
    {
        result += pop_list.at(fish_pop.at(k));
    }
    

    std::cout << "Result: " << result << std::endl;

    return 0;
}