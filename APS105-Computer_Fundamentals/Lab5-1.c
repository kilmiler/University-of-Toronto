#include <stdio.h>
#include <math.h>
#include <stdbool.h>

//introducing variables
double i;
int originalNum, encryptNum, numOfDig;

//receiving inputs from user
void input(int *num){
	while(i==0){
    	printf("Please enter an integer greater than 99999: ");
    	scanf("%d", num);
    	if(*num<=99999){
        	printf("Incorrect input.\n");
    	}else{
        	printf("The number entered is %d\n", *num);
        	i=1;
    	}   
	}
}

//changing the input number (1st step)
int add4(int num){
	int deci, o=1, numOfDig = 0;
	while(o==1){
    	deci=num%(int)pow(10,numOfDig);
    	if(deci==num){
        	o=0;
    	}
    	numOfDig++;
	} numOfDig=numOfDig-1;
	int a, c=0;
	for(i=0; i<numOfDig ;i++){
    	a=num%10;
    	num/=10;
    	a+=4;
    	if(a>=10){
        	a-=10;
    	}
    	c=c+a*(int)pow(10,i);
	}
	return c;
}

//changing the input number (2nd step)
int shift(int num){
	int deci, o=1, numOfDig = 0;
	while(o==1){
    	deci=num%(int)pow(10,numOfDig);
    	if(deci==num){
        	o=0;
    	}
    	numOfDig++;
	} numOfDig=numOfDig-1;
    
	int back, front, div;
	div=pow(10, numOfDig-1);
	back=num%div;
	front=num/div;
	num=(back*10)+front;
    
	return num;
}

// printing the original input number and the output encrypted number
void printOutput(int encryptNum, int originalNum){
	printf("Original number: %d\n", originalNum);
	printf("Encrypted number: %d\n", encryptNum);
}

//main function that uses all the functions above
/*int main(void){
	input(&originalNum);   
	encryptNum=shift(add4(originalNum));
	printOutput(encryptNum, originalNum);
	 
return 0;   
}*/





