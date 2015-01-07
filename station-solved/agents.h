// agents.h
#ifndef AGENTS_H
#define AGENTS_H

#include <iostream>
#include <string>
#include <map>
#include <set>

#include "map.h"

class Agent {
protected:
    Agent();
    Agent(std::string);
    std::string name;
    std::set<std::string> items;
public:
    virtual bool act(std::string, std::string)=0;
    Room * cr;
};

class Asteroid : public Agent {
protected:
    int start_time;
    int time_left;
public:
    Asteroid(std::string);
    bool act(std::string, std::string);
    void get_time();
    void get_end_time();
};

class Player : public Agent {
public:
    Player();
    Player(std::string, std::set<std::string>);
    std::map<std::string, bool> conditions;
    int get_info(Asteroid &);
    bool act(std::string, std::string);
    std::string get_name();
    bool take_item(std::string);
    bool drop_item(std::string);
    bool use_item(std::string);
    void check_items();
};



Player read_player_info();

// Levels
void level_one(Player &);
void alien(Player &);
void end_game(Player &);
// void end_game(Monster &);

#endif
