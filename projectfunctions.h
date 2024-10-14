void signup()
{
    struct personInfo
    {
        char firstName[20];
        char lastName[40];
        char id[11];
        char mobileNo[12];
        char email[70];
        char pass[17];
        char passAgain[16];
    };
    struct personInfo person;
    char fileName[50], fileCountStr[12], passNumStr[2], tempPass, compare[15], idForComparing[15];
    FILE *profile, *fileCount;
    long int  fileCountNo, multiplyIn, passNum;
    int i=0, sign=0, alphaAndSign=0, digit=0;

    //getting sign up information
    printf("Please fill out the form below\n");
    printf("First name:");
    gets(person.firstName);

    //checking first name not to contain any number
    while(person.firstName[i] != '\0')
    {
        while(isdigit(person.firstName[i]) == 1)
        {
            printf("The entered first name isn't in correct format(It mustn't contain any number or sign)\nPlease try again:");
            gets(person.firstName);
            i=0;
        }
        i++;
    }

    printf("Last name:");
    gets(person.lastName);

    //checking last name not to have any number
    i=0;
    while(person.lastName[i] != '\0')
    {
        while(isdigit(person.lastName[i]) == 1)
        {
            printf("The entered last name isn't in correct format(It mustn't contain any number or sign)\nPlease try again:");
            gets(person.lastName);
            i=0;
        }
        i++;
    }

    printf("ID:");
    gets(person.id);

    /*opening counter file to know what number the last profile had been so we start to open
    income files from the last file to the first file to check if the entered id is repeated
    if the id has already existed in the files it means the user has entered a wrong id because id must be unique
    so the program asks the user to try again because the program is gonna use the id as the username so it must be unique*/
    do
    {
        sign=0;
        //checking id to just contain numbers and checking its length
        i=0;
        while(person.id[i] != '\0')
        {
            while(isdigit(person.id[i]) == 0 || strlen(person.id) != 10)
            {
                printf("The entered id isn't in correct format(The length of your id most be 10 characters and it mustn't contain any letter or sign)\nPlease try again:");
                gets(person.id);
                i=0;
            }
            i++;
        }

        fileCount = fopen("file_counter.txt", "r");
        if
            (fileCount == NULL)
            printf("The file couldn't be opened");
        else
        {
            fgets(fileCountStr, 11, fileCount);
            fileCountNo = atoi(fileCountStr);
            fileCountNo = fileCountNo-2;
            /*mines 2 is because the number we get is one digit more than the last file which is expense file
            so it's 2 digits more than the last income file and we need to check just income file*/
            fclose(fileCount);
        }
        for(fileCountNo ;fileCountNo>=0 ;fileCountNo = fileCountNo-2)
        {
            //preparing the file name to open it
            strcpy(fileName, "profile");
            itoa(fileCountNo, fileCountStr, 10);
            strcat(fileName, fileCountStr);
            strcat(fileName, ".txt");
            profile = fopen(fileName, "r");
            //opening the file and start checking
            if
                (profile == NULL)
                printf("The file couldn't be opened");
            else
            {
                fgets(compare, 20, profile);
                fgets(compare, 20, profile);
                fgets(compare, 20, profile);
                fgets(compare, 20, profile);
                fgets(compare, 20, profile);
                fgets(compare, 20, profile);
                fgets(compare, 20, profile);
                fgets(compare, 20, profile);
                fgets(compare, 20, profile);
                strcpy(idForComparing, person.id);
                strcat(idForComparing, "\n");
                if
                    (strcmp(compare ,idForComparing) == 0)
                    {
                        printf("\nThe entered id is repeated!!!Please enter a unique id:");
                        gets(person.id);
                        sign=1;
                        fclose(profile);
                        break;
                    }

            }
            fclose(profile);
        }

    }while(sign == 1);


    printf("Mobile number:");
    gets(person.mobileNo);

    //checking mobile number to began with 09 and contain just numbers and also checking its length
    i=0;
    while(person.mobileNo[i] != '\0')
    {
        while(isdigit(person.mobileNo[i]) == 0 || strlen(person.mobileNo) != 11 || person.mobileNo[0] != '0' || person.mobileNo[1] != '9')
        {
            printf("The entered mobile number isn't in correct format(The length of your id most be 11 characters and it mustn't contain any letter or sign and it must began with '09')\nPlease try again:");
            gets(person.mobileNo);
            i=0;
        }
        i++;
    }

    printf("Email:");
    gets(person.email);

    //checking email format to contain @ and .
    sign=0;
    i=0;
    while(person.email[i] != '\0')
    {
        if(person.email[i] == '@')
        {
            sign++;
        }
        else
            if(person.email[i] == '.')
            {
                sign++;
            }
        i++;
    }

    while(sign != 2)
    {
        printf("The entered email address isn't in correct format(It must contain '@' and '.' character)\nPlease try again:");
        gets(person.email);
        sign=0;
        i=0;
        while(person.email[i] != '\0')
        {
            if(person.email[i] == '@')
            {
                sign++;
            }
            else
                if(person.email[i] == '.')
                {
                    sign++;
                }
            i++;
        }
    }

    printf("Password:");
    gets(person.pass);

    //checking password to contain letters and digits both and not to be too short or too long
    i=0;
    while(person.pass[i] != '\0')
    {
        if
            (isdigit(person.pass[i]) == 1)
        {
            digit++;
        }
        else
            alphaAndSign++;

        i++;
    }

    while(alphaAndSign<1 || digit<1 || strlen(person.pass)<8 || strlen(person.pass)>15)
    {
        printf("The entered password isn't in correct format(It must be at least 8 and at most 15 characters and it must contain letters and numbers both together)\nPlease try again:");
        gets(person.pass);
        i=0;
        alphaAndSign=0;
        digit=0;
        while(person.pass[i] != '\0')
        {
            if
                (isdigit(person.pass[i]) == 1)
            {
                digit++;
            }
            else
                alphaAndSign++;

            i++;
        }
    }

    //getting password again and compare it to confirm it
    printf("Password again:");
    gets(person.passAgain);
    while(strcmp(person.passAgain ,person.pass) != 0)
    {
        printf("Your password is incompatible!!!Please try again\n");
        printf("Password:");
        gets(person.pass);

        printf("Password again:");
        gets(person.passAgain);
    }

    //manipulating the password then saving it in file to improve security
    i=0;
    multiplyIn=2;
    //changing the numbers in password
    while(person.pass[i] != '\0')
    {
        if
            (isdigit(person.pass[i]) == 1)
        {
            passNumStr[0] = person.pass[i];
            passNumStr[1] = '\0';
            passNum = atoi(passNumStr);
            passNum = passNum * multiplyIn;
            passNum = passNum % 10;
            itoa(passNum, passNumStr, 10);
            person.pass[i] = passNumStr[0];
            multiplyIn = (multiplyIn + 2) * 3;
        }
        if
                (i==4 || i==9)
            {
                multiplyIn = 3;
            }
            else
                if
                    (i==13)
                {
                    multiplyIn = 2;
                }
        i++;
    }
    //changing the places of the first 8 characters in password(because we're sure there is at least 8 characters
    tempPass = person.pass[3];
    person.pass[3] = person.pass[5];
    person.pass[5] = tempPass;
    tempPass = person.pass[4];
    person.pass[4] = person.pass[6];
    person.pass[6] = tempPass;
    tempPass = person.pass[1];
    person.pass[1] = person.pass[7];
    person.pass[7] = tempPass;
    tempPass = person.pass[2];
    person.pass[2] = person.pass[8];
    person.pass[8] = tempPass;

    //getting the number from a file(it's a counter file that contains zero at first and increase one digit every time we make a new profile that changes the program to a multi user program)
    fileCount = fopen("file_counter.txt", "r+");
    if
        (fileCount == NULL)
        printf("File couldn't be opened!!!");
    else
    {
        //preparing the name of the new profile
        strcpy(fileName, "profile");
        fgets(fileCountStr, 11, fileCount);
        strcat(fileName, fileCountStr);
        strcat(fileName ,".txt");

        //increasing one digit to the number and saving it in counter file to have a new number for the next new profile
        fileCountNo = atoi(fileCountStr);
        fileCountNo++;
        itoa(fileCountNo, fileCountStr, 10);
        rewind(fileCount);
        fputs(fileCountStr, fileCount);
        fclose(fileCount);

        profile = fopen(fileName, "w");
        if
            (profile == NULL)
            printf("File couldn't be opened!!!");
        else
        {
            //saving entered data by the user to a specific file which is gonna contain sign up data and also incomes data
            fputs("Confirmed password:\n", profile);
            fputs(person.pass, profile);
            fputc('\n', profile);

            fputs("First name:\n", profile);
            fputs(person.firstName, profile);
            fputc('\n', profile);

            fputs("Last name:\n", profile);
            fputs(person.lastName, profile);
            fputc('\n', profile);

            fputs("ID:\n", profile);
            fputs(person.id, profile);
            fputc('\n', profile);

            fputs("Mobile number:\n", profile);
            fputs(person.mobileNo, profile);
            fputc('\n', profile);

            fputs("Email:\n", profile);
            fputs(person.email, profile);
            fputc('\n', profile);
            fputc('\n', profile);
            fputc('\n', profile);

            fputs("Incomes:\n", profile);
        }
        fclose(profile);
    }

    system("cls");
    printf("Congratulation\nYou signed up successfully");

    //using the counter file again to make a new file for expenses data
    fileCount = fopen("file_counter.txt", "r+");
    if
        (fileCount == NULL)
        printf("File couldn't be opened!!!");
    else
    {
        strcpy(fileName, "profile");
        fgets(fileCountStr, 11, fileCount);
        strcat(fileName, fileCountStr);
        strcat(fileName ,".txt");
        profile = fopen(fileName, "w");
        fileCountNo = atoi(fileCountStr);
        fileCountNo++;
        itoa(fileCountNo, fileCountStr, 10);
        rewind(fileCount);
        fputs(fileCountStr, fileCount);
        fclose(fileCount);
        if
            (profile == NULL)
            printf("File couldn't be opened!!!");
        else
        {
            fputs("expenses:\n", profile);
            fclose(profile);
        }
    }

}




int login()
{
    char asterisk, username[20], password[17], fileCountStr[12], fileName[50], compare[20], tempPass, passNumStr[2];
    FILE *profile, *fileCount;
    long int fileCountNo=-1, sign=1, mainFileCountNo, multiplyIn, passNum;
    int i=0;
    static int counter;
    /*static int is because we want the counter to increase one digit every time we call the function and because
    we call the function inside the function itself we need something that initialize just one time at first and doesn't loose its value when we call the function again*/

    printf("Please enter your username and password to login\n");
    printf("Username(Enter your ID as the username):\n");
    gets(username);

    //checking id to just contain numbers and checking its length
    i=0;
    while(username[i] != '\0')
    {
        while(isdigit(username[i]) == 0 || strlen(username) != 10)
        {
            printf("The entered username isn't in correct format(The length of your username most be 10 characters and it mustn't contain any letter or sign)\nPlease try again:");
            gets(username);
            i=0;
        }
        i++;
    }

    strcat(username, "\n");
    printf("Password:\n");

    //printing asterisks instead of the password characters
    i=0;
    while(1)
    {
        asterisk = getch();
        while(asterisk == '\b')
        {
            printf("\b \b");
            i--;
            asterisk = getch();
        }
        if
            (asterisk == '\r')
        {
            password[i] = '\0';
            break;
        }
        password[i] = asterisk;
        asterisk = '*';
        printf("%c", asterisk);
        i++;
    }
    //manipulating the password(the exact way we did it in sign up section)to compare it with the manipulated password which has been saved in file
    i=0;
    multiplyIn=2;
    //changing the password numbers
    while(password[i] != '\0')
    {
        if
            (isdigit(password[i]) == 1)
        {
            passNumStr[0] = password[i];
            passNumStr[1] = '\0';
            passNum = atoi(passNumStr);
            passNum = passNum * multiplyIn;
            passNum = passNum % 10;
            itoa(passNum, passNumStr, 10);
            password[i] = passNumStr[0];
            multiplyIn = (multiplyIn + 2) * 3;
        }
        if
                (i==4 || i==9)
            {
                multiplyIn = 3;
            }
            else
                if
                    (i==13)
                {
                    multiplyIn = 2;
                }
        i++;
    }
    //changing the places of the first 8 characters in password(because we're sure there is at least 8 characters
    tempPass = password[3];
    password[3] = password[5];
    password[5] = tempPass;
    tempPass = password[4];
    password[4] = password[6];
    password[6] = tempPass;
    tempPass = password[1];
    password[1] = password[7];
    password[7] = tempPass;
    tempPass = password[2];
    password[2] = password[8];
    password[8] = tempPass;

    strcat(password, "\n");

    /*opening counter file to know what number the last profile had been so we start to open
    income files from the last file to the first file to check the username and password*/
    fileCount = fopen("file_counter.txt", "r");
    if
        (fileCount == NULL)
        printf("The file couldn't be opened");
    else
    {
        fgets(fileCountStr, 11, fileCount);
        fileCountNo = atoi(fileCountStr);
        fileCountNo = fileCountNo-2;
        /*mines 2 is because the number we get is one digit more than the last file which is expense file
        so it's 2 digits more than the last income file and we need to check just income file*/
        fclose(fileCount);
    }

    //opening every income file from the last one to the first one which is profile0 to check the username and password
    for(fileCountNo ;fileCountNo>=0 ;fileCountNo = fileCountNo-2)
    {
        //preparing the file name to open it
        strcpy(fileName, "profile");
        itoa(fileCountNo, fileCountStr, 10);
        strcat(fileName, fileCountStr);
        strcat(fileName, ".txt");
        profile = fopen(fileName, "r");
        //opening the file and start checking
        if
            (profile == NULL)
            printf("The file couldn't be opened");
        else
        {
            while(feof(profile) == 0)
            {
                fgets(compare, 20, profile);
                if
                    (strcmp(compare, password) == 0)
                {
                    fgets(compare, 20, profile);
                    fgets(compare, 20, profile);
                    fgets(compare, 20, profile);
                    fgets(compare, 20, profile);
                    fgets(compare, 20, profile);
                    fgets(compare, 20, profile);
                    if
                        (strcmp(compare ,username) == 0)
                        sign = 0;
                }
            }
        }
        if
            (sign == 0)
            break;
        fclose(profile);
    }
    if(sign != 0)
            {
                system("cls");
                printf("The information you entered is incompatible!!!\n");
                counter++;
                //if the user enters wrong information for 5 times the program locks for 10 minutes
                if
                    (counter == 5)
                {
                    printf("You've entered incompatible information for 5 times so your access to login has been disconnected for 10 minutes!!");
                    Sleep(600000);
                }
                printf("Please try again\n\n");
                login();
            }
    /*sending the counter to the main function is because to use it again and again as we want to use
    the files that is related to the user who has just logged in*/
    mainFileCountNo = atoi(fileCountStr);
    return mainFileCountNo;

}







void income(long int fileCountNo)
{
    char choice[3], fileCountStr[12], fileName[50], incomeType[50], incomeAmount[20], incomeDate[20], description[250];
    FILE *profile;
    int choiceNo, i=0, counter=0;

    //getting income information
    printf("Please fill out the form below with your income information\n\n");
    printf("Income type:\n");
    printf("1)Programming salary\n2)Yaraneh\n3)Pocket money\n4)University grant\n5)Other\n");
    printf("Please enter the number of your choice:");
    gets(choice);
    choiceNo=atoi(choice);

    //checking if the number is out of range
    while(choiceNo>5 || choiceNo<1)
    {
        system("cls");
        printf("The number you entered is out of range.Please try again\n\n");
        printf("Income type:\n");
        printf("1)Programming salary\n2)Yaraneh\n3)Pocket money\n4)University grant\n5)Other\n");
        printf("Please enter the number of your choice:");
        gets(choice);
        choiceNo=atoi(choice);
    }

    //an option to save another type of income except the 4 specific items which have been mentioned
    if
        (choiceNo == 5)
    {
        printf("Please enter your income type:");
        gets(incomeType);
    }

    printf("\n\nAmount of income(in rial format):");
    gets(incomeAmount);

    //checking income amount to contain just numbers
    while(incomeAmount[i] != '\0')
    {
        while(isdigit(incomeAmount[i]) == 0)
        {
            printf("The entered amount isn't in correct format(It mustn't contain any letter or sign)\nPlease try again:");
            gets(incomeAmount);
            i=0;
        }
        i++;
    }

    printf("\n\nIncome date(in yyyy/mm/dd format):");
    gets(incomeDate);

    //checking income date to contain two / characters and also just contain numbers and also checking its length
    i=0;
    while(incomeDate[i] != '\0')
    {
        if
            (incomeDate[i] == '/')
        {
            counter++;
            i++;
            continue;
        }
        while(isdigit(incomeDate[i]) == 0 || strlen(incomeDate)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(incomeDate);
            i=0;
            counter=0;
        }
        i++;
    }

    while(counter != 2)
    {
        i=0;
        counter = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(incomeDate);
        while(incomeDate[i] != '\0')
        {
            if
                (incomeDate[i] == '/')
            {
                counter++;
                i++;
                continue;
            }
            while(isdigit(incomeDate[i]) == 0 || strlen(incomeDate)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(incomeDate);
                i=0;
                counter=0;
            }
            i++;
        }
    }

    printf("\n\nShort description:");
    gets(description);

    //checking description length
    while(strlen(description)>200)
    {
        printf("The entered description is too long!!!\nPlaese try again:");
        gets(description);
    }

    /*opening the income file of the user and saving income data
    (we use the number which has been returned from login function as the income file number)*/
    strcpy(fileName, "profile");
    itoa(fileCountNo, fileCountStr, 10);
    strcat(fileName, fileCountStr);
    strcat(fileName, ".txt");
    profile = fopen(fileName, "a");
    if
        (profile == NULL)
        printf("File couldn't be opened!!!");
    else
    {
    fputc('\n', profile);
    if
        (choiceNo == 1)
        fputs("Programming salary\n", profile);
    else
        if
            (choiceNo == 2)
            fputs("Yaraneh\n", profile);
        else
            if
                (choiceNo == 3)
                fputs("Pocket money\n", profile);
            else
                if
                    (choiceNo == 4)
                    fputs("University grant\n", profile);
                else
                {
                    fputs(incomeType, profile);
                    fputc('\n', profile);
                }
    fputs(incomeAmount, profile);
    fputc('\n', profile);
    fputs(incomeDate, profile);
    fputc('\n', profile);
    fputs(description, profile);
    fputc('\n', profile);
    printf("\nYour income information has been recorded successfully");
    }
    fclose(profile);

}




void expense(long int fileCountNo)
{
    char choice[3], choice2[3], fileCountStr[12], fileName[50], expenseType[50], expenseAmount[20], expenseDate[20], expenseDescription[250];
    FILE *profile;
    long int fileCountNo2;
    int choiceNo, choice2No, i=0, counter=0;

    //getting expense information
    printf("Please fill out the form below with your expenses information\n\n");
    printf("expense type:\n");
    printf("1)Tuition fees\n2)Transportation cost\n3)Medical expenses\n4)Leisure expenses\n5)Mobile and internet bills\n6)Buying clothes\n7)Helping charity\n8)Other\n");
    printf("Please enter the number of your choice:");
    gets(choice);
    choiceNo=atoi(choice);

    //checking if the number is out of range
    while(choiceNo>8 || choiceNo<1)
    {
        system("cls");
        printf("The number you entered is out of range.Please try again\n\n");
        printf("expense type:\n");
        printf("1)Tuition fees\n2)Transportation cost\n3)Medical expenses\n4)Leisure expenses\n5)Mobile and internet bills\n6)Buying clothes\n7)Helping charity\n8)Other\n");
        printf("Please enter the number of your choice:");
        gets(choice);
        choiceNo=atoi(choice);
    }

    //an option to save another type of income except the 7 specific items which have been mentioned
    if
        (choiceNo == 8)
    {
        printf("Please enter your expense type:");
        gets(expenseType);
    }
    printf("\n\nAmount of expense(in rial format):");
    gets(expenseAmount);

    //checking expense amount to contain just numbers
    while(expenseAmount[i] != '\0')
    {
        while(isdigit(expenseAmount[i]) == 0)
        {
            printf("The entered amount isn't in correct format(It mustn't contain any letter or sign)\nPlease try again:");
            gets(expenseAmount);
            i=0;
        }
        i++;
    }

    printf("\n\nExpense date(in yyyy/mm/dd format):");
    gets(expenseDate);

    //checking expense date to contain two / characters and also just contain numbers and also checking its length
    i=0;
    while(expenseDate[i] != '\0')
    {
        if
            (expenseDate[i] == '/')
        {
            counter++;
            i++;
            continue;
        }
        while(isdigit(expenseDate[i]) == 0 || strlen(expenseDate)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(expenseDate);
            i=0;
            counter=0;
        }
        i++;
    }

    while(counter != 2)
    {
        i=0;
        counter = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(expenseDate);
        while(expenseDate[i] != '\0')
        {
            if
                (expenseDate[i] == '/')
            {
                counter++;
                i++;
                continue;
            }
            while(isdigit(expenseDate[i]) == 0 || strlen(expenseDate)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(expenseDate);
                i=0;
                counter=0;
            }
            i++;
        }
    }

    printf("\n\nShort description:");
    gets(expenseDescription);

    //checking description length
    while(strlen(expenseDescription)>200)
    {
        printf("The entered description is too long!!!\nPlaese try again:");
        gets(expenseDescription);
    }

    /*opening the expense file of the user and saving expense data(we use the number which has been returned from
    login function and we increase it one digit to get the expense file number because the number of the expense file
    of the user who has just logged in is 1 digit more than the number income file of the user)*/
    strcpy(fileName, "profile");
    fileCountNo2 = fileCountNo+1;
    itoa(fileCountNo2, fileCountStr, 10);
    strcat(fileName, fileCountStr);
    strcat(fileName, ".txt");
    profile = fopen(fileName, "a");
    if
        (profile == NULL)
        printf("File couldn't be opened!!!");
    else
    {
    fputc('\n', profile);
    if
        (choiceNo == 1)
        fputs("Tuition fees\n", profile);
    else
        if
            (choiceNo == 2)
            fputs("Transportation cost\n", profile);
        else
            if
                (choiceNo == 3)
                fputs("Medical expenses\n", profile);
            else
                if
                    (choiceNo == 4)
                    fputs("Leisure expenses\n", profile);
                else
                    if
                        (choiceNo == 5)
                        fputs("Mobile and internet bills\n", profile);
                    else
                        if
                            (choiceNo == 6)
                            fputs("Buying clothes\n", profile);
                        else
                            if
                                (choiceNo == 7)
                                fputs("Helping charity\n", profile);
                            else
                            {
                                fputs(expenseType, profile);
                                fputc('\n', profile);
                            }

    fputs(expenseAmount, profile);
    fputc('\n', profile);
    fputs(expenseDate, profile);
    fputc('\n', profile);
    fputs(expenseDescription, profile);
    fputc('\n', profile);
    printf("\nYour expense information has been recorded successfully");
    }
    fclose(profile);
}




int accountBalance()
{
    long int incomesSum=0, expensesSum=0, incomeAmountNo, expenseAmountNo, acountBalance;
    int choiceNo;
    char choice[3];

    temp = start;
    while(temp != NULL)
    {
        incomeAmountNo = atoi(temp->amount);
        incomesSum = incomesSum + incomeAmountNo;
        temp = temp->next;
    }
    eTemp = eStart;
    while(eTemp != NULL)
    {
        expenseAmountNo = atoi(eTemp->amount);
        expensesSum = expensesSum + expenseAmountNo;
        eTemp = eTemp->next;
    }

    acountBalance = incomesSum - expensesSum;
    printf("Amount of your account balance is %d", acountBalance);

    printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
    gets(choice);
    choiceNo = atoi(choice);
    while(choiceNo<1 || choiceNo>2)
    {
        printf("The number you entered is out of range!!!\nPlease try again:");
        gets(choice);
        choiceNo = atoi(choice);
    }
    system("cls");
    return choiceNo;
}



void specificYearIncomes()
{
    char incomeYear[5];
    long int incomesSum=0, incomeAmountNo, counter, sign=0, i=0;

    printf("Please enter your intended year:");
    gets(incomeYear);

    //checking the year to just contain numbers
    while(incomeYear[i] != '\0')
    {
        while(isdigit(incomeYear[i]) == 0)
        {
            printf("The entered amount isn't in correct format(It mustn't contain any letter or sign)\nPlease try again:");
            gets(incomeYear);
            i=0;
        }
        i++;
    }

    temp = start;
    while(temp != 0)
    {
        sign = 0;
        for(counter=0; counter<=3; counter++)
        {
            if(incomeYear[counter] == temp->date[counter])
                sign++;
        }
        if
            (sign == 4)
        {
            incomeAmountNo = atoi(temp->amount);
            incomesSum = incomesSum + incomeAmountNo;
        }
        temp = temp->next;
    }
    printf("Amount of total incomes in your intended year is %d", incomesSum);
}



void specificYearExpenses()
{
    char expenseYear[5];
    long int expensesSum=0, expenseAmountNo, counter, sign=0, i=0;

    printf("Please enter your intended year:");
    gets(expenseYear);

    //checking the year to just contain numbers
    while(expenseYear[i] != '\0')
    {
        while(isdigit(expenseYear[i]) == 0)
        {
            printf("The entered amount isn't in correct format(It mustn't contain any letter or sign)\nPlease try again:");
            gets(expenseYear);
            i=0;
        }
        i++;
    }

    expensesSum = 0;
    eTemp = eStart;
    while(eTemp != 0)
    {
        sign = 0;
        for(counter=0; counter<=3; counter++)
        {
            if(expenseYear[counter] == eTemp->date[counter])
            sign++;
        }
        if
            (sign == 4)
        {
            expenseAmountNo = atoi(eTemp->amount);
            expensesSum = expensesSum + expenseAmountNo;
        }
        eTemp = eTemp->next;
    }

    printf("Amount of total expenses in your intended year is %d", expensesSum);
}





int checkIncomeDate(int intendedStartYearNo,int intendedStartMonthNo,int intendedStartDayNo,int intendedEndYearNo,int intendedEndMonthNo,int intendedEndDayNo)
{
    char iYear[5], iMonth[3], iDay[3];
    int counter = 0, counter2 = 0, sign, iYearNo, iMonthNo, iDayNo;

    //this function checks a date income file and returns 1 if the date is between the start date and end date that the user has entered

    /*separating year, month and day of the date in income file and changing them to integers to
    compare them to the start year, month and day and end year, month and day which the user has entered*/
    while(temp->date[counter] != '/')
    {
        iYear[counter2] = temp->date[counter];
        counter++;
        counter2++;
    }
    iYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(temp->date[counter] != '/')
    {
        iMonth[counter2] = temp->date[counter];
        counter++;
        counter2++;
    }
    iMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(temp->date[counter] != '\n')
    {
        iDay[counter2] = temp->date[counter];
        counter++;
        counter2++;
    }
    iDay[counter2] = '\0';

    iYearNo = atoi(iYear);
    iMonthNo = atoi(iMonth);
    iDayNo = atoi(iDay);

    sign = 0;
    //start of comparing
    if
        ((iYearNo > intendedStartYearNo) && (iYearNo < intendedEndYearNo))
    {
        sign = 1;
    }
    else
        if
            ((iYearNo == intendedStartYearNo) && (iYearNo < intendedEndYearNo))
        {
            if
                (iMonthNo > intendedStartMonthNo)
            {
                sign = 1;
            }
            else
                if
                    (iMonthNo == intendedStartMonthNo)
                {
                    if
                        (iDayNo >= intendedStartDayNo)
                    {
                        sign = 1;
                    }
                }
        }
        else
            if
                ((iYearNo > intendedStartYearNo) && (iYearNo == intendedEndYearNo))
            {
                if
                    (iMonthNo < intendedEndMonthNo)
                {
                    sign = 1;
                }
                else
                    if
                        (iMonthNo == intendedEndMonthNo)
                    {
                        if
                            (iDayNo <= intendedEndDayNo)
                        {
                            sign = 1;
                        }
                    }
            }
            else
                if
                    ((iYearNo == intendedStartYearNo) && (iYearNo == intendedEndYearNo))
                {
                    if
                        ((iMonthNo > intendedStartMonthNo) && (iMonthNo < intendedEndMonthNo))
                    {
                        sign = 1;
                    }
                    else
                        if
                            ((iMonthNo == intendedStartMonthNo) && (iMonthNo == intendedEndMonthNo))
                        {
                            if
                                (iDayNo >= intendedStartDayNo && iDayNo <= intendedEndDayNo)
                            {
                                sign = 1;
                            }
                        }
                        else
                            if
                                (iMonthNo == intendedStartMonthNo)
                            {
                                if
                                    (iDayNo >= intendedStartDayNo)
                                {
                                    sign = 1;
                                }
                            }
                            else
                                if
                                    (iMonthNo == intendedEndMonthNo)
                                {
                                    if
                                        (iDayNo <= intendedEndDayNo)
                                    {
                                        sign = 1;
                                    }
                                }

                }
    return sign;
}





int checkExpenseDate(int intendedStartYearNo,int intendedStartMonthNo,int intendedStartDayNo,int intendedEndYearNo,int intendedEndMonthNo,int intendedEndDayNo)
{
    char eYear[5], eMonth[3], eDay[3];
    int counter = 0, counter2 = 0, sign, eYearNo, eMonthNo, eDayNo;

    //this function checks a date in expense file and returns 1 if the date is between the start date and end date that the user has entered

    /*separating year, month and day of the date in expense file and changing them to integers to
    compare them to the start year, month and day and end year, month and day which the user has entered*/
    while(eTemp->date[counter] != '/')
    {
        eYear[counter2] = eTemp->date[counter];
        counter++;
        counter2++;
    }
    eYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(eTemp->date[counter] != '/')
    {
        eMonth[counter2] = eTemp->date[counter];
        counter++;
        counter2++;
    }
    eMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(eTemp->date[counter] != '\n')
    {
        eDay[counter2] = eTemp->date[counter];
        counter++;
        counter2++;
    }
    eDay[counter2] = '\0';

    eYearNo = atoi(eYear);
    eMonthNo = atoi(eMonth);
    eDayNo = atoi(eDay);

    sign = 0;
    //start of comparing
    if
        ((eYearNo > intendedStartYearNo) && (eYearNo < intendedEndYearNo))
    {
        sign = 1;
    }
    else
        if
            ((eYearNo == intendedStartYearNo) && (eYearNo < intendedEndYearNo))
        {
            if
                (eMonthNo > intendedStartMonthNo)
            {
                sign = 1;
            }
            else
                if
                    (eMonthNo == intendedStartMonthNo)
                {
                    if
                        (eDayNo >= intendedStartDayNo)
                    {
                        sign = 1;
                    }
                }
        }
        else
            if
                ((eYearNo > intendedStartYearNo) && (eYearNo == intendedEndYearNo))
            {
                if
                    (eMonthNo < intendedEndMonthNo)
                {
                    sign = 1;
                }
                else
                    if
                        (eMonthNo == intendedEndMonthNo)
                    {
                        if
                            (eDayNo <= intendedEndDayNo)
                        {
                            sign = 1;
                        }
                    }
            }
            else
                if
                    ((eYearNo == intendedStartYearNo) && (eYearNo == intendedEndYearNo))
                {
                    if
                        ((eMonthNo > intendedStartMonthNo) && (eMonthNo < intendedEndMonthNo))
                    {
                        sign = 1;
                    }
                    else
                        if
                            ((eMonthNo == intendedStartMonthNo) && (eMonthNo == intendedEndMonthNo))
                        {
                            if
                                (eDayNo >= intendedStartDayNo && eDayNo <= intendedEndDayNo)
                            {
                                sign = 1;
                            }
                        }
                        else
                            if
                                (eMonthNo == intendedStartMonthNo)
                            {
                                if
                                    (eDayNo >= intendedStartDayNo)
                                {
                                    sign = 1;
                                }
                            }
                            else
                                if
                                    (eMonthNo == intendedEndMonthNo)
                                {
                                    if
                                        (eDayNo <= intendedEndDayNo)
                                    {
                                        sign = 1;
                                    }
                                }

                }
    return sign;
}





void specificDateRangeIncomes()
{
    char dateRangeStart[20], dateRangeEnd[20];
    int intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo;
    char intendedStartYear[6], intendedStartMonth[3], intendedStartDay[3], intendedEndYear[6], intendedEndMonth[3], intendedEndDay[3];
    long int incomesSum=0, incomeAmountNo, counter, counter2, sign=0, i=0, counter3=0;

    printf("Please enter the start and the end of your intended date range(in yyyy/mm/dd format)\n");
    printf("\nStart of date range:");
    gets(dateRangeStart);

    /*checking start of date range format(it must contain two / characters and
    the other characters must be numbers and also its length can't be more than 20 characters*/
    while(dateRangeStart[i] != '\0')
    {
        if
            (dateRangeStart[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeStart[i]) == 0 ||strlen(dateRangeStart)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeStart);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeStart);
        while(dateRangeStart[i] != '\0')
        {
            if
                (dateRangeStart[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeStart);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    /*separating year, month and the day of the given start date range to compare the year, month and day
    of the dates of the income file with them*/
    counter = 0;
    counter2 = 0;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartYear[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartMonth[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '\0')
    {
        intendedStartDay[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedStartYearNo = atoi(intendedStartYear);
    intendedStartMonthNo = atoi(intendedStartMonth);
    intendedStartDayNo = atoi(intendedStartDay);


    printf("\nEnd of date range:");
    gets(dateRangeEnd);

    /*checking end of date range format(it must contain two / characters and
    the other characters must be numbers and also its length can't be more than 20 characters*/
    i=0;
    counter3=0;
    while(dateRangeEnd[i] != '\0')
    {
        if
            (dateRangeEnd[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeEnd);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeEnd);
        while(dateRangeEnd[i] != '\0')
        {
            if
                (dateRangeEnd[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeEnd);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    /*separating year, month and the day of the given end date range to compare the year, month and day
    of the dates of the income file with them*/
    counter = 0;
    counter2 = 0;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndYear[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndMonth[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '\0')
    {
        intendedEndDay[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedEndYearNo = atoi(intendedEndYear);
    intendedEndMonthNo = atoi(intendedEndMonth);
    intendedEndDayNo = atoi(intendedEndDay);

    /*checking all the saved incomes dates one by one with the start and end date range with using linked list
    and also using "checkIncomeDate" function*/
    //(the linked list is global so we can access the values in it in all functions also here)
    //in every round, a new value of date goes in "checkIncomeDate" function because linked list is global
    incomesSum = 0;
    temp = start;
    while(temp != 0)
    {
        sign = checkIncomeDate(intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo);
        if
            (sign == 1)
        {
            incomeAmountNo = atoi(temp->amount);
            incomesSum = incomesSum + incomeAmountNo;
        }

        temp = temp->next;
    }
    printf("The amount of total incomes in your intended date range is %d", incomesSum);

}






void specificDateRangeExpenses()
{
    char dateRangeStart[20], dateRangeEnd[20];
    int intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo;
    char intendedStartYear[6], intendedStartMonth[3], intendedStartDay[3], intendedEndYear[6], intendedEndMonth[3], intendedEndDay[3];
    long int expensesSum=0, expenseAmountNo, counter, counter2, sign=0, i=0, counter3=0;

    printf("Please enter the start and the end of your intended date range(in yyyy/mm/dd format)\n");
    printf("\nStart of date range:");
    gets(dateRangeStart);

    //checking start of date range format
    while(dateRangeStart[i] != '\0')
    {
        if
            (dateRangeStart[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeStart);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeStart);
        while(dateRangeStart[i] != '\0')
        {
            if
                (dateRangeStart[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeStart);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given start date range
    counter = 0;
    counter2 = 0;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartYear[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartMonth[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '\0')
    {
        intendedStartDay[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedStartYearNo = atoi(intendedStartYear);
    intendedStartMonthNo = atoi(intendedStartMonth);
    intendedStartDayNo = atoi(intendedStartDay);


    printf("\nEnd of date range:");
    gets(dateRangeEnd);

    //checking end of date range format
    i=0;
    counter3=0;
    while(dateRangeEnd[i] != '\0')
    {
        if
            (dateRangeEnd[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeEnd);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeEnd);
        while(dateRangeEnd[i] != '\0')
        {
            if
                (dateRangeEnd[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeEnd);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given end date range
    counter = 0;
    counter2 = 0;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndYear[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndMonth[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '\0')
    {
        intendedEndDay[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedEndYearNo = atoi(intendedEndYear);
    intendedEndMonthNo = atoi(intendedEndMonth);
    intendedEndDayNo = atoi(intendedEndDay);

    /*checking all the saved expenses dates one by one with the start and end date range with using linked list
    and also using "checkExpenseDate" function*/
    //(the linked list is global so we can access the values in it in all functions also here)
    //in every round, a new value of date goes in "checkExpenseDate" function because linked list is global
    expensesSum = 0;
    eTemp = eStart;
    while(eTemp != NULL)
    {
        sign = checkExpenseDate(intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo);
        if
            (sign == 1)
        {
            expenseAmountNo = atoi(eTemp->amount);
            expensesSum = expensesSum + expenseAmountNo;
        }
        eTemp = eTemp->next;
    }

    printf("The amount of total expenses in your intended date range is %d", expensesSum);

}





void specificDateRangeIncomesWithSpecificType()
{
    char dateRangeStart[20], dateRangeEnd[20], intendedIncomeType[50], choice[3];
    int intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo;
    char intendedStartYear[6], intendedStartMonth[3], intendedStartDay[3], intendedEndYear[6], intendedEndMonth[3], intendedEndDay[3];
    long int incomesSum=0, incomeAmountNo, counter, counter2, sign=0, choiceNo, i=0, counter3=0;

    printf("Please enter the start and the end of your intended date range(in yyyy/mm/dd format)\n");
    printf("\nStart of date range:");
    gets(dateRangeStart);

    //checking start of date range format
    while(dateRangeStart[i] != '\0')
    {
        if
            (dateRangeStart[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeStart);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeStart);
        while(dateRangeStart[i] != '\0')
        {
            if
                (dateRangeStart[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeStart);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given start date range
    counter = 0;
    counter2 = 0;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartYear[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartMonth[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '\0')
    {
        intendedStartDay[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedStartYearNo = atoi(intendedStartYear);
    intendedStartMonthNo = atoi(intendedStartMonth);
    intendedStartDayNo = atoi(intendedStartDay);


    printf("\nEnd of date range:");
    gets(dateRangeEnd);

    //checking end of date range format
    i=0;
    counter3=0;
    while(dateRangeEnd[i] != '\0')
    {
        if
            (dateRangeEnd[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeEnd);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeEnd);
        while(dateRangeEnd[i] != '\0')
        {
            if
                (dateRangeEnd[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeEnd);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given end date range
    counter = 0;
    counter2 = 0;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndYear[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndMonth[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '\0')
    {
        intendedEndDay[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedEndYearNo = atoi(intendedEndYear);
    intendedEndMonthNo = atoi(intendedEndMonth);
    intendedEndDayNo = atoi(intendedEndDay);

    printf("\nPlease choose your intended type of income\n");
    printf("1)Programming salary\n2)Yaraneh\n3)Pocket money\n4)University grant\n5)Other\n");
    printf("Please enter the number of your choice:");
    gets(choice);
    choiceNo=atoi(choice);

    //checking the number not to be out of range
    while(choiceNo>5 || choiceNo<1)
    {
        system("cls");
        printf("The number you entered is out of range.Please try again\n\n");
        printf("\nPlease choose your intended type of income\n");
        printf("1)Programming salary\n2)Yaraneh\n3)Pocket money\n4)University grant\n5)Other\n");
        printf("Please enter the number of your choice:");
        gets(choice);
        choiceNo=atoi(choice);
    }

    //an option to search another type of income except the 4 items above
    if
        (choiceNo == 5)
    {
        printf("Please enter your intended income type:");
        gets(intendedIncomeType);
    }
    strcat(intendedIncomeType, "\n");

    /*checking all saved incomes dates one by one with the start and end date range with using linked list
    and also using "checkIncomeDate" function*/
    //(the linked list is global so we can access the values in it in all functions also here)
    //in every round, a new value of date goes in "checkExpenseDate" function because linked list is global
    incomesSum = 0;
    temp = start;
    while(temp != 0)
    {
        sign = checkIncomeDate(intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo);
        if
            (sign == 1)
        {
            /*if the date was between the given start and end date, now we check
            the saved incomes types with the given income type and calculate the sum of them*/
            if
                (choiceNo == 1)
            {
                if
                    (strcmp("Programming salary\n", temp->type) == 0)
                {
                    incomeAmountNo = atoi(temp->amount);
                    incomesSum = incomesSum + incomeAmountNo;
                }
            }
            else
                if
                    (choiceNo == 2)
                {
                    if
                        (strcmp("Yaraneh\n", temp->type) == 0)
                    {
                        incomeAmountNo = atoi(temp->amount);
                        incomesSum = incomesSum + incomeAmountNo;
                    }
                }
                else
                    if
                        (choiceNo == 3)
                    {
                        if
                            (strcmp("Pocket money\n", temp->type) == 0)
                        {
                            incomeAmountNo = atoi(temp->amount);
                            incomesSum = incomesSum + incomeAmountNo;
                        }
                    }
                    else
                        if
                            (choiceNo == 4)
                        {
                            if
                                (strcmp("University grant\n", temp->type) == 0)
                            {
                                incomeAmountNo = atoi(temp->amount);
                                incomesSum = incomesSum + incomeAmountNo;
                            }
                        }
                        else
                            if
                                (choiceNo == 5)
                            {
                                if
                                    (strcmp(intendedIncomeType, temp->type) == 0)
                                {
                                    incomeAmountNo = atoi(temp->amount);
                                    incomesSum = incomesSum + incomeAmountNo;
                                }
                            }
        }
        temp = temp->next;
    }
    printf("The amount of total incomes with your intended type in your intended date range is %d", incomesSum);
}





void specificDateRangeExpensesWithSpecificType()
{
    char dateRangeStart[20], dateRangeEnd[20], intendedExpenseType[50], choice[3];
    int intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo;
    char intendedStartYear[6], intendedStartMonth[3], intendedStartDay[3], intendedEndYear[6], intendedEndMonth[3], intendedEndDay[3];
    long int expensesSum=0, expenseAmountNo, counter, counter2, sign=0, choiceNo, i=0, counter3=0;

    printf("Please enter the start and the end of your intended date range(in yyyy/mm/dd format)\n");
    printf("\nStart of date range:");
    gets(dateRangeStart);

    //checking start of date range format
    while(dateRangeStart[i] != '\0')
    {
        if
            (dateRangeStart[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeStart);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeStart);
        while(dateRangeStart[i] != '\0')
        {
            if
                (dateRangeStart[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeStart);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given start date range
    counter = 0;
    counter2 = 0;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartYear[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartMonth[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '\0')
    {
        intendedStartDay[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedStartYearNo = atoi(intendedStartYear);
    intendedStartMonthNo = atoi(intendedStartMonth);
    intendedStartDayNo = atoi(intendedStartDay);


    printf("\nEnd of date range:");
    gets(dateRangeEnd);

    //checking end of date range format
    i=0;
    counter3=0;
    while(dateRangeEnd[i] != '\0')
    {
        if
            (dateRangeEnd[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeEnd);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeEnd);
        while(dateRangeEnd[i] != '\0')
        {
            if
                (dateRangeEnd[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeEnd);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given end date range
    counter = 0;
    counter2 = 0;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndYear[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndMonth[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '\0')
    {
        intendedEndDay[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedEndYearNo = atoi(intendedEndYear);
    intendedEndMonthNo = atoi(intendedEndMonth);
    intendedEndDayNo = atoi(intendedEndDay);

    printf("Please choose your intended type of expense\n");
    printf("1)Tuition fees\n2)Transportation cost\n3)Medical expenses\n4)Leisure expenses\n5)Mobile and internet bills\n6)Buying clothes\n7)Helping charity\n8)Other\n");
    printf("Please enter the number of your choice:");
    gets(choice);
    choiceNo=atoi(choice);

    //checking the number not to be out of range
    while(choiceNo>8 || choiceNo<1)
    {
        system("cls");
        printf("The number you entered is out of range.Please try again\n\n");
        printf("Please choose your intended type of expense");
        printf("1)Tuition fees\n2)Transportation cost\n3)Medical expenses\n4)Leisure expenses\n5)Mobile and internet bills\n6)Buying clothes\n7)Helping charity\n8)Other\n");
        printf("Please enter the number of your choice:");
        gets(choice);
        choiceNo=atoi(choice);
    }

    //an option to search another type of expense except the 7 items above
    if
        (choiceNo == 8)
    {
        printf("Please enter your expense type:");
        gets(intendedExpenseType);
        strcat(intendedExpenseType, "\n");
    }

    /*checking all saved expenses dates one by one with the start and end date range with using linked list
    and also using "checkExpenseDate" function*/
    //(the linked list is global so we can access the values in it in all functions also here)
    //in every round, a new value of date goes in "checkExpenseDate" function because linked list is global
    expensesSum = 0;
    eTemp = eStart;
    while(eTemp != NULL)
    {
        sign = checkExpenseDate(intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo);
        if
            (sign == 1)
        {
            /*if the date was between the given start and end date, now we check
            the saved expenses types with the given expense type and calculate the sum of them*/
            if
                (choiceNo == 1)
            {
                if
                    (strcmp("Tuition fees\n", eTemp->type) == 0)
                {
                    expenseAmountNo = atoi(eTemp->amount);
                    expensesSum = expensesSum + expenseAmountNo;
                }
            }
            else
                if
                    (choiceNo == 2)
                {
                    if
                        (strcmp("Transportation cost\n", eTemp->type) == 0)
                    {
                        expenseAmountNo = atoi(eTemp->amount);
                        expensesSum = expensesSum + expenseAmountNo;
                    }
                }
                else
                    if
                        (choiceNo == 3)
                    {
                        if
                            (strcmp("Medical expenses\n", eTemp->type) == 0)
                        {
                            expenseAmountNo = atoi(eTemp->amount);
                            expensesSum = expensesSum + expenseAmountNo;
                        }
                    }
                    else
                        if
                            (choiceNo == 4)
                        {
                            if
                                (strcmp("Leisure expenses\n", eTemp->type) == 0)
                            {
                                expenseAmountNo = atoi(eTemp->amount);
                                expensesSum = expensesSum + expenseAmountNo;
                            }
                        }
                        else
                            if
                                (choiceNo == 5)
                            {
                                if
                                    (strcmp("Mobile and internet bills\n", eTemp->type) == 0)
                                {
                                    expenseAmountNo = atoi(eTemp->amount);
                                    expensesSum = expensesSum + expenseAmountNo;
                                }
                            }
                            else
                                if
                                    (choiceNo == 6)
                                {
                                    if
                                        (strcmp("Buying clothes\n", eTemp->type) == 0)
                                    {
                                        expenseAmountNo = atoi(eTemp->amount);
                                        expensesSum = expensesSum + expenseAmountNo;
                                    }
                                }
                                else
                                    if
                                        (choiceNo == 7)
                                    {
                                        if
                                            (strcmp("Helping charity\n", eTemp->type) == 0)
                                        {
                                            expenseAmountNo = atoi(eTemp->amount);
                                            expensesSum = expensesSum + expenseAmountNo;
                                        }
                                    }
                                    else
                                        if
                                            (choiceNo == 8)
                                        {
                                            if
                                                (strcmp(intendedExpenseType, eTemp->type) == 0)
                                            {
                                                expenseAmountNo = atoi(eTemp->amount);
                                                expensesSum = expensesSum + expenseAmountNo;
                                            }
                                        }

        }
        eTemp = eTemp->next;
    }
    printf("The amount of total expenses with your intended type in your intended date range is %d", expensesSum);
}




void incomeRatio()
{
    int intendedIncomeTypeRatio, salaryRatio, yaraneRatio, pocketMoneyRatio, universityGrantRatio, othersRatio;
    long int salarySum=0, yaraneSum=0, pocketMoneySum=0, universityGrantSum=0, othersSum=0, intendedIncomeTypeSum=0, incomeAmountNo, incomesSum=0;
    double incomesSumFloat;
    char searchInRatios[5], intendedIncomeType[50];

    temp=start;
    while(temp != NULL)
    {
        //calculating the total sum of income amounts
        incomeAmountNo = atoi(temp->amount);
        incomesSum = incomesSum + incomeAmountNo;

        //calculating each specific type of income amounts
        if
            (strcmp("Programming salary\n", temp->type) == 0)
        {
            incomeAmountNo = atoi(temp->amount);
            salarySum = salarySum + incomeAmountNo;
        }
        else
            if
                (strcmp("Yaraneh\n", temp->type) == 0)
            {
                incomeAmountNo = atoi(temp->amount);
                yaraneSum = yaraneSum + incomeAmountNo;
            }
            else
                if
                    (strcmp("Pocket money\n", temp->type) == 0)
                {
                    incomeAmountNo = atoi(temp->amount);
                    pocketMoneySum = pocketMoneySum + incomeAmountNo;
                }
                else
                    if
                        (strcmp("University grant\n", temp->type) == 0)
                    {
                        incomeAmountNo = atoi(temp->amount);
                        universityGrantSum = universityGrantSum + incomeAmountNo;
                    }
                    else
                    {
                        incomeAmountNo = atoi(temp->amount);
                        othersSum = othersSum + incomeAmountNo;
                    }
        temp = temp->next;
    }
    //changing the total sum to a float value to have the exact amount of the divides(jologiri az taghsime sahih)
    incomesSumFloat = incomesSum;

    //calculating and showing the percentage ratio of each specific type of income to the user
    salaryRatio = salarySum / incomesSumFloat * 100;
    yaraneRatio = yaraneSum / incomesSumFloat * 100;
    pocketMoneyRatio = pocketMoneySum / incomesSumFloat * 100;
    universityGrantRatio = universityGrantSum / incomesSumFloat * 100;
    othersRatio = othersSum / incomesSumFloat * 100;
    printf("Percentage ratio of programming salary = %d\n",salaryRatio);
    printf("Percentage ratio of yarane = %d\n",yaraneRatio);
    printf("Percentage ratio of pocket money = %d\n",pocketMoneyRatio);
    printf("Percentage ratio of university grant = %d\n",universityGrantRatio);
    printf("Percentage ratio of other types of income = %d\n",othersRatio);

    //an option to search the percentage ratio of another type of income
    printf("Do you want to receive percentage ratio of an special type of income(which has been included in 'other types of income' section)?\nYour answer must be yes or no:");
    gets(searchInRatios);

    /*making all characters to lower case and the comparing them with "yes" word so it doesn't differ
    if the user enters "Yes" or "yes"*/
    strlwr(searchInRatios);

    while(strcmp(searchInRatios, "yes") == 0)
    {
        intendedIncomeTypeSum = 0;
        printf("Please enter your intended type of income:");
        gets(intendedIncomeType);
        strcat(intendedIncomeType , "\n");
        temp = start;
        while(temp != NULL)
        {
            if
                (strcmp(temp->type, intendedIncomeType) == 0)
            {
                //calculating the sum of given income type amounts
                incomeAmountNo = atoi(temp->amount);
                intendedIncomeTypeSum = intendedIncomeTypeSum + incomeAmountNo;
            }
            temp = temp->next;
        }

        //calculating and showing the percentage ratio of given income type to the user
        intendedIncomeTypeRatio = intendedIncomeTypeSum / incomesSumFloat * 100;
        printf("\nPercentage Ratio of your intended type of income = %d\n",intendedIncomeTypeRatio);

        //asking the user if they want to search another type again
        printf("\n\nDo you want to search another ratio?(Your answer must be yes or no):");
        gets(searchInRatios);
    }
}






void expenseRatio()
{
    int tuitionFeesRatio, transportationCostRatio, medicalExpensesRatio, leisureExpensesRatio, mobileBillRatio, buyingClothesRatio, helpingcharityRatio, othersRatio, intendedExpenseTypeRatio, expenseAmountNo, expensesSum=0;
    long int tuitionFeesSum=0, transportationCostSum=0, medicalExpensesSum=0, leisureExpensesSum=0, mobileBillSum=0, buyingClothesSum=0, helpingCharitySum=0, othersSum=0, intendedExpenseTypeSum=0;
    double expensesSumFloat;
    char searchInRatios[5], intendedExpenseType[50];

    eTemp=eStart;
    while(eTemp != NULL)
    {
        //calculating the total sum of expense amounts
        expenseAmountNo = atoi(eTemp->amount);
        expensesSum = expensesSum + expenseAmountNo;

        //calculating each specific type of expense amounts
        if
            (strcmp("Tuition fees\n", eTemp->type) == 0)
        {
            expenseAmountNo = atoi(eTemp->amount);
            tuitionFeesSum = tuitionFeesSum + expenseAmountNo;
        }
        else
            if
                (strcmp("Transportation cost\n", eTemp->type) == 0)
            {
                expenseAmountNo = atoi(eTemp->amount);
                transportationCostSum = transportationCostSum + expenseAmountNo;
            }
            else
                 if
                    (strcmp("Medical expenses\n", eTemp->type) == 0)
                {
                    expenseAmountNo = atoi(eTemp->amount);
                    medicalExpensesSum = medicalExpensesSum + expenseAmountNo;
                }
                else
                    if
                        (strcmp("Leisure expenses\n", eTemp->type) == 0)
                    {
                        expenseAmountNo = atoi(eTemp->amount);
                        leisureExpensesSum = leisureExpensesSum + expenseAmountNo;
                    }
                    else
                        if
                            (strcmp("Mobile and internet bills\n", eTemp->type) == 0)
                        {
                            expenseAmountNo = atoi(eTemp->amount);
                            mobileBillSum = mobileBillSum + expenseAmountNo;
                        }
                        else
                            if
                                (strcmp("Buying clothes\n", eTemp->type) == 0)
                            {
                                expenseAmountNo = atoi(eTemp->amount);
                                buyingClothesSum = buyingClothesSum + expenseAmountNo;
                           }
                            else
                                if
                                    (strcmp("Helping charity\n", eTemp->type) == 0)
                                {
                                    expenseAmountNo = atoi(eTemp->amount);
                                    helpingCharitySum = helpingCharitySum + expenseAmountNo;
                                }
                                else
                                {
                                    expenseAmountNo = atoi(eTemp->amount);
                                    othersSum = othersSum + expenseAmountNo;
                                }
        eTemp = eTemp->next;
    }
    //changing the total sum to a float value to have the exact amount of the divides(jologiri az taghsime sahih)
    expensesSumFloat = expensesSum;

    //calculating and showing the percentage ratio of each specific type of expense to the user
    tuitionFeesRatio = tuitionFeesSum / expensesSumFloat * 100;
    transportationCostRatio = transportationCostSum / expensesSumFloat * 100;
    medicalExpensesRatio = medicalExpensesSum / expensesSumFloat * 100;
    leisureExpensesRatio = leisureExpensesSum / expensesSumFloat * 100;
    mobileBillRatio = mobileBillSum / expensesSumFloat * 100;
    buyingClothesRatio = buyingClothesSum / expensesSumFloat * 100;
    helpingcharityRatio = helpingCharitySum / expensesSumFloat * 100;
    othersRatio = othersSum / expensesSumFloat * 100;
    printf("Percentage ratio of tuition fees = %d\n",tuitionFeesRatio);
    printf("Percentage ratio of transportation cost = %d\n",transportationCostRatio);
    printf("Percentage ratio of medical expenses = %d\n",medicalExpensesRatio);
    printf("Percentage ratio of leisure expenses = %d\n",leisureExpensesRatio);
    printf("Percentage ratio of mobile and internet bills = %d\n",mobileBillRatio);
    printf("Percentage ratio of Buying clothes = %d\n",buyingClothesRatio);
    printf("Percentage ratio of Helping charity = %d\n",helpingcharityRatio);
    printf("Percentage ratio of other types of expense = %d\n",othersRatio);

    //an option to search the percentage ratio of another type of expense
    printf("Do you want to receive percentage ratio of an special type of expense(which has been included in 'other types of expense' section)?\nYour answer must be yes or no:");
    gets(searchInRatios);

    /*making all characters to lower case and the comparing them with "yes" word so it doesn't differ
    if the user enters "Yes" or "yes"*/
    strlwr(searchInRatios);

    while(strcmp(searchInRatios, "yes") == 0)
    {
        intendedExpenseTypeSum = 0;
        printf("Please enter your intended type of expense:");
        gets(intendedExpenseType);
        strcat(intendedExpenseType , "\n");
        eTemp = eStart;
        while(eTemp != NULL)
        {
            if
                (strcmp(eTemp->type, intendedExpenseType) == 0)
            {
                //calculating the sum of given expense type amounts
                expenseAmountNo = atoi(eTemp->amount);
                intendedExpenseTypeSum = intendedExpenseTypeSum + expenseAmountNo;
            }
            eTemp = eTemp->next;
        }

        //calculating and showing the percentage ratio of given expense type to the user
        intendedExpenseTypeRatio = intendedExpenseTypeSum / expensesSumFloat * 100;
        printf("\nPercentage Ratio of your intended type of expense = %d\n",intendedExpenseTypeRatio);

        //asking the user if they want to search another type again
        printf("\n\nDo you want to search another ratio?(Your answer must be yes or no):");
        gets(searchInRatios);
    }
}





void specificDateRangeIncomesDetails()
{
    char dateRangeStart[20], dateRangeEnd[20], intendedIncomeType[50];
    int intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo;
    char intendedStartYear[6], intendedStartMonth[3], intendedStartDay[3], intendedEndYear[6], intendedEndMonth[3], intendedEndDay[3];
    int counter, counter2, sign=0, counter3=0, i=0;

    printf("Please enter the start and the end of your intended date range(in yyyy/mm/dd format)\n");
    printf("\nStart of date range:");
    gets(dateRangeStart);

    //checking start of date range format
    while(dateRangeStart[i] != '\0')
    {
        if
            (dateRangeStart[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeStart);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeStart);
        while(dateRangeStart[i] != '\0')
        {
            if
                (dateRangeStart[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeStart);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given start date range
    counter = 0;
    counter2 = 0;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartYear[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartMonth[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '\0')
    {
        intendedStartDay[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedStartYearNo = atoi(intendedStartYear);
    intendedStartMonthNo = atoi(intendedStartMonth);
    intendedStartDayNo = atoi(intendedStartDay);


    printf("\nEnd of date range:");
    gets(dateRangeEnd);

    //checking end of date range format
    i=0;
    counter3=0;
    while(dateRangeEnd[i] != '\0')
    {
        if
            (dateRangeEnd[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeEnd);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeEnd);
        while(dateRangeEnd[i] != '\0')
        {
            if
                (dateRangeEnd[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeEnd);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given end date range
    counter = 0;
    counter2 = 0;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndYear[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndMonth[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '\0')
    {
        intendedEndDay[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedEndYearNo = atoi(intendedEndYear);
    intendedEndMonthNo = atoi(intendedEndMonth);
    intendedEndDayNo = atoi(intendedEndDay);

    /*checking all saved incomes dates one by one with the start and end date range with using linked list
    and also using "checkIncomeDate" function*/
    //(the linked list is global so we can access the values in it in all functions also here)
    //in every round, a new value of date goes in "checkExpenseDate" function because linked list is global
    temp = start;
    while(temp != 0)
    {
        sign = checkIncomeDate(intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo);
        if
            (sign == 1)
        {
            //if the date was between the given start and end date, the program shows the detail of that income
            printf("\nIncome type : ");
            puts(temp->type);
            printf("Income amount : ");
            puts(temp->amount);
            printf("Income date : ");
            puts(temp->date);
            printf("Income description : ");
            puts(temp->description);
            printf("\n");
        }
        temp = temp->next;
    }
}






void specificDateRangeExpensesDetails()
{
    char dateRangeStart[20], dateRangeEnd[20], intendedExpenseType[50];
    int intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo;
    char intendedStartYear[6], intendedStartMonth[3], intendedStartDay[3], intendedEndYear[6], intendedEndMonth[3], intendedEndDay[3];
    int counter, counter2, sign=0, i=0, counter3=0;

    printf("Please enter the start and the end of your intended date range(in yyyy/mm/dd format)\n");
    printf("\nStart of date range:");
    gets(dateRangeStart);

    //checking start of date range format
    while(dateRangeStart[i] != '\0')
    {
        if
            (dateRangeStart[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeStart);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeStart);
        while(dateRangeStart[i] != '\0')
        {
            if
                (dateRangeStart[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeStart);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given start date range
    counter = 0;
    counter2 = 0;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartYear[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartMonth[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '\0')
    {
        intendedStartDay[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedStartYearNo = atoi(intendedStartYear);
    intendedStartMonthNo = atoi(intendedStartMonth);
    intendedStartDayNo = atoi(intendedStartDay);


    printf("\nEnd of date range:");
    gets(dateRangeEnd);

    //checking end of date range format
    i=0;
    counter3=0;
    while(dateRangeEnd[i] != '\0')
    {
        if
            (dateRangeEnd[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeEnd);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeEnd);
        while(dateRangeEnd[i] != '\0')
        {
            if
                (dateRangeEnd[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeEnd);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given end date range
    counter = 0;
    counter2 = 0;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndYear[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndMonth[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '\0')
    {
        intendedEndDay[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedEndYearNo = atoi(intendedEndYear);
    intendedEndMonthNo = atoi(intendedEndMonth);
    intendedEndDayNo = atoi(intendedEndDay);

    /*checking all saved expenses dates one by one with the start and end date range with using linked list
    and also using "checkExpenseDate" function*/
    //(the linked list is global so we can access the values in it in all functions also here)
    //in every round, a new value of date goes in "checkExpenseDate" function because linked list is global
    eTemp = eStart;
    while(eTemp != NULL)
    {
        sign = checkExpenseDate(intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo);
        if
            (sign == 1)
        {
            //if the date was between the given start and end date, the program shows the detail of that expense
            printf("\nExpense type : ");
            puts(eTemp->type);
            printf("Expense amount : ");
            puts(eTemp->amount);
            printf("Expense date : ");
            puts(eTemp->date);
            printf("Expense description : ");
            puts(eTemp->description);
            printf("\n");
        }
        eTemp = eTemp->next;
    }
}






void specificDateRangeMaxIncome()
{
    char dateRangeStart[20], dateRangeEnd[20], intendedIncomeType[50];
    int intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo;
    char intendedStartYear[6], intendedStartMonth[3], intendedStartDay[3], intendedEndYear[6], intendedEndMonth[3], intendedEndDay[3];
    int counter, counter2, sign=0, counter3=0, i=0;
    long int incomeAmount, maxIncome = 0, lastIncomeAmount = 0;

    printf("Please enter the start and the end of your intended date range(in yyyy/mm/dd format)\n");
    printf("\nStart of date range:");
    gets(dateRangeStart);

    //checking start of date range format
    while(dateRangeStart[i] != '\0')
    {
        if
            (dateRangeStart[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeStart);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeStart);
        while(dateRangeStart[i] != '\0')
        {
            if
                (dateRangeStart[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeStart);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given start date range
    counter = 0;
    counter2 = 0;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartYear[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartMonth[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '\0')
    {
        intendedStartDay[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedStartYearNo = atoi(intendedStartYear);
    intendedStartMonthNo = atoi(intendedStartMonth);
    intendedStartDayNo = atoi(intendedStartDay);


    printf("\nEnd of date range:");
    gets(dateRangeEnd);

    //checking end of date range format
    i=0;
    counter3=0;
    while(dateRangeEnd[i] != '\0')
    {
        if
            (dateRangeEnd[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeEnd);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeEnd);
        while(dateRangeEnd[i] != '\0')
        {
            if
                (dateRangeEnd[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeEnd);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given end date range
    counter = 0;
    counter2 = 0;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndYear[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndMonth[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '\0')
    {
        intendedEndDay[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedEndYearNo = atoi(intendedEndYear);
    intendedEndMonthNo = atoi(intendedEndMonth);
    intendedEndDayNo = atoi(intendedEndDay);

    /*checking all saved incomes dates one by one with the start and end date range with using linked list
    and also using "checkIncomeDate" function*/
    //(the linked list is global so we can access the values in it in all functions also here)
    //in every round, a new value of date goes in "checkExpenseDate" function because linked list is global
    temp = start;
    while(temp != 0)
    {
        sign = checkIncomeDate(intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo);
        if
            (sign == 1)
        {
            incomeAmount = atoi(temp->amount);
            if
                (incomeAmount >= lastIncomeAmount)
            {
                maxIncome = incomeAmount;
            }
            else
            {
                maxIncome = lastIncomeAmount;
            }
            lastIncomeAmount = atoi(temp->amount);
        }
        temp = temp->next;
    }
    printf("\nThe maximum income amount = %d", maxIncome);
}






void specificDateRangeMaxExpense()
{
    char dateRangeStart[20], dateRangeEnd[20], intendedExpenseType[50];
    int intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo;
    char intendedStartYear[6], intendedStartMonth[3], intendedStartDay[3], intendedEndYear[6], intendedEndMonth[3], intendedEndDay[3];
    int counter, counter2, sign=0, i=0, counter3=0;
    long int expenseAmount, maxExpense = 0, lastExpenseAmount = 0;
    printf("Please enter the start and the end of your intended date range(in yyyy/mm/dd format)\n");
    printf("\nStart of date range:");
    gets(dateRangeStart);

    //checking start of date range format
    while(dateRangeStart[i] != '\0')
    {
        if
            (dateRangeStart[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeStart);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeStart);
        while(dateRangeStart[i] != '\0')
        {
            if
                (dateRangeStart[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeStart[i]) == 0 || strlen(dateRangeStart)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeStart);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given start date range
    counter = 0;
    counter2 = 0;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartYear[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '/')
    {
        intendedStartMonth[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeStart[counter] != '\0')
    {
        intendedStartDay[counter2] = dateRangeStart[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedStartYearNo = atoi(intendedStartYear);
    intendedStartMonthNo = atoi(intendedStartMonth);
    intendedStartDayNo = atoi(intendedStartDay);


    printf("\nEnd of date range:");
    gets(dateRangeEnd);

    //checking end of date range format
    i=0;
    counter3=0;
    while(dateRangeEnd[i] != '\0')
    {
        if
            (dateRangeEnd[i] == '/')
        {
            counter3++;
            i++;
            continue;
        }
        while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
        {
            printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
            gets(dateRangeEnd);
            i=0;
            counter3=0;
        }
        i++;
    }

    while(counter3 != 2)
    {
        i=0;
        counter3 = 0;
        printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
        gets(dateRangeEnd);
        while(dateRangeEnd[i] != '\0')
        {
            if
                (dateRangeEnd[i] == '/')
            {
                counter3++;
                i++;
                continue;
            }
            while(isdigit(dateRangeEnd[i]) == 0 || strlen(dateRangeEnd)>10)
            {
                printf("The entered date isn't in correct format(It mustn't contain any letter or sign and it must be in yyyy/mm/dd format)\nPlease try again:");
                gets(dateRangeEnd);
                i=0;
                counter3=0;
            }
            i++;
        }
    }

    //separating year, month and the day of the given end date range
    counter = 0;
    counter2 = 0;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndYear[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndYear[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '/')
    {
        intendedEndMonth[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedEndMonth[counter2] = '\0';
    counter2 = 0;
    counter++;

    while(dateRangeEnd[counter] != '\0')
    {
        intendedEndDay[counter2] = dateRangeEnd[counter];
        counter++;
        counter2++;
    }
    intendedStartDay[counter2] = '\0';

    intendedEndYearNo = atoi(intendedEndYear);
    intendedEndMonthNo = atoi(intendedEndMonth);
    intendedEndDayNo = atoi(intendedEndDay);

    /*checking all saved expenses dates one by one with the start and end date range with using linked list
    and also using "checkExpenseDate" function*/
    //(the linked list is global so we can access the values in it in all functions also here)
    //in every round, a new value of date goes in "checkExpenseDate" function because linked list is global
    eTemp = eStart;
    while(eTemp != NULL)
    {
        sign = checkExpenseDate(intendedStartYearNo, intendedStartMonthNo, intendedStartDayNo, intendedEndYearNo, intendedEndMonthNo, intendedEndDayNo);
        if
            (sign == 1)
        {
           expenseAmount = atoi(eTemp->amount);
            if
                (expenseAmount >= lastExpenseAmount)
            {
                maxExpense = expenseAmount;
            }
            else
            {
                maxExpense = lastExpenseAmount;
            }
            lastExpenseAmount = atoi(eTemp->amount);
        }
        eTemp = eTemp->next;
    }
    printf("\nThe maximum expense amount = %d",  maxExpense);
}






void searchInIncomeDescription()
{
    char intendedWord[60], word[60];
    int counter=0, counter2=0;

    printf("Please enter your intended word to search in description fields of income:");
    gets(intendedWord);
    temp = start;
    while(temp != 0)
    {
        while(temp->description[counter] != '\n')
        {
            //separating the description field to words and comparing the given word with them
            word[counter2] = temp->description[counter];
            if
                (temp->description[counter] == ' ')
            {
                word[counter2] = '\0';
                if
                    (strcmp(word, intendedWord) == 0)
                {
                    //if the word in description field was exactly the given word, the program shows the detail of that income
                    printf("\nIncome type : ");
                    puts(temp->type);
                    printf("Income amount : ");
                    puts(temp->amount);
                    printf("Income date : ");
                    puts(temp->date);
                    printf("Income description : ");
                    puts(temp->description);
                    printf("\n");
                }
                strcpy(word, " ");
                counter2 = -1;
            }
            counter++;
            counter2++;
        }
        word[counter2] = '\0';
        //comparing the last word with the given word
        if
            (strcmp(word, intendedWord) == 0)
        {
            printf("\nIncome type : ");
            puts(temp->type);
            printf("Income amount : ");
            puts(temp->amount);
            printf("Income date : ");
            puts(temp->date);
            printf("Income description : ");
            puts(temp->description);
            printf("\n");
        }
        strcpy(word, " ");
        counter = 0;
        counter2 = 0;
        temp = temp->next;
    }
}






void searchInExpenseDescription()
{
    char intendedWord[60], word[60];
    int counter=0, counter2=0;
    printf("Please enter your intended word to search in description fields of expense:");
    gets(intendedWord);
    eTemp = eStart;
    while(eTemp != 0)
    {
        while(eTemp->description[counter] != '\n')
        {
            //separating the description field to words and comparing the given word with them
            word[counter2] = eTemp->description[counter];
            if
                (eTemp->description[counter] == ' ')
            {
                word[counter2] = '\0';
                if
                    (strcmp(word, intendedWord) == 0)
                {
                    //if the word in description field was exactly the given word, the program shows the detail of that income
                    printf("\nExpense type : ");
                    puts(eTemp->type);
                    printf("Expense amount : ");
                    puts(eTemp->amount);
                    printf("Expense date : ");
                    puts(eTemp->date);
                    printf("Expense description : ");
                    puts(eTemp->description);
                    printf("\n");
                }
                strcpy(word, " ");
                counter2 = -1;
            }
            counter++;
            counter2++;
        }
        word[counter2] = '\0';
        //comparing the last word with the given word
        if
            (strcmp(word, intendedWord) == 0)
        {
            printf("\nExpense type : ");
            puts(eTemp->type);
            printf("Expense amount : ");
            puts(eTemp->amount);
            printf("Expense date : ");
            puts(eTemp->date);
            printf("Expense description : ");
            puts(eTemp->description);
            printf("\n");
        }
        strcpy(word, " ");
        counter = 0;
        counter2 = 0;
        eTemp = eTemp->next;
    }
}




int incomeReports()
{
    char choice[3], choice2[3];
    int choiceNo, choice2No;
    printf("1)Total incomes in a specific year\n\n");
    printf("2)Total incomes in a specific date range\n\n");
    printf("3)A specific type of income in a specific date range\n\n");
    printf("4)Percentage ratio of different incomes\n\n");
    printf("5)Incomes detail in a specific date range\n\n");
    printf("6)Maximum amount of income in a specific date range\n\n");
    printf("7)Search word in description field of incomes\n\n");
    printf("Please enter the number of your choice:");
    gets(choice);
    choiceNo=atoi(choice);
    system("cls");

    //checking the number not to be out of range
    while(choiceNo>7 || choiceNo<1)
    {
        printf("1)Total incomes in a specific year\n\n");
        printf("2)Total incomes in a specific date range\n\n");
        printf("3)A specific type of income in a specific date range\n\n");
        printf("4)Percentage ratio of different incomes\n\n");
        printf("5)Incomes detail in a specific date range\n\n");
        printf("6)Maximum amount of income in a specific date range\n\n");
        printf("7)Search word in description field of incomes\n\n");
        printf("Please enter the number of your choice:");
        gets(choice);
        choiceNo=atoi(choice);
        system("cls");
    }

    if
        (choiceNo == 1)
    {
        specificYearIncomes();
        printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
        gets(choice2);
    }
    else
        if
            (choiceNo == 2)
        {
            specificDateRangeIncomes();
            printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
            gets(choice2);
        }
        else
            if
                (choiceNo == 3)
            {
                specificDateRangeIncomesWithSpecificType();
                printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                gets(choice2);
            }
            else
                if
                    (choiceNo == 4)
                {
                    incomeRatio();
                    printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                    gets(choice2);
                }
                else
                    if
                        (choiceNo == 5)
                    {
                        specificDateRangeIncomesDetails();
                        printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                        gets(choice2);
                    }
                    else
                        if
                            (choiceNo == 6)
                        {
                            specificDateRangeMaxIncome();
                            printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                            gets(choice2);
                        }
                        else
                        {
                            searchInIncomeDescription();
                            printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                            gets(choice2);
                        }
    choice2No = atoi(choice2);
    while(choice2No<1 || choice2No>2)
    {
        printf("The number you entered is out of range!!!\nPlease try again:");
        gets(choice2);
        choice2No = atoi(choice2);
    }
    system("cls");
    //returning the choice of the user(to go back to the main menu or exit the program)to the main menu
    return choice2No;

}




int expenseReports()
{
    char choice[3], choice2[3];
    int choiceNo, choice2No;
    printf("1)Total expenses in a specific year\n\n");
    printf("2)Total expenses in a specific date range\n\n");
    printf("3)A specific type of expense in a specific date range\n\n");
    printf("4)Percentage ratio of different expenses\n\n");
    printf("5)expenses detail in a specific date range\n\n");
    printf("6)Maximum amount of expense in a specific date range\n\n");
    printf("7)Search word in description field of expenses\n\n");
    printf("Please enter the number of your choice:");
    gets(choice);
    choiceNo=atoi(choice);
    system("cls");

    //checking the number not to be out of range
    while(choiceNo>7 || choiceNo<1)
    {
        printf("1)Total expenses in a specific year\n\n");
        printf("2)Total expenses in a specific date range\n\n");
        printf("3)A specific type of expense in a specific date range\n\n");
        printf("4)Percentage ratio of different expenses\n\n");
        printf("5)expenses detail in a specific date range\n\n");
        printf("6)Maximum amount of expense in a specific date range\n\n");
        printf("7)Search word in description field of expenses\n\n");
        printf("Please enter the number of your choice:");
        gets(choice);
        choiceNo=atoi(choice);
        system("cls");
    }

    if
        (choiceNo == 1)
    {
        specificYearExpenses();
        printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
        gets(choice2);
    }
    else
        if
            (choiceNo == 2)
        {
            specificDateRangeExpenses();
            printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
            gets(choice2);
        }
        else
            if
                (choiceNo == 3)
            {
                specificDateRangeExpensesWithSpecificType();
                printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                gets(choice2);
            }
            else
                if
                    (choiceNo == 4)
                {
                    expenseRatio();
                    printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                    gets(choice2);
                }
                else
                    if
                        (choiceNo == 5)
                    {
                        specificDateRangeExpensesDetails();
                        printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                        gets(choice2);
                    }
                    else
                        if
                            (choiceNo == 6)
                        {
                            specificDateRangeMaxExpense();
                            printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                            gets(choice2);
                        }
                        else
                        {
                            searchInExpenseDescription();
                            printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                            gets(choice2);
                        }
    choice2No = atoi(choice2);
    while(choice2No<1 || choice2No>2)
    {
        printf("The number you entered is out of range!!!\nPlease try again:");
        gets(choice2);
        choice2No = atoi(choice2);
    }
    system("cls");
    //returning the choice of the user(to go back to the main menu or exit the program)to the main menu
    return choice2No;
}






void changeEmail(long int fileCountNo)
{
    struct personInfo
    {
        char firstName[20];
        char lastName[40];
        char id[16];
        char mobileNo[16];
        char pass[17];
    };
    struct personInfo person;
    char fileCountStr[12], fileName[50], newEmail[70], line[100];
    FILE *profile;
    int i, sign=0;

    printf("Please enter your new email address:");
    gets(newEmail);

    //checking email format
    i=0;
    while(newEmail[i] != '\0')
    {
        if(newEmail[i] == '@')
        {
            sign++;
        }
        else
            if(newEmail[i] == '.')
            {
                sign++;
            }
        i++;
    }
    while(sign != 2)
    {
        printf("The entered email address isn't in correct format(It must contain '@' and '.' character)\nPlease try again:");
        gets(newEmail);
        sign=0;
        i=0;
        while(newEmail[i] != '\0')
        {
            if(newEmail[i] == '@')
            {
                sign++;
            }
            else
                if(newEmail[i] == '.')
                {
                    sign++;
                }
            i++;
        }
    }
    strcat(newEmail, "\n");

    strcpy(fileName, "profile");
    itoa(fileCountNo, fileCountStr, 10);
    strcat(fileName, fileCountStr);
    strcat(fileName, ".txt");
    profile = fopen(fileName, "r");
    if
        (profile == NULL)
        printf("The file couldn't be opened");
    else
    {
        //saving the person's information to variables
        fgets(line, 100, profile);
        fgets(person.pass, 100, profile);
        fgets(line, 100, profile);
        fgets(person.firstName, 100, profile);
        fgets(line, 100, profile);
        fgets(person.lastName, 100, profile);
        fgets(line, 100, profile);
        fgets(person.id, 100, profile);
        fgets(line, 100, profile);
        fgets(person.mobileNo, 100, profile);

    }

    //opening file in "w" mode which will erase the whole file
    strcpy(fileName, "profile");
    itoa(fileCountNo, fileCountStr, 10);
    strcat(fileName, fileCountStr);
    strcat(fileName, ".txt");
    profile = fopen(fileName, "w");
    if
        (profile == NULL)
        printf("The file couldn't be opened");
    else
    {
        /*writing all the information(that we got from the file)in file again except the email
        instead we write the given email in file*/
        fputs("Confirmed password:\n", profile);
        fputs(person.pass, profile);

        fputs("First name:\n", profile);
        fputs(person.firstName, profile);

        fputs("Last name:\n", profile);
        fputs(person.lastName, profile);

        fputs("ID:\n", profile);
        fputs(person.id, profile);

        fputs("Mobile number:\n", profile);
        fputs(person.mobileNo, profile);

        fputs("Email:\n", profile);
        fputs(newEmail, profile);
        fputc('\n', profile);
        fputc('\n', profile);

        fputs("Incomes:\n", profile);

        //writing income information which has been saved in linked list
        temp = start;
        while(temp != 0)
        {
            fputc('\n', profile);
            fputs(temp->type, profile);
            fputs(temp->amount, profile);
            fputs(temp->date, profile);
            fputs(temp->description, profile);

            temp = temp->next;
        }

    }
    fclose(profile);
}






void changeMobileNo(long int fileCountNo)
{
    struct personInfo
    {
        char firstName[20];
        char lastName[40];
        char id[16];
        char email[70];
        char pass[17];
    };
    struct personInfo person;
    char fileCountStr[12], fileName[50], newMobileNo[15], line[100];
    FILE *profile;
    int i;
    printf("Please enter your new mobile number:");
    gets(newMobileNo);

    //checking mobile number format
    i=0;
    while(newMobileNo[i] != '\0')
    {
        while(isdigit(newMobileNo[i]) == 0 || strlen(newMobileNo) != 11 || newMobileNo[0] != '0' || newMobileNo[1] != '9')
        {
            printf("The entered mobile number isn't in correct format(The length of your id most be 11 characters and it mustn't contain any letter or sign and it must began with '09')\nPlease try again:");
            gets(newMobileNo);
            i=0;
        }
        i++;
    }
    strcat(newMobileNo, "\n");

    strcpy(fileName, "profile");
    itoa(fileCountNo, fileCountStr, 10);
    strcat(fileName, fileCountStr);
    strcat(fileName, ".txt");
    profile = fopen(fileName, "r");
    if
        (profile == NULL)
        printf("The file couldn't be opened");
    else
    {
        //saving the person's information to variables
        fgets(line, 100, profile);
        fgets(person.pass, 100, profile);
        fgets(line, 100, profile);
        fgets(person.firstName, 100, profile);
        fgets(line, 100, profile);
        fgets(person.lastName, 100, profile);
        fgets(line, 100, profile);
        fgets(person.id, 100, profile);
        fgets(line, 100, profile);
        fgets(line, 100, profile);
        fgets(line, 100, profile);
        fgets(person.email, 100, profile);
    }

    //opening file in "w" mode which will erase the whole file
    strcpy(fileName, "profile");
    itoa(fileCountNo, fileCountStr, 10);
    strcat(fileName, fileCountStr);
    strcat(fileName, ".txt");
    profile = fopen(fileName, "w");
    if
        (profile == NULL)
        printf("The file couldn't be opened");
    else
    {
        /*writing all the information(that we got from the file)in file again except the mobile number
        instead we write the given mobile in file*/
        fputs("Confirmed password:\n", profile);
        fputs(person.pass, profile);

        fputs("First name:\n", profile);
        fputs(person.firstName, profile);

        fputs("Last name:\n", profile);
        fputs(person.lastName, profile);

        fputs("ID:\n", profile);
        fputs(person.id, profile);

        fputs("Mobile number:\n", profile);
        fputs(newMobileNo, profile);

        fputs("Email:\n", profile);
        fputs(person.email, profile);
        fputc('\n', profile);
        fputc('\n', profile);

        fputs("Incomes:\n", profile);

        //writing income information which has been saved in linked list
        temp = start;
        while(temp != 0)
        {
            fputc('\n', profile);
            fputs(temp->type, profile);
            fputs(temp->amount, profile);
            fputs(temp->date, profile);
            fputs(temp->description, profile);

            temp = temp->next;
        }
    }
    fclose(profile);
}







void changePass(long int fileCountNo)
{
    struct personInfo
    {
        char firstName[30];
        char lastName[40];
        char id[15];
        char email[70];
        char mobileNo[15];
    };
    struct personInfo person;
    char fileCountStr[12], fileName[50], line[100], newPass[17], passAgain[17], tempPass, passNumStr[2];
    FILE *profile;
    int i, digit=0, alphaAndSign=0;
    long int multiplyIn, passNum;

    printf("Please enter your new password:");
    gets(newPass);
    i=0;

    //checking password format
    while(newPass[i] != '\0')
    {
        if
            (isdigit(newPass[i]) == 1)
        {
            digit++;
        }
        else
            alphaAndSign++;

        i++;
    }

    while(alphaAndSign<1 || digit<1 || strlen(newPass)<8 || strlen(newPass)>15)
    {
        printf("The entered password isn't in correct format(It must be at least 8 and at most 15 characters and it must contain letters and numbers both together)\nPlease try again:");
        gets(newPass);
        i=0;
        alphaAndSign=0;
        digit=0;
        while(newPass[i] != '\0')
        {
            if
                (isdigit(newPass[i]) == 1)
            {
                digit++;
            }
            else
                alphaAndSign++;

            i++;
        }
    }

    //getting password again to confirm it
    printf("Password again:");
    gets(passAgain);
    while(strcmp(passAgain ,newPass) != 0)
    {
        printf("Your password is incompatible!!Please try again\n");
        printf("Password:");
        gets(newPass);

        printf("Password again:");
        gets(passAgain);
    }

    //manipulating the password then saving it in file to improve security
    i=0;
    multiplyIn=2;
    //changing the numbers in password
    while(newPass[i] != '\0')
    {
        if
            (isdigit(newPass[i]) == 1)
        {
            passNumStr[0] = newPass[i];
            passNumStr[1] = '\0';
            passNum = atoi(passNumStr);
            passNum = passNum * multiplyIn;
            passNum = passNum % 10;
            itoa(passNum, passNumStr, 10);
            newPass[i] = passNumStr[0];
            multiplyIn = (multiplyIn + 2) * 3;
        }
        if
                (i==4 || i==9)
            {
                multiplyIn = 3;
            }
            else
                if
                    (i==13)
                {
                    multiplyIn = 2;
                }
        i++;
    }
    //changing the places of the first 8 characters in password(because we're sure there is at least 8 characters
    tempPass = newPass[3];
    newPass[3] = newPass[5];
    newPass[5] = tempPass;
    tempPass = newPass[4];
    newPass[4] = newPass[6];
    newPass[6] = tempPass;
    tempPass = newPass[1];
    newPass[1] = newPass[7];
    newPass[7] = tempPass;
    tempPass = newPass[2];
    newPass[2] = newPass[8];
    newPass[8] = tempPass;

    strcat(newPass, "\n");

    strcpy(fileName, "profile");
    itoa(fileCountNo, fileCountStr, 10);
    strcat(fileName, fileCountStr);
    strcat(fileName, ".txt");
    profile = fopen(fileName, "r");
    if
        (profile == NULL)
        printf("The file couldn't be opened");
    else
    {
        //saving the person's information to variables
        fgets(line, 100, profile);
        fgets(line, 100, profile);
        fgets(line, 100, profile);
        fgets(person.firstName, 100, profile);
        fgets(line, 100, profile);
        fgets(person.lastName, 100, profile);
        fgets(line, 100, profile);
        fgets(person.id, 100, profile);
        fgets(line, 100, profile);
        fgets(person.mobileNo, 100, profile);
        fgets(line, 100, profile);
        fgets(person.email, 100, profile);
    }

    //opening file in "w" mode which will erase the whole file
    strcpy(fileName, "profile");
    itoa(fileCountNo, fileCountStr, 10);
    strcat(fileName, fileCountStr);
    strcat(fileName, ".txt");
    profile = fopen(fileName, "w");
    if
        (profile == NULL)
        printf("The file couldn't be opened");
    else
    {
        /*writing all the information(that we got from the file)in file again except the password
        instead we write the given password in file*/
        fputs("Confirmed password:\n", profile);
        fputs(newPass, profile);

        fputs("First name:\n", profile);
        fputs(person.firstName, profile);

        fputs("Last name:\n", profile);
        fputs(person.lastName, profile);

        fputs("ID:\n", profile);
        fputs(person.id, profile);

        fputs("Mobile number:\n", profile);
        fputs(person.mobileNo, profile);

        fputs("Email:\n", profile);
        fputs(person.email, profile);
        fputc('\n', profile);
        fputc('\n', profile);

        fputs("Incomes:\n", profile);

        temp = start;
        while(temp != 0)
        {
            fputc('\n', profile);
            fputs(temp->type, profile);
            fputs(temp->amount, profile);
            fputs(temp->date, profile);
            fputs(temp->description, profile);

            temp = temp->next;
        }
    }
    fclose(profile);
}






int setting(long int fileCountNo)
{
    char choice[3], choice2[3];
    int choiceNo, choice2No;
    printf("Welcome to the setting section.Please choose one of the items below\n\n");
    printf("1)Change email address\n2)Change mobile number\n3)Change password\n");
    printf("Please enter the number of your choice:");
    gets(choice);
    choiceNo = atoi(choice);
    system("cls");
    //checking the number not to be out of range
    while(choiceNo>3 || choiceNo<1)
    {
        printf("The number you entered is out of range.Please try again\n\n");
        printf("Welcome to the setting section.Please choose one of the items below\n\n");
        printf("1)Change email address\n2)Change mobile number\n3)Change password\n");
        gets(choice);
        choiceNo = atoi(choice);
    }
    if
        (choiceNo == 1)
    {
        changeEmail(fileCountNo);
        printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
        gets(choice2);
    }
    else
        if
            (choiceNo == 2)
        {
            changeMobileNo(fileCountNo);
            printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
            gets(choice2);
        }
        else
            if
                (choiceNo == 3)
            {
                changePass(fileCountNo);
                printf("\n\n1)Exit\n2)Going back to the main menu\n\nPlease enter the number of your choice:");
                gets(choice2);
            }
    choice2No = atoi(choice2);
    while(choice2No<1 || choice2No>2)
    {
        printf("The number you entered is out of range!!!\nPlease try again:");
        gets(choice2);
        choice2No = atoi(choice2);
    }
    system("cls");
    //returning the choice of the user(to go back to the main menu or exit the program)to the main menu
    return choice2No;
}




