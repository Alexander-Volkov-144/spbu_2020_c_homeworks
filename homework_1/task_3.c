#include <stdio.h>

const int MAX_LENGTH = 2048;

int main()
{
    char s1[MAX_LENGTH], s2[MAX_LENGTH];
    printf("enter s1\n");
    scanf("%s", &s1);
    printf("enter s2\n");
    scanf("%s", &s2);
    int i = 0, count = 0;
    for (int i = 0; s1[i] != '\0'; ++i) {
        if (s1[i] == s2[0]) {
            int j = 1;
            for (; (s1[i + j] == s2[j]) && (s2[j] != '\0'); ++j); // второе условие нужно, чтобы не выйти за строку
            if (s2[j] == '\0')
                ++count;
        }
    }
    printf("%d", count);
    return 0;
}