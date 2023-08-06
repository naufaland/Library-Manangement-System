#include <stdio.h>
#include <string.h>

struct Book {
    char title[100];
    char author[100];
    int iSBN;
    int quantity;
};

struct Borrower {
    char name[100];
    char address[100];
    char contact[100];
};

struct BorrowingTransaction {
    char name[100];
    char book[100];
    char type[20];
    int borrowDate;
    int borrowMonth;
    int borrowYear;
    int returnDate;
    int returnMonth;
    int returnYear;
};

void displayMainMenu() {
    printf("WELCOME TO LIBRARY\n");
    printf("Select Menu (Type the Number):\n");
    printf("1. Book Management\n");
    printf("2. Borrower Management\n");
    printf("3. Borrowing Transaction\n");
    printf("4. Returning Book\n");
    printf("5. Exit\n");
}

void addBook(struct Book books[], int *bookCount) {
    printf("Add New Book\n");
    printf("Title: ");
    scanf(" %[^\n]", books[*bookCount].title);
    printf("Author: ");
    scanf(" %[^\n]", books[*bookCount].author);
    printf("ISBN: ");
    scanf("%d", &books[*bookCount].iSBN);
    printf("Quantity: ");
    scanf("%d", &books[*bookCount].quantity);
    (*bookCount)++;
}

void displayBooks(struct Book books[], int bookCount) {
    printf("List Book\n");
    printf("Title#Author#ISBN#Quantity\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%s#%s#%d#%d\n", books[i].title, books[i].author, books[i].iSBN, books[i].quantity);
    }
}

void addBorrower(struct Borrower borrowers[], int *borrowerCount) {
    printf("Add New Borrower\n");
    printf("Name: ");
    scanf(" %[^\n]", borrowers[*borrowerCount].name);
    printf("Address: ");
    scanf(" %[^\n]", borrowers[*borrowerCount].address);
    printf("Phone Number: ");
    scanf(" %[^\n]", borrowers[*borrowerCount].contact);
    (*borrowerCount)++;
}

void displayBorrowers(struct Borrower borrowers[], int borrowerCount) {
    printf("List Borrower\n");
    printf("Name#Address#Contact\n");
    for (int i = 0; i < borrowerCount; i++) {
        printf("%s#%s#%s\n", borrowers[i].name, borrowers[i].address, borrowers[i].contact);
    }
}

void addBorrowTransaction(struct BorrowingTransaction transactions[], int *transactionCount) {
    printf("Add New Transaction\n");
    printf("Name: ");
    scanf(" %[^\n]", transactions[*transactionCount].name);
    printf("Book Title: ");
    scanf(" %[^\n]", transactions[*transactionCount].book);
    printf("Book Type (fiksi/nonfiksi): ");
    scanf(" %[^\n]", transactions[*transactionCount].type);
    printf("Borrow Date (day month year): ");
    scanf("%d %d %d", &transactions[*transactionCount].borrowDate, &transactions[*transactionCount].borrowMonth, &transactions[*transactionCount].borrowYear);
    printf("Return Date (day month year): ");
    scanf("%d %d %d", &transactions[*transactionCount].returnDate, &transactions[*transactionCount].returnMonth, &transactions[*transactionCount].returnYear);
    (*transactionCount)++;
}

void displayBorrowTransactions(struct BorrowingTransaction transactions[], int transactionCount) {
    printf("List Transaction\n");
    printf("Name#Book Title#Type#Borrow Date#Return Date#Late#Denda\n");
    for (int i = 0; i < transactionCount; i++) {
        int returnDay = transactions[i].borrowDate + 7;
        int returnMonth = transactions[i].borrowMonth;
        int returnYear = transactions[i].borrowYear;

        if (returnDay > 30) {
            returnDay -= 30;
            returnMonth++;
        }

        int late = 0;
        if (returnMonth < transactions[i].returnMonth) {
            late = (transactions[i].returnMonth - returnMonth) * 30;
        } else if (returnMonth == transactions[i].returnMonth) {
            if (returnDay < transactions[i].returnDate) {
                late = transactions[i].returnDate - returnDay;
            }
        }

        int denda = 0;
        if (strcmp(transactions[i].type, "fiksi") == 0) {
            denda = late * 2000;
        } else {
            denda = late * 3000;
        }

        if (denda > 50000) {
            denda = 50000;
        }

        printf("%s#%s#%s#%d-%d-%d#%d-%d-%d#%d#%d\n",
            transactions[i].name, transactions[i].book, transactions[i].type,
            transactions[i].borrowDate, transactions[i].borrowMonth, transactions[i].borrowYear,
            transactions[i].returnDate, transactions[i].returnMonth, transactions[i].returnYear,
            late, denda);
    }
}

void returnBook(struct BorrowingTransaction transactions[], int transactionCount) {
    char borrowerName[100];
    printf("Enter Borrower Name: ");
    scanf(" %[^\n]", borrowerName);

    int found = 0;
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].name, borrowerName) == 0) {
            printf("Return Book\n");
            printf("Book Title: %s\n", transactions[i].book);
            printf("Book Type (fiksi/nonfiksi): %s\n", transactions[i].type);
            printf("Borrow Date: %d-%d-%d\n", transactions[i].borrowDate, transactions[i].borrowMonth, transactions[i].borrowYear);
            printf("Return Date (day month year): ");
            scanf("%d %d %d", &transactions[i].returnDate, &transactions[i].returnMonth, &transactions[i].returnYear);

            int returnDay = transactions[i].borrowDate + 7;
            int returnMonth = transactions[i].borrowMonth;
            int returnYear = transactions[i].borrowYear;

            if (returnDay > 30) {
                returnDay -= 30;
                returnMonth++;
            }

            int late = 0;
            if (returnMonth < transactions[i].returnMonth) {
                late = (transactions[i].returnMonth - returnMonth) * 30;
            } else if (returnMonth == transactions[i].returnMonth) {
                if (returnDay < transactions[i].returnDate) {
                    late = transactions[i].returnDate - returnDay;
                }
            }

            int denda = 0;
            if (strcmp(transactions[i].type, "fiksi") == 0) {
                denda = late * 2000;
            } else {
                denda = late * 3000;
            }

            if (denda > 50000) {
                denda = 50000;
            }

            printf("Late: %d\n", late);
            printf("Denda: %d\n", denda);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No transaction found for borrower: %s\n", borrowerName);
    }
}

int main() {
    struct Book books[100];
    struct Borrower borrowers[100];
    struct BorrowingTransaction transactions[100];
    int bookCount = 0;
    int borrowerCount = 0;
    int transactionCount = 0;
    int choice;

    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook(books, &bookCount);
                break;
            case 2:
                addBorrower(borrowers, &borrowerCount);
                break;
            case 3:
                addBorrowTransaction(transactions, &transactionCount);
                break;
            case 4:
                returnBook(transactions, transactionCount);
                break;
            case 5:
                printf("Exiting Library Management System...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
