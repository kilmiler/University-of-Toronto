#include <stdio.h>

int main(void)
{
    //Introducing Variables (Input and Output)
    //Double for decimals, int for integers
    double inputPrice, inputUserMoney;
    int inputCouponsNeeded;
    double outputMoney, outputAveMoney;
    int outputCoffPurch, outputAddCoff1, outputCouponsLeft;
    
    //Printing texts to user, and receiving the inputs from user
    //If for false statements, Else for true statements and continue
    //return 0 to exit successfully at that point and not progress forward
    printf("How much does a coffee cost?\n");
    scanf("%lf", &inputPrice);
    if(inputPrice<0.01){
   	 printf("Invalid Input.\n");
   	 return 0;
    }else{
   	 printf("How many coupons does it take to get a free coffee?\n");
   	 scanf("%d", &inputCouponsNeeded);
   	 if(inputCouponsNeeded<=1){
   		 printf("Invalid Input.\n");
   		 return 0;
   	 }else{
   		 printf("How much money do you have to spend on coffee this month?\n");
   		 scanf("%lf", &inputUserMoney);
   		 if(inputUserMoney<0){
   			 printf("Invalid Input.\n");
   			 return 0;
   		 }    
   	 }
    }
    
    //calculating outputs with inputed data from user
    //printing the calculated output to user
    //If for not sufficient amount of coupons, Else for sufficient amount of coupons
    outputCoffPurch = inputUserMoney/inputPrice;
    printf("This month, you can purchase %d coffees at $%0.2lf each.\n", outputCoffPurch, inputPrice);
    
    outputAddCoff1 = outputCoffPurch/inputCouponsNeeded;
    outputCouponsLeft = outputCoffPurch-(outputAddCoff1*inputCouponsNeeded)+outputAddCoff1;
    while(outputCouponsLeft>=inputCouponsNeeded){
   	 outputAddCoff1++;
   	 outputCouponsLeft++;
   	 outputCouponsLeft-= inputCouponsNeeded;
    }    
   	 if(outputAddCoff1<1){
   		 printf("You will not be able to redeem any additional coffees from coupons this month.\n");
   	 }
   	 else{
   		 printf("You will be able to redeem an additional %d coffee(s) from coupons.\n", outputAddCoff1);
   	 }
    
    outputMoney = inputUserMoney - (outputCoffPurch*inputPrice);
    outputCouponsLeft = outputCoffPurch-(outputAddCoff1*inputCouponsNeeded)+outputAddCoff1;
    printf("At the end of the month, you will have $%0.2lf and %d coupon(s) remaining.\n", outputMoney, outputCouponsLeft);\
    
    outputAveMoney = inputPrice*outputCoffPurch/(outputCoffPurch+outputAddCoff1);
    printf("On average, you spent $%0.2lf on each cup of coffee this month.\n", outputAveMoney);
    return 0;
}


