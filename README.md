Station
=======

Station - A text based adventure game by Michael Kalvas

Coded in C++ for a class I took titled CSE 2122 at Ohio State.

Just download the source, compile, and run.

Mac/*nix: Clone the repo (or download as zip and unzip to folder), navigate to source folder, run ```g++ *.cpp; ./a.out```

Windows:  Can use Code::Blocks (or some similar c++ IDE) to build and run or through Cygwin gcc/g++ compilers use the command line like on a Unix based machine.

How to Play
===========
The game is mostly self explanatory and contains help in itself.

The basic premise is that you find yourself on a space station orbiting a planet. The station is in disrepair and the goal is to get it working enough to get off of it and down to the planet.

All commands should be two parts: An "action" (e.g. help, take, move, look) and an "object" (e.g. me, wrench, forwards, closely). This will make more sense when actually starting the game. All of the commands can be seen at any point by typing "help me" into the input.

Other Thoughts
==============
Some of the error messages may not do well at being situationally aware but I tried to make them vague and broadly applicable. Also, there are no specific errors for mis-spelled input and as I was testing the game, realized that this was the biggest source of frustration in the play testers' experience. So be careful you spell your input correctly.

I will not be supporting this in any way. Although there is always a faint chance that I will be bored some day and update this or make some tweaks. Other than that, see the license for as is open source software.

I've included the solution.txt file in the repository so you can see what you need to do if you get stuck. Also, for the industrious among you, there's some commented out code in the source files that are marked testing, that when properly uncommented (and commenting out a "production" line) and recompiling the program, will solve the game for you.
