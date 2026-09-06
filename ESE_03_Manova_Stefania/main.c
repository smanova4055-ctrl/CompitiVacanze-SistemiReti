#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct
{
    char cognome[30];
    char nome[30];
    char sesso;
    char indirizzo[50];
    char telefono[20];
    int eta;
} Contatto;

void caricaFile(Contatto rubrica[], int* n);
void inserisci(Contatto rubrica[], int* n);
void salvaFile(Contatto rubrica[], int n);
int cerca(Contatto rubrica[], int n, char cognome[]);
void visualizza(Contatto rubrica[], int n);
void statistiche(Contatto rubrica[], int n);
void modifica(Contatto rubrica[], int n);
void creaFileFiltrati(Contatto rubrica[], int n);

int main()
{
    Contatto rubrica[MAX];
    int n = 0;
    int scelta;
    char cognome[30];
    int pos;

    caricaFile(rubrica, &n);

    do
    {
        printf("\n\n--- RUBRICA TELEFONICA ---");
        printf("\n0 - Esci");
        printf("\n1 - Inserisci nuovo elemento");
        printf("\n2 - Salva file rubrica");
        printf("\n3 - Cerca elemento");
        printf("\n4 - Visualizza tutto");
        printf("\n5 - Statistiche");
        printf("\n6 - Modifica elemento");
        printf("\n7 - Crea file filtrati");
        printf("\nScelta: ");

        scanf("%d", &scelta);

        switch(scelta)
        {
            case 0:
                printf("\nProgramma terminato.");
                break;

            case 1:
                inserisci(rubrica, &n);
                break;

            case 2:
                salvaFile(rubrica, n);
                printf("\nFile salvato.");
                break;

            case 3:
                printf("\nInserisci il cognome da cercare: ");
                scanf(" %29[^\n]", cognome);

                pos = cerca(rubrica, n, cognome);

                if(pos == -1)
                {
                    printf("\nContatto non trovato.");
                }
                else
                {
                    printf("\n%s %s %c %s %s %d",
                           rubrica[pos].cognome,
                           rubrica[pos].nome,
                           rubrica[pos].sesso,
                           rubrica[pos].indirizzo,
                           rubrica[pos].telefono,
                           rubrica[pos].eta);
                }
                break;

            case 4:
                visualizza(rubrica, n);
                break;

            case 5:
                statistiche(rubrica, n);
                break;

            case 6:
                modifica(rubrica, n);
                salvaFile(rubrica, n);
                break;

            case 7:
                creaFileFiltrati(rubrica, n);
                break;

            default:
                printf("\nScelta non valida.");
        }

    } while(scelta != 0);

    return 0;
}

void caricaFile(Contatto rubrica[], int* n)
{
    FILE* fp;

    fp = fopen("rubrica.txt", "r");

    if(fp == NULL)
    {
        printf("File rubrica.txt non trovato.\n");
        return;
    }

    while(*n < MAX &&
          fscanf(fp, " %29[^;];%29[^;];%c;%49[^;];%19[^;];%d",
                 rubrica[*n].cognome,
                 rubrica[*n].nome,
                 &rubrica[*n].sesso,
                 rubrica[*n].indirizzo,
                 rubrica[*n].telefono,
                 &rubrica[*n].eta) == 6)
    {
        (*n)++;
    }

    fclose(fp);
}

void inserisci(Contatto rubrica[], int* n)
{
    Contatto nuovo;
    int pos;

    if(*n >= MAX)
    {
        printf("\nRubrica piena.");
        return;
    }

    printf("\nCognome: ");
    scanf(" %29[^\n]", nuovo.cognome);

    printf("Nome: ");
    scanf(" %29[^\n]", nuovo.nome);

    printf("Sesso M/F: ");
    scanf(" %c", &nuovo.sesso);

    printf("Indirizzo: ");
    scanf(" %49[^\n]", nuovo.indirizzo);

    printf("Telefono: ");
    scanf(" %19s", nuovo.telefono);

    printf("Eta: ");
    scanf("%d", &nuovo.eta);

    pos = 0;

    while(pos < *n && strcmp(rubrica[pos].cognome, nuovo.cognome) < 0)
    {
        pos++;
    }

    for(int i = *n; i > pos; i--)
    {
        rubrica[i] = rubrica[i - 1];
    }

    rubrica[pos] = nuovo;
    (*n)++;

    printf("\nContatto inserito.");
}

void salvaFile(Contatto rubrica[], int n)
{
    FILE* fp;

    fp = fopen("rubrica.txt", "w");

    if(fp == NULL)
    {
        printf("\nErrore apertura file.");
        return;
    }

    for(int i = 0; i < n; i++)
    {
        fprintf(fp, "%s;%s;%c;%s;%s;%d\n",
                rubrica[i].cognome,
                rubrica[i].nome,
                rubrica[i].sesso,
                rubrica[i].indirizzo,
                rubrica[i].telefono,
                rubrica[i].eta);
    }

    fclose(fp);
}

int cerca(Contatto rubrica[], int n, char cognome[])
{
    for(int i = 0; i < n; i++)
    {
        if(strcmp(rubrica[i].cognome, cognome) == 0)
        {
            return i;
        }
    }

    return -1;
}

void visualizza(Contatto rubrica[], int n)
{
    if(n == 0)
    {
        printf("\nRubrica vuota.");
        return;
    }

    for(int i = 0; i < n; i++)
    {
        printf("\n%d) %s %s - %c - %s - %s - %d",
               i + 1,
               rubrica[i].cognome,
               rubrica[i].nome,
               rubrica[i].sesso,
               rubrica[i].indirizzo,
               rubrica[i].telefono,
               rubrica[i].eta);
    }
}

void statistiche(Contatto rubrica[], int n)
{
    int sommaM = 0;
    int sommaF = 0;
    int contaM = 0;
    int contaF = 0;

    for(int i = 0; i < n; i++)
    {
        if(rubrica[i].sesso == 'M')
        {
            sommaM += rubrica[i].eta;
            contaM++;
        }
        else if(rubrica[i].sesso == 'F')
        {
            sommaF += rubrica[i].eta;
            contaF++;
        }
    }

    if(contaM > 0)
    {
        printf("\nEta media maschi: %.2f", (float)sommaM / contaM);
    }
    else
    {
        printf("\nNessun maschio presente.");
    }

    if(contaF > 0)
    {
        printf("\nEta media femmine: %.2f", (float)sommaF / contaF);
    }
    else
    {
        printf("\nNessuna femmina presente.");
    }
}

void modifica(Contatto rubrica[], int n)
{
    char cognome[30];
    int pos;

    printf("\nCognome del contatto da modificare: ");
    scanf(" %29[^\n]", cognome);

    pos = cerca(rubrica, n, cognome);

    if(pos == -1)
    {
        printf("\nContatto non trovato.");
        return;
    }

    printf("Nuovo cognome: ");
    scanf(" %29[^\n]", rubrica[pos].cognome);

    printf("Nuovo nome: ");
    scanf(" %29[^\n]", rubrica[pos].nome);

    printf("Nuovo sesso M/F: ");
    scanf(" %c", &rubrica[pos].sesso);

    printf("Nuovo indirizzo: ");
    scanf(" %49[^\n]", rubrica[pos].indirizzo);

    printf("Nuovo telefono: ");
    scanf(" %19s", rubrica[pos].telefono);

    printf("Nuova eta: ");
    scanf("%d", &rubrica[pos].eta);

    printf("\nContatto modificato.");
}

void creaFileFiltrati(Contatto rubrica[], int n)
{
    FILE* maggiorenni;
    FILE* maschi;
    FILE* femmine;

    maggiorenni = fopen("Maggiorenni.txt", "w");
    maschi = fopen("Maschi.txt", "w");
    femmine = fopen("Femmine.txt", "w");

    if(maggiorenni == NULL || maschi == NULL || femmine == NULL)
    {
        printf("\nErrore nella creazione dei file.");
        return;
    }

    for(int i = 0; i < n; i++)
    {
        if(rubrica[i].eta >= 18)
        {
            fprintf(maggiorenni, "%s;%s;%c;%s;%s;%d\n",
                    rubrica[i].cognome,
                    rubrica[i].nome,
                    rubrica[i].sesso,
                    rubrica[i].indirizzo,
                    rubrica[i].telefono,
                    rubrica[i].eta);
        }

        if(rubrica[i].sesso == 'M')
        {
            fprintf(maschi, "%s;%s;%c;%s;%s;%d\n",
                    rubrica[i].cognome,
                    rubrica[i].nome,
                    rubrica[i].sesso,
                    rubrica[i].indirizzo,
                    rubrica[i].telefono,
                    rubrica[i].eta);
        }

        if(rubrica[i].sesso == 'F')
        {
            fprintf(femmine, "%s;%s;%c;%s;%s;%d\n",
                    rubrica[i].cognome,
                    rubrica[i].nome,
                    rubrica[i].sesso,
                    rubrica[i].indirizzo,
                    rubrica[i].telefono,
                    rubrica[i].eta);
        }
    }

    fclose(maggiorenni);
    fclose(maschi);
    fclose(femmine);

    printf("\nFile filtrati creati.");
}
