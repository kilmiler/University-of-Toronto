//
//  playMove.cpp
//  TicTacTo
//
//  Updated by Tarek Abdelrahman on 2019-06-07.
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018-2019 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include "tictactoe.h"
#include "gameState.h"

using namespace std;

//check for valid moves, wins, gameover
//switch player turn, play move, then print board
void playMove(gameState& game_state) {
    int row, col;
    
    row = game_state.get_clickedRow();
    col = game_state.get_clickedColumn();
    
    //check validity of current move for X or O
    //check if the player's current clicked row/column is empty and set moveValid boolean
    //note: empty is defined already as 0 when setting board[i][j] == 0
    if(game_state.get_gameBoard(row, col) == 0){
        game_state.set_moveValid(true);
    } else{
        game_state.set_moveValid(false);
    }
    
    //if move is valid --> place X or O --> print board
    if(game_state.get_moveValid()){

        //place value 1(X) or -1(O) on player's current clicked row/column
        if(game_state.get_turn()){
                game_state.set_gameBoard(row, col, 1);
            }else if(!game_state.get_turn()){
                game_state.set_gameBoard(row, col, -1);
            }
        //& print board
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cout << game_state.get_gameBoard(i,j) << " ";
            }
        }
        
        //change turn: switch X to O (turn true --> false), vise versa
        //only when move is valid
        if(game_state.get_turn()){
            game_state.set_turn(false);
        }else if(!game_state.get_turn()){
            game_state.set_turn(true);
        }
    }
        
    //3 for X's win(1+1+1), -3 for O's win(-1-1-1)
    //use wincode 1-8 for win & corresponding display server //use wincode 0 for not win
    //check all winning patterns
    if(game_state.get_gameBoard(0,0) + game_state.get_gameBoard(0,1) + game_state.get_gameBoard(0,2) == 3 || game_state.get_gameBoard(0,0) + game_state.get_gameBoard(0,1) + game_state.get_gameBoard(0,2) == -3){
        game_state.set_winCode(1);
    }
    if(game_state.get_gameBoard(1,0) + game_state.get_gameBoard(1,1) + game_state.get_gameBoard(1,2) == 3 || game_state.get_gameBoard(1,0) + game_state.get_gameBoard(1,1) + game_state.get_gameBoard(1,2) == -3){
        game_state.set_winCode(2);
    }
    if(game_state.get_gameBoard(2,0) + game_state.get_gameBoard(2,1) + game_state.get_gameBoard(2,2) == 3 || game_state.get_gameBoard(2,0) + game_state.get_gameBoard(2,1) + game_state.get_gameBoard(2,2) == -3){
        game_state.set_winCode(3);
    }
    if(game_state.get_gameBoard(0,0) + game_state.get_gameBoard(1,0) + game_state.get_gameBoard(2,0) == 3 || game_state.get_gameBoard(0,0) + game_state.get_gameBoard(1,0) + game_state.get_gameBoard(2,0) == -3){
        game_state.set_winCode(4);
    }
    if(game_state.get_gameBoard(0,1) + game_state.get_gameBoard(1,1) + game_state.get_gameBoard(2,1) == 3 || game_state.get_gameBoard(0,1) + game_state.get_gameBoard(1,1) + game_state.get_gameBoard(2,1) == -3){
        game_state.set_winCode(5);
    }
    if(game_state.get_gameBoard(0,2) + game_state.get_gameBoard(1,2) + game_state.get_gameBoard(2,2) == 3 || game_state.get_gameBoard(0,2) + game_state.get_gameBoard(1,2) + game_state.get_gameBoard(2,2) == -3){
        game_state.set_winCode(6);
    }
    if(game_state.get_gameBoard(0,0) + game_state.get_gameBoard(1,1) + game_state.get_gameBoard(2,2) == 3 || game_state.get_gameBoard(0,0) + game_state.get_gameBoard(1,1) + game_state.get_gameBoard(2,2) == -3){
        game_state.set_winCode(7);
    }
    if(game_state.get_gameBoard(0,2) + game_state.get_gameBoard(1,1) + game_state.get_gameBoard(2,0) == 3 || game_state.get_gameBoard(0,2) + game_state.get_gameBoard(1,1) + game_state.get_gameBoard(2,0) == -3){
        game_state.set_winCode(8);
    }else{
        game_state.set_winCode(0);
    }
    
    //winCode 1-8 or none empty: gameover --> true //winCode 0 and empty: gameover --> false
    //note:empty is defined already as 0 for setting board[i][j]
    game_state.set_gameOver(false);
    
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(game_state.get_winCode() != 0 || game_state.get_gameBoard(i,j) != 0){
                game_state.set_gameOver(true);
            }
        }
    }
        
    //if game is over, exit void
    if(game_state.get_gameOver()){
        return;
    }
}
