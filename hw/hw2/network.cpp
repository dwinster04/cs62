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
#include <stack>

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
    return nullptr;
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
    if (from == to)  // same people were input (shortest path is -1)
    {
        std::cout << "Same person" << std::endl;
        break;
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
            if (prev.find(getUser(neighbor)) == prev.end() && getUser(neighbor) != source)
            {
                queue.push(getUser(neighbor));
                prev[getUser(neighbor)] = curr;
            }
        }
    }
    std::cout << "Not connected..." << std::endl;
    std::vector<int> empty;
    return empty;
}

std::vector<int> Network::distanceUser(int from, int& to, int distance)
{

    std::unordered_map<User*, int> dist;  // keep track of map of distances in nodes
    std::unordered_map<User*, User*> prev;
    std::queue<User*> queue;

    User* source = getUser(from);
    queue.push(source);
    dist[source] = 0;

    while (queue.size() > 0)
    {
        User* curr = queue.front();
        queue.pop();

        if (dist[curr] == distance)
        {
            std::vector<int> path;
            to = curr->getId();
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
            if (prev.find(getUser(neighbor)) == prev.end() && getUser(neighbor) != source)
            {
                queue.push(getUser(neighbor));
                prev[getUser(neighbor)] = curr;
                dist[getUser(neighbor)] = dist[curr] + 1;
            }
        }
    }
    std::cout << "Not connected..." << std::endl;
    std::vector<int> empty;
    return empty;
}

vector<int> Network::suggestFriends(int who, int& score)
// needs: dist(map), common(map), queue
{
    std::unordered_map<User*, int> dist;  // keep track of map of distances in nodes
    std::unordered_map<int, int> scores;
    int max_score;
    std::queue<User*> queue;

    User* source = getUser(who);
    queue.push(source);
    dist[source] = 0;

    while (queue.size() > 0)
    {
        User* curr = queue.front();
        queue.pop();


        for (auto neighbor : curr->getFriends())
        {
            if (getUser(neighbor) == source || dist.find(neighbor) != dist.end() && dist[getUser(neighbor)] == 1)
            {
                continue;
            }
            if (dist.find(neighbor)!=dist.end() && dist[neighbor] == 2)
            {
                scores[neighbor]++;
                max_score = std::max(max_score, scores[neighbor]);
            }
            else
            {
                dist[getUser(neighbor)] = dist[curr] + 1;
                if (dist[getUser(neighbor)] == 2)
                {
                    scores[neighbor] = 1;
                    if (max_score == 0)
                    {
                        max_score = 1;
                    }
                }
                else
                {
                    queue.push(getUser(neighbor));
                }
            }
        }
    }

    std::vector<int> suggestions;
    score = max_score;  // score is an address
    if (max_score == 0)
    {
        return suggestions;
    }
    for (const auto& pair : scores)
    {
        if (pair.second == max_score)
        {
            suggestions.push_back(pair.first);
        }
    }
    return suggestions;
}

vector<vector<int>> Network::groups()
{
    std::set<int> visited;
    std::stack<int> stck;
    std::vector<std::vector<int>> groups; 
    for (auto user : users_)
    {
        if (!visited.find(user->getId()) == visited.end())
        {
            // perform DFS
            // returns vector of everyone visited by DFS
            groups.push_back(result of DFS);
        }
    }
}