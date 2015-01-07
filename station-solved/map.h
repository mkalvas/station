// map.h
#ifndef MAP_H
#define MAP_H

#include <typeinfo>
#include <iostream>
#include <string>
#include <map>
#include <set>

class Room {
protected:
    std::string name;
    std::string description;
    std::map<std::string, Room *> room_map;

public:
    Room();
    Room(std::string, std::string);
    std::set<std::string> items_here;
    std::map<std::string, std::string> usables;

    std::string get_name();
    std::string get_description();
    Room * get_link(std::string);
    void set_link(std::string, Room *);
    void print_linked(bool);

    bool move_rules(std::set<std::string>, std::string, std::map<std::string, bool>);
    void add_item(std::string);
    void remove_item(std::string);
    void add_usable(std::string, std::string);
    void remove_usable(std::string);
};

#endif
