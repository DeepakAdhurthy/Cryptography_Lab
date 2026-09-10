#include <stdio.h>
#include <string.h>
#include <ctype.h>

char m[5][5];
char key[100];

void createMatrix()
{
    int used[26] = {0};
    int i, k = 0;

    used['J' - 'A'] = 1;

    for(i = 0; key[i] != '\0'; i++)
    {
        key[i] = toupper(key[i]);

        if(key[i] >= 'A' && key[i] <= 'Z' &&
           !used[key[i] - 'A'])
        {
            m[k / 5][k % 5] = key[i];
            used[key[i] - 'A'] = 1;
            k++;
        }
    }

    for(i = 0; i < 26; i++)
    {
        if(!used[i])
        {
            m[k / 5][k % 5] = 'A' + i;
            k++;
        }
    }
}

void pos(char x, int *r, int *c)
{
    int i, j;

    if(x == 'J')
        x = 'I';

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            if(m[i][j] == x)
            {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

void cipher(char t[], int shift)
{
    int i, r1, c1, r2, c2;

    for(i = 0; t[i] != '\0'; i += 2)
    {
        pos(t[i], &r1, &c1);
        pos(t[i + 1], &r2, &c2);

        if(r1 == r2)
        {
            t[i] = m[r1][(c1 + shift + 5) % 5];
            t[i + 1] = m[r2][(c2 + shift + 5) % 5];
        }
        else if(c1 == c2)
        {
            t[i] = m[(r1 + shift + 5) % 5][c1];
            t[i + 1] = m[(r2 + shift + 5) % 5][c2];
        }
        else
        {
            t[i] = m[r1][c2];
            t[i + 1] = m[r2][c1];
        }
    }
}

int main()
{
    char text[100];
    int i, j, n;

    printf("Enter key: ");
    scanf("%s", key);

    createMatrix();

    printf("\nPlayfair Matrix:\n");

    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            printf("%c ", m[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter plaintext: ");
    scanf("%s", text);

    for(i = 0; text[i] != '\0'; i++)
    {
        text[i] = toupper(text[i]);

        if(text[i] == 'J')
            text[i] = 'I';
    }

    n = strlen(text);

    if(n % 2 != 0)
    {
        text[n] = 'X';
        text[n + 1] = '\0';
    }

    cipher(text, 1);
    printf("Ciphertext: %s\n", text);

    cipher(text, -1);
    printf("Decrypted text: %s\n", text);

    return 0;
}

