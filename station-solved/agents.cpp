// agents.cpp

/* testing */
#include <fstream>

#include <limits>
#include "agents.h"
using namespace std;

// Constructors and construction functions
Agent::Agent(string _name){
    name = _name;
    cr = NULL;
}
Asteroid::Asteroid(string _name) : Agent(_name) {
    start_time = 480;
    time_left = start_time;
}
Player::Player(string _name, set<string> _items) : Agent(_name) {
    items = _items;
    conditions.insert(pair<string, bool> ("core", false));
    conditions.insert(pair<string, bool> ("power", false));
    conditions.insert(pair<string, bool> ("comms", false));
    conditions.insert(pair<string, bool> ("screw", false));
    conditions.insert(pair<string, bool> ("rephull", false));
    conditions.insert(pair<string, bool> ("repguid", false));
}
Player read_player_info(){
    string new_name;
    cout << "Enter your first name: ";
    cin >> new_name;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << endl;
    set<string> items;
    items.insert("spacesuit");
    return Player(new_name, items);
}

// GET functions
string Player::get_name() {
    return name;
}
int Player::get_info(Asteroid &asteroid) {
    string action, object, line, temp_line;
    size_t pos = 0;
    size_t last = string::npos;
    cout << "What do you do " << name << "?: ";

    /* production
    getline(cin, line); */

    /* testing */
    ifstream usefile_orig("usefile.txt");
    ofstream temp("temp.txt");
    int i = 0;
    while(getline(usefile_orig, temp_line)) {
        if(i == 0) {
            line = temp_line;
        } else {
            temp << temp_line << endl;
        }
        ++i;
    }


    if((pos = line.find(' ')) != string::npos){
        action = line.substr(0, pos);
        line.erase(0, pos + 1);
    } else {
        action = "a";
    }
    if((pos = line.find(last))) {
        object = line.substr(0, pos);
        line.erase(0, numeric_limits<streamsize>::max());
    } else {
        object = "a";
    }
    cout << action << " " << object << endl;

    /* testing */
    usefile_orig.close();
    temp.close();
    ofstream usefile_new("usefile.txt");
    ifstream temp_new("temp.txt");
    while(getline(temp_new, temp_line)) {
        usefile_new << temp_line << endl;
    }
    temp_new.close();
    usefile_new.close();
    remove("temp.txt");

    cout << endl;
    if(asteroid.act(action, object)) {
        return 2;
    } else if(this->act(action, object)){
        return 0;
    } else {
        return 1;
    }
}
void Player::check_items(){
    cout << "You have";
    if(!items.empty()){
        cout << ":" << endl;
        set<string>::iterator item_it;
        for(item_it = items.begin(); item_it != items.end(); ++item_it){
            cout << *item_it << endl;
        }
    } else {
        cout << " nothing." <<  endl;
    }
    cout << endl;
}
void Asteroid::get_time() {
    cout << "T-MINUS: ";
    if((time_left / 60) < 10){
        cout << "0" << time_left / 60;
    }  else {
        cout << time_left / 60;
    }
    cout << ":";
    if(time_left % 60 < 10) {
        cout << "0" << time_left % 60;
    }  else {
        cout << time_left % 60;
    }
     cout << " UNTIL IMPACT" << endl << endl;
}
void Asteroid::get_end_time() {
    cout << "You completed the game in ";
    time_left = start_time - time_left;
        if((time_left / 60) < 10){
        cout << "0" << time_left / 60;
    }  else {
        cout << time_left / 60;
    }
    cout << ":";
    if(time_left % 60 < 10) {
        cout << "0" << time_left % 60;
    }  else {
        cout << time_left % 60;
    }
    cout << endl;
}

// SET functions
bool Player::take_item(string item) {
    if(cr->items_here.find(item) != cr->items_here.end()){
        items.insert(item);
        cout << "You picked up the " << item << endl << endl;
        return true;
    } else {
        cout << "That cannot be taken" << endl << endl;
        return false;
    }
}
bool Player::drop_item(string item) {
    if(!(cr->get_name()[0] == 'v' && item == "spacesuit")){
        if(items.find(item) != items.end()){
            items.erase(item);
            cout << "You dropped the " << item << endl << endl;
            return true;
        } else {
            cout << "You can't drop something you don't have." << endl << endl;
            return false;
        }
    } else {
        cout << "You can't drop your spacesuit in space!" << endl << endl;
        return false;
    }
}

// ACTION functions
bool Player::use_item(string item){
    if(items.find(item) != items.end()) {
        if(cr->usables.find(item) != cr->usables.end()) {
            if(item == "ignition-sequence") {
                if( conditions["core"] && conditions["power"] && conditions["comms"] && conditions["rephull"] && conditions["repguid"]) {
                    items.erase(item);
                    cout << "You used the " << item << " on the " << cr->usables.find(item)->second << endl << endl;
                    return true;
                } else {
                    if(items.find(item) != items.end()) {
                        cout << "The shuttle is still inoperable." << endl << endl;
                    } else {
                        cout << "You don't have that." << endl << endl;
                    }
                    return false;
                }
            } else

            if(item == "hull-parts") {
                if(conditions["screw"]) {
                    items.erase(item);
                    cout << "You used the " << item << " on the " << cr->usables.find(item)->second << endl << endl;
                    return true;
                } else {
                    if(items.find(item) != items.end()) {
                        cout << "You need the correct tool to use that." << endl << endl;
                    } else {
                        cout << "You don't have that." << endl << endl;
                    }
                    return false;
                }
            } else

            if(item == "guidance-unit") {
                if(conditions["screw"]) {
                    items.erase(item);
                    cout << "You used the " << item << " on the " << cr->usables.find(item)->second << endl << endl;
                    return true;
                } else {
                    if(items.find(item) != items.end()) {
                        cout << "You need the correct tool to use that." << endl << endl;
                    } else {
                        cout << "You don't have that." << endl << endl;
                    }
                    return false;
                }
            }

            else {
                if(items.find(item) != items.end()) {
                    items.erase(item);
                    cout << "You used the " << item << " on the " << cr->usables.find(item)->second << endl << endl;
                    return true;
                } else {
                    cout << "You don't have that." << endl << endl;
                    return false;
                }
            }
        } else {
            if(items.find(item) != items.end()) {
                cout << "You can't use this like that." << endl << endl;
            } else {
                cout << "You don't have that." << endl << endl;
            }
            return false;
        }
    } else {
        cout << "You don't have that." << endl << endl;
        return false;
    }
}
bool Asteroid::act(string action, string object) {
    if(action == "move") {
        time_left -= 5;
    } else if(action == "take" || action == "drop" || action == "use") {
        time_left -= 2;
    } else if(action == "look") {
        if(object == "closely") {
            time_left -= 3;
        } else {
            time_left -= 1;
        }
    } else if(action == "check") {
        time_left -= 1;
    }
    if(time_left <= 0) {
        return true;
    } else {
        get_time();
        return false;
    }
}
bool Player::act(string action, string object) {

    if(action == "help" && object == "me"){
        cout << endl << "Valid commands and syntax guide:" << endl;
        cout << "Please note that the timer is NOT real time. Each action takes a set amount of time." << endl << endl;
        cout << "move [direction]          moves character in a valid direction." << endl;
        cout << "look [around || closely]  gives information about the room you are in." << endl;
        cout << "take [object]             picks up object in room." << endl;
        cout << "drop [object]             drop an item from your inventory." << endl;
        cout << "use  [object]             uses object in inventory." << endl;
        cout << "check items               lists items in your inventory." << endl;
        cout << "help me                   lists commands." << endl << endl;
    } else

    if(action == "move") {
        if(cr->move_rules(items, object, conditions)) {
            cr = cr->get_link(object);
        } else {
            cout << "You can't do that. Type \"help me\" for help" << endl << endl;
        }
    } else

    if(action == "look") {
        if(object == "around") {
            cr->print_linked(false);
        } else
        if(object == "closely") {
            cr->print_linked(true);
        } else {
            cout << "There is nothing to see there." << endl << endl;
        }
    } else

    if(action == "take") {
        if(take_item(object)){
            if(object == "sonic-screwdriver") {
                conditions["screw"] = true;
            }
            cr->remove_item(object);
        }
    } else

    if(action == "drop") {
        if(drop_item(object)){
            if(object == "sonic-screwdriver") {
                conditions["screw"] = false;
            }
            cr->add_item(object);
        }
    } else

    if(action == "use") {
        if(use_item(object)) {
            cr->remove_usable(object);
            if(object == "keyboard") {
                cout << "You re-attach the keyboard to the terminal." << endl;
                cout << "The terminal turns on and you see the power is out in the station." << endl;
                cout << "You select the open Reactor Core hatch and below you a hatch opens." << endl << endl;
                conditions["core"] = true;
            }
            if(object == "wrench") {
                cout << "You close the open release valve and see the reactor shine brightly." << endl;
                cout << "There is now a faint humming noise all throughout the station." << endl;
                cout << "You hear a notification, \"STATION HUB HATCHES NOW OPEN\"" << endl << endl;
                conditions["power"] = true;
            }
            if(object == "command-code") {
                cout << "You use the command-code to access the command systems." << endl;
                cout << "You activate the station's comms relays." << endl;
                cout << "The escape shuttle will now have the ability to find location beacons." << endl << endl;
                conditions["comms"] = true;
            }
            if(object == "guidance-unit") {
                cout << "The shuttle now has an operable guidance-unit" << endl << endl;
                conditions["repguid"] = true;
            }
            if(object == "hull-parts") {
                cout << "The shuttle now has a patched hull and is structurally sound" << endl << endl;
                conditions["rephull"] = true;
            }
            if(object == "ignition-sequence") {
                return true;
            }
        }
    } else

    if(action == "check" && object == "items"){
        check_items();
    }

    else {
        cout << "You can't do that. Type \"help me\" for help" << endl << endl;
    }
    return false;
}
