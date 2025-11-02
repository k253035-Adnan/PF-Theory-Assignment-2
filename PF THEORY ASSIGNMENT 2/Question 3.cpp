#include <stdio.h>
#define R 3
#define C 3
void editCell(int map[R][C]) {
    int x, y, bit, val;
    printf("Enter row and col: ");
    scanf("%d%d", &x, &y);
    if (x < 0 || x >= R || y < 0 || y >= C) {
        printf("Invalid input.\n");
        return;
    }
    printf("Flag (0=Power,1=Overload,2=Service): ");
    scanf("%d", &bit);
    if (bit < 0 || bit > 2) {
        printf("Wrong flag.\n");
        return;
    }
    printf("Set(1) or Clear(0): ");
    scanf("%d", &val);
    if (val == 1)
        map[x][y] |= (1 << bit);
    else
        map[x][y] &= ~(1 << bit);
    printf("Updated.\n");
}
void checkCell(int map[R][C]) {
    int x, y;
    printf("Enter row and col to check: ");
    scanf("%d%d", &x, &y);
    if (x < 0 || x >= R || y < 0 || y >= C) {
        printf("Invalid input.\n");
        return;
    }
    int s = map[x][y];
    printf("Cell [%d][%d]:\n", x, y);
    printf("Power: %s\n", (s & 1) ? "ON" : "OFF");
    printf("Overload: %s\n", (s & 2) ? "YES" : "NO");
    printf("Service: %s\n", (s & 4) ? "YES" : "NO");
}
void scanAll(int map[R][C]) {
    int over = 0, fix = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (map[i][j] & 2) over++;
            if (map[i][j] & 4) fix++;
        }
    }
    printf("Overloaded: %d\n", over);
    printf("Need Service: %d\n", fix);
}
int main() {
    int map[R][C] = {0};
    int ch;
    while (1) {
        printf("\nPower Grid Menu\n");
        printf("1. Edit Sector\n");
        printf("2. Check Sector\n");
        printf("3. Run Check\n");
        printf("4. Exit\n");
        printf("Choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: editCell(map); break;
            case 2: checkCell(map); break;
            case 3: scanAll(map); break;
            case 4: return 0;
            default: printf("Wrong choice.\n");
        }
    }
    return 0;
}

