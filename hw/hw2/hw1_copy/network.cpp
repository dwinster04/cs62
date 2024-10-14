#include "network.h"
#include "user.h"
#include "user.cpp"
#include <vector>
#include <set>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

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