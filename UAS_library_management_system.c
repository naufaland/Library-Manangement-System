#include <stdio.h>
#include <string.h>

// Mendifinisikan struktur untuk buku, peminjaman dan transaksi peminjaman buku
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
    int dueDate;  
    int dueMonth;
    int dueYear;
};

// Fungsi untuk menampilkan menu utama
void displayMainMenu() {
    printf("WELCOME TO LIBRARY\n");
    printf("Select Menu (Type the Number):\n");
    printf("1. Book Management\n");
    printf("2. Borrower Management\n");
    printf("3. Borrowing Transaction\n");
    printf("4. Returning Book\n");
    printf("5. Exit\n");
}

// Fungsi untuk menambahkan data buku ke dalam daftar buku
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

// Fungsi untuk menampilkan daftar buku
void displayBooks(struct Book books[], int bookCount) {
    printf("List Book\n");
    printf("Title#Author#ISBN#Quantity\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%s#%s#%d#%d\n", books[i].title, books[i].author, books[i].iSBN, books[i].quantity);
    }
}

// Fungsi untuk menambahkan data peminjam
void addBorrower(struct Borrower borrowers[], int *borrowerCount) {
    // Pengisian data peminjam
    printf("Add New Borrower\n");
    printf("Name: ");
    scanf(" %[^\n]", borrowers[*borrowerCount].name);
    printf("Address: ");
    scanf(" %[^\n]", borrowers[*borrowerCount].address);
    printf("Phone Number: ");
    scanf(" %[^\n]", borrowers[*borrowerCount].contact);
    (*borrowerCount)++;
}

// Fungsi untuk menampilkan daftar peminjam
void displayBorrowers(struct Borrower borrowers[], int borrowerCount) {
    printf("List Borrower\n");
    printf("Name#Address#Contact\n");
    for (int i = 0; i < borrowerCount; i++) {
        printf("%s#%s#%s\n", borrowers[i].name, borrowers[i].address, borrowers[i].contact);
    }
}

// Fungsi untuk menambahkan transaksi peminjaman
void addBorrowTransaction(struct BorrowingTransaction transactions[], int *transactionCount) {
     // Pengisian data transaksi peminjaman
    printf("Add New Transaction\n");
    printf("Perhatian: Jika buku tidak dikembalikan pada tempo nya, maka akan dikenakan denda.\n");
    
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
    
    int dueDay = transactions[*transactionCount].borrowDate + 7;
    int dueMonth = transactions[*transactionCount].borrowMonth;
    int dueYear = transactions[*transactionCount].borrowYear;

    if (dueDay > 30) {
        dueDay -= 30;
        dueMonth++;
    }

    transactions[*transactionCount].dueDate = dueDay;
    transactions[*transactionCount].dueMonth = dueMonth;
    transactions[*transactionCount].dueYear = dueYear;
    
    (*transactionCount)++;
}

// Fungsi untuk menampilkan daftar transaksi peminjaman dan menghitung denda
void displayBorrowTransactions(struct BorrowingTransaction transactions[], int transactionCount) {
    printf("List Transaction\n");
    printf("Name#Book Title#Type#Borrow Date#Return Date#Late#Denda\n");
    for (int i = 0; i < transactionCount; i++) {
        int borrowDays = transactions[i].dueDate + transactions[i].dueMonth * 30 + transactions[i].dueYear * 365;
        int returnDaysActual = transactions[i].returnDate + transactions[i].returnMonth * 30 + transactions[i].returnYear * 365;

        int lateDays = returnDaysActual - borrowDays;
        if (lateDays > 0) {
            int denda = 0;
            if (strcmp(transactions[i].type, "fiksi") == 0) {
                denda = lateDays * 2000;
            } else {
                denda = lateDays * 3000;
            }

            if (denda > 50000) {
                denda = 50000;
            }

            printf("%s#%s#%s#%d-%d-%d#%d-%d-%d#%d#%d\n",
                transactions[i].name, transactions[i].book, transactions[i].type,
                transactions[i].borrowDate, transactions[i].borrowMonth, transactions[i].borrowYear,
                transactions[i].returnDate, transactions[i].returnMonth, transactions[i].returnYear,
                lateDays, denda);
        } else {
            printf("%s#%s#%s#%d-%d-%d#%d-%d-%d#%d#0\n",
                transactions[i].name, transactions[i].book, transactions[i].type,
                transactions[i].borrowDate, transactions[i].borrowMonth, transactions[i].borrowYear,
                transactions[i].returnDate, transactions[i].returnMonth, transactions[i].returnYear,
                lateDays);
        }
    }
}

// Fungsi untuk mengelola pengembalian buku
void returnBook(struct BorrowingTransaction transactions[], int transactionCount) {
    // Pengembalian buku dan menghitung denda
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
            
            int returnDateActual, returnMonthActual, returnYearActual;
            printf("Enter Actual Return Date (day month year): ");
            scanf("%d %d %d", &returnDateActual, &returnMonthActual, &returnYearActual);
            
            printf("Return Date (Actual): %d-%d-%d\n", returnDateActual, returnMonthActual, returnYearActual);

            // Menghitung keterlambatan dan denda
            int borrowDays = transactions[i].dueDate + transactions[i].dueMonth * 30 + transactions[i].dueYear * 365;
            int returnDaysActual = returnDateActual + returnMonthActual * 30 + returnYearActual * 365;

            int lateDays = returnDaysActual - borrowDays;
            if (lateDays > 0) {
                int denda = 0;
                if (strcmp(transactions[i].type, "fiksi") == 0) {
                    denda = lateDays * 2000;
                } else {
                    denda = lateDays * 3000;
                }

                if (denda > 50000) {
                    denda = 50000;
                }

                printf("Late: %d days\n", lateDays);
                printf("Denda: %d\n", denda);
            } else {
                printf("Returned on time.\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No transaction found for borrower: %s\n", borrowerName);
    }
}


int main() { // Fungsi Utama dari program
    // Mendeklarasikan variabel dan stuktur data
    struct Book books[100];
    struct Borrower borrowers[100];
    struct BorrowingTransaction transactions[100];
    int bookCount = 0;
    int borrowerCount = 0;
    int transactionCount = 0;
    int choice;

    // Iterasi pada menu utama
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
