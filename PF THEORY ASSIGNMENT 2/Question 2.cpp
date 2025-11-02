#include <stdio.h>
#include <string.h>
#define ITEMS 4
#define CODE_LEN 4
#define NAME_SIZE 50
#define ID_SIZE 20
#define CART_SIZE 100

int sameCode(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return a[i] == b[i];
}
void getBuyer(char name[], char id[]) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Enter name: ");
    fgets(name, NAME_SIZE, stdin);
    int i = 0;
    while (name[i] != '\0') i++;
    if (i > 0 && name[i-1] == '\n') name[i-1] = '\0';
    printf("Enter CNIC: ");
    fgets(id, ID_SIZE, stdin);
    i = 0;
    while (id[i] != '\0') i++;
    if (i > 0 && id[i-1] == '\n') id[i-1] = '\0';
}
void showStock(char code[][CODE_LEN], int qty[], int rate[]) {
    printf("\nCode\tQty\tPrice\n");
    for (int i = 0; i < ITEMS; i++) {
        printf("%s\t%d\t%d\n", code[i], qty[i], rate[i]);
    }
}
int findCode(char code[][CODE_LEN], char input[]) {
    for (int i = 0; i < ITEMS; i++) {
        if (sameCode(code[i], input)) return i;
    }
    return -1;
}
void addItem(char code[][CODE_LEN], int stock[], int rate[], char cartCode[][CODE_LEN], int cartQty[], int *cartNum) {
    char input[CODE_LEN];
    int q;
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Enter product code: ");
    fgets(input, CODE_LEN, stdin);
    int i = 0;
    while (input[i] != '\0' && input[i] != '\n') i++;
    input[i] = '\0';
    int idx = findCode(code, input);
    if (idx == -1) {
        printf("Wrong code.\n");
        return;
    }
    printf("Enter quantity: ");
    if (scanf("%d", &q) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }
    if (q <= 0 || stock[idx] < q) {
        printf("Not enough stock.\n");
        return;
    }
    int found = -1;
    for (int j = 0; j < *cartNum; j++) {
        if (sameCode(cartCode[j], input)) {
            found = j;
            break;
        }
    }
    if (found == -1) {
        if (*cartNum >= CART_SIZE) return;
        strcpy(cartCode[*cartNum], input);
        cartQty[*cartNum] = q;
        (*cartNum)++;
    } else {
        cartQty[found] += q;
    }
    stock[idx] -= q;
    printf("Added %d of %s\n", q, input);
}
double subtotal(char code[][CODE_LEN], int rate[], char cartCode[][CODE_LEN], int cartQty[], int cartNum) {
    double total = 0;
    for (int i = 0; i < cartNum; i++) {
        int idx = findCode(code, cartCode[i]);
        if (idx != -1) total += (double)rate[idx] * cartQty[i];
    }
    return total;
}
void bill(char code[][CODE_LEN], int rate[], char cartCode[][CODE_LEN], int cartQty[], int cartNum) {
    if (cartNum == 0) {
        printf("Cart empty.\n");
        return;
    }
    printf("\nCode\tQty\tRate\tTotal\n");
    for (int i = 0; i < cartNum; i++) {
        int idx = findCode(code, cartCode[i]);
        if (idx != -1) printf("%s\t%d\t%d\t%d\n", cartCode[i], cartQty[i], rate[idx], rate[idx] * cartQty[i]);
    }
    double total = subtotal(code, rate, cartCode, cartQty, cartNum);
    printf("Subtotal: %.2f\n", total);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    char promo[20];
    printf("Promo code (press Enter to skip): ");
    fgets(promo, 20, stdin);
    int i = 0;
    while (promo[i] != '\0' && promo[i] != '\n') i++;
    promo[i] = '\0';
    double dis = 0;
    if (strcmp(promo, "Eid2025") == 0) dis = 0.25 * total;
    printf("Discount: %.2f\n", dis);
    printf("Total: %.2f\n", total - dis);
}
void invoice(char name[], char id[], char code[][CODE_LEN], int rate[], char cartCode[][CODE_LEN], int cartQty[], int cartNum) {
    printf("\nName: %s\nCNIC: %s\n", name, id);
    bill(code, rate, cartCode, cartQty, cartNum);
}
int main() {
    char codeList[ITEMS][CODE_LEN];
    strcpy(codeList[0], "001");
    strcpy(codeList[1], "002");
    strcpy(codeList[2], "003");
    strcpy(codeList[3], "004");
    int stock[ITEMS] = {50, 10, 20, 8};
    int rate[ITEMS] = {100, 200, 300, 150};
    char name[NAME_SIZE] = "";
    char id[ID_SIZE] = "";
    char cartCode[CART_SIZE][CODE_LEN];
    int cartQty[CART_SIZE];
    int cartNum = 0;
    int ch, run = 1;
    while (run) {
        printf("\nShop Menu\n1. Buyer Info\n2. Show Stock\n3. Add Item\n4. Bill\n5. Invoice\n6. Exit\nChoice: ");
        if (scanf("%d", &ch) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        switch (ch) {
            case 1: getBuyer(name, id); break;
            case 2: showStock(codeList, stock, rate); break;
            case 3: addItem(codeList, stock, rate, cartCode, cartQty, &cartNum); break;
            case 4: bill(codeList, rate, cartCode, cartQty, cartNum); break;
            case 5: invoice(name, id, codeList, rate, cartCode, cartQty, cartNum); break;
            case 6: run = 0; break;
            default: break;
        }
    }
    return 0;
}

