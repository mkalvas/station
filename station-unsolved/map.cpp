// map.cpp

/* testing
#include <fstream> */

#include "map.h"
#include "agents.h"
using namespace std;

// Constructors
Room::Room() {
    name = "generic room";
    description = "a generic room ";
}
Room::Room(string _name, string _description) {
    name = _name;
    description = _description;
}

// GET functions
string Room::get_name() {
    return name;
}
string Room::get_description() {
    return description;
}
Room * Room::get_link(string dir) {
    if(room_map.find(dir) != room_map.end()) {
        cout << "You float into the " << room_map.find(dir)->second->get_name() << "." << endl << endl;
        return room_map.find(dir)->second;
    } else {
        cout << "You cannot go that way." << endl << endl;
        return this;
    }
}
bool Room::move_rules(set<string> items, string action, map<string, bool> conditions) {

    if(name == "Airlock") {
        if(action == "outside"){
            if(items.find("spacesuit") != items.end()) { return true; } else {
                cout << "You can't go outside without a spacesuit" << endl;
                return false; }
        } else if(action == "inside") {
            if(items.find("spacesuit") != items.end()) {
                cout << "Please remove your spacesuit before entering the station" << endl;
                return false;
            } else { return true; }
        } else { return true; }
    } else

    if(name == "Station Hub") {
        if(action == "forwards" || action == "left" || action == "right" || action == "up") {
            if(conditions["power"]) { return true; } else { return false; }
        } else { return true; }
    } else

    if(name == "Reactor Interface Node") {
        if(action == "down"){
            if(conditions["core"]) { return true; } else { return false; }
        } else { return true; }
    } else { return true; }
}


// SET functions
void Room::set_link(string dir, Room * room) {
    room_map.insert(pair<string, Room *>(dir,room));
}
void Room::add_item(string item){
    items_here.insert(item);
}
void Room::remove_item(string item) {
    items_here.erase(item);
}
void Room::add_usable(string key, string lock) {
    usables.insert(pair<string, string>(key, lock));
}
void Room::remove_usable(string key) {
    usables.erase(usables.find(key));
}


// Display functions
void Room::print_linked(bool closely) {
    if(closely) {
        cout << "You look closely and find" << endl;
        if(items_here.empty() && usables.empty()) {
            cout << "nothing interesting" << endl;
        }
        if(!usables.empty()) {
            map<string, string>::iterator usable_it;
            for(usable_it = usables.begin(); usable_it != usables.end(); ++usable_it) {
                cout << usable_it->second << endl;
            }
        }
        if(!items_here.empty()) {
            set<string>::iterator item_it;
            for(item_it = items_here.begin(); item_it != items_here.end(); ++item_it) {
                cout << *item_it << endl;
            }
        }
    } else {
        cout << "You are in the " << name << "." << endl;
        cout << "You look around and see " << description << "." << endl;
        map<string, Room *>::iterator it;
        for(it = room_map.begin(); it != room_map.end(); ++it) {
            cout << "Looking " << (it->first) << ", you see the " << (it->second)->get_name() << "." << endl;
        }
    }
    cout << endl;
}


// Level building and running functions
void alien(Player &player) {

    // Generate Rooms
    Room airlock = Room("Airlock", "a small cramped room with two airtight hatches at either end. There are compartments for storing spacesuits but they are all empty");
    Room hub = Room("Station Hub", "a small room with tunnels leading in all directions");
    Room command = Room("Command Center", "two chairs facing a large window into space. There are command and control panels with blinking lights lining the walls");
    Room engineering = Room("Engineering Node", "a room filled with high tech equipment for conduction research and development");
    Room workshop = Room("Workshop", "a workbench situated against the far wall. There are compartments for all manner of tools and spare parts");
    Room mess = Room("Mess Hall", "a relatively large clean room with a table in the center. There are 6 chairs around the table and a kitchenette against the wall");
    Room cabin = Room("Crew Cabin", "6 beds stacked 3 high against opposite walls. Against the far wall there are six compartments for storing personal belongings");
    Room storage = Room("Storage Node", "food, clothing, and an assortment of other goods. It looks picked over as if someone took the useful supplies");
    Room obs = Room("Observation Room", "a room with high tech viewing equipment. The ceiling is a dome shaped window that meets with the floor on all sides. You can see that you are in orbit around a planet with evidence of life");
    Room rein = Room("Reactor Interface Node", "a small node with large bulks of wire and piping leading to one control panel");
    Room recore = Room("Reactor Core", "a cylindrical room in the middle of which is a bright tube of pulsating blue light");
    Room mainext = Room("vicinity of the Airlock", "the station in front of you and the planet behind it. Behind you is a large dying star emitting a reddish light");
    Room upperext = Room("vicinity of the Observation Room", "into the observation room. The light from the star and planet make it impossible to see the stars above. You feel lonely in the vast emptiness of space");
    Room bayone = Room("Shuttle Bay 1", "an empty docking mechanism for a small shuttle and shuttle bay doors");
    Room baytwo = Room("Shuttle Bay 2", "a docking bay with a small emergency shuttle docked and shuttle bay doors");
    Room shuttle = Room("Shuttle", "a small emergency shuttle that needs repairs");

    // Link Rooms to form map
    upperext.set_link("downwards", &mainext);
    mainext.set_link("inside", &airlock);
    mainext.set_link("upwards", &upperext);
    airlock.set_link("outside", &mainext);
    airlock.set_link("inside", &hub);
    hub.set_link("backwards", &airlock);
    hub.set_link("forwards", &mess);
    hub.set_link("up", &obs);
    hub.set_link("down", &rein);
    hub.set_link("left", &command);
    hub.set_link("right", &engineering);
    obs.set_link("down", &hub);
    command.set_link("backwards", &hub);
    command.set_link("down", &bayone);
    bayone.set_link("up", &command);
    engineering.set_link("left", &workshop);
    engineering.set_link("backwards", &hub);
    engineering.set_link("down", &baytwo);
    baytwo.set_link("up", &engineering);
    baytwo.set_link("inside", &shuttle);
    shuttle.set_link("outside", &baytwo);
    rein.set_link("up", &hub);
    rein.set_link("down", &recore);
    recore.set_link("up", &rein);
    storage.set_link("backwards", &mess);
    workshop.set_link("backwards", &engineering);
    mess.set_link("left", &storage);
    mess.set_link("forwards", &cabin);
    mess.set_link("backwards", &hub);
    cabin.set_link("backwards", &mess);


    // Populate items into rooms
    // open reactor core hatch
    rein.add_item("keyboard");
    rein.add_usable("keyboard","terminal");
    // close release valve with wrench to turn on power
    upperext.add_item("wrench");
    recore.add_usable("wrench","open release valve");
    // get ignition sequence
    shuttle.add_usable("ignition-sequence","ignition");
    mess.add_item("ignition-sequence");
    // get command code for comms
    command.add_usable("command-code", "inactive comms relay");
    cabin.add_item("command-code");
    // need sonic screwdriver to repair shuttle
    workshop.add_item("sonic-screwdriver");
    // get spare shuttle parts
    baytwo.add_usable("hull-parts", "unpatched shuttle hull");
    baytwo.add_usable("guidance-unit", "missing guidance-unit slot");
    bayone.add_item("hull-parts");
    obs.add_item("guidance-unit");


    // Put player into room
    Asteroid asteroid = Asteroid("A-Class");
    cout << "You wake to the sound of an alarm." << endl;
    cout << "WARNING: ASTEROID INCOMING. COLLISION IMMINENT." << endl;
    asteroid.get_time();
    player.cr = &airlock;
    player.cr->print_linked(false);
    int level_end = 1;

    /* testing
    string line;
    ifstream ifile("solution.txt");
    ofstream ofile("usefile.txt");
    if(ifile.is_open()) {
        if(ofile.is_open()) {
            while(getline(ifile, line)) {
                ofile << line << endl;
            }
        } else {
            cout << "bad file read" << endl;
        }
    } else {
        cout << "bad file read" << endl;
    }
    ifile.close();
    ofile.close(); */

    // Run level
    do { level_end = player.get_info(asteroid); } while(level_end == 1);

    // Outro text for level completion
    if(level_end == 0) {
        cout << "You see the station shrinking into the distance as your shuttle makes its way" << endl;
        cout << "to the planet below. An alarm goes off as you determine the location of a" << endl;
        cout << "transmission beacon coming from the surface. You switch the alarm off and put" << endl;
        cout << "the coordinates of the beacon into the shuttle's computer. Your shuttle lands" << endl;
        cout << "and you walk to the hatch. It opens in front of you and you see a man and a" << endl;
        cout << "woman standing there. The man says, \"Welcome to planetoid LV-426.\"" << endl;
        cout << "\"We call it Acheron.\"" << endl << endl;
        asteroid.get_end_time();

    } else if(level_end == 2) {
        cout << "The asteroid impacts the station and rips it apart." << endl;
        cout << "You survive for a moment but the high velocity debris and vacuum of space are inescapable." << endl << endl;
    } else {
        cout << "The asteroid grazed the station. The life support still works but all other systems are irreparable." << endl;
        cout << "You are forced to wait and see if someone comes to rescue you..." << endl;
    }
}

void end_game(Player &player) {
    /* testing
    remove("usefile.txt");
     */
    cout << "Thank you for playing my game " << player.get_name() << "." << endl << endl;
    cout << "Made by Mike Kalvas 2014" << endl;
}

/* LEVEL TEMPLATE
void level_one_alien(Player &player) {

    bool beat_level = false;

    // *set up level here*

    player.cr->print_linked(false);

    // Run level
    do { beat_level = player.get_info(); } while(!beat_level);

    // Outro text for level completion
    cout << "Congrats on beating the level." << endl << endl;
}
*/
