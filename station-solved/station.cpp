/*  filename:   wanderer.cpp
*   created by: Michael Kalvas on 11-12-2014 for 2122 homework #7
*   synopsis:   This is a text adventure game I built! Have fun with it.
*               It's easily extensible if you know a little bit of c++
*               but I didn't code it with that intention so yeah.
*/

#include "map.h"
#include "agents.h"
#include <typeinfo>

using namespace std;

int main() {

    cout << "Welcome to my text based game. (type \"help me\" for help)" << endl << endl;
    Player player = read_player_info();
    alien(player);
    end_game(player);

    return 0;
}
