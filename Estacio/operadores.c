#include <stdio.h>

int main(){
    int num1,num2,num3,num4,num5,num6;
    int soma,subtr,multp,divis;
    
    //Inserir dados
    printf("Informe o número 1: ");
    scanf("%i",&num1);
    printf("Informe o número 2: ");
    scanf("%i",&num2);

    //Operadores Matematicos
    soma=num1+num2;
    subtr=num1-num2;
    multp=num1*num2;
    divis=num1/num2;

    printf("\nOperadores Matemáticos:");
    //Soma
    printf("\nSoma de %i e %i: %i",num1,num2,soma);

    //Subtração    
    printf("\nSubtração de %i e %i: %i",num1,num2,subtr);

    //Multiplicação    
    printf("\nMultiplicação de %i e %i: %i",num1,num2,multp);

    //Divisão    
    printf("\nDivisão de %i e %i: %i",num1,num2,divis);

    printf("\n\nOperadores de Atribuição:");
        printf("\nSimples (=): Número 1 = %i",num1);
        num1+=2;
        printf("\nNúmero 1 com Atribuição de Soma 2: %i",num1);
        num1-=2;
        printf("\nNúmero 1 com Atribuição de Subtração 2: %i",num1);
        num1*=2;
        printf("\nNúmero 1 com Atribuição de Multiplicação 2: %i",num1);
        num1/=2;
        printf("\nNúmero 1 com Atribuição de Divisão 2: %i",num1);
        printf("\nObs.: Identificado que se realizar dentro da mesma variável, o valor vai substindo conforme as linhas de código seguem.");
    
    printf("\n\nOperadores de Incremento:");
        printf("\nInforme o número 3: ");
        scanf("%i",&num3);
        num3++;
        printf("\nNúmero 3 com Incrimento: %i",num3);
        num4=++num3;
        printf("\nNúmero 3 e 4 com Pré-Incrimento: %i e %i",num3,num4);
        num4=num3++;
        printf("\nNúmero 3 e 4 com Pós-Incrimento: %i e %i",num3,num4);

    printf("\n\nOperadores de Decremento:");
        printf("\nInforme o número 5: ");
        scanf("%i",&num5);
        num5--;
        printf("\nNúmero 5 com Decremento: %i",num5);
        num6=--num5;
        printf("\nNúmero 5 e 6 com Pré-Decremento: %i e %i",num5,num6);
        num6=num5--;
        printf("\nNúmero 5 e 6 com Pós-Decremento: %i e %i",num5,num6);

    return 0;
}