/*
Objetivo da Atividade:
    Criar duas cartas do Super Trunfo, sem utilizar while/for/if/else, apenas com o que foi aprendido.
    Pela solicitacao da atividade, sem reducao de casa decimal no float tambem.

Dos dados:
    Estado: Escolher da letra A ao H (char)
    Codigo da Carta: Escolher do 01 ao 04 (string - char[5])
    Cidade: Informar o nome da cidade (string - cha[50])
    Populacao: Quantidade de pessoas da cidade (int)
    Pontos Turisticos: Quantidade de pontos turisticos da cidade (int)
    Area: Informar a area, em km quadrados, da cidade (float)
    PIB: produto interno bruto da cidade (float)

Apos inserir os valores, passar no final de forma legivel os dados de cada carta, entitulando de
Carta 1 e Carta 2.
    Exemplo:
        Carta 1:

        Estado: A
        Código: A01
        Nome da Cidade: São Paulo
        População: 12325000
        Área: 1521.11 km²
        PIB: 699.28 bilhões de reais
        Número de Pontos Turísticos: 50
*/

#include <stdio.h>

int main(){
    char estado1,estado2,cod1[5],cod2[5],cidade1[50],cidade2[50];
    int pop1,pop2,pturis1,pturis2;
    float area1,area2,pib1,pib2;

    //Dados das Cartas 1 e 2
    printf(">>Dados da Carta 1<<\n");
    printf("Informe o Estado (A - H): ");
    scanf(" %c",&estado1);
    printf("Informe o Código da Carta (01 - 04): ");
    scanf("%s",&cod1);
    printf("Informe o nome da Cidade: ");
    scanf("%s",&cidade1);
    printf("Informe a Quantidade Populacional da cidade: ");
    scanf("%i",&pop1);
    printf("Informe a Área da cidade (km²): ");
    scanf("%f",&area1);
    printf("Informe o PIB (Produto Interno Bruto), em bilhões, da cidade: ");
    scanf("%f",&pib1);
    printf("Informe a quantidade de Pontos Turisticos da cidade: ");
    scanf("%i",&pturis1);

    printf("\n>>Dados da Carta 2<<\n");
    printf("Informe o Estado (A - H): ");
    scanf(" %c",&estado2);
    printf("Informe o Código da Carta (01 - 04): ");
    scanf("%s",&cod2);
    printf("Informe o nome da Cidade: ");
    scanf("%s",&cidade2);
    printf("Informe a Quantidade Populacional da cidade: ");
    scanf("%i",&pop2);
    printf("Informe a Área da cidade (km²): ");
    scanf("%f",&area2);
    printf("Informe o PIB (Produto Interno Bruto), em bilhões, da cidade: ");
    scanf("%f",&pib2);
    printf("Informe a quantidade de Pontos Turisticos da cidade: ");
    scanf("%i",&pturis2);

    //Impressão das Cartas 1 e 2
    printf("\nCarta 1:\nEstado: %c\nCódigo: %c%s\nNome da Cidade: %s\nPopulação: %i\nÁrea: %f km²\nPIB: %f bilhões de reais\nNúmero de Pontos Turisticos: %i\n\n", estado1,estado1,cod1,cidade1,pop1,area1,pib1,pturis1);
    printf("Carta 2:\nEstado: %c\nCódigo: %c%s\nNome da Cidade: %s\nPopulação: %i\nÁrea: %f km²\nPIB: %f bilhões de reais\nNúmero de Pontos Turisticos: %i\n", estado2,estado2,cod2,cidade2,pop2,area2,pib2,pturis2);

    return 0;
}