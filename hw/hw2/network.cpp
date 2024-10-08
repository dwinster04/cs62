#include "network.h"
#include "user.h"
#include <vector>
#include <set>
#include <queue>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>

// constructor
Network::Network() {}                         // default network object auto set with size zero

// operations


int Network::numUsers()
{
    return users_.size();
}

User* Network::getUser(int id)
{
    for (auto e: users_)
    {
        if (e->getId() == id)
            return e;
    }
}

void Network::addUser(User* user)
{
    if (user != nullptr)
        users_.push_back(user);               // push back user into vector
    else
        return;                               // returns if user = null ptr
}



int Network::addConnection(std::string s1, std::string s2)
{
   
    User* user1 = nullptr;                    // initialize users to nullptr
    User* user2 = nullptr;

    for (int i = 0; i <= users_.size(); ++i)
    {
        if (users_[i]->getName() == s1)       // access the data stored vector of User*'s
            {
                user1 = users_[i];            // first user found
            }
            if (users_[i]->getName() == s2)
            {
                user2 = users_[i];            // found second user
            }
    }

    if (user1 != nullptr && user2 != nullptr)
    {
        user1->addFriend(user2->getId());     // code from notes
        user2->addFriend(user1->getId());

        
        return 0;
    }

    return -1;                                // users not found
}

int Network::deleteConnection(std::string s1, std::string s2)
{
   
    User* user1 = nullptr;                    // initialize users to nullptr
    User* user2 = nullptr;

    for (int i = 0; i <= users_.size(); ++i)
    {
        if (users_[i]->getName() == s1)
            {
                user1 = users_[i]; 
            }
            if (users_[i]->getName() == s2)
            {
                user2 = users_[i]; 
            }
    }

    if (user1 != nullptr && user2 != nullptr)
    {
        user1->deleteFriend(user2->getId()); // code from notes
        user2->deleteFriend(user1->getId()); // undirected connection


        return 0;
    }

    return -1;                               // user(s) not found
}

int Network::getId(std::string name)
{
    for (int i = 0; i <= users_.size(); ++i)  
    {
        if (users_[i]->getName() == name)   // check if users_[i] == input name
            return users_[i]->getId();      // returns id of users[i]
    }
    return -1;
}

void Network::readUsers(char* name)
{
    
    std::ifstream inputFile(name);
    if (inputFile.is_open())
        {
            std::string lines;
            while(std::getline(inputFile, lines))
            {
                // reading id
                std::stringstream ss(lines);
                int id;
                ss >> id;

                // reading name
                std::getline(inputFile, lines);
                if (lines.size() > 1)
                {
                    std::string name = lines.substr(1);
                }
                else
                {
                    std::cerr << "Line is too short or missing for... " << id << std::endl;
                    continue;
                }

                // read year
                std::getline(inputFile, lines);
                if (lines.size() > 1)
                {
                    std::string year = lines.substr(1);
                }
                else
                {
                    std::cerr << "Line is too short or missing for... " << id << std::endl;
                    continue;
                } // use ss to parse the file (stoi does not work: tried and failed)
                int year;
                std::stringstream ssYear(lines.substr(1));
                ssYear >> year;

                // read zip
                std::getline(inputFile, lines);
                std::stringstream ssZip(lines.substr(1));
                int zip;
                ssZip >> zip;

                // read friends
                std::getline(inputFile, lines);
                std::stringstream ssfriends(lines);
                std::set<int> friends;
                int friendId;
                while (ssfriends >> friendId)
                {
                    friends.insert(friendId);
                }

                User* tempUser = new User(id, name, year, zip, friends);
                addUser(tempUser); // call add user function to add tempUser which holds string of read users
            }
                              
        }
        inputFile.close();
}

void Network::writeUsers(char* fname)
{
    std::ofstream outputFile(fname);
    if (outputFile.is_open())
    {
        for (auto& user : users_)         // direct reference to user object
        {
            if (user != nullptr)
                outputFile << user->getId() << std::endl;
                outputFile << "\t" << user->getName() << std::endl;
                outputFile << user->getYear() << std::endl;
                outputFile << user->getZip() << std::endl;

                std::set<int> friends = user->getFriends(); // get friends of user and put it in their friends list
                for (auto& id : friends) // traverse through friend list
                {
                    outputFile << id << " ";
                }
                outputFile << std::endl;
        }
    }
    outputFile.close();
}


std::vector<int> Network::shortestPath(int from, int to)
{
    if (from == to)
    {
        std::cout << "Same person" << std::endl;
    }

    std::unordered_map<User*, User*> prev;
    std::queue<User*> queue;

    User* source = getUser(from);
    queue.push(source);
    

    while (queue.size() > 0)
    {
        User* curr = queue.front();
        queue.pop();

        if (curr->getId() == to)
        {
            std::vector<int> path;
            while (curr != source)
            {
                path.push_back(curr->getId());
                curr = prev[curr];
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (auto neighbor : curr->getFriends())
        {
            if (!prev.contains(neighbor))
            {
                queue.push(getUser(neighbor));
                prev[neighbor] = curr;
            }
        }
    }
    std::cout << "Not connected..." << std::endl;
}