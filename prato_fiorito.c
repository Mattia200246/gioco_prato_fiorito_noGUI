/* SIMULAZIONE DEL GIOCO "PRATO FIORITO" 

    Dimensione del prato: 20x20
    Numero di bombe posizionate casualmente a inizio gioco: 10
    
    Il giocatore deve inserire le coordinate di una cella del prato e il programma deve:
    - verificare se la cella contiene una bomba
    - se la cella contiene una bomba, il gioco termina e il giocatore perde
    - se la cella non contiene una bomba, il programma deve contare il numero di bombe nelle celle adiacenti e stampare il numero di bombe nelle celle adiacenti
    - il giocatore deve continuare a inserire le coordinate di una cella del prato fino a quando non trova una cella con una bomba o fino a quando non ha trovato tutte le celle senza una bomba
    - se il giocatore ha trovato tutte le celle senza una bomba, il gioco termina e il giocatore vince

    Il programma deve stampare il prato a video dopo ogni mossa del giocatore e deve stampare il numero di bombe nelle celle adiacenti a quella scelta dal giocatore
    Il programma prima di terminare deve stampare il numero di mosse effettuate dal giocatore

    Si usano le seguenti funzioni:
    - void stampa_prato(char prato[20][20]) -> stampa il prato a video
    - void inizializza_prato(char prato[20][20]) -> inizializza il prato con il carattere ' '
    - void posiziona_bombe(char prato[20][20], int n_bombe) -> posiziona n_bombe bombe casualmente nel prato
    - int conta_bombe(char prato[20][20], int x, int y) -> conta il numero di bombe nelle celle adiacenti a quella in posizione (x,y)
    - int gioca(char prato[20][20], int n_bombe) -> funzione principale del gioco

    Si usano le seguenti variabili globali:
    - int mosse
    - int vittoria

    costanti:
    - #define DIM 20 -> dimensione del prato
    - #define BOMBA '*' -> carattere che rappresenta una bomba
    - #define VUOTO ' ' -> carattere che rappresenta una cella vuota

    Si usa una "struct" per memorizzare le coordinate di una cella del prato
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM 20
#define BOMBA '*'
#define VUOTO ' '

int mosse = 0;
int vittoria = 0;

void stampa_prato(char prato[20][20])
{
    //le bombe non devono essere mostrate a video
    int i, j;

    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            if (prato[i][j] == BOMBA)
                printf("%c ", VUOTO);
            else
                printf("%c ", prato[i][j]);
        }
        printf("\n");
    }
}

void inizializza_prato(char prato[20][20])
{
    int i, j;
    for (i = 0; i < DIM; i++)
    {
        for (j = 0; j < DIM; j++)
        {
            prato[i][j] = VUOTO;
        }
    }
}

void posiziona_bombe(char prato[20][20], int n_bombe)
{
    int i, x, y;
    srand(time(NULL));
    for (i = 0; i < n_bombe; i++)
    {
        x = rand() % DIM;
        y = rand() % DIM;
        prato[x][y] = BOMBA;
    }
}

int conta_bombe(char prato[20][20], int x, int y)
{
    int i, j, n_bombe = 0;
    for (i = x - 1; i <= x + 1; i++)
    {
        for (j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < DIM && j >= 0 && j < DIM)
            {
                if (prato[i][j] == BOMBA)
                {
                    n_bombe++;
                }
            }
        }
    }
    return n_bombe;
}

int gioca(char prato[20][20], int n_bombe)
{
    int x, y, n_bombe_adiacenti;
    while (vittoria < (DIM * DIM) - n_bombe)
    {
        printf("Inserisci le coordinate della cella: ");
        scanf("%d %d", &x, &y);
        if (prato[x][y] == BOMBA)
        {
            printf("Hai perso!\n");

            return 0;
        }
        else
        {
            n_bombe_adiacenti = conta_bombe(prato, x, y);
            prato[x][y] = n_bombe_adiacenti + '0';
            vittoria++;
            mosse++;
            stampa_prato(prato);
        }
    }
    printf("Hai vinto!\n"); 
    return 1;
}

int main()
{
    char prato[20][20];
    int n_bombe = 10;
    inizializza_prato(prato);
    posiziona_bombe(prato, n_bombe);
    stampa_prato(prato);
    gioca(prato, n_bombe);
    printf("Numero di mosse: %d", mosse);
    return 0;
}


