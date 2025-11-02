#include <stdio.h>
#define MAX_BOOKS 100
#define NAME_LEN 50
int searchBook(int ids[], int total, int id) {
    for (int i = 0; i < total; i++) {
        if (ids[i] == id) {
            return i;
        }
    }
    return -1;
}
void addBook(int ids[], char names[][NAME_LEN], float costs[], int stock[], int *total) {
    if (*total >= MAX_BOOKS) {
        printf("Inventory full. Can't add more books.\n");
        return;
    }

    int id;
    printf("Enter ISBN number: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    if (searchBook(ids, *total, id) != -1) {
        printf("Book with this ISBN already exists.\n");
        return;
    }

    while (getchar() != '\n');
    char name[NAME_LEN];
    printf("Enter Book Title: ");
    if (fgets(name, NAME_LEN, stdin) == NULL) {
        printf("Input error.\n");
        return;
    }

    int n = 0;
    while (name[n] != '\0') n++;
    if (n > 0 && name[n - 1] == '\n') name[n - 1] = '\0';

    float cost;
    printf("Enter Price: ");
    if (scanf("%f", &cost) != 1) {
        printf("Invalid price.\n");
        while (getchar() != '\n');
        return;
    }

    int qty;
    printf("Enter Quantity: ");
    if (scanf("%d", &qty) != 1) {
        printf("Invalid quantity.\n");
        while (getchar() != '\n');
        return;
    }

    int pos = *total;
    ids[pos] = id;
    for (int i = 0; i < NAME_LEN; i++) {
        names[pos][i] = name[i];
        if (name[i] == '\0') break;
    }
    costs[pos] = cost;
    stock[pos] = qty;
    (*total)++;

    printf("Book added successfully! Total books: %d\n", *total);
}
void sellBook(int ids[], char names[][NAME_LEN], float costs[], int stock[], int total) {
    if (total == 0) {
        printf("No books in inventory.\n");
        return;
    }

    int id;
    printf("Enter ISBN to sell: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    int index = searchBook(ids, total, id);
    if (index == -1) {
        printf("Book not found.\n");
        return;
    }

    int sold;
    printf("Enter copies sold: ");
    if (scanf("%d", &sold) != 1 || sold <= 0) {
        printf("Invalid number.\n");
        while (getchar() != '\n');
        return;
    }

    if (stock[index] < sold) {
        printf("Not enough stock. Only %d left.\n", stock[index]);
        return;
    }

    stock[index] -= sold;
    printf("Sold %d copies of '%s'. Remaining: %d\n", sold, names[index], stock[index]);
}
void showLowStock(int ids[], char names[][NAME_LEN], float costs[], int stock[], int total) {
    printf("\nLow Stock (less than 5):\n");
    printf("ISBN\tTitle\t\tPrice\tQuantity\n");
    int any = 0;

    for (int i = 0; i < total; i++) {
        if (stock[i] < 5) {
            any = 1;
            printf("%d\t%s\t\t%.2f\t%d\n", ids[i], names[i], costs[i], stock[i]);
        }
    }

    if (!any) {
        printf("All books have enough stock.\n");
    }
}
int main() {
    int ids[MAX_BOOKS];
    char names[MAX_BOOKS][NAME_LEN];
    float costs[MAX_BOOKS];
    int stock[MAX_BOOKS];
    int totalBooks = 0;
    int option;
    while (1) {
        printf("\n==== Book Inventory System ====\n");
        printf("1. Add Book\n");
        printf("2. Sell Book\n");
        printf("3. Low Stock Report\n");
        printf("4. Exit\n");
        printf("Choose option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }
        switch (option) {
            case 1:
                addBook(ids, names, costs, stock, &totalBooks);
                break;
            case 2:
                sellBook(ids, names, costs, stock, totalBooks);
                break;
            case 3:
                showLowStock(ids, names, costs, stock, totalBooks);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Please choose between 1-4.\n");
        }
    }
    return 0;
}

