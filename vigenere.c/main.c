//
//  main.c
//  vigenere.c
//
//  Created by Jennifer Nguyen on 2/23/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCHAR 512

// Encrypts the plaintext using the key
void vigenere(char *plaintxt, char *keytxt)
{
    int i, j, k;
    char *encoded = (char*) malloc(MAXCHAR * sizeof(char));
    
    k = 0;
    for (i = 0; i < MAXCHAR; i++)
    {
        if (keytxt[k] == '\0')
            k = 0;
        
        encoded[i] = (((plaintxt[i]  - 'a') + (keytxt[k] - 'a')) % 26) + 'a';
        k++;
    }
    printf("\nCiphertext:\n");
    for (j = 0; j < MAXCHAR; j++)
    {
        if (j % 80 == 0)
            printf("\n");
        printf("%c", encoded[j]);
    }
    printf("\n");
}
// Prints formatted arguments
void arguments(char *plaintxt, char *keytxt)
{
    int i, j;
    
    printf("\nVigenere Key:\n");
    for (j = 0; j < MAXCHAR; j++)
    {
        if (j % 80 == 0)
            printf("\n");
        printf("%c", keytxt[j]);
        if (keytxt[j] == '\0')
            break;
    }
    printf("\n\n");
    
    printf("\nPlaintext:\n");
    for (i = 0; i < MAXCHAR; i++)
    {
        if (i % 80 == 0)
            printf("\n");
        printf("%c", plaintxt[i]);
    }
    printf("\n\n");
}
// Make all letters lower case
void lower(char *txt)
{
    int i;
    for (i = 0; i < MAXCHAR; i++)
    {
        txt[i] = tolower(txt[i]);
    }
    
}

int main(int argc, char** argv)
{
    int i, j , k , p, t;
    
    FILE * ifp;
    FILE * ifk;
    
    char *plaintxt = (char*) malloc(MAXCHAR * sizeof(char));
    char *keytxt = (char*) malloc(MAXCHAR * sizeof(char));
    char hold;

    ifk = fopen(argv[1], "r");
    ifp = fopen(argv[2], "r");
    
    // Scan key file; when the file ends breaks; p is so there are never spaces
    p = 0;
    for (k = 0; k < MAXCHAR; k++)
     {
         fscanf(ifk, "%c", &hold);
    
         
         if (hold == '\0')
         {
             break;
         }
         else if (isalpha(hold) != 0)
         {
             keytxt[p] = hold;
             p++;
         }
         
     }

    // Pre-pad the plain text
    for (t = 0; t < MAXCHAR; t++)
    {
        plaintxt[t] = 'x';
    }
    
    // Scan plain text file only allows letters; j is so plain text never has spaces
    j = 0;
    for (i = 0; i < MAXCHAR; i++)
    {
        
        fscanf(ifp, "%c", &hold);

        if (hold == '\0')
        {
            plaintxt[j] = 'x';
            j++;
        }
        else if (isalpha(hold) != 0)
        {
            plaintxt[j] = hold;
            j++;
        }
        else
        {
            hold = '\0';
            continue;
        }
        
        
    }
    lower(plaintxt);
    lower(keytxt);
    arguments(plaintxt, keytxt);
    vigenere(plaintxt, keytxt);
    free(plaintxt);
    free(keytxt);
    return 0;
}
