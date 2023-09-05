/***************************************************************/
/**                                                           **/
/**   José Victor Lyra de Castro            14747340          **/
/**   Exercício-Programa 2                                    **/
/**   Professor: Guilherme Mota                               **/
/**   Turma: 03                                               **/
/**                                                           **/
/***************************************************************/

#include <stdio.h> 
#include <math.h> 
/*Função para ler os dados*/ 
void read_data(double *x0, double *x1, double *x2, double *x3, 
double *v0, double *v1, double *v2, double *v3, 
double *m0, double *m1, double *m2, double *m3,
double *T_max); 
/*Função para determinar o tempo até a próxima colisão entre dois blocos*/ 
double t(double x, double xx, double v, double vv); 
/*Calcula o módulo de um número*/ 
double modulo(double modulo); 
/*Função para determinar o mínimo entre três valores*/ 
double min(double a, double b, double c, int *i); 
/*Função para executar um movimento uniforme, calculando deslocamento*/ 
double adv(double *x, double v, double t); 
/*Função para execução de uma colisão, redefinindo as velocidades dos blocos envolvidos*/ 
void resolve(double *v, double *vv, double m, double mm); 
/*Função para imprimir as informações*/ 
void print_data(long c1, long c2, long c3,
double x0, double x1, double x2, double x3,
double v0, double v1, double v2, double v3,
double d0, double d1, double d2, double d3); 

int main () { 
double x0, x1, x2, x3, v0, v1, v2, v3, m0, m1, m2, m3, T_max; 
double d0, d1, d2, d3, tCHOQUE, tSOMADO, tSOMADOsalvo, tCHOQUEsalvo; 
long c1, c2, c3; 
int qualchoque; 

read_data(&x0, &x1, &x2, &x3, &v0, &v1, &v2, &v3, &m0, &m1, &m2, &m3, &T_max); 
tSOMADO = 0; 
tSOMADOsalvo = 0; 
c1 = 0; 
c2 = 0; 
c3 = 0; 
d0 = 0; 
d1 = 0; 
d2 = 0; 
d3 = 0; 
/*Definição do primeiro tempo de choque e primeiro tempo somado*/ 
tCHOQUE = min(t(x0, x1, v0, v1), t(x1, x2, v1, v2), t(x2, x3, v2, v3), &qualchoque);
tSOMADO += tCHOQUE; 

/*Looping para calcular os choques até atingir o tempo limite*/ 
while (tSOMADO <= T_max && tCHOQUE != HUGE_VAL) { 
    /*Realização dos deslocamentos em MRU*/ 
    d0 += modulo(adv(&x0, v0, tCHOQUE)); 
    d1 += modulo(adv(&x1, v1, tCHOQUE)); 
    d2 += modulo(adv(&x2, v2, tCHOQUE)); 
    d3 += modulo(adv(&x3, v3, tCHOQUE)); 

    /*Definição de qual será o tipo de choque e redefinição das velocidades dos blocos envolvidos*/ 
    if (qualchoque == 1) { 
        c1 += 1; 
        resolve(&v0, &v1, m0, m1); 
    }
    if (qualchoque == 2) { 
        c2 += 1; 
        resolve(&v1, &v2, m1, m2); 
    }
    if (qualchoque == 3) {  
        c3 += 1; 
        resolve(&v2, &v3, m2, m3); 
    } 
    /*Salvando o tempo somado anterior, definindo o próximo tempo de choque e somando o tempo do choque ao tempo da simulação*/ 
    tSOMADOsalvo = tSOMADO; 
    tCHOQUE = min(t(x0, x1, v0, v1), t(x1, x2, v1, v2), t(x2, x3, v2, v3), &qualchoque);   
    tSOMADO += tCHOQUE; 
} 
/*Calculando o tempo de choque e o deslocamento de cada bloco entre o momento limite da simulação e o ultimo tempo salvo antes de superar o tempo limite*/ 
tCHOQUEsalvo = tCHOQUE; 
tCHOQUE = (T_max - tSOMADOsalvo); 
d0 += modulo(adv(&x0, v0, tCHOQUE)); 
d1 += modulo(adv(&x1, v1, tCHOQUE)); 
d2 += modulo(adv(&x2, v2, tCHOQUE)); 
d3 += modulo(adv(&x3, v3, tCHOQUE)); 

/*Imprimindo os dados finais e analisando se tem ou se não tem choques depois do tempo limite*/ 
print_data(c1, c2, c3, x0, x1, x2, x3, v0, v1, v2, v3, d0, d1, d2, d3); 
if (tCHOQUEsalvo != HUGE_VAL) 
    printf ("Ha colisoes remanescentes\n"); 
else 
    printf ("Nao ha mais colisoes\n"); 
return 0; 
} 

void read_data(double *x0, double *x1, double *x2, double *x3, 
double *v0, double *v1, double *v2, double *v3, 
double *m0, double *m1, double *m2, double *m3,
double *T_max) { 

scanf("%lf %lf %lf", &*x0, &*v0, &*m0); 
scanf("%lf %lf %lf", &*x1, &*v1, &*m1); 
scanf("%lf %lf %lf", &*x2, &*v2, &*m2); 
scanf("%lf %lf %lf", &*x3, &*v3, &*m3); 
scanf("%lf", &*T_max); 
} 

double t(double x, double xx, double v, double vv) { 
double deltaT, L = 0.1; 

/*Definição do tempo de choque como infinito para os bloco que nunca irão se chocar*/ 
if (v <= vv) { 
    deltaT = HUGE_VAL; 
    return deltaT; 
} 
/*Definindo o tempo de choque para os blocos que irão se chocar*/ 
deltaT = (xx - x - L)/(v - vv); 
return deltaT; 
} 

double modulo(double modulo) { 
if (modulo < 0) 
    modulo = -(modulo); 
return modulo; 
} 

double min(double a, double b, double c, int *i) { 
double m; 
m = HUGE_VAL; 

/*Calculo do valor mínimo*/ 
if (a <= b && a <= c) 
    m = a; 
if (b <= a && b <= c) 
    m = b; 
if (c <= a && c <= b) 
    m = c; 
/*Definindo qual o choque ocorrerá primeiro*/ 
if (m == a) 
    *i = 1; 
if (m == b && m != a) 
    *i = 2; 
if (m != a && m != b) 
    *i = 3; 

return m; 
} 

double adv(double *x, double v, double t) { 
double deslocamento; 

deslocamento = v*t; 
*x += deslocamento; 
return deslocamento; 
} 

void resolve(double *v, double *vv, double m, double mm) { 
double A; 

A = (2*((*v) * m + (*vv) * mm)) / (m + mm); 
*v = A - *v; 
*vv = A - *vv; 
} 

void print_data(long c1, long c2, long c3,
double x0, double x1, double x2, double x3,
double v0, double v1, double v2, double v3,
double d0, double d1, double d2, double d3) { 
long cTOTAL, cESQUERDA; 
cTOTAL = c1 + c2 + c3; 
cESQUERDA = c2 + c3; 

printf ("Numero de colisoes por bloco: %ld %ld %ld\n", c1, c2, c3); 
printf ("Numero total de colisoes: %ld\n", cTOTAL); 
printf ("Colisoes dos dois blocos a direita: %ld\n", cESQUERDA); 
printf ("x0 = %9.6f  v0 = %9.6f  d0 = %9.6f\n", x0, v0, d0); 
printf ("x1 = %9.6f  v1 = %9.6f  d1 = %9.6f\n", x1, v1, d1); 
printf ("x2 = %9.6f  v2 = %9.6f  d2 = %9.6f\n", x2, v2, d2); 
printf ("x3 = %9.6f  v3 = %9.6f  d3 = %9.6f\n", x3, v3, d3); 
} 