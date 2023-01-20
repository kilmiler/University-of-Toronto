#include <stdio.h>
#include <stdlib.h>

void printBoard(int board[], int playerA, int playerB){
  printf("\n");
  for(int i=0; i<9; i++){
    if(board[i]=='A'){
      printf(" %c", (char)board[i]);
    }else if (board[i]=='B'){
      printf(" %c", (char)board[i]);
    }else{
      printf(" %d", board[i]);
    }
    if((i+1)%3==0){
      printf("\n");
    }
  }
  printf("\n");
}


int checkForWinner(int board[], int playerA, int playerB){
  if(board[0]==board[1] && board[1]==board[2] && board[2]=='A'){
    printf("Player A wins!\n");
    return playerA;
  }else if(board[3]==board[4] && board[4]==board[5] && board[5]=='A'){
    printf("Player A wins!\n");
    return playerA;
  }else if(board[6]==board[7] && board[7]==board[8] && board[8]=='A'){
    printf("Player A wins!\n");
    return playerA;
  }else if(board[0]==board[3] && board[3]==board[6] && board[6]=='A'){
    printf("Player A wins!\n");
    return playerA;
  }else if(board[1]==board[4] && board[4]==board[7] && board[7]=='A'){
    printf("Player A wins!\n");
    return playerA;
  }else if(board[2]==board[5] && board[5]==board[8] && board[8]=='A'){
    printf("Player A wins!\n");
    return playerA;
  }else if(board[0]==board[4] && board[4]==board[8] && board[8]=='A'){
    printf("Player A wins!\n");
    return playerA;
  }else if(board[2]==board[4] && board[4]==board[6] && board[6]=='A'){
    printf("Player A wins!\n");
    return playerA;
  }else if(board[0]==board[1] && board[1]==board[2] && board[2]=='B'){
    printf("Player B wins!\n");
    return playerB;
  }else if(board[3]==board[4] && board[4]==board[5] && board[5]=='B'){
    printf("Player B wins!\n");
    return playerB;
  }else if(board[6]==board[7] && board[7]==board[8] && board[8]=='B'){
    printf("Player B wins!\n");
    return playerB;
  }else if(board[0]==board[3] && board[3]==board[6] && board[6]=='B'){
    printf("Player B wins!\n");
    return playerB;
  }else if(board[1]==board[4] && board[4]==board[7] && board[7]=='B'){
    printf("Player B wins!\n");
    return playerB;
  }else if(board[2]==board[5] && board[5]==board[8] && board[8]=='B'){
    printf("Player B wins!\n");
    return playerB;
  }else if(board[0]==board[4] && board[4]==board[8] && board[8]=='B'){
    printf("Player B wins!\n");
    return playerB;
  }else if(board[2]==board[4] && board[4]==board[6] && board[6]=='B'){
    printf("Player B wins!\n");
    return playerB;
  }else{
    return 0;
  }
}


int requestValidInput(int board[], int playerA, int playerB){
  int move1, move2, move3, move4, move5, move6, move7, move8, move9;
  int temp;
  int i=0;
  int j=0;

  printf("It is Player A's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move1);
    if(move1>9 || move1<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else{
      board[move1-1]= 'A';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    i=1;
    return 0;
  }else{
    i=0;
    printf("The current state of the Tic-tac-toe Board:\n");
    printBoard(board, playerA, playerB);
  }


  printf("It is Player B's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move2);
    if(move2>9 || move2<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else if(move2==move1){
      printf("That position has already been played, please try again.\n");
      i=0;
    }else{
      board[move2-1]='B';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    i=1;
    return 0;
  }else{
    i=0;
    printf("The current state of the Tic-tac-toe Board:\n");
    printBoard(board, playerA, playerB);
  }


  printf("It is Player A's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move3);
    if(move3>9 || move3<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else if(move3==move1 ||move3==move2){
      printf("That position has already been played, please try again.\n");
      i=0;
    }else{
      board[move3-1]='A';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    i=1;
    return 0;
  }else{
    i=0;
    printf("The current state of the Tic-tac-toe Board:\n");
    printBoard(board, playerA, playerB);
  }


  printf("It is Player B's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move4);
    if(move4>9 || move4<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else if(move4==move1 || move4==move2 || move4==move3){
      printf("That position has already been played, please try again.\n");
      i=0;
    }else{
      board[move4-1]='B';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    i=1;
    return 0;
  }else{
    i=0;
    printf("The current state of the Tic-tac-toe Board:\n");
    printBoard(board, playerA, playerB);
  }


  printf("It is Player A's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move5);
    if(move5>9 || move5<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else if(move5==move1 || move5==move2 || move5==move3 || move5==move4){
      printf("That position has already been played, please try again.\n");
      i=0;
    }else{
      board[move5-1]='A';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    i=1;
    return 0;
  }else{
    i=0;
    printf("The current state of the Tic-tac-toe Board:\n");
    printBoard(board, playerA, playerB);
  }


  printf("It is Player B's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move6);
    if(move6>9 || move6<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else if(move6==move1 || move6==move2 || move6==move3 || move6==move4 || move6==move5){
      printf("That position has already been played, please try again.\n");
      i=0;
    }else{
      board[move6-1]='B';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    i=1;
    return 0;
  }else{
    i=0;
    printf("The current state of the Tic-tac-toe Board:\n");
    printBoard(board, playerA, playerB);
  }


  printf("It is Player A's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move7);
    if(move7>9 || move7<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else if(move7==move1 || move7==move2 || move7==move3 || move7==move4 || move7==move5 || move7==move6){
      printf("That position has already been played, please try again.\n");
      i=0;
    }else{
      board[move7-1]='A';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    i=1;
    return 0;
  }else{
    i=0;
    printf("The current state of the Tic-tac-toe Board:\n");
    printBoard(board, playerA, playerB);
  }


  printf("It is Player B's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move8);
    if(move8>9 || move8<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else if(move8==move1 || move8==move2 || move8==move3 || move8==move4 || move8==move5 || move8==move6 || move8==move7){
      printf("That position has already been played, please try again.\n");
      i=0;
    }else{
      board[move8-1]='B';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    i=1;
    return 0;
  }else{
    i=0;
    printf("The current state of the Tic-tac-toe Board:\n");
    printBoard(board, playerA, playerB);
  }


  printf("It is Player A's turn.\n");
  printf("Please enter a valid position to play.\n");
  while(i==0){
    scanf("%d", &move9);
    if(move9>9 || move9<1){
      printf("Invalid input, please try again.\n");
      i=0;
    }else if(move9==move1 || move9==move2 || move9==move3 || move9==move4 || move9==move5 || move9==move6 || move9==move7 || move9==move8){
      printf("That position has already been played, please try again.\n");
      i=0;
    }else{
      board[move9-1]='A';
      i=1;
    }
  }
  temp=checkForWinner(board, playerA, playerB);
  if(temp==playerA || temp==playerB){
    j=1;
    return 0;
  }else{
    printf("It's a draw!\n");
  }

  return 5;
}


int main(void){
int playerA=10;
int playerB=11;

int board[9]={1,2,3,4,5,6,7,8,9};

printf("The current state of the Tic-tac-toe Board:\n");
printBoard(board, playerA, playerB);
requestValidInput(board, playerA, playerB);
printBoard(board, playerA, playerB);

return 0;
}

