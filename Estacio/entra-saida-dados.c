/*#include <stdio.h>
 
int main() {
    int idade = 25;
    float altura = 1.75;
    double saldoBancario = 12345.67;
    char inicial = 'A';
    char nome[20] = "Bruno";
 
    printf("Idade: %d anos\n", idade);
    printf("Altura: %.2f metros\n", altura);
    printf("Saldo Bancário: %.2f reais\n", saldoBancario);
    printf("Inicial do Nome: %c\n", inicial);
    printf("Nome: %s\n", nome);
 
    return 0;
}*/

#include <stdio.h>

int main(){
    char nome[10];
    int idade;
    float altura;
    float peso;
    double imc;

    printf("Digite seu nome: ");
    scanf("%s",&nome);
    printf("Digite sua idade: ");
    scanf("%i",&idade);
    printf("Digite sua altura em metros: ");
    scanf("%f",&altura);
    printf("Digite seu pelo em kg: ");
    scanf("%f",&peso);

    imc=peso/(altura*altura);

    printf("Nome: %s\nIdade: %i\nAltura: %.2f\nPeso: %.2f\nIMC: %.5f",nome,idade,altura,peso,imc);

    return 0;
}