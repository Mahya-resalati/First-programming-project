#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#include<ctype.h>
#include<time.h>
#include<windows.h>

//the linked list is global because the program needs it in many functions
struct income
    {
        char type[50];
        char amount[20];
        char date[20];
        char description[250];
        struct income *next;
    };

    struct expense
    {
        char type[50];
        char amount[20];
        char date[20];
        char description[250];
        struct expense *next;
    };

struct income *start, *end, *temp;
struct expense *eStart, *eEnd, *eTemp;

#include"projectfunctions.h"

void main()
{
    char choice[3], choice2[3], choice3[3], choice4[3], fileCountStr[12], fileName[50], incomeStart[10], expenseStart[15];
    FILE *profile, *fileCount;
    int choiceNo, choice2No, choice3No, choice4No;
    long int fileCountNo, fileCountNo2;

    do
    {
        printf("Welcome to this accounting program\n\n");
        printf("1)Sign up\n2)Login\n3)Exit\n");
        printf("Please enter the number of your choice:");
        gets(choice);
        choiceNo=atoi(choice);
        system("cls");

        //checking the number not to be out of range
        while(choiceNo>3 || choiceNo<1)
        {
            printf("The number you entered is out of range.Please try again\n\n");
            printf("1)Sign up\n2)Login\n3)Exit\n");
            printf("Please enter the number of your choice:");
            gets(choice);
            choiceNo=atoi(choice);
            system("cls");
        }
        while(choiceNo==1)
        {
            signup();
            printf("\nNow login to your account to use the program\n");
            printf("1)Sign up\n2)Login\n3)Exit\n");
            printf("Please enter the number of your choice:");
            gets(choice);
            choiceNo=atoi(choice);
            system("cls");

            //checking the number not to be out of range
            while(choiceNo>3 || choiceNo<1)
            {
                printf("The number you entered is out of range.Please try again\n\n");
                printf("1)Sign up\n2)Login\n3)Exit\n");
                printf("Please enter the number of your choice:");
                gets(choice);
                choiceNo=atoi(choice);
                system("cls");
            }
        }
        if
        (choiceNo==2)
        {
            fileCountNo = login();
            system("cls");

            do
            {
                choice3No=0;
                printf("Welcome to the main menu\n");
                printf("1)Income\n2)Expenses\n3)Reports\n4)Settings\n5)Sign out\n6)Exit\n");
                printf("Please enter the number of your choice:");
                gets(choice2);
                choice2No=atoi(choice2);
                system("cls");
                //checking the range of choice
                while(choice2No>6 || choice2No<1)
                {
                    printf("The number you entered is out of range.Please try again\n\n");
                    printf("1)Income\n2)Expenses\n3)Reports\n4)Settings\n5)Sign out\n6)Exit\n");
                    printf("Please enter the number of your choice:");
                    gets(choice2);
                    choice2No=atoi(choice2);
                    system("cls");
                }
                //end of checking process
                if
                    (choice2No == 1)
                {
                    //start of saving incomes section
                    income(fileCountNo);
                    printf("\n\n1)Adding another income\n2)Going back to the main menu\n3)exit\n\nPlease enter the number of your choice:");
                    gets(choice3);
                    choice3No = atoi(choice3);

                    //checking the number not to be out of range
                    while(choice3No<1 || choice3No>3)
                    {
                        printf("The number you entered is out of range!!!\nPlease try again:");
                        gets(choice3);
                        choice3No = atoi(choice3);
                    }

                    /*if the choice of the user is 1 the program will get another income information
                    if the choice is 2 the program will go back to the main menu
                    and if it's 3 the user will exit the program*/
                    while(choice3No == 1)
                    {
                        income(fileCountNo);
                        printf("\n\n1)Adding another income\n2)Going back to the main menu\n3)exit\n\nPlease enter the number of your choice:");
                        gets(choice3);
                        choice3No = atoi(choice3);
                    }
                    if
                        (choice3No == 3)
                        exit(main);

                    system("cls");
                }
                else
                    if
                        (choice2No == 2)
                    {
                        //start of saving expenses section
                        expense(fileCountNo);

                        printf("\n\n1)Adding another expense\n2)Going back to the main menu\n3)exit\n\nPlease enter the number of your choice:");
                        gets(choice3);
                        choice3No = atoi(choice3);

                        //checking the number not to be out of range
                        while(choice3No<1 || choice3No>3)
                        {
                            printf("The number you entered is out of range!!!\nPlease try again:");
                            gets(choice3);
                            choice3No = atoi(choice3);
                        }

                        /*if the choice of the user is 1 the program will get another expense information
                        if the choice is 2 the program will go back to the main menu
                        and if it's 3 the user will exit the program*/
                        while(choice3No == 1)
                        {
                            expense(fileCountNo);
                            printf("\n\n1)Adding another expense\n2)Going back to the main menu\n3)exit\n\nPlease enter the number of your choice:");
                            gets(choice3);
                            choice3No = atoi(choice3);
                        }
                        if
                            (choice3No == 3)
                            exit(main);

                        system("cls");
                    }
                    else
                        if
                            (choice2No == 3)
                        {
                            //saving income file data in linked list
                            strcpy(fileName, "profile");
                            itoa(fileCountNo, fileCountStr, 10);
                            strcat(fileName, fileCountStr);
                            strcat(fileName, ".txt");
                            profile = fopen(fileName, "r");
                            if
                                (profile == NULL)
                                printf("File couldn't be opened!!!");
                            else
                            {
                                do
                                    fgets(incomeStart, 12, profile);
                                while(strcmp(incomeStart, "Incomes:\n") != 0);

                                fgets(incomeStart, 12, profile);

                                start = malloc(sizeof(struct income));
                                temp = start;
                                fgets(temp->type, 50, profile);
                                fgets(temp->amount, 20, profile);
                                fgets(temp->date, 20, profile);
                                fgets(temp->description, 250, profile);
                                temp->next = NULL;
                                fgets(incomeStart, 12, profile);

                                while(feof(profile) == 0)
                                {
                                    end = malloc(sizeof(struct income));
                                    temp->next = end;
                                    temp = end;
                                    fgets(temp->type, 50, profile);
                                    fgets(temp->amount, 20, profile);
                                    fgets(temp->date, 20, profile);
                                    fgets(temp->description, 250, profile);
                                    fgets(incomeStart, 12, profile);
                                    temp->next = NULL;
                                }
                            }
                            fclose(profile);

                            //saving expense file data in linked list
                            strcpy(fileName, "profile");
                            fileCountNo2 = fileCountNo + 1;
                            itoa(fileCountNo2, fileCountStr, 10);
                            strcat(fileName, fileCountStr);
                            strcat(fileName, ".txt");
                            profile = fopen(fileName, "r");
                            if
                                (profile == NULL)
                                printf("File couldn't be opened!!!");
                            else
                            {
                                fgets(expenseStart, 12, profile);
                                fgets(expenseStart, 12, profile);

                                eStart = malloc(sizeof(struct expense));
                                eTemp = eStart;
                                fgets(eTemp->type, 50, profile);
                                fgets(eTemp->amount, 20, profile);
                                fgets(eTemp->date, 20, profile);
                                fgets(eTemp->description, 250, profile);
                                eTemp->next = NULL;
                                fgets(expenseStart, 12, profile);

                                while(feof(profile) == 0)
                                {
                                    eEnd = malloc(sizeof(struct expense));
                                    eTemp->next = eEnd;
                                    eTemp = eEnd;
                                    fgets(eTemp->type, 50, profile);
                                    fgets(eTemp->amount, 20, profile);
                                    fgets(eTemp->date, 20, profile);
                                    fgets(eTemp->description, 250, profile);
                                    fgets(expenseStart, 12, profile);
                                    eTemp->next = NULL;
                                }
                            }
                            fclose(profile);
                            //end of linked list process

                            printf("Welcome to the reports section\n\n");
                            printf("1)Account balance\n2)Income reports\n3)Expense reports\n\nPlease enter the number of your choice:");
                            gets(choice4);
                            choice4No = atoi(choice4);

                            //checking the range of choice
                            while(choice4No>3 || choice4No<1)
                            {
                                printf("The number you entered is out of range!!!\nPlease try again:");
                                gets(choice4);
                                choice4No = atoi(choice4);

                            }
                            system("cls");

                            if
                                (choice4No == 1)
                            {
                                //account balance section
                                choice3No = accountBalance();
                            }
                            else
                                if
                                    (choice4No == 2)
                                {
                                    //income reports section
                                    choice3No = incomeReports();
                                }
                                else
                                    if
                                        (choice4No == 3)
                                    {
                                        //expense reports section
                                        choice3No = expenseReports();
                                    }

                            //free linked list to get the new data for next time
                            free(temp);
                            free(end);
                            free(start);
                            free(eTemp);
                            free(eEnd);
                            free(eStart);
                        }
                        else
                            if
                                (choice2No == 4)
                            {
                                //saving income file data in linked list
                                strcpy(fileName, "profile");
                                itoa(fileCountNo, fileCountStr, 10);
                                strcat(fileName, fileCountStr);
                                strcat(fileName, ".txt");
                                profile = fopen(fileName, "r");
                                if
                                    (profile == NULL)
                                    printf("File couldn't be opened!!!");
                                else
                                {
                                    do
                                        fgets(incomeStart, 12, profile);
                                    while(strcmp(incomeStart, "Incomes:\n") != 0);

                                    fgets(incomeStart, 12, profile);

                                    if
                                        (feof(profile) == 0)
                                    {
                                        start = malloc(sizeof(struct income));
                                        temp = start;
                                        fgets(temp->type, 50, profile);
                                        fgets(temp->amount, 20, profile);
                                        fgets(temp->date, 20, profile);
                                        fgets(temp->description, 250, profile);
                                        temp->next = NULL;
                                        fgets(incomeStart, 12, profile);
                                    }

                                    while(feof(profile) == 0)
                                    {
                                        end = malloc(sizeof(struct income));
                                        temp->next = end;
                                        temp = end;
                                        fgets(temp->type, 50, profile);
                                        fgets(temp->amount, 20, profile);
                                        fgets(temp->date, 20, profile);
                                        fgets(temp->description, 250, profile);
                                        fgets(incomeStart, 12, profile);
                                        temp->next = NULL;
                                    }
                                }
                                fclose(profile);
                                //end of linked list process

                                //setting section
                                choice3No = setting(fileCountNo);

                                //free linked list to get the new data for next time
                                free(temp);
                                free(end);
                                free(start);
                            }
                            else
                                if
                                    (choice2No == 6)
                                    exit(main);
            }
            //if the choice of the user is 2 it will go back to the main menu again
            while(choice3No == 2);

            //if the choice of the user is 1 it will go back to the main menu again
            if
                (choice3No == 1)
            {
                exit(main);
            }
        }
        else
            if
                (choiceNo == 3)
                exit(main);
    }
    while(choice2No == 5);
    getch();
}

