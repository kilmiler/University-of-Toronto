#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void initializeBoard(char board[26][26], int n); //
void printConfiguration(char board[26][26], int n); //
void printBoard(char board[26][26], int n); //

bool positionInBounds(int n, int row, int col); //
bool checkLegalInDirection(char board[26][26], int n, int row, int col, char colour, int deltaRow, int deltaCol); //
bool ValidOrInvalid(char board[26][26], int n, int row, int col, char colour);

bool AvailableMoves(char board[26][26], int n, char colour); //

void flipColour(char board[26][26], int row, int col, char colour, int deltaRow, int deltaCol); //

void computerMove(char board[26][26], int n, char computer);
int countScore(char board[26][26], int row, int col, char colour, int deltaRow, int deltaCol);
void bestmove(char board[26][26], int n, int row, int col, char computer, int deltaRow, int deltaCol);
char winnerOfGame(char board[26][26], int n);
char nextColor(char colour);


int main(void){
  int n, deltaRow, deltaCol;
  char row, col;
  char board[26][26];
  char colour;
  char compColor;
  char playerColor;
  char currentTurn;
  int i, j;

  printf("Enter the board dimension: ");
  scanf("%d", &n);
  printf("Computer plays (B/W): ");
  scanf(" %c", &compColor);

  initializeBoard(board, n);

  if(compColor == 'B'){
    playerColor = 'W';
  } else if(compColor == 'W'){
    playerColor = 'B';
  }

  currentTurn = 'B';
  while(AvailableMoves(board, n, playerColor) || AvailableMoves(board, n, compColor)){
    printf("While loop was executed");
    if(currentTurn == compColor){
      computerMove(board, n, compColor);
      printBoard(board, n);
    } else{
      printf("Enter a move for colour %c (RowCol): ", playerColor);
      scanf(" %c%c", &row, &col);
        if(!checkLegalInDirection(board, n, row, col, playerColor, deltaRow, deltaCol)){
          printf("Invalid move.\n");
          printf("%c player wins.\n", compColor);
          return 0;
        } else{
          flipColour(board, row, col, playerColor, deltaRow, deltaCol);
          printBoard(board, n);
        }
    }

    if(AvailableMoves(board, n, playerColor) || AvailableMoves(board, n, compColor)){
      if(AvailableMoves(board, n, nextColor(currentTurn))){
        currentTurn = nextColor(currentTurn);
      } else{
        printf("%c player has no valid move\n", nextColor(currentTurn));
      }
    } else{
      char winnerColor = winnerOfGame(board, n);
      if(winnerColor == 'B'){
        printf("B player wins.\n");
      } else if(winnerColor == 'W'){
        printf("W player wins.\n");
      } else if(winnerColor == 'D'){
        printf("Draw!\n");
      }
      return 0;
    }
  }
}

//Initializing the initial board
void initializeBoard(char board[26][26], int n){
  int i, j;
  //Empty Space Position
  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      board[i][j]='U';
    }
  }
  //Initial White and Black Position
  board[(n/2)-1][(n/2)-1]='W';
  board[(n/2)][(n/2)]='W';
  board[(n/2)-1][(n/2)]='B';
  board[(n/2)][(n/2)-1]='B';

  printBoard(board, n);
}


//Initializing the board after Board Configuration
void printConfiguration(char board[26][26], int n){
  int i;
  char colourConfig;
  char rowConfig;
  char colConfig;

  //saving Configuration until !!! into board
  printf("Enter board configuration:");
  printf("\n");
  for(i=0; colourConfig!='!' && rowConfig!='!' && colConfig!='!'; i++){
    scanf(" %c%c%c", &colourConfig, &rowConfig, &colConfig);
    board[rowConfig-97][colConfig-97]=colourConfig;
  }
}


void printBoard(char board[26][26], int n){
  int i, j;

  //Printing Column Name
  printf("  ");
  for(i=0; i<n; i++){
    printf("%c", 'a'+i);
  }
  printf("\n");

  //Printing Row Name & Printing Board
  for(i=0; i<n; i++){
    printf("%c ", 'a'+i);
      for(j=0; j<n; j++){
        printf("%c", board[i][j]);
        if((j+1)%n==0){
          printf("\n");
        }
      }
  }
}


//Checking if position is in bounds of the board dimension
bool positionInBounds(int n, int row, int col){
  if(row>-1 && row<n && col>-1 && col<n){
    return true;
  } else{
    return false;
  }
}


bool checkLegalInDirection(char board[26][26], int n, int row, int col, char colour, int deltaRow, int deltaCol){
  printf("%c", colour);

  if(board[row][col] != 'U' || board[row+deltaRow][col+deltaCol] == 'U' || board[row+deltaRow][col+deltaCol] == colour || !positionInBounds(n, row+deltaRow, col+deltaCol)){
    return false;
  }

  while(positionInBounds(n,row+deltaRow,col+deltaCol) && board[row+deltaRow][col+deltaCol] != colour){
    if(deltaRow<0){
      deltaRow --;
    } else if(deltaRow>0){
      deltaRow ++;
    }

    if(deltaCol<0){
      deltaCol --;
    } else if(deltaCol>0){
      deltaCol ++;
    }

    if(board[row+deltaRow][col+deltaCol] == colour){
      return true;
    } else if(board[row+deltaRow][col+deltaCol] == 'U'){
      return false;
    }
  }

  return false; // Question ??? doesn't this return false always?
}


bool ValidOrInvalid(char board[26][26], int n, int row, int col, char colour){
  bool TorF = false;
  int computer;

  if(checkLegalInDirection(board, n, row-97, col-97, colour, 1, 0)){
    flipColour(board, row-97, col-97, colour, 1, 0);
    TorF = true;
  } else if(checkLegalInDirection(board, n, row-97, col-97, colour, -1, 0)){
    flipColour(board, row-97, col-97, colour, -1, 0);
    TorF = true;
  } else if(checkLegalInDirection(board, n, row-97, col-97, colour, 0, 1)){
    flipColour(board, row-97, col-97, colour, 0, 1);
    TorF = true;
  } else if(checkLegalInDirection(board, n, row-97, col-97, colour, 0, -1)){
    flipColour(board, row-97, col-97, colour, 0, -1);
    TorF = true;
  } else if(checkLegalInDirection(board, n, row-97, col-97, colour, -1, -1)){
    flipColour(board, row-97, col-97, colour, -1, -1);
    TorF = true;
  } else if(checkLegalInDirection(board, n, row-97, col-97, colour, 1, 1)){
    flipColour(board, row-97, col-97, colour, 1, 1);
    TorF = true;
  } else if(checkLegalInDirection(board, n, row-97, col-97, colour, 1, -1)){
    flipColour(board, row-97, col-97, colour, 1, -1);
    TorF = true;
  } else if(checkLegalInDirection(board, n, row-97, col-97, colour, -1, 1)){
    flipColour(board, row-97, col-97, colour, -1, 1);
    TorF = true;
  }

  if(TorF){
    board[row-97][col-97] = colour;
    return true;
  } else{
    return false;
  }
}


bool AvailableMoves(char board[26][26], int n, char colour){
  int i, j;

    for(i=0; i<n; i++){
      for(j=0; j<n; j++){
        if(checkLegalInDirection(board, n, i, j, colour, 1, 0)){
          return true;
          printf("This is for AvailableMoves");
        } else if(checkLegalInDirection(board, n, i, j, colour, 1, 1)){
          return true;
          printf("This is for AvailableMoves");
        } else if(checkLegalInDirection(board, n, i, j, colour, 0, 1)){
          return true;
          printf("This is for AvailableMoves");
        } else if(checkLegalInDirection(board, n, i, j, colour, -1, 1)){
          return true;
          printf("This is for AvailableMoves");
        } else if(checkLegalInDirection(board, n, i, j, colour, -1, 0)){
          return true;
          printf("This is for AvailableMoves");
        } else if(checkLegalInDirection(board, n, i, j, colour, -1, -1)){
          return true;
          printf("This is for AvailableMoves");
        } else if(checkLegalInDirection(board, n, i, j, colour, 0, -1)){
          return true;
          printf("This is for AvailableMoves");
        } else if(checkLegalInDirection(board, n, i, j, colour, 1, -1)){
          return true;
          printf("This is for AvailableMoves");
        } else{
          return false;
          printf("This is for AvailableMoves");
        }
      }
    }
}


void flipColour(char board[26][26], int row, int col, char colour, int deltaRow, int deltaCol){
  while (board[row+deltaRow][col+deltaCol] != colour){
    board[row+deltaRow][col+deltaCol] = colour;
    if(deltaRow<0){
      deltaRow --;
    } else if(deltaRow>0){
      deltaRow ++;
    }

    if(deltaCol<0){
      deltaCol --;
    } else if(deltaCol>0){
      deltaCol ++;
    }
  }
}




void computerMove(char board[26][26], int n, char computer){
  int row, col;
  int deltaRow, deltaCol;
  int maxI, maxJ;

  for(int i=0; checkLegalInDirection(board, n, row, col, computer, deltaRow, deltaCol); i++){
    bestmove(board, n, row, col, computer, deltaRow, deltaCol);
    printf("Computer places %c at %c%c", computer, maxI+97, maxJ+97);
    ValidOrInvalid(board, n, row, col, computer);
    printBoard(board, n);
  }
}


int countScore(char board[26][26], int row, int col, char computer, int deltaRow, int deltaCol){
  int score=0;

  while(board[row+deltaRow][col+deltaCol] != computer){
    score++;
    if(deltaRow<0){
      deltaRow --;
    } else if(deltaRow>0){
      deltaRow ++;
    }

    if(deltaCol<0){
      deltaCol --;
    } else if(deltaCol>0){
      deltaCol ++;
    }
  }
  return score;
}


void bestmove(char board[26][26], int n, int row, int col, char computer, int deltaRow, int deltaCol){
int i, j, score[26][26];
int maxScore=0;
int maxI, maxJ;
for(i=0; i<n; i++){
  for(j=0; j<n; j++){
    score[i][j]=0;
  }
}

  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      if(checkLegalInDirection(board, n, i, j, computer, 1, 0)){
        score[i][j]=countScore(board, row, col, computer, 1, 0);
      } else if(checkLegalInDirection(board, n, i, j, computer, 1, 1)){
        score[i][j]+=countScore(board, row, col, computer, 1, 1);
      } else if(checkLegalInDirection(board, n, i, j, computer, 0, 1)){
        score[i][j]+=countScore(board, row, col, computer, 0, 1);
      } else if(checkLegalInDirection(board, n, i, j, computer, -1, 1)){
        score[i][j]+=countScore(board, row, col, computer, -1, 1);
      } else if(checkLegalInDirection(board, n, i, j, computer, -1, 0)){
        score[i][j]+=countScore(board, row, col, computer, -1, 0);
      } else if(checkLegalInDirection(board, n, i, j, computer, -1, -1)){
        score[i][j]+=countScore(board, row, col, computer, -1, -1);
      } else if(checkLegalInDirection(board, n, i, j, computer, 0, -1)){
        score[i][j]+=countScore(board, row, col, computer, 0, -1);
      } else if(checkLegalInDirection(board, n, i, j, computer, 1, -1)){
        score[i][j]+=countScore(board, row, col, computer, 1, -1);
      }
    }
  }

  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      if(score[i][j]>maxScore){
        maxScore=score[i][j];
        maxI=i;
        maxJ=j;
      }
    }
  }

board[maxI-97][maxJ-97] = computer;
}


char winnerOfGame(char board[26][26], int n){
int i, j;
int countForB = 0;
int countForW = 0;

  for(i=0; i<n; i++){
    for(j=0; j<n; j++){
      if(board[i][j] == 'B'){
        countForB ++;
      }else if(board[i][j] == 'W'){
        countForW ++;
      }
    }
  }

  if(countForB>countForW){
    return 'B';
  } else if (countForW>countForB){
    return 'W';
  } else{
    return 'D';
  }
}


char nextColor(char colour){
  if(colour == 'B'){
    return 'W';
  } else if(colour == 'W'){
    return 'B';
  }
}



