#include <stdio.h>
#include <math.h>

void calculator(){

int choice=0;


    while(choice!=3){



    int num1;
    int num2;
    char op;

    printf("\npress 1 to perform two number calculations\n");

    printf("\nPress 2 to perform one number(sin/cos/tan) calculations\n");

    printf("\npress 3 to perform square,square root and cube calculations\n");

    printf("\nPress 4 to Exit\n");

    printf("Enter your choice:");




    int choice;

    scanf("%d",&choice);

    if(choice == 1){


    printf("Enter your first number:\n");
    scanf("%d",&num1);

    printf("Enter your second number:\n");
    scanf("%d",&num2);

    printf("Choose your operator(+,-,*,/):");
    scanf(" %c",&op);

    switch (op)
    {
case '+':
    printf("%d+%d=%d",num1,num2,num1+num2);
    break;

case '-':
    printf("%d-%d=%d",num1,num2,num1-num2);
    break;

case '*':
    printf("%d*%d=%d",num1,num2,num1*num2);
    break;

case '/':
    if(num2==0){
        printf("Num2 cannot be zero");
        break;
    }
    printf("%d/%d=%d",num1,num2,num1/num2);
    break;


    }
    }

    else if(choice==2){
        double x;
        double x_in_radius;

        char opar;

        double result;

    printf("Enter angle in degree:\n");
        scanf("%lf",&x);
       
        printf("Choose your operation:\n");
        printf("sinx(press s)\n");
        printf("cosx(press c)\n");
        printf("tanx(press t)\n");

        

        scanf(" %c",&opar);





        switch(opar){

        case 's':
            x_in_radius=x*(M_PI/180);
            result=sin(x_in_radius);
            printf(" sin(%lf)=%lf",x,result);

            break;
         case 'c':
            x_in_radius=x*(M_PI/180);
            result=cos(x_in_radius);
            printf(" cos(%lf)=%lf",x,result);

            break;
         case 't':
            x_in_radius=x*(M_PI/180);
            result=tan(x_in_radius);
            printf(" tan(%lf)=%lf",x,result);

            break;


}

    }else if(choice==3){

        int num;
        char opr;

        printf("Enter your number:\n");
        scanf("%d",&num);

        printf("Choose your operation:\n");
        printf("Square(press s)\n");
        printf("Square root(press r)\n");
        printf("Cube(press c)\n");

        scanf(" %c",&opr);

        switch(opr){

        case 's':
            printf("Square of %d is %d",num,num*num);
            break;

         case 'r':
            printf("Square root of %d is %lf",num,sqrt(num));
            break;

         case 'c':
            printf("Cube of %d is %d",num,num*num*num);
            break;

        }

    }

    else if(choice==4){
        break;
    }

    else{
        printf("Invalid choice");
    }

    }
}


int main(){

calculator();


}
