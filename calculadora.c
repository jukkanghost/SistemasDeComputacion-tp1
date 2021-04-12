#include "cdecl.h"
#include <stdio.h>
#include <stdlib.h>

int PRE_CDECL asm_main(void) POST_CDECL;
int PRE_CDECL sumaDecimal(int, int) POST_CDECL;
int PRE_CDECL restaDecimal(int, int) POST_CDECL;
int PRE_CDECL sumaBinaria(char, char, char, char, char, char, char, char) POST_CDECL;
int PRE_CDECL restaBinaria(char, char, char, char, char, char, char, char) POST_CDECL;

void decabin (int n) {
    if (n) {
        decabin(n / 2);
        printf("%d", n % 2);
    }
}

int main(int argc, char *argv[])
{

    int a, b, resultado;
    resultado = 0;
    int esDecimal = atoi(argv[1]);
    char binario1[4];
    char binario2[4];
    

    if(esDecimal){
        a = atoi(argv[2]);
        b = atoi(argv[4]);

        if ((char)argv[3][0] == '+')
        {
            resultado = sumaDecimal(a, b);
        }
        if ((char)argv[3][0] == '-')
        {
            resultado = restaDecimal(a, b);
        }
        printf("%i\n", resultado);
    }
    else{
        for(int j=0; j<4; j++){
            binario1[j] = (char)argv[2][j];
            binario2[j] = (char)argv[4][j];
        }

        if ((char)argv[3][0] == '+')
        {
            resultado = sumaBinaria(binario1[0], binario1[1], binario1[2], binario1[3], binario2[0], binario2[1], binario2[2], binario2[3]);
        }

        if ((char)argv[3][0] == '-')
        {
            resultado = restaBinaria(binario1[0], binario1[1], binario1[2], binario1[3], binario2[0], binario2[1], binario2[2], binario2[3]);            
        }
        decabin(resultado);
        printf("\n");
    }

    return 0;
}