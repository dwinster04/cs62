#include "network.h"
#include "user.h"
#include <vector>
#include <set>
#include <queue>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>

Network::Network() 
{
    users_ = {};
} 

User* Network::getUser(int id) 
{
    for (auto e : users_) 
    {
        if (e -> getId() == id) 
        {
            return e;
        }
    }
    return nullptr;
}

void Network::addUser(User* newUser) 
{
    for (auto e : users_) 
    {
        if (e -> getId() == newUser -> getId()) 
        {
            return;
        }
    }
    users_.push_back(newUser);
}

int Network::addConnection(std::string s1, std::string s2) 
{
    int id1 = getId(s1);
    int id2 = getId(s2);
    User* user1 = getUser(id1);
    User* user2 = getUser(id2);

    if ((id1 == -1) || (id2 == -1)) 
    {
        return -1;
    }
    else {
        user1 -> addFriend(id2);
        user2 -> addFriend(id1);

    }
    return 0;
}

int Network::deleteConnection(std::string s1, std::string s2) 
{
    int id1 = getId(s1);
    int id2 = getId(s2);

    if ((id1 == -1) || (id2 == -1)) {
        return -1;
    }
    
    User* user1 = getUser(id1);
    User* user2 = getUser(id2);

    if ((user1 == nullptr) || (user2 == nullptr)) 
    {
        return -1;
    }

    if (user1 -> getFriends().find(id2) != user1 -> getFriends().end()) 
    {
        user1 -> deleteFriend(id2);
        user2 -> deleteFriend(id1);
        return 0;
    }
    else 
    {
        return -1;
    }
}

int Network::getId(std::string name) 
{
    for (auto e : users_) 
    {
        if (e->getName() == name) 
        {
            return e->getId();
        }
    }
    return -1;
}

int Network::numUsers() 
{
    return users_.size();
}

void Network::readUsers(char * fname)
{   
    
    std::ifstream file(fname);

    if(!file)
    {
        return;
    }

    std::string line; // line takes in each line in file fname
    getline(file, line); // set line to the first line in fname
    std::stringstream ss; 
    ss << line; 
    int numUsers; 
    ss >> numUsers; 

    
    
    for(int i = 0; i < numUsers; i++)
    {
        // parse id
        std::string stringId; 
        getline(file,stringId);
        std::stringstream sId(stringId);
        int intId; 
        sId >> intId;

        // parse name
        std::string string; 
        std::string temp;
        getline(file, string); 
        std::stringstream sName(string);
        std::string name;
        while(sName >> temp)
        {
            name = name + temp + " "; 
        }

        if(name[name.size()-1] == ' ') // removing tab character
        {
            name = name.substr(0,name.size()-1); // removes space after name
        }
        

        // parse year
        std::string year; 
        getline(file,year); 
        std::stringstream sYear(year);
        int intYear;
        sYear >> intYear; 

        // parse zip
        std::string zip; 
        getline(file,zip); 
        std::stringstream sZip(zip); 
        int intZip; 
        sZip >> intZip; 

        std::string fList;
        std::set<int> connections;
        getline(file, fList); // gets line of friends
        std::stringstream fss; // friend stringstream
        fss << fList; 
        int friendId; 
        while(fss >> friendId)
        {
            connections.insert(friendId);

        } 
        User* newUser = new User(intId, name, intYear, intZip, connections);
        addUser(newUser);
    }
   

    file.close();


}

void Network::writeUsers(char* fname) 
{
    std::ofstream fout(fname);

    if (!fout.is_open()) 
    {
        std::cout << "error opening file..." << std::endl;
        return;
    }

    fout << users_.size() << std::endl;

    for (int i = 0; i < users_.size(); ++i) 
    {
        User* e = users_[i];
        fout << e -> getId() << std::endl;
        fout << '\t' << e -> getName() << std::endl;
        fout << '\t' << e -> getYear() << std::endl;
        fout << '\t' << e -> getZip() << std::endl;
        fout << "\t"; 
        auto friends = e->getFriends();
        for (int friendId : friends) 
        {
            fout << friendId << " "; 
        }
        fout << std::endl;
    }   
    fout.close();
}


std::vector<int> Network::shortestPath(int from, int to)
{
    
    if (to < 0 || to >= users_.size() || from < 0 || from >= users_.size()) 
    {
        return {}; // valid id check
    }

    
    std::queue<int> queue;
    std::vector<bool> visited(users_.size(), false); 
    std::vector<int> dist(users_.size(), -1); 
    std::vector<int> prev(users_.size(), -1); 

    // INITIALIZE BFS
    dist[from] = 0;
    visited[from] = true;
    queue.push(from);

    // PERFORM BFS
    while (!queue.empty()) 
    {
        int current = queue.front();
        queue.pop();

        if (current == to) // found target
        {
            break;
        }
        
        for (int neighbor : users_[current]->getFriends()) // look at friends of the current 
        {
            if (!visited[neighbor]) 
            {
                visited[neighbor] = true;
                dist[neighbor] = dist[current] + 1;
                prev[neighbor] = current;
                queue.push(neighbor);
            }
        }
    }

    std::vector<int> result; // return vector

    if (dist[to] == -1) 
    {
        return result; // cannot find to
    }


    for (int current = to; current != -1; current = prev[current]) // building shortest path
    {
        result.push_back(current);
    }

    std::reverse(result.begin(), result.end()); // reverse to get in from to to order
    return result;
}



std::vector<int> Network::distanceUser(int from, int& to, int distance) 
{
    if (from < 0 || from >= users_.size()) // valid id check
    {
        to = -1; 
        return {}; 
    }

    std::queue<int> queue; 
    std::vector<bool> visited(users_.size(), false); 
    std::vector<int> dist(users_.size(), -1); 
    std::vector<int> prev(users_.size(), -1); 

    bool distanceFound = false; 

    // INITIALIZE BFS
    dist[from] = 0; 
    visited[from] = true; 
    queue.push(from); 

    // PERFORM BFS
    while (!queue.empty()) 
    {
        int current = queue.front();
        queue.pop();

        
        for (int neighbor : users_[current]->getFriends()) // look at current's friends
        {
            if (!visited[neighbor]) 
            {
                dist[neighbor] = dist[current] + 1;
                visited[neighbor] = true;
                prev[neighbor] = current;
                queue.push(neighbor);

                
                if (dist[neighbor] == distance) // check if friend matches target dist
                {
                    to = neighbor;
                    distanceFound = true;
                    break;
                }
            }
        }

        if (distanceFound) 
        {
            break; 
        }
    }


    if (!distanceFound) // no user found case
    {
        to = -1;
        return {};
    }

    
    std::vector<int> result; // vector to return
    int userInPath = to;

    if (prev[to] == from) // if from and to are neighbors
    {
        result.push_back(from);
        result.push_back(to);
        return result;
    }

    
    while (userInPath != -1) // rebuild the path
    {
        result.push_back(userInPath);
        userInPath = prev[userInPath];
    }

    
    std::reverse(result.begin(), result.end()); // reverse to get correct order
    return result;
}

std::vector<int> Network::suggestFriends(int who, int& score) 
{
    score = 0; // initialize score to 0

    User* user = getUser(who);

    if (!user) // user not found
    {
        return {};
    }

    std::vector<int> userFriends(user->getFriends().begin(), user->getFriends().end()); // convert user's friends to a vector

    std::vector<std::pair<int, int>> suggestions;                                       // stores suggestions and their scores

    for (int friendId : userFriends)                                                    // go through friends of the users
    {
        User* friendUser = getUser(friendId); // get friend of current user

        std::vector<int> friendOfFriends(friendUser->getFriends().begin(), friendUser->getFriends().end()); // get current friend's friends

        for (int mutuals : friendOfFriends) // looping through friend of friends
        {
            if (mutuals == who) // mutual equals user then skip
            {
                continue;
            }

            bool isFriend = std::find(userFriends.begin(), userFriends.end(), mutuals) != userFriends.end(); // check if mutual is already direct friend (can also check if distance 1)
                                                                                                             // initialize to isFriend for ease of use

            if (!isFriend)
            {
                bool foundInPotential = false;

                for (auto& potential : suggestions) 
                {
                    if (potential.first == mutuals) 
                    {
                        potential.second++; // increase score if in found in mutuals
                        foundInPotential = true;
                        break;
                    }
                }

                
                if (!foundInPotential) 
                {
                    suggestions.push_back(std::make_pair(mutuals, 1)); // add mutual to suggestions and set score to 1
                }
            }
        }
    }

    if (suggestions.empty())  // no suggestions found
    {
        score = 0;
        return {};
    }

    std::vector<int> strongMutual;
    int highestScore = 0;

    for (const auto& candidate : suggestions) 
    {
        if (candidate.second > highestScore) 
        {
            // update strongMutual with new highest scores
            strongMutual.clear();
            highestScore = candidate.second;
            strongMutual.push_back(candidate.first);
        } 
        else if (candidate.second == highestScore) 
        {
            strongMutual.push_back(candidate.first); // add candidate if they share a score
        }
    }

    score = highestScore; // set score to highest score

    return strongMutual;  // return strongest mutuals
}

std::vector<std::vector<int>> Network::groups() 
{
    std::vector<bool> visited(users_.size(), false); 

    if (users_.empty()) 
    {
        return {};
    }

    
    std::vector<std::vector<int>> result; // stores all connected groups in a vector of vectors
    
    for (int i = 0; i < users_.size(); ++i)
    {
        if (!visited[i]) 
        {
            // INITIALIZE DFS
            std::vector<int> currentGroup; // stores one currentGroup
            std::stack<int> stack;
            stack.push(i);
            visited[i] = true;

            // PERFORM DFS
            while (!stack.empty()) 
            {
                int current = stack.top();
                stack.pop();
                currentGroup.push_back(current);

                for (int friendId : users_[current]->getFriends()) // look at friends of current user
                {
                    if (!visited[friendId])
                    {
                        visited[friendId] = true;
                        stack.push(friendId);
                    }
                }
            }
            result.push_back(currentGroup);
        }
    }
    return result; // return all connected groups in the network
}
