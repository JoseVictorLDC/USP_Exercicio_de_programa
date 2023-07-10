/***************************************************************/
/**                                                           **/
/**   José Victor Lyra de Castro            14747340          **/
/**   Exercício-Programa 1-b                                  **/
/**   Professor: Guilherme Mota                               **/
/**   Turma: 03                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
int main () { 
/*Variáveis gerais*/
int opcao, a, b, c, decimal; 
a = 0; 
b = 1; 
c = 0; 
/*Variáveis da opção 0*/
int x, n; 
n = -1; 
/*Variáveis da opção 1*/
int i, decimalprimeiro; 
/*Variáveis da opção 2*/
int numerofib, algarismo; 

/*Leitura do opção desejada*/
scanf ("%d", &opcao); 

/*Converte os números da sequência para a representação fibonacciana*/
if (opcao == 0) { 
    scanf ("%d", &decimal); 
    while (decimal != 0) { 
        a = 0; 
        b = 1; 
        c = 0; 
        /*Definição do maior número de Fibonacci que consegue fazer a subtração do DECIMAL dado e sobrar um resto positivo ou igual a zero, 
        salvando sua posição X na sequência de Fibonacci*/
        for (x = -1; c <= decimal; x++) { 
            c = b + a; 
            a = b; 
            b = c; 
        } 
        decimal = decimal - a; 
        printf ("1"); 
        /*Looping que ira testar e imprimir os demais números de Fibonacci que são menores que o número encontrado anteriormente*/
        while (n != x-2) { 
            a = 0; 
            b = 1; 
            c = 0; 
            for (n = -1; n < x - 1; n++) { 
                c = b + a; 
                a = b; 
                b = c; 
            } 
            if (a > decimal) { 
                printf ("0"); 
            } 
            /*Condicional que irá variar o valor do DECIMAL dado até que ele atinja zero*/
            if (a <= decimal) { 
                printf ("1"); 
                decimal = decimal - a; 
            } 
        /*Redefinição de variaveis responsáveis pela diminuiçaõ da ordem de repetição do segundo looping FOR acima*/
        n = -1; 
        x = x - 1; 
        } 
        scanf ("%d", &decimal); 
        printf ("\n"); 
    } 
} 

/*Converte os números da sequência em somas de números de Fibonacci distintos, sem dois números de Fibonacci consecutivos*/
if (opcao == 1) { 
    scanf ("%d", &decimal); 
    decimalprimeiro = decimal; 
while (decimal != 0) { 
    while (decimal != 0) { 
        a = 0; 
        b = 1; 
        c = 0; 
        /*Looping também responsável por adquirir o valor i que o número menor que o DECIMAL dado está na sequência de Fibonacci*/
        for (i = -1; c <= decimal; i++) { 
            c = a + b; 
            a = b; 
            b = c; 
        } 
        /*Condicional para o maior número de Fibonacci que consegue subtrair-se do DECIMAL dado e fazer com que sobre resto positivo ou igual a zero*/
        if (decimal == decimalprimeiro) { 
            decimal = decimal - a; 
            printf ("F_%d (%d) ", i, a); 
        } 
        /*Condicional responsável pelo "+" na frente da sequência*/
        else { 
            decimal = decimal - a; 
            printf ("+ F_%d (%d) ", i, a); 
        } 
    } 
    scanf ("%d", &decimal); 
    decimalprimeiro = decimal; 
    printf ("\n"); 
} 
} 

/*Converte os números da sequência, que estão em representação fibonacciana, para o inteiro correspondente*/
if (opcao == 2) { 
    scanf ("%d", &numerofib); 
    while (numerofib != 0) { 
        a = 0; 
        b = 1; 
        c = 0; 
        decimal = 0; 
        /*Looping que adquire e define cada algarismo e multiplica pelo respectivo número de Fibonacci*/
        while (numerofib != 0) { 
            c = b + a; 
            a = b; 
            b = c; 
            algarismo = numerofib % 10; 
            numerofib = numerofib/10; 
            decimal = decimal + algarismo*c; 
        } 
        printf ("%d \n", decimal); 
        scanf ("%d", &numerofib); 
    } 
} 
return 0; 
} 