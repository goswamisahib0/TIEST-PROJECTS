#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_ACCOUNTS 10
#define MAX_TRANSACTIONS 50
struct Transaction
{
    char type;
    int amount;
    char accountDetails[50];
    int numTransactions;
};
struct BankAccount
{
    char name[50];
    char fathersName[50];
    char cityName[50];
    int age, balance;
    char mobileNumber[12];
    char cnic[14];
    char password[20];
    struct Transaction transactions[MAX_TRANSACTIONS];
    int numTransactions;
};
struct BankAccount accounts[MAX_ACCOUNTS];
int logged_in_user = -1, numAccounts = MAX_ACCOUNTS;
void createAccount();
void login();
void logout();
void display_main_menu();
void sendbalance();
void depositbalance();
void accountinfo();
void changePassword();
void about();
int validatePassword(const char *password);
void displayTransactionHistory();
void accountinfo()
{
    printf("\t***********************\n");
    printf("\t* ACCOUNT INFORMATION *\n");
    printf("\t***********************\n");
    printf("Name: %s\n", accounts[logged_in_user].name);
    printf("Father's Name: %s\n", accounts[logged_in_user].fathersName);
    printf("City Name: %s\n", accounts[logged_in_user].cityName);
    printf("Age: %d\n", accounts[logged_in_user].age);
    printf("Mobile Number: %s\n", accounts[logged_in_user].mobileNumber);
    printf("CNIC: %s\n", accounts[logged_in_user].cnic);
    printf("Balance: %d\n", accounts[logged_in_user].balance);
    display_main_menu();

}
void logout()
{

    printf("Logout successful! BYE BYE, %s.\n", accounts[logged_in_user].name);
    logged_in_user = -1;

    main();
}
void createAccount()
{
    if (numAccounts > 0)
    {
        struct BankAccount *newAccount = &accounts[MAX_ACCOUNTS - numAccounts];
        printf("\t******************\n");
        printf("\t* CREATE ACCOUNT *\n");
        printf("\t******************\n");
        printf("\nEnter your details to create an account:\n");
        printf("Name: ");
        scanf(" %[^\n]s", newAccount->name);
        printf("Father's Name: ");
        scanf(" %[^\n]s", newAccount->fathersName);
        printf("City Name: ");
        scanf(" %[^\n]s", newAccount->cityName);
        printf("Age: ");
        scanf("%d", &(newAccount->age));
        if (newAccount->age < 18)
        {
            printf("Under 18 are not eligible! Age must be 18 or older to create an account.\n");
            return;
        }
        do
        {
            printf("Mobile Number (11 digits, without spaces or dashes): ");
            scanf("%s", newAccount->mobileNumber);
            for (int i = 0; i < MAX_ACCOUNTS - numAccounts; i++)
            {
                if (strcmp(newAccount->mobileNumber, accounts[i].mobileNumber) == 0)
                {
                    printf("This Mobile Number is already used in another account. (You can't create multiple accounts on one Number)\n");
                    return;
                }
            }
            int valid = 1;
            for (int i = 0; newAccount->mobileNumber[i] != '\0'; i++)
            {
                if (!isdigit(newAccount->mobileNumber[i]))
                {
                    printf("Enter Only Digits.\n");
                    valid = 0;
                    break;
                }
            }
            if (valid && strlen(newAccount->mobileNumber) == 11)
            {
                break;
            }
            else
            {
                printf("Invalid mobile number. Please enter a valid mobile number. (11 Digits Only)\n");
            }
        }
        while (1);
        do
        {
            printf("CNIC Number (13 digits, Without spaces or dashes): ");
            scanf("%s", newAccount->cnic);
            for (int i = 0; i < MAX_ACCOUNTS - numAccounts; i++)
            {
                if (strcmp(newAccount->cnic, accounts[i].cnic) == 0)
                {
                    printf("This CNIC Number is already used in another account. (You can't create multiple accounts on one CNIC Number)\n");
                    return;
                }
            }
            int valid = 1;
            for (int i = 0; newAccount->cnic[i] != '\0'; i++)
            {
                if (!isdigit(newAccount->cnic[i]))
                {
                    printf("Enter Only Digits.\n");

                    valid = 0;
                    break;
                }
            }
            if (valid && strlen(newAccount->cnic) == 13)
            {
                break;
            }
            else
            {
                printf("Invalid CNIC. Please enter a valid CNIC. (13 Digits Only)\n");
            }
        }
        while (1);

        do
        {
            printf("Password (at least 1 small letter, 1 capital letter, 1 numeric, min length 6): ");
            scanf("%s", newAccount->password);

        }
        while (!(validatePassword(newAccount->password)));

        printf("\nAccount created successfully!\n");
        numAccounts--;
        newAccount->balance = 0;
        newAccount->numTransactions = 0;
    }
    else
    {
        printf("The Slots Of Accounts Are Full.\nTry Again Later! Thank you.\n");
    }
}
void changePassword()
{
    char newPassword[20];
    char reEnterPassword[20];

    do
    {
        printf("\t*******************\n");
        printf("\t* CHANGE PASSWORD *\n");
        printf("\t*******************\n");

        printf("Enter your new password (at least 1 small letter, 1 capital letter, 1 numeric, min length 6): ");
        scanf("%s", newPassword);

        if (!validatePassword(newPassword))
        {
            printf("Invalid password. Please try again.\n");
            continue;
        }

        printf("Re-enter your new password: ");
        scanf("%s", reEnterPassword);

        if (strcmp(newPassword, reEnterPassword) != 0)
        {
            printf("Passwords do not match. Please try again.\n");
        }
        else
        {
            break;
        }
    }
    while (1);

    strcpy(accounts[logged_in_user].password, newPassword);
    printf("Password changed successfully!\n");

    display_main_menu();
}

void login()
{
    printf("\t*****************\n");
    printf("\t* LOGIN ACCOUNT *\n");
    printf("\t*****************\n");
    char enteredMobileNumber[12];
    char enteredPassword[20];

    printf("\nEnter your mobile number to login: ");
    scanf("%11s", enteredMobileNumber);
    int i;
    for (i = 0; i < MAX_ACCOUNTS; i++)
    {
        if (strcmp(enteredMobileNumber, accounts[i].mobileNumber) == 0)
        {
            printf("Enter your password: ");
            scanf("%s", enteredPassword);
            if (strcmp(enteredPassword, accounts[i].password) == 0)
            {
                printf("Login successful! You are now logged in as: %s\n", accounts[i].name);
                logged_in_user = i;
                display_main_menu();
            }
            else
            {
                printf("Incorrect password. Login failed.\n");
                return;
            }
        }
    }
    printf("Account not found. Enter correct number.\n");
}
void sendbalance()
{
    printf("\t****************\n");
    printf("\t* SEND BALANCE *\n");
    printf("\t****************\n");
    int amount;
    char recipientMobileNumber[12];


    printf("Enter the recipient's mobile number: ");
    scanf("%11s", recipientMobileNumber);

    if (strcmp(recipientMobileNumber, accounts[logged_in_user].mobileNumber) == 0)
    {
        printf("Cannot send money to yourself.\n");
        display_main_menu();
        return;
    }

    int recipientIndex = -1;
    for (int i = 0; i < MAX_ACCOUNTS; i++)
    {
        if (strcmp(recipientMobileNumber, accounts[i].mobileNumber) == 0)
        {
            recipientIndex = i;
            break;
        }
    }

    if (recipientIndex != -1)
    {
        printf("Recipient's Account Name: %s\n", accounts[recipientIndex].name);
        printf("Enter the amount to send: ");
        scanf("%d", &amount);
        if (amount > 0 && accounts[logged_in_user].balance >= amount)
        {
            accounts[logged_in_user].balance -= amount;
            accounts[recipientIndex].balance += amount;

            accounts[logged_in_user].transactions[accounts[logged_in_user].numTransactions].type = 'T';
            accounts[logged_in_user].transactions[accounts[logged_in_user].numTransactions].amount = amount;
            strcpy(accounts[logged_in_user].transactions[accounts[logged_in_user].numTransactions].accountDetails,accounts[recipientIndex].name);
            accounts[logged_in_user].numTransactions++;

            accounts[recipientIndex].transactions[accounts[recipientIndex].numTransactions].type = 'R';
            accounts[recipientIndex].transactions[accounts[recipientIndex].numTransactions].amount = amount;
            strcpy(accounts[recipientIndex].transactions[accounts[recipientIndex].numTransactions].accountDetails,accounts[logged_in_user].name);
            accounts[recipientIndex].numTransactions++;

            printf("Money sent successfully! Current balance: %d\n", accounts[logged_in_user].balance);
        }
        else
        {
            printf("Invalid amount or insufficient balance. Please try again.\n");
        }
    }

    else
    {
        printf("Recipient account not found. Please check the mobile number and try again.\n");
    }


    display_main_menu();
}

void depositbalance()
{
    int amount;
    printf("\t*******************\n");
    printf("\t* DEPOSIT BALANCE *\n");
    printf("\t*******************\n");
    printf("Enter the amount to deposit: ");
    scanf("%d", &amount);
    if (amount > 0)
    {
        accounts[logged_in_user].transactions[accounts[logged_in_user].numTransactions].type = 'D';
        accounts[logged_in_user].transactions[accounts[logged_in_user].numTransactions].amount = amount;
        strcpy(accounts[logged_in_user].transactions[accounts[logged_in_user].numTransactions].accountDetails, "Self Account");
        accounts[logged_in_user].numTransactions++;
        accounts[logged_in_user].balance += amount;
        printf("Deposit successful! Current balance: %d\n", accounts[logged_in_user].balance);
    }
    else
    {
        printf("Invalid amount. Please enter a positive value.\n");
    }

    display_main_menu();
}
void display_main_menu()
{
    int choice;
    do
    {

        printf("\t*************\n");
        printf("\t* MAIN MENU *\n");
        printf("\t*************\n");

        printf("\n1. Send Money.\n2. Deposit Cash.\n3. Check Account Info.\n4. View Transaction History.\n5. Change Password.\n6. Logout.\n7. About.\n0. Exit.\nEnter Your Choice. (0-7)\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            sendbalance();
            break;
        case 2:
            depositbalance();
            break;
        case 3:
            accountinfo();
            break;
        case 4:
            displayTransactionHistory();
            break;
        case 5:
            changePassword();
            break;
        case 6:
            logout();
            break;
        case 7:
            about();
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\tInvalid Choice\n");
        }

    }
    while(choice != 0);

}
void displayTransactionHistory()
{
    printf("\t***********************\n");
    printf("\t* TRANSACTION HISTORY *\n");
    printf("\t***********************\n");

    if (accounts[logged_in_user].numTransactions == 0)
    {
        printf("No transactions found.\n");
    }
    else
    {
        for (int i = 0; i < accounts[logged_in_user].numTransactions; i++)
        {
            char *transactionType;
            switch (accounts[logged_in_user].transactions[i].type)
            {
            case 'T':
                transactionType = "Money Transferred";
                break;
            case 'R':
                transactionType = "Money Received";
                break;
            case 'D':
                transactionType = "Money Deposited";
                break;
            default:
                transactionType = "Unknown";
                break;
            }
            printf("Transfer Type: %s\tAmount: %d\tDetails: %s\n", transactionType, accounts[logged_in_user].transactions[i].amount, accounts[logged_in_user].transactions[i].accountDetails);
        }
    }
    display_main_menu();

}


void about()
{
    printf("\t************\n");
    printf("\t* ABOUT US *\n");
    printf("\t************\n");
    printf("\n\nBANK MANAGMENT SYSTEM.\nVersion 1.0\nFor support, contact: bsm.pk@gmail.com\n");
    return;
}
int validatePassword(const char *password)
{
    int hasLowerCase = 0, hasUpperCase = 0, hasDigit = 0, valid = 1;
    if (strlen(password) < 6)
    {
        printf("\nPassword must be at least 6 characters long.\n");
        return 0;
    }
    for (int i = 0; i < strlen(password); i++)
    {
        if (islower(password[i]))
        {
            hasLowerCase = 1;
        }
        else if (isupper(password[i]))
        {
            hasUpperCase = 1;
        }
        else if (isdigit(password[i]))
        {
            hasDigit = 1;
        }
    }
    if (!hasLowerCase || !hasUpperCase || !hasDigit)
    {
        printf("\nPassword must contain at least 1 lowercase letter, 1 uppercase letter, and 1 digit.\n");
        valid = 0;
    }
    return valid;
}
int main()
{
    int choice;
    printf("\t ****************************\n");
    printf("\t *  Bank Management System  *\n");
    printf("\t ****************************\n");



    do
    {
        printf("\n\t1. Create Account\n\t2. Login\n\t3. About\n\t0. Exit\n\tEnter your choice. (0-3) : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
            login();
            break;
        case 3:
            about();
            break;
        case 0:
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    while (choice != 0);
    return 0;
}