#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//introducing integers for counting wins and losses.
int countWin=0, countLose=0;

//function for rolling 2 dice with sum of 2 random numbers from 2-12
int rollDice(void){
	int firstNum, secondNum;
	firstNum = (rand() %6 )+1;
	secondNum = (rand() %6 )+1;
	return firstNum + secondNum;
}

//creating a function to play a craps game (rules and other given rules)
bool playGame(void){
	int sum, point, i=0, j=0;
	char playAgain;
	while(i==0){
    	sum = rollDice();
    	if(sum==7 || sum==11){
        	printf("You rolled: %d\n", sum);
        	printf("You win!\n");
        	countWin ++;
        	printf("Play again? ");
        	scanf(" %c", &playAgain);
            	if(playAgain=='y'||playAgain=='Y'){
                	i=0;
            	}else{
                	i=1;
            	}
    	}else if(sum==2 || sum==3 || sum==12){
        	printf("You rolled: %d\n", sum);
   		 printf("You lose!\n");
        	countLose ++;
        	printf("Play again? ");
        	scanf(" %c", &playAgain);
            	if(playAgain=='y'||playAgain=='Y'){
                	i=0;
            	}else{
                	i=1;
            	}
    	}else{
        	printf("You rolled: %d\n", sum);
        	point = sum;
        	printf("Your point is: %d\n", point);
   		 j=0;
        	while(j==0){
            	sum=rollDice();
            	if(sum==point){
                	printf("You rolled: %d\n", sum);
                	printf("You win!\n");
                	countWin ++;
                	printf("Play again? ");
                	scanf(" %c", &playAgain);
                    	if(playAgain=='y'||playAgain=='Y'){
                        	j=1;
                        	i=0;
                    	}else{
                        	j=1;
                        	i=1;
                    	}
            	}else if(sum==7){
                	printf("You rolled: %d\n", sum);
                	printf("You lose!\n");
                	countLose ++;
                	printf("Play again? ");
                	scanf(" %c", &playAgain);
                    	if(playAgain=='y'||playAgain=='Y'){
                        	j=1;
                        	i=0;
                    	}else{
                        	j=1;
                        	i=1;
                    	}
            	}else{
            	printf("You rolled: %d\n", sum);
            	j=0;
            	}
        	}
    	}
	}
	return 1;
}

// printing the wins and losses that have been saved from above.
void winLoss(void){
	playGame();
	printf("\nWins: %d\n", countWin);
	printf("Losses: %d\n", countLose);
}

//main function that uses all other functions from above
/*int main(void){
	winLoss();
    
return 0;
}*/




