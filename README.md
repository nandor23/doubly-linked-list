# Doubly linked list with extra functionality
It's based on the C++ STL list data structure, with some extra functionalities like: 
- replacing every element equal equal to a given element
- removing every element equal to a given element
- inserting before/after a given position
- inserting an element N times before/after a position
- removing an element before/after a given position
- removing elements between two positions
- every function has its reversed form (performs like the list was numbered backwards)


## War - Game
It's a console based game, no GUI.
The game is implemented by using the doubly linked list. The extra functions were not used, the projects main goal was the implementation of the C++ STL list.

<img src="https://github.com/nandor23/doubly-linked-list/blob/main/Screenshot.png" alt="game" width="500"/>

## Gameplay

[Wikipedia link](https://en.wikipedia.org/wiki/War_(card_game))

- The objective of the game is to win all of the cards.
- The deck is divided evenly among the players, giving each a down stack. Each player reveals the top card of their deck—this is a "battle"—and the player with the higher card takes both of the cards played and moves them to their stack.
- If the two cards played are of equal value, then there is a "war". Both players place the next three cards face down and then another card face-up. The owner of the higher face-up card wins the war and adds all the cards on the table to the bottom of their deck. If the face-up cards are again equal then the battle repeats with another set of face-down/up cards. This repeats until one player's face-up card is higher than their opponent's
