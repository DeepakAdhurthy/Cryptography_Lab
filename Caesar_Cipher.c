#include <stdio.h>
#include <ctype.h>

int main() {
    char text[200], encrypted[200], decrypted[200];
    int shift, i;

    printf("Enter the message: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the shift value: ");
    scanf("%d", &shift);

    shift = shift % 26;

    for (i = 0; text[i] != '\0'; i++) {
        char ch = text[i];

        if (isupper(ch))
            encrypted[i] = (ch - 'A' + shift) % 26 + 'A';
        else if (islower(ch))
            encrypted[i] = (ch - 'a' + shift) % 26 + 'a';
        else
            encrypted[i] = ch;
    }

    encrypted[i] = '\0';

    printf("\nEncrypted Message: %s", encrypted);

    for (i = 0; encrypted[i] != '\0'; i++) {
        char ch = encrypted[i];

        if (isupper(ch))
            decrypted[i] = (ch - 'A' - shift + 26) % 26 + 'A';
        else if (islower(ch))
            decrypted[i] = (ch - 'a' - shift + 26) % 26 + 'a';
        else
            decrypted[i] = ch;
    }

    decrypted[i] = '\0';

    printf("Decrypted Message: %s", decrypted);

    return 0;
}

