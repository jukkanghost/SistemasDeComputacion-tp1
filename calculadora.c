#include "cdecl.h"
#include <stdio.h>
#include <stdlib.h>

int PRE_CDECL asm_main(void) POST_CDECL;
int PRE_CDECL sumaDecimal(int, int) POST_CDECL;
int PRE_CDECL restaDecimal(int, int) POST_CDECL;
int PRE_CDECL sumaBinaria(int, int) POST_CDECL;
int PRE_CDECL restaBinaria(int, int) POST_CDECL;

int main(int argc, char *argv[])
{

    int a, b, resultado;
    resultado = 0;
    int esDecimal = 1;

    /*if(esDecimal){
        if ((char)argv[2][0] == '+')
        {
            int y = atoi(argv[1]);
            int x = atoi(argv[3]);
            resultado = sumaDecimal(x, y);
        }

        if ((char)argv[2][0] == '-')
        {
            int y = atoi(argv[1]);
            int x = atoi(argv[3]);
            resultado = restaDecimal(x, y);
        }
    }*/
    /*else{
        if ((char)argv[2][0] == '+')
        {
            int y = atoi(argv[1]);
            int x = atoi(argv[3]);
            resultado = sumaBinaria(x, y);
        }

        if ((char)argv[2][0] == '-')
        {
            int y = atoi(argv[1]);
            int x = atoi(argv[3]);
            resultado = restaBinaria(x, y);
        }
    }*/

    int y = atoi(argv[1]);
    int x = atoi(argv[3]);
    resultado = sumaBinaria(x, y);

    printf("%i\n", resultado);

    return 0;
}