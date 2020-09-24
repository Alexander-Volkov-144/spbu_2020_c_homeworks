#include <stdio.h>

int main()
{
    char s1[2048], s2[2048];
    scanf("%s", &s1);
    scanf("%s", &s2);
    int i = 0, count = 0;
    while (s1[i] != '\0') {
        if (s1[i] == s2[0]) {
            int j = 1;
            while (s2[j] != '\0') {
                if (s2[j] != s1[i + j]) {
                    break;
                }
                j++;
            }
            if (s2[j] == '\0')
                count++;
        }
        i++;
    }
    printf("%d", count);
    return 0;
}