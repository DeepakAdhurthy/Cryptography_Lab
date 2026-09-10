#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod26(int x) {
    return (x % 26 + 26) % 26;
}

int modInverse(int a) {
    int i;
    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}

int main() {
    char plaintext[200], encrypted[200], decrypted[200];
    int key[2][2], inverse[2][2];
    int det, invDet;
    int i, len;

    printf("Enter the message: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter 2x2 key matrix:\n");
    scanf("%d %d", &key[0][0], &key[0][1]);
    scanf("%d %d", &key[1][0], &key[1][1]);

    len = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i]))
            plaintext[len++] = toupper(plaintext[i]);
    }
    plaintext[len] = '\0';

    if (len % 2 != 0) {
        plaintext[len++] = 'X';
        plaintext[len] = '\0';
    }

    for (i = 0; i < len; i += 2) {
        int x = plaintext[i] - 'A';
        int y = plaintext[i + 1] - 'A';

        encrypted[i] = mod26(key[0][0] * x + key[0][1] * y) + 'A';
        encrypted[i + 1] = mod26(key[1][0] * x + key[1][1] * y) + 'A';
    }

    encrypted[len] = '\0';

    printf("\nEncrypted Message: %s\n", encrypted);

    det = mod26(key[0][0] * key[1][1] - key[0][1] * key[1][0]);
    invDet = modInverse(det);

    if (invDet == -1) {
        printf("Decryption is not possible with this key.\n");
        return 0;
    }

    inverse[0][0] = mod26(key[1][1] * invDet);
    inverse[0][1] = mod26(-key[0][1] * invDet);
    inverse[1][0] = mod26(-key[1][0] * invDet);
    inverse[1][1] = mod26(key[0][0] * invDet);

    for (i = 0; i < len; i += 2) {
        int x = encrypted[i] - 'A';
        int y = encrypted[i + 1] - 'A';

        decrypted[i] = mod26(inverse[0][0] * x + inverse[0][1] * y) + 'A';
        decrypted[i + 1] = mod26(inverse[1][0] * x + inverse[1][1] * y) + 'A';
    }

    decrypted[len] = '\0';

    printf("Decrypted Message: %s\n", decrypted);

    return 0;
}

