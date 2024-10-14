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
#include <unordered_set>

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
    for (auto e: users_)   
    {
        if (e -> getId() == user -> getId())
        {
            return;
        }
        users_.push_back(user);
    }      
}



int Network::addConnection(std::string s1, std::string s2)
{
   
    int id1 = getId(s1);
    int id2 = getId(s2);
    User* user1 = getUser(id1);                    // initialize users to nullptr
    User* user2 = getUser(id2);

    if ((id1 == -1) || (id2 == -1))
    {
        return -1;
    }
    else
    {
        user1 -> addFriend(id2);                   // undirected
        user2 -> addFriend(id1);
    }
    return 0;
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
    for (auto e: users_)
    {
        if (e -> getName() == name)
        {
            return e -> getId();
        }
    }
}

std::string Network::removeTabs(const std::string& fileLine)
{
    std::string result;
    for (size_t i = 0; i < fileLine.size(); ++i)
    {
        if (fileLine[i] != '\t')
        {
            result += fileLine[i];
        }
    }
}

void Network::readUsers(char* name)
{
    std::ifstream inputFile(name);
    if (!inputFile.is_open())
    {
        std::cout << "error opening file..." << std::endl;
        return;
    }
    else
    {
        int numUsers = 0;
        std::string line;

        std::getline(inputFile, line);
        std::stringstream ss(line);
        ss >> numUsers;

        for (int i = 0; i < numUsers; ++i)
        {
            int id;
            std::string name, first, last, line;
            int year, zip, friendId;
            std::set<int> friends;

            std::getline(inputFile, line);
            if (fileLine.empty()) 
                continue;
            std::stringstream ssid(line);
            ssid >> id;

            std::getline(inputFile, line);
            if (fileLine.empty())
                continue;
            std::stringstream ssname;
            ssname >> first >> last;
            name = first + " " + last;

            std::getline(inputFile, line);
            if (fileLine.empty())
                continue;
            std::stringstream sszip(removeTabs(line));
        }
    }
}

void Network::writeUsers(char* fname)
{
    std::ofstream outputFile(fname);

    if (!outputFile.is_open())
    {
        std::cout << "error opening file..." << std::endl;
        return;
    }

    outputFile << users_.size() << std::endl;

    for (int i = 0; i < users_.size(); ++i)
    {
        User* user = users_[i];

        outputFile << user -> getId() << std::endl;
        outputFile << '\t' << user -> getName() << std::endl;
        outputFile << '\t' << user -> getYear() << std::endl;
        outputFile << '\t' << user -> getZip() << std::endl;
        outputFile << '\t';
        auto friends = user->getFriends();
        for (int friendId : friends)
        {
            outputFile << friendId << " ";
        }
        outputFile <<std::endl;
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
    std::unordered_map<User*, User*> prev; // map to keep track of prev visied
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
            std::reverse(path.begin(), path.end()); // reverse path to get "from to to"
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
{
    std::unordered_map<User*, int> dist;  // keep track of map of distances in nodes
    std::unordered_map<int, int> scores;  // initialize map of scores
    int max_score;                        // max score to search all users with that score
    std::queue<User*> queue;

    User* source = getUser(who);
    queue.push(source);
    dist[source] = 0;

    while (queue.size() > 0) // DFS
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
                if (dist[getUser(neighbor)] == 2) // distance of neighbor = 2 since dist = 1 are direct friends
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
    std::unordered_set<int> visited;
    std::vector<std::vector<int>> groups;
    std::vector<int> group;
    for (auto user : users_)
    {
        if (!visited.find(user->getId()) == visited.end())
        {
            group = dfshelper(user);
            groups.push_back(group);
            for (auto userId : group)
            {
                visited.insert(userId);
            }
        }
    }
    return groups;
}

vector<int> Network::dfshelper(User* source)
{
    std::stack<int> stck;
    std::vector<int> visited;

    source = source->getId();
    visited.push_back(source);
    stck.push(source);

    while (stck.size() > 0) 
    {
        int cur = stck.top();
        stck.pop();
        for (auto neighbor : getUser(cur)->getFriends()) 
        {
            if (visited.find(neighbor) ==  visited.end()) 
            {
                visited.push_back(neighbor);
                stck.push(neighbor);
            }
        }
    }
    return visited;
}