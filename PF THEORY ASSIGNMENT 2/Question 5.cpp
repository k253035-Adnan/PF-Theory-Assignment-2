#include <stdio.h>
void flip(char *x) {
    *x ^= (1 << 1);
    *x ^= (1 << 4);
}
void rev(char s[]) {
    int n = 0;
    while (s[n] != '\0') n++;
    for (int i = 0; i < n / 2; i++) {
        char t = s[i];
        s[i] = s[n - 1 - i];
        s[n - 1 - i] = t;
    }
}
void encode(char s[]) {
    rev(s);
    for (int i = 0; s[i] != '\0'; i++) flip(&s[i]);
}
void decode(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) flip(&s[i]);
    rev(s);
}
int main() {
    char txt[200];
    int ch;
    while (1) {
        printf("\nTCS Message App\n");
        printf("1.Encode\n2.Decode\n3.Exit\nChoice: ");
        scanf("%d", &ch);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (ch == 1) {
            printf("Enter text: ");
            fgets(txt, 200, stdin);
            int i = 0;
            while (txt[i] != '\0' && txt[i] != '\n') i++;
            txt[i] = '\0';
            encode(txt);
            printf("Encoded: %s\n", txt);
        } else if (ch == 2) {
            printf("Enter text: ");
            fgets(txt, 200, stdin);
            int i = 0;
            while (txt[i] != '\0' && txt[i] != '\n') i++;
            txt[i] = '\0';
            decode(txt);
            printf("Decoded: %s\n", txt);
        } else if (ch == 3) {
            printf("Bye.\n");
            return 0;
        } else {
            printf("Invalid\n");
        }
    }
}

