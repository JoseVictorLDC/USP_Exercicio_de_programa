/***************************************************************/
/**                                                           **/
/**   José Victor Lyra de Castro            14747340          **/
/**   Exercício-Programa 1-a                                  **/
/**   Professor: Guilherme Mota                               **/
/**   Turma: 03                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>
int main () 
{
    int numero, algarismo, potencia, decimal; 
    scanf ("%d", &numero); 
    /*Definindo o loop e suas variáveis necessárias*/
    while (numero != 0)  
    { 
    potencia = 1; 
    decimal = 0; 
        /*Definindo cada algarismo/resto, fazendo sua respectiva multiplicação pela potência 
        de três e encontrando o número dado agora em formato decimal*/
        while (numero != 0) 
        { 
            algarismo = numero % 10; 
            decimal = decimal + (algarismo*potencia); 
            potencia = potencia*3; 
            numero = numero/10; 
        } 
    /*Imprimindo o resultado e reiniciando o loop*/
    printf ("%d \n", decimal); 
    scanf ("%d", &numero); 
    } 
return 0; 
} 