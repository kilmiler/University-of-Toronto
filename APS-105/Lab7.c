#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void initializeBoard(char board[26][26], int n);
void printConfiguration(char board[26][26], int n);
void showMoves(char board[26][26], int m, char colour);
bool positionInBounds(int m, int row, int col);
void printStep(char board[26][26], int n);
bool checkLegalInDirection(char board[26][26], int m, int row, int col, char colour, int deltaRow, int deltaCol);
bool checkLegalMoves(char board[26][26], int m, char row, char col, char colour);

void initializeBoard(char board[26][26], int n){
  int i, j;

  printf("  ");
  for(i=0; i<n; i++){
	printf("%c", 'a'+i);
  }
  printf("\n");

  for(i=0; i<n; i++){
	for(j=0; j<n; j++){
  	board[i][j]='U';
	}
  }

  board[(n/2)-1][(n/2)-1]='W';
  board[(n/2)][(n/2)]='W';
  board[(n/2)-1][(n/2)]='B';
  board[(n/2)][(n/2)-1]='B';

  for(i=0; i<n; i++){
	printf("%c ", 'a'+i);
	for(j=0; j<n; j++){
  	if(board[i][j]=='B'){
    	printf("%c", board[i][j]);
  	}else if(board[i][j]=='W'){
    	printf("%c", board[i][j]);
  	}else{
    	printf("%c", board[i][j]);
  	}

  	if((j+1)%n==0){
    	printf("\n");
  	}
	}
  }
}

void printConfiguration(char board[26][26], int n){
  int i, j;
  char colour;
  char rowAlph;
  char colAlph;

  printf("Enter board configuration:");
  printf("\n");

  for(i=0; colour!='!' && rowAlph!='!' && colAlph!='!'; i++){
	scanf(" %c%c%c", &colour, &rowAlph, &colAlph);
	board[rowAlph-97][colAlph-97]=colour;
  }

  printf("  ");
  for(i=0; i<n; i++){
	printf("%c", 'a'+i);
  }
  printf("\n");

  for(i=0; i<n; i++){
	printf("%c ", 'a'+i);
	for(j=0; j<n; j++){
  	if(board[i][j]=='B'){
    	printf("%c", board[i][j]);
  	}else if(board[i][j]=='W'){
    	printf("%c", board[i][j]);
  	}else{
    	printf("%c", board[i][j]);
  	}

  	if((j+1)%n==0){
    	printf("\n");
  	}
	}
  }
}

void printStep(char board[26][26], int n){
  int i, j;
  char colour;
  char row;
  char col;
  char x;
  x=board[row-97][col-97];

  printf("Enter a move:\n");
  scanf(" %c%c%c", &colour, &row, &col);

 
	if(checkLegalMoves(board, n, row, col, colour)){
   	 board[row-97][col-97]=colour;
  	printf("  ");
    	for(i=0; i<n; i++){
      	printf("%c", 'a'+i);
    	}
      	printf("\n");
        	for(i=0; i<n; i++){
          	printf("%c ", 'a'+i);
            	for(j=0; j<n; j++){
              	printf("%c", board[i][j]);
            	}
            	printf("\n");
        	}
        	printf("\n");
	}else{
  	//board[row-97][col-97]=x;
  	printf("  ");
  	for(i=0; i<n; i++){
    	printf("%c", 'a'+i);
  	}
  	printf("\n");
    	for(i=0; i<n; i++){
      	printf("%c ", 'a'+i);
        	for(j=0; j<n; j++){
          	printf("%c", board[i][j]);
        	}
        	printf("\n");
    	}
	}
}

void showMoves(char board[26][26], int m, char colour){
  int i, j;
  int w=0;
  int deltaRow, deltaCol;
  int temp[26][26];
 
  for(i=0; i<26; i++){
      for(j=0; j<26; j++){
      temp[i][j]=0;
      }
  }

  printf("Available moves for %c:\n", colour);
  while(w==0){
	for(i=0; i<m; i++){
  	for(j=0; j<m; j++){
    	if(board[i][j]==colour){
      	for(deltaRow=-1; deltaRow<2; deltaRow++){
        	for(deltaCol=-1; deltaCol<2; deltaCol++){
          	if(deltaRow==0 && deltaCol==0){
            	w=1;
          	}else if(positionInBounds(m, (97+i+deltaRow), (97+j+deltaCol))){
             	 
   			   
   			   
   			   if(true){//checkLegalInDirection(board, m, (97+i+deltaRow), (97+j+deltaCol), colour, deltaRow, deltaCol)){
   					 int ii, jj;
   					 int k=0;
   					 char row = (97+i+deltaRow);
   					 char col = (97+j+deltaCol);
   					 ii=i+deltaRow;
   					 jj=j+deltaCol;

   					 while(positionInBounds(m, row+(k*deltaRow), col+(k*deltaCol)) && board[ii+(k*deltaRow)][jj+(k*deltaCol)]!=colour && board[ii+(k*deltaRow)][jj+(k*deltaCol)]!='U'){
   						 k++;
   						 if(positionInBounds(m, row+(k*deltaRow), col+(k*deltaCol)) && board[ii+(k*deltaRow)][jj+(k*deltaCol)]=='U'){
   							 temp[ii+(k*deltaRow)][jj+(k*deltaCol)]=1;
   						 }
   					 }

   			   }
   			   
   			   
            	}
          	}
        	}
      	}
    	}
  	}
	}
     for(i=97; i<26+97; i++){
      for(j=97; j<26+97; j++){
      if(temp[i-97][j-97]==1){
   	   char c1=i, c2=j;
   	   printf("%c%c\n", c1, c2);
      }
    }
  }
}

bool positionInBounds(int m, int row, int col){
int i, j;
i=row-97;
j=col-97;

if(i>-1 && i<m && j>-1 && j<m){
  return true;
}else{
  return false;
}
}

bool checkLegalInDirection(char board[26][26], int m, int row, int col, char colour, int deltaRow, int deltaCol){
int i, j;
int k=0;
int p=0;
i=row-97;
j=col-97;

while(positionInBounds(m, row+(k*deltaRow), col+(k*deltaCol)) && board[i+(k*deltaRow)][j+(k*deltaCol)]!=colour && board[i+(k*deltaRow)][j+(k*deltaCol)]!='U'){
  k++;
  if(positionInBounds(m, row+(k*deltaRow), col+(k*deltaCol)) && board[i+(k*deltaRow)][j+(k*deltaCol)]=='U'){
  	//printf("%c%c\n", row+(k*deltaRow), col+(k*deltaCol));
  	return true;
  }else{
	return false;
  }
}
return false;
}

bool checkLegalMoves(char board[26][26], int m, char row, char col, char colour){
  int i, j, deltaRow, deltaCol;
  i=row-97;
  j=col-97;
  for(deltaRow=-1; deltaRow<2; deltaRow ++){
	for(deltaCol=-1; deltaCol<2; deltaCol ++){
  	if(positionInBounds(m, row, col) && checkLegalInDirection(board, m, row, col, colour, deltaRow, deltaCol)){
    	printf("Valid move.\n");
    	return true;
  	}printf("Invalid move.\n");
   	return false;
	}
  }
}

int main(void){
int n;
char board[26][26];

printf("Enter the board dimension: ");
scanf("%d", &n); // receiving n value (dimension)
initializeBoard(board, n);
printConfiguration(board, n);
showMoves(board, n, 'W');
showMoves(board, n, 'B');
printStep(board, n);

return 0;
}




