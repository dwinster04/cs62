#include "network.h"
#include "user.h"
#include "post.h"
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
    numPosts_ = 0;
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

    std::string line; // initialize a string "line" to store the line from following get line function call
    std::getline(file, line); // sets first line to the first line in file (number of users: 148)
    std::stringstream ss; // initialize stringstream ss to store line as string
    ss << line; // reads line into ss as string
    int numUsers; // initialize an integer to store number of users
    ss >> numUsers; // store string (148) as integer (148)

    
    
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

        if(name[name.size()-1] == ' ') // removing tab character (possibly)
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

    
    std::queue<int> queue; // initializes queue for bfs performing
    std::vector<bool> visited(users_.size(), false); // initialize a vector of bool to check whether visited or not that equals the users_.size() of the network and initializes all to false
    std::vector<int> dist(users_.size(), -1); // initializes a vector of integers to track distance and sets all distances equal to -1 at the beginning
    std::vector<int> prev(users_.size(), -1); // initializes a vector to keep track of previous vertices visited and initializes them all to -1 (starting vertex should stay -1 since no previous)

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
            break; // breaks out of bfs to down to result line
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


    for (int current = to; current != -1; current = prev[current]) // building shortest path / current not equal to -1 as the end since prev[startingNode] will equal -1 which we initialized it as
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

    bool distanceFound = false; // keeps track of if distance has been found to break out of bfs loop early or not

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
                visited[neighbor] = true;
                dist[neighbor] = dist[current] + 1; // distance of neighbor will always be distance of current + 1
                prev[neighbor] = current; // set the prev[neighbor] equal to current since previous node of the neighbor that is being visited is the one you are currently looking at
                queue.push(neighbor); // push neighbor into queue

                
                if (dist[neighbor] == distance) // check if neighbor/friend matches target dist
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
        result.push_back(userInPath); // pushes back "to" node 
        userInPath = prev[userInPath]; // sets userInPath equal to its previous at each iteration
    }

    
    std::reverse(result.begin(), result.end()); // reverse to get correct order
    return result;
}

std::vector<int> Network::suggestFriends(int who, int& score) 
{
    score = 0; // initialize score to 0

    User* mainGuy = getUser(who);

    if (!mainGuy) // user not found
    {
        return {};
    }

    std::vector<int> mainGuysFriends(mainGuy->getFriends().begin(), mainGuy->getFriends().end()); // convert user's friends to a vector
    std::vector<std::pair<int, int>> suggestions;                                       // stores suggestions and their scores

    for (int friendId : mainGuysFriends)                                                    // go through friends of the users
    {
        User* currentUser = getUser(friendId); // get friend of current user

        std::vector<int> friendOfMainGuyFriends(currentUser->getFriends().begin(), currentUser->getFriends().end()); // get main guy's friend's friends

        for (int mutuals : friendOfMainGuyFriends) // looping through friend of friends
        {
            if (mutuals == who) // mutual equals user then skip
            {
                continue;
            }

            bool friendsWMainGuy = std::find(mainGuysFriends.begin(), mainGuysFriends.end(), mutuals) != mainGuysFriends.end(); // check if mutual is already direct friend (can also check if distance 1)
                                                                                                                                // initialize to friendsWMainGuy for ease of use

            if (!friendsWMainGuy) // if mutual is not a direct friend then add them to suggestions vector and increment their score
            {
                bool foundInSuggestions = false;

                for (auto& potential : suggestions) 
                {
                    if (potential.first == mutuals)
                    {
                        potential.second++; // increase score if in found in mutuals
                        foundInSuggestions = true;
                        break;
                    }
                }

                
                if (!foundInSuggestions) 
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
            strongMutual.clear();
            highestScore = candidate.second; // update strongMutual with new highest scores
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

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic)
{
    for (auto user: users_)
    {
        if (user->getId() == ownerId)
        {
            int messageId = numPosts_++; // returns number of posts user has 
                                                     // chance this should be total number of posts in network
                                                     // CHECK LATER
            Post* newPost;

            if (isIncoming)
            {
                newPost = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
            }
            else
            {
                newPost = new Post(messageId, ownerId, message, likes);
            }
            user->addPost(newPost); // add newPost object to messages_ User class method to add to messages_ vector
            return; // return within loop since we found the owner id of the user whos post we want to add
        }
    }
}

std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic)
{
    User* user = getUser(ownerId); // set user equal to ownerId (person we want to return their posts)

    if (user != nullptr)
    {
        return user->getPostsString(howMany, showOnlyPublic);
    }
    else
    {
        return "User not found."; // user does not exist
    }
}

int Network::readPosts(char* fname)
{
    std::ifstream file(fname);

    if(!file)
    {
        return -1;
    }

    std::string line; // initialize a string "line" to store the line from following get line function call
    std::getline(file, line); // sets first line to the first line in file (number of users: 148)
    std::stringstream ss; // initialize stringstream ss to store line as string
    ss << line; // reads line into ss as string
    int numPosts; // initialize an integer to store number of users
    ss >> numPosts; // store string (148) as integer (148)

    for(int i = 0; i < numPosts; ++i)
    { 
        getline(file, line); // message id
        int messageId;
        messageId = std::stoi(line);

        getline(file, line); // message
        std::string message;
        message = line;
        message = message.substr(1, message.size()); // removes tab at the start

        getline(file, line); // owner id
        line = line.substr(1, line.size());
        int ownerId;
        ownerId = std::stoi(line);

        getline(file, line); // likes
        line = line.substr(1, line.size());
        int likes;
        likes = std::stoi(line);

        getline(file, line); // public/private
        if(line.size() == 0)
        {
            addPost(ownerId, message, likes, false, "", false); // creates normal post
            
            getline(file, line);
        }
        else
        {
            bool isPublic = false;
            if(line == "\tpublic")
            {
                isPublic = true;
            }

            getline(file, line); // author
            line = line.substr(1, line.size());
            std::string author = line;

            addPost(ownerId, message, likes, true, author, isPublic);
        }
    }
    return 0;
}

bool key(Post* post1, Post* post2) // sorting key
{
    return post1->getMessageId() < post2->getMessageId();
}

int Network::writePosts(char* fname)
{
    std::vector<Post*> posts;
    for (auto user : users_)
    {
        for (auto post : user->getPosts())
        {
            posts.push_back(post);
        }
    }

    std::sort(posts.begin(), posts.end(), key);
    
    std::ofstream fout(fname);

    if (!fout.is_open()) 
    {
        return -1;
    }

    fout << posts.size() << std::endl;

    for (auto post : posts) 
    {
        fout << post -> getMessageId() << std::endl;
        fout << '\t' << post -> getMessage() << std::endl;
        fout << '\t' << post -> getOwnerId() << std::endl;
        fout << '\t' << post -> getLikes() << std::endl;
        if (post->getAuthor().size() > 0)
        {
            if (post->getIsPublic())
            {
                fout << '\t' << "public" << std::endl;
            }
            else
            {
                fout << '\t' << "private" << std::endl;
            }
            fout << '\t' << post -> getAuthor() << std::endl;
        }
        else
        {
            fout << std::endl << std::endl;
        }
    }   
    fout.close();
    return 0;
}