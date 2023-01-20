#include <stdio.h>
#include <math.h>
#include <stdbool.h>

double stepsize, a, b, y, x;
int numOfRec, i;

void skipLine(void){
    printf("\n");
}

void GetInputs(void){
    printf("Enter the Left boundary: a, Right boundary: b, and No. of rectangles to use.\n");
    printf("To exit enter 0 0 0\n");
    scanf("%lf %lf %d", &a, &b, &numOfRec);
}

bool validateInput(double left, double right, int n){
    int exit;
    exit = 0;
    
        if(left==exit && right==exit && n==exit){
            printf("Invalid inputs...\n");
            skipLine();
            printf("Terminating main!\n");
            i=2;
        }else if(left<-10 || right>10 || right<=left || n<=0){
             printf("Invalid inputs...\n");
        }
        i = 1;
return 1;
}

double evalFunc(double x){
    y = 2*pow(x,2) - (7*x) - 2;
    return y;
}

int main(void){
    while(i==0){
    GetInputs();
    validateInput(a, b, numOfRec);
    }
    if(i==2){
        return 0;
    } 
    
    stepsize=(b-a)/numOfRec;
    printf("With step size: %.4lf\n", stepsize);
    printf("The approximate integral of the f(x) = 2(x^2)-7x-2\n");
    printf("Bound between %.2lf and %.2lf, using %d rectangles is as follows\n", a, b, numOfRec);
    
    double midEvalY, leftEvalY, rightEvalY, areaMid, areaLeft, areaRight, sumLeft=0, sumMid=0, sumRight=0;

    
    for(int n=0; n<=numOfRec-1; n++){
    leftEvalY = evalFunc(a+(stepsize*n));
    sumLeft=leftEvalY+sumLeft;
    }
    
    areaLeft = sumLeft*stepsize;
    
    for(int m=0; m<=numOfRec-1; m++){
    midEvalY = evalFunc(a+(stepsize/2)+(stepsize*m));
    sumMid=midEvalY+sumMid;
    }
    
    areaMid = sumMid*stepsize;
    
    for(int l=1; l<=numOfRec; l++){
    rightEvalY = evalFunc(a+(stepsize*l));
    sumRight=rightEvalY+sumRight;
    }
    
    areaRight = sumRight*stepsize;
    
    skipLine();
    printf("Mid point evaluation approximate: %.4lf\n", areaMid);
    printf("Left point evaluation approximate: %.4lf\n", areaLeft);
    printf("Right point evaluation approximate: %.4lf\n", areaRight);
     
	return 0;
}


