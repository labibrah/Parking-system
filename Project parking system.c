#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>


int i,j;     /*Global variables*/
int main_exit;
int park_row;
int park_column;
FILE *fptr;


void fordelay(int j);
void exit_park(void);
void check_set_park(void);
void reset_parkings(void);
void menu(void);

typedef struct{
    char vehicle_type[5];
    int hours;
    int flag;
    time_t enter_time;

}space;

space spaces[2][2];

int main()
{
    char pass[10],password[20]="pass";    /*For login by admin of system*/



    printf("\n\n\t\tEnter the administrator password to login:");
    scanf("%s",pass);


    if (strcmp(pass,password)==0){
        {printf("\n\nPassword Match!\nLOADING");
        }
        for(i=0;i<6;i++)
        {
            fordelay(100000000);
            printf(".");
        }
                system("cls");
            menu();
        }
    else
    {
            MessageBeep(MB_ICONQUESTION);
            printf("\n\nWrong password!\a\a\a");
            printf("\nEnter 1 to try again and 0 to exit:");
            scanf("%d",&main_exit);
                if(main_exit==1){
                    main();
                }
                else{
                    return 0;
                }
    }

}

void fordelay(int j)  /*Creating delays while loading screens*/
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}

void menu(void)
{   int choice;

    system("cls");
    system("color 9");

    printf("\n\n\t\t\t\tPARKING LOT MANAGEMENT SYSTEM");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1.Car entry\n\t\t2.Car exit\n\t\t3.Reset all parkings\n\t\t4.Close menu\n\t\tEnter your choice: ");
    scanf("%d",&choice);

    system("cls");

    switch(choice)
    {
        case 1:check_set_park();
            {printf("\n\nRedirecting to main menu");
        }
        for(i=0;i<15;i++)
        {
            fordelay(100000000);
            printf(".");
        }
            menu();

        break;
        case 2:exit_park();
        break;
        case 3:reset_parkings();
            menu();
        break;
        case 4:
        exit(1);

    }
}

void check_set_park(void){

    int found=0;
    int choice;
    fptr = fopen("entry_data.txt","a");


    for(i=0;i<2;i++){              /*Check for empty parking spaces*/
        for(j=0;j<2;j++){
            if(spaces[i][j].flag==0){
                found +=1;
            }
        }
    }

    if(found==0){
        printf("Sorry no parking is available!");

    }
    else{
        printf("There are %d parking space(s) available:\n",found);

        for(i=0;i<2;i++){              /*Choose which empty parking space*/
            for(j=0;j<2;j++){
                if(spaces[i][j].flag==0){
                    printf("Row:%d Column:%d\n",i,j);
                }
            }
        }


        printf("Enter your choice of row: ");
        scanf("%d",&park_row);
        printf("Enter your choice of column: ");
        scanf("%d",&park_column);
        printf("Rates for parking:\n1)Sedan: Tk.10/sec\n2)SUV: Tk.20/sec\n3)Truck: Tk.40/sec\nEnter your vehicle type:");
        scanf("%d",&choice);

        if(choice==1){
                strcpy(spaces[park_row][park_column].vehicle_type,"Sedan");
        }
        else if(choice==2){
                strcpy(spaces[park_row][park_column].vehicle_type,"SUV");
        }
        else if(choice==2){
            strcpy(spaces[park_row][park_column].vehicle_type,"Truck");
            }


        spaces[park_row][park_column].enter_time= time(NULL);
        spaces[park_row][park_column].flag=1;
        printf("You have been assigned parking lot with row:%d and column:%d\n",park_row,park_column);

        fprintf(fptr, "\nVehicle of type \"%s\" at Row:%d Column:%d entered parking lot.\n", spaces[park_row][park_column].vehicle_type,park_row,park_column);
        fclose(fptr);

    }




}

void exit_park(void){


    float pay;
    float time_spent;
    int option;
    time_t end;
    fptr = fopen("exit_data.txt","a");

    printf("Enter your parking lot row: ");
    scanf("%d",&park_row);
    printf("Enter your parking lot column: ");
    scanf("%d",&park_column);

    spaces[park_row][park_column].flag=0; /*Sets parking lot location to empty*/

    end = time(NULL); /*Exit time assigned to 'end' variable*/
    time_spent = difftime(end,spaces[park_row][park_column].enter_time); /*Time spent at parking lot*/

    if(strcmp(spaces[park_row][park_column].vehicle_type,"Sedan")==0){
        pay = time_spent * 10;
    }
    else if(strcmp(spaces[park_row][park_column].vehicle_type,"SUV")==0){
        pay = time_spent * 20;
    }
    else if(strcmp(spaces[park_row][park_column].vehicle_type,"Truck")==0){
        pay = time_spent * 40;
    }

    fprintf(fptr, "\nVehicle of type \"%s\" at Row:%d Column:%d exited parking lot,spent %.2f seconds and paid a sum of Tk.%.2f.\n", spaces[park_row][park_column].vehicle_type,park_row,park_column,time_spent,pay);
    fclose(fptr);

    printf("Your total is TK: %.2f\nTime spent: %.2f seconds\n",pay,time_spent);
    printf("Press 1 after payment: \n");
    scanf("%d",&option);

    switch(option){
    case 1:
        printf("\n\nProcessing transaction. Have a nice day!");
        for(i=0;i<=6;i++)
        {
            fordelay(100000000);
            printf(".");
        }
        menu();

    }

}

void reset_parkings(void){

    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            spaces[i][j].flag=0;
        }
    }
    printf("\n\nAll parkings have been reset!\n\nRedirecting to main menu");

        for(i=0;i<=6;i++)
        {
            fordelay(100000000);
            printf(".");
        }
        menu();
}
