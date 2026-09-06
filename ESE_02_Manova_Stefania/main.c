#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generaPassword(int Length);

int main()
{
    int lunghezza;
    char* password;

    srand(time(NULL));

    printf("Inserisci la lunghezza della password: ");
    scanf("%d", &lunghezza);

    password = generaPassword(lunghezza);

    printf("\nPassword generata: %s\n", password);

    free(password);

    return 0;
}

char* generaPassword(int Length)
{
    char* password;

    password = (char*)malloc((Length + 1) * sizeof(char));

    for(int i = 0; i < Length; i++)
    {
        password[i] = rand() % ('}' - '0' + 1) + '0';
    }

    password[Length] = '\0';

    return password;
}
