#include <stdio.h>

int main(){
    char nome[50];
    int idade, matricula;
    float altura;

    printf("Informe a sua matrícula:\n");
    scanf("%i",&matricula);
    printf("Informe o seu nome:\n");
    scanf("%s",&nome);
    printf("Informe a sua idade:\n");
    scanf("%i",&idade);
    printf("Informe a sua altura (em metros):\n");
    scanf("%f",&altura);

    printf("Dados do Aluno\n\nMatricula: %i\nNome: %s\nIdade: %i anos\nAltura: %.2fm",matricula,nome,idade,altura);

    return 0;
}