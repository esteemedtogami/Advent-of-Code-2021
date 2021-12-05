/*
    Programmer: Sam Pickell
    Date: 12/5/21
    Filename: Day4b.cpp
    Description: Let the giant squid win.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


// Sum up the values of
// the winning board, multiply the sum by the
// winning number, store in result,
// and quit the loop.
int calc_result(int winning_num, std::vector<std::vector<int>> winning_board);

int main()
{
    // Variables
    int result = 0, remaining_boards = 0;
    std::ifstream my_file("Bingo.txt");
    std::string curr_line;
    std::vector<std::vector<std::vector<int>>> bingo_board;
    std::vector<int> curr_number;
    std::vector<int> winning_vector(5, 0);
    bool found_a_winner = false;

    // Make sure file opens
    if (my_file.is_open())
    {
        // Use "peek" to check for and filter out comma
        /* https://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring */
        std::getline(my_file, curr_line);
        std::stringstream my_stringstream(curr_line);

        for (int i = 0; my_stringstream >> i;)
        {
            curr_number.push_back(i);
            if (my_stringstream.peek() == ',')
            {
                my_stringstream.ignore();
            }
        }

        // Eat the whitespace line
        std::getline(my_file, curr_line);

        // Populate the bingo board
        while (!my_file.eof())
        {
            std::vector<std::vector<int>> curr_bingo_board;
            // Bingo board is known to be 5x5
            for (int i = 0; i < 5; i++)
            {
                // Read in space separated numbers
                /* https://stackoverflow.com/questions/10130432/parsing-space-delimited-numbers-from-getline */
                std::vector<int> bingo_line(5, 0);
                std::getline(my_file, curr_line);
                std::istringstream(curr_line) >> bingo_line.at(0) >> bingo_line.at(1) >> bingo_line.at(2)
                    >> bingo_line.at(3) >> bingo_line.at(4);

                // Push the line to the current bingo board
                curr_bingo_board.push_back(bingo_line);
            }

            // Add board to bingo board
            bingo_board.push_back(curr_bingo_board);

            // Eat the whitespace line
            std::getline(my_file, curr_line);
        }
    }

    my_file.close();

    // Track the remaining number of boards
    remaining_boards = bingo_board.size();
    std::vector<int> vec_remaining_boards(bingo_board.size(), 0);

    // Play Bingo
    for (int i = 0; i < curr_number.size(); i++)
    {
        // Check each board in the container of boards
        for (int j = 0; j < bingo_board.size(); j++)
        {
            // Check each row
            for (int k = 0; k < bingo_board.at(j).size(); k++)
            {
                // Check each element and mark any matches (ie change the number to 0)
                for (int l = 0; l < bingo_board.at(j).at(k).size(); l++)
                {
                    if (bingo_board.at(j).at(k).at(l) == curr_number.at(i))
                    {
                        bingo_board.at(j).at(k).at(l) = 0;
                    }
                }

                // Check to see if we get bingo (this row)
                    // If we do, calculate the result
                if (bingo_board.at(j).at(k) == winning_vector)
                {
                    // See if this is the last board to get a solution
                    if (remaining_boards == 1 && vec_remaining_boards.at(j) == 0)
                    {
                        found_a_winner = true;
                        result = calc_result(curr_number.at(i), bingo_board.at(j));
                        break;
                    }
                    else
                    {
                        if (vec_remaining_boards.at(j) == 0)
                        {
                            vec_remaining_boards.at(j) = 1;
                            remaining_boards--;
                        }
                    }
                    
                }
            }

            if (found_a_winner)
            {
                break;
            }
            else
            {
            // Check to see if we get bingo (column)
                // If we do, calculate the result
                for (int k = 0; k < 5; k++)
                {
                    if (('0' + bingo_board.at(j).at(0).at(k)) == '0' &&
                        ('0' + bingo_board.at(j).at(1).at(k)) == '0' &&
                        ('0' + bingo_board.at(j).at(2).at(k)) == '0' &&
                        ('0' + bingo_board.at(j).at(3).at(k)) == '0' &&
                        ('0' + bingo_board.at(j).at(4).at(k)) == '0')
                    {
                        // See if this is the last board to get a solution
                        if (remaining_boards == 1 && vec_remaining_boards.at(j) == 0)
                        {
                            found_a_winner = true;
                            result = calc_result(curr_number.at(i), bingo_board.at(j));
                            break;
                        }
                        else
                        {
                            if (vec_remaining_boards.at(j) == 0)
                            {
                                vec_remaining_boards.at(j) = 1;
                                remaining_boards--;
                            }
                        }
                    }
                }
            }
        }

        if (found_a_winner)
        {
            break;
        }
    }

    std::cout << "Winning score: " << result << std::endl;

    return 0;
}

int calc_result(int winning_num, std::vector<std::vector<int>> winning_board)
{
    int sum = 0;

    for (int i = 0; i < winning_board.size(); i++)
    {
        for (int j = 0; j < winning_board.at(i).size(); j++)
        {
            sum += winning_board.at(i).at(j);
        }
    }

    return sum * winning_num;
}