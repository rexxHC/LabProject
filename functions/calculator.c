#include <stdio.h>
#include <math.h>

void calculator(){

int choice=0;


    while(choice!=3){



    int num1;
    int num2;
    char op;

    printf("\npress 1 to perform two number calculations:\n");

    printf("\nPress 2 to perform one number calculations:\n");

    printf("\nPress 3 to Exit:\n");




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
        float x;
        float x_in_radius;

        char opar;

        float result;


        printf("Enter angle in degree:\n");
        scanf("%f",&x);
        printf("Choose your operation:\n");
        printf("sinx(press s)\n");
        printf("cosx(press c)\n");
        printf("tanx(press t)\n");

        scanf(" %c",&opar);





        switch(opar){

        case 's':
            x_in_radius=x*(M_PI/180);
            result=sin(x_in_radius);
            printf("%f",result);

            break;
         case 'c':
            x_in_radius=x*(M_PI/180);
            result=cos(x_in_radius);
            printf("%f",result);

            break;
         case 't':
            x_in_radius=x*(M_PI/180);
            result=tan(x_in_radius);
            printf("%f",result);

            break;


}

    }



    else{
        printf("Invalid choice");
    }

    }
}


int main(){

calculator();


}
