/***************************************************************/ 
/**                                                           **/ 
/**   José Victor Lyra de Castro     Número USP: 14747340     **/ 
/**   Exercício-Programa 3                                    **/ 
/**   Professor: Guilherme Mota                               **/ 
/**   Turma: 03                                               **/ 
/**                                                           **/ 
/***************************************************************/ 

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#define MAX_PIXELS 1000000 
#define rand2166() (rand2166f(-1)) 
#define srand2166(seed) (rand2166f((seed))) 
#define AA 16807 
#define MM 2147483647 

void output_image(int col, int row, int v_max, int image[]); 
void read_image(int *col, int *row, int *v_max, int image[]); 
void encode(int col, int row, int v_max, int image[], int key); 
void decode(int col, int row, int v_max, int image[], int key, int decoded[]); 
void decode_in_loco(int col, int row, int v_max, int image[], int key); 
void decode_brute_force(int col, int row, int v_max, int image[], int max_key); 
double entropy(int v_max, int N, int image[]); 
double calculador_de_quantidades (long i, int N, int image[]); 
int rand2166f(int seed); 

int main(int argc, char *argv[]) { 
int col, row, v_max, image[MAX_PIXELS]; 
int key = atoi(argv[2]); 
int max_key = atoi(argv[2]); 
int opcao = atoi(argv[1]); 

read_image(&col, &row, &v_max, image); 

if (opcao == 0) { 
    encode(col, row, v_max, image, key); 
} 
else if (opcao == 1) { 
    decode_in_loco(col, row, v_max, image, key); 
} 
else { 
    decode_brute_force(col, row, v_max, image, max_key); 
} 

output_image(col, row, v_max, image); 

return 0; 
} 

/*IMPLEMENTAÇÕES DAS FUNCÕES*/ 
/*Impressão da imagem*/ 
void output_image(int col, int row, int v_max, int image[]) { 
int i, j, rowPASSADO; 
rowPASSADO = 0; 

/*Imprimindo propriedades do arquivo*/ 
printf("P2 \n"); 
printf("%d %d \n%d \n", col, row, v_max); 

for(i = 0; i < row; i++) { 
    for(j = 0; j < col; j++) { 
        /*Variando o número do vetor proporcional a uma matriz*/ 
        printf("%d ", image[rowPASSADO*col + j]); 
        rowPASSADO = i; 
    } 
    /*Pulando de linha no final de cada linha*/ 
    printf ("\n"); 
} 
} 

/*Ler a imagem de entrada*/ 
void read_image(int *col, int *row, int *v_max, int image[]) { 
char P, PP; 
int k; 

scanf("%c %c", &P, &PP); 
scanf("%d %d %d", &*col, &*row, &*v_max); 

for(k = 0; k <= (*col)*(*row); k++) { 
    scanf("%d", &image[k]); 
} 
} 

/*Codificar a imagem no mesmo vetor*/ 
void encode(int col, int row, int v_max, int image[], int key) { 
int k, N; 
N = col*row; 

srand2166(key); 
for(k = 0; k < N; k++) { 
    image[k] = (image[k] + (rand2166() % (v_max + 1))) % (v_max + 1); 
} 
} 

/*Descodificar a imagem em outro vetor*/ 
void decode(int col, int row, int v_max, int image[], int key, int decoded[]) { 
int k, N; 
N = col*row; 

srand2166(key); 
for(k = 0; k < N; k++) { 
    decoded[k] = (image[k] - (rand2166()%(v_max + 1)) + (v_max + 1)) % (v_max + 1); 
} 
} 

/*Descodificar a imagem no mesmo vetor*/ 
void decode_in_loco(int col, int row, int v_max, int image[], int key) { 

decode(col, row, v_max, image, key, image); 
} 

/*Descodificar sem saber a senha e salvando num mesmo vetor*/ 
void decode_brute_force(int col, int row, int v_max, int image[], int max_key) { 
int keyTESTANDO, imageTESTANDO[MAX_PIXELS], keyCERTA, N; 
double entropiaTESTANDO, entropiaSALVO; 
N = col*row; 
keyCERTA = 0; 
entropiaSALVO = entropy(v_max, N, image); 

/*Variando as multiplas chaves possíveis até max_key e fazendo a entropia de cada uma delas*/ 
for(keyTESTANDO = 0; keyTESTANDO <= max_key; keyTESTANDO++) { 
    decode(col, row, v_max, image, keyTESTANDO, imageTESTANDO); 
    entropiaTESTANDO = entropy(v_max, N, imageTESTANDO); 

    /*Comparando cada entropia com o menor valor até o momento até achar a de menor valor de todos, que é a imagem "real"*/ 
    if(entropiaTESTANDO < entropiaSALVO) { 
        entropiaSALVO = entropiaTESTANDO; 
        keyCERTA = keyTESTANDO; 
    } 
} 
decode_in_loco(col, row, v_max, image, keyCERTA); 
} 

/*Calculando a entropia de uma imagem*/ 
double entropy(int v_max, int N, int image[]) { 
long k; 
double Pi, entropia; 
entropia = 0; 

for(k = 0; k <= v_max; k++) { 
    /*Utilizando-se de uma função que traz a quantidade k no vetor correspondente a imagem que possui N pixels*/ 
    Pi = calculador_de_quantidades(k, N, image) / N; 

    if (Pi != 0) { 
    entropia += Pi*log(1/Pi); 
    } 
} 
return entropia; 
} 

/*Calculando a quantidade de elementos i no vetor imagem*/ 
double calculador_de_quantidades (long i, int N, int image[]) { 
int k, iCONTADO; 
iCONTADO = 0; 

for(k = 0; k < N; k++) { 
    if(image[k] == i) { 
        iCONTADO++; 
    } 
} 
return iCONTADO; 
} 

int rand2166f(int seed) { 
static long r; 
if (seed >= 0) { 
r = seed; 
return 0; 
} 
r = (r * AA) % MM; 
return r; 
} 