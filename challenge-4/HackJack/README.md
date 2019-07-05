# HackJack (Based on 'WhackJack', modified by the Frama-C team)

## Original Author Information

"Steve Wood" <swood@cromulence.com>

## Description

This program is a game of chance called HackJack.  It might or might not bear a similarity to another game with a rhyming name.  It allows up to 8 players to play, with players being human or computer simulated according to various play algorithms.

Unlike similar games, scoring starts at 0: an ace is worth 0 or 11 points,
a 2 is worth 1 point, and so on; 10 is worth 9 points, but J/Q/K are worth 10
points each.

### Feature List

The service simulates a card game where the goal is to get a higher score than the dealer without going over 21.  Up to 8 players can play with the option of making some of those players computer simulated.  Five different algorithms are included that embody various schools of thought on how to play the game.  The game also includes a training mode whereby human players can get play hints from one of the algorithms.

### Sample Input

To help with testing, a sample input file is provided: in.txt.

If you compile the program to a binary, say `hackjack`, you can run `./hackjack < in.txt` to quickly execute a test run.
Remember, this is a single test run, it may not reveal all bugs!
