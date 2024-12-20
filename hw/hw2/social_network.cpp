#include "network.h"
#include "user.h"
#include <iostream>
#include <string>
#include <fstream>

void user_choice()
{
    std::cout << "1) Add a user..." << std::endl;
    std::cout << "2) Add a friend..." << std::endl;
    std::cout << "3) Delete friend..." << std::endl;
    std::cout << "4) Write to file..." << std::endl;
    std::cout << "5) View posts..." << std::endl;
    std::cout << "Enter any other number to exit..." << std::endl;
}


int main(int argc, char *argv[])
{
    Network network;
    network.readUsers(argv[1]);     // argv[1] = opening of the given user input file
    network.readPosts(argv[2]);     // argv[2] = opening of the given user input file 2

    while(true)
    {
        user_choice();
        int choice;
        std::cin >> choice;

        if (choice == 1) // option 1: add a user
        {
            std::string firstN, lastN;
            int year, zip;

            std::cout << "Please enter the first name, last name, year of birth, and zip code number in that order: " <<std::endl;
            std::cin >> firstN >> lastN >> year >> zip;
            std::cout << std::endl;


            int id = network.numUsers();        // sets new id = to number of users in the network at nth iteration
            std::string fullName = firstN + " " + lastN; // makes first name and last name new variable full name
            network.addUser(new User(network.numUsers(), fullName, year, zip, {}));     // creates the new user with new id and given inputs
            std::cout << fullName << " has been added to the network." << std::endl;
        }
        else if (choice == 2) // option 2: add a friend connection
        {
            std::string f1_first, f1_last, f2_first, f2_last;
            std::string f1_full, f2_full;
            
            std::cout << "Please enter the first and last name of the two users you would like to add a connection to: ";
            std::cin >> f1_first >> f1_last >> f2_first >> f2_last;
            
            f1_full = f1_first + " " + f1_last;
            f2_full = f2_first + " " + f2_last;

            if (network.addConnection(f1_full, f2_full) == 1)
            {
                std::cout << "Friend connection successfully added..." << std::endl;
            }
            else
            {
                std::cerr << "User does not exist...";
            }
        }

        else if (choice == 3) // delete a friend connection
        {
            std::string f1_first, f1_last, f2_first, f2_last;
            std::string f1_full, f2_full;
            
            std::cout << "Please enter the first and last name of the two users you would like to delete their connection with: ";
            std::cin >> f1_first >> f1_last >> f2_first >> f2_last;
            
            f1_full = f1_first + " " + f1_last;
            f2_full = f2_first + " " + f2_last;

            if (network.deleteConnection(f1_full, f2_full) == 1)
            {
                std::cout << "Friend connection successfully deleted..." << std::endl;
            }
            else
            {
                std::cerr << "Users do not have existing connection/User(s) do not exist...";
            }
        } 
        
        else if (choice == 4) // write to file
        {
            std::string ofile;

            std::cout << "Enter a file name to create: ";
            network.writeUsers(const_cast<char*>(ofile.c_str()));
        }
        else if (choice == 5)
        {
            std::string firstN, lastN, numPostsStr;
            std::cout << "Please enter first/last name and number of posts that you want to see..." <<std::endl;
            std::cin >> firstN >> lastN >> numPostsStr;
            int numPosts = std::stoi(numPostsStr);
            std::cout << (network.getPostsString(network.getId(firstN + " " + lastN), numPosts, false)) << std::endl;             
        }
        else
        {
            break;
        }
    }

return 0;
};