#include <stdio.h>
#define MAX 100
void push(int s[], int *t, int n) {
    if (*t == n - 1) {
        printf("Overflow\n");
        return;
    }
    int v;
    printf("Enter value: ");
    scanf("%d", &v);
    s[++(*t)] = v;
    printf("Pushed.\n");
}
void pop(int s[], int *t) {
    if (*t == -1) {
        printf("Underflow\n");
        return;
    }
    printf("Popped: %d\n", s[(*t)--]);
}
void peek(int s[], int t) {
    if (t == -1) {
        printf("Empty\n");
        return;
    }
    printf("Top: %d\n", s[t]);
}
void show(int s[], int t) {
    if (t == -1) {
        printf("Empty\n");
        return;
    }
    printf("Stack:\n");
    for (int i = t; i >= 0; i--)
        printf("%d\n", s[i]);
}
int main() {
    int s[MAX], t = -1, c;
    while (1) {
        printf("\n1.Push\n2.Pop\n3.Peek\n4.Show\n5.Exit\nChoice: ");
        scanf("%d", &c);
        switch (c) {
            case 1: push(s, &t, MAX); break;
            case 2: pop(s, &t); break;
            case 3: peek(s, t); break;
            case 4: show(s, t); break;
            case 5: return 0;
            default: printf("Invalid\n");
        }
    }
}

