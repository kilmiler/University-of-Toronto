//
//  gameState.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Copyright © 2019 Tarek Abdelrahman. All rights reserved.

#include "tictactoe.h"
#include "gameState.h"

// Return the clicked row (0..boardSize-1)
int gameState::get_clickedRow(){
    return clickedRow;
}

// Return the clicked column (0..boardSize-1)
int gameState::get_clickedColumn(){
    return clickedColumn;
}

// Set the clicked row to value (0..boardSize-1)
// An invalid value is ignored and no action is taken
void gameState::set_clickedRow(int value){
    clickedRow = value;
}

// Return the clicked column (0..boardSize-1)
// An invalid value is ignored and no action is taken
void gameState::set_clickedColumn(int value){
    clickedColumn = value;
}

// Get the moveValid value
bool gameState::get_moveValid(){
    return moveValid;
}

// Set the moveValid variable to value
void gameState::set_moveValid(bool value){
    moveValid = value;
}

// Get the gameOver value
bool gameState::get_gameOver(){
    return gameOver;
}

// Set the gameOver variable to value
void gameState::set_gameOver(bool value){
    gameOver = value
}

// Get the winCode
int gameState::get_winCode(){
    return winCode;
}

// Set the winCode to value
// An invalid value is ignored and no action is takem
void gameState::set_winCode(int value){
    winCode = value;
}

// Get the value of turn
bool gameState::get_turn(){
    return turn;
}

// Set the value of turn
void gameState::set_turn(bool value){
    turn = value;
}

// Get the game board value at the board location at row and col
int gameState::get_gameBoard(int row, int col){
    return gameBoard[row][col];
}

// Set the game board value at the board location at row and col to value
// This method checks that row, col and value are valid and if not it
// performs no action
void gameState::set_gameBoard(int row, int col, int value){
    gameBoard[row][col] = value;
}
