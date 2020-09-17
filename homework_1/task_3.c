#include <stdio.h>

int main()
{
    char s1[100], s2[100];
    scanf("%s", &s1);
    scanf("%s", &s2);
    int i = 0, count = 0;
    while (*(s1 + i) != '\0') {
        if (*(s1 + i) == *(s2)) {
            int j = 1, flag = 1;
            while (*(s2 + j) != '\0') {
                if (*(s2 + j) != *(s1 + i + j)) {
                    flag = 0;
                    break;
                }
                j++;
            }
            if (flag == 1)
                count++;
        }
        i++;
    }
    printf("%d", count);
    return 0;
}