#include <stdio.h>

int A, B, C, D, W, X, Y, Z, R;

//using void function to receive inputs from user
void inputDate(int *day, int *month, int *year){
	printf("Please enter a date: ");
	scanf("%d/%d/%d", day, month, year);
}

//using void function to calculate the Zeller's Algorith
void calculateDay(int day, int month, int year){
	if(month>=3){
    	A=month-2;
	} else{
    	A=month+10;
	}
	B=day;
	if(month<=2){
    	int newyear = year -1;
   	 C=newyear%100;
   	 D=newyear/100;
    }else{
    C=year%100;
	D=year/100;
    }
    
	W=(13*A-1)/5;
	X = C/4;
	Y = D/4;
	Z = W+X+Y+B+C-(2*D);
	R = Z%7;
    	if(R<0){
        	R=+7;
    	}
    
//Using if statement to display different outputs according to different inputs of user.

	if(R==0){
    	printf("The day %d/%d/%d is a Sunday.\n", day, month, year);
	}else if(R==1){
    	printf("The day %d/%d/%d is a Monday.\n", day, month, year);
	}else if(R==2){
    	printf("The day %d/%d/%d is a Tuesday.\n", day, month, year);
	}else if(R==3){
    	printf("The day %d/%d/%d is a Wednesday.\n", day, month, year);
	}else if(R==4){
    	printf("The day %d/%d/%d is a Thursday.\n", day, month, year);
	}else if(R==5){
    	printf("The day %d/%d/%d is a Friday.\n", day, month, year);
	}else{
    	printf("The day %d/%d/%d is a Saturday.\n", day, month, year);
	}
    
}
/*
//Using main function to receive inputs and calculate, then display the results using the functions created above.
int main(void){
	int a, b, c;
	inputDate(&a, &b, &c);
	calculateDay(a, b, c);
    
return 0;    
}*/




