/*
REDT08N25
Link: https://www.onlinegdb.com/

Sintaxe: <tipo> <nome_variavel>

#int - var numer inteira
----------------------------------------
#float - var numer real (casa decimal)
----------------------------------------
#char - caractere
	## Variaveis nao podem ser iguais a palavras reservadas de uso do sistema.
		### Ex.: "int", "main", "PARA", "algoritmo", "print", etc.
	## Inicia sempre com letra ou underline ("_");
	## Sem espacamamento;
	## Nome Unico.
----------------------------------------	
#"%d"/"%i" - Valor em digito inteiro;
----------------------------------------
#"%f" - Valor em digito real;
----------------------------------------
#"%c" - Valor em caractere;
----------------------------------------
#include <locale.h> - Utilizado para colocar caractere
	## utilize ',setlocale(LC_ALL,"")' dentro do printf para valida��o de
	caractere especial.
----------------------------------------
#include <iostream>
using namespace std;
cout.precision(2);
"%.2f"
	##Utilizado para reduzir as casas decimais.
----------------------------------------
#Operadores b�sicos:
	+: Soma;
	-: Subtracao;
	*: Multiplicacao
	/: Divisao
	%: Modulo
	==: Igualdade
	!=: Diferente
	>: Maior
	<: Menor
	>=: Maior ou Igual
	<=: Menor ou Igual
	&&: E
	||: Ou	
========================================
>> Exemplo 1:
#include <stdio.h>
int main() {
int numero1;
char turno;
float media;
}

>> Exemplo 2:
#include <stdio.h>
#include <stdlib.h>
int main() {
	int a,b,c;
	a=1;
	b=2;
	c=a+b;
	printf("%d",c);
	return 0;
}

>> Exemplo 3:
#include <stdio.h>
 int main() {
	printf("Hello, World!");
}

>> Exemplo 4:
#include <stdio.h>
int main() {
	int a,b;
	float c;
	a=1;
	b=2;
	c=a/b;
	printf("%d",c);
}

>> Exercicio 1:
#include <stdio.h>
int main() {
	int a,b,c,soma_valor;
	a=5;
	b=3;
	c=10;
	soma_valor=a+b+c;
	printf("%d",soma_valor);
}

>> Exercicio 2:
#include <stdio.h>
#include <stdlib.h>
int main() {
	int a,b,c,soma_valor;
	a=5;
	b=3;
	c=10;
	soma_valor=a+b+c;
	printf("Valor = ");
	printf("%i",soma_valor);
	return 0;
}

>> Exercicio 3:
#include <stdio.h>
#include <stdlib.h>
int main() {
	float a,b,c,soma_valor;
	a=5;
	b=3;
	c=10;
	soma_valor=(a+b)/c;
	printf("Valor = ");
	printf("%f",soma_valor);
	return 0;
}

>> Exercicio 4:
#include <stdio.h>
#include <stdlib.h>
int main() {
	int a,b,c,soma_valor;
	a=5;
	b=3;
	c=10;
	soma_valor=a+b+c;
	printf("a = ");
	printf("%i",a);
	printf("| b = ");
	printf("%i",b);
	printf("| c = ");
	printf("%i",c);
	printf("| Valor = a + b + c");
	printf("| Valor = ");
	printf("%i",soma_valor);
	return 0;
}

>> Exercicio 5:
#include <stdio.h>
int main() {
	int a,b,c,soma_valor;
	a=5;
	b=3;
	c=10;
	soma_valor=a+b+c;
	printf("Valor = %d",soma_valor);
}

>> Exercicio 6:
#include <stdio.h>
#include <stdlib.h>
int main() {
	int a,b,c,soma_valor;
	a=5;
	b=3;
	c=10;
	soma_valor=a+b+c;
	printf("a = %d | b = %d | c = %d | Valor = a + b + c = %d",a,b,c,soma_valor);
}

>> Exercicio 7:
Criar um programa que cria variaveis nota1, nota2, nota3, e media do tipo real.
Atribuir os valores (nota1= 5.3|nota2= 7.4|nota3=8.2|media=(nota1+nota2+nota3)/3.
Imprimir o valor da media.

> V.1:
#include <stdio.h>
int main() {
	float nota1,nota2,nota3,media;
	nota1=5.3;
	nota2=7.4;
	nota3=8.2;
	media=(nota1+nota2+nota3)/3;
	printf("Media = %f",media);
}

> V.2:
#include <stdio.h>
int main() {
	float nota1,nota2,nota3,media;
	nota1=5.3;
	nota2=7.4;
	nota3=8.2;
	media=(nota1+nota2+nota3)/3;
	printf("Media = (Nota 1 + Nota 2 + Nota 3) / 3 = %f pts",media);
}

> V.3
#include <stdio.h>
int main() {
	float nota1,nota2,nota3,media;
	nota1=5.3;
	nota2=7.4;
	nota3=8.2;
	media=(nota1+nota2+nota3)/3;
	printf("\n********** Exercicio 7 **********\n\n ");
	printf("Media = %f",media);
}

>V.4
#include <stdio.h>
#include <locale.h>
int main() {
	float nota1,nota2,nota3,media;
	nota1=5.3;
	nota2=7.4;
	nota3=8.2;
	media=(nota1+nota2+nota3)/3;
	printf("********** Exercicio 7 **********\n\nCriar um programa que cria vari�veis 'nota1', 'nota2', 'nota3', e 'media' do tipo real.\n\n",setlocale(LC_ALL,""));
	printf("Atribuir os valores:\nNota 1 = 5.3 | Nota 2 = 7.4 | Nota 3 = 8.2.\n\n");
	printf("Imprimir o valor da m�dia:\nM�dia = (Nota 1 + Nota 2 + Nota 3) / 3\n\n==============================\n\nM�dia = %f pts\n\n",media);
	printf("******************************");
}

Exemplo 5: M�dia por Input de vari�vel num�rica
#include <stdio.h>
#include <locale.h>

int main (void) {
   float a, b;
   printf ("Informe a: ",setlocale(LC_ALL,""));
   scanf ("%f",&a);
   printf ("Informe b: ");
   scanf ("%f",&b);
   float media;
   media = (a + b)/2;
   printf ("A m�dia de %f e %f � %f", a, b, media);
   return 0;
}

>> Exercicio 8:
Criar um programa que calcule a area do trapezio.
Atribuir os valores (basemaior= 10|basemenor= 2|altura=5|area_trapezio=((basemaior+basemenor)/2)*altura.
Imprimir o valor Area do Trapezio.

V1:
#include <stdio.h>
#include <locale.h>
int main() {
	printf("********** Exercicio 8 **********\n\nCriar um programa que calcule a �rea do Trap�zio.\n\n",setlocale(LC_ALL,""));
	printf("Inserir por Input os valores das bases e altura:\nbasemaior,basemenor,altura\n\n");
	printf("Imprimir o valor da �rea do Trap�zio:\n area_trapezio = ( basemaior + basemenor) / 2 * altura");
	printf("Imprimir o valor rea do Trapezio\n\n==============================\n\n");
	float basemaior,basemenor,altura,area_trapezio;
   	printf ("Informe Base Maior: ");
   	scanf ("%f",&basemaior);
   	printf ("Informe Base Menor: ");
   	scanf ("%f",&basemenor);
   	printf ("Informe Altura: ");
   	scanf ("%f",&altura);
   	
   	area_trapezio = (basemaior + basemenor)/2*altura;
   	printf ("A �rea do Trap�zio �: %f", area_trapezio);

	printf("\n\n******************************");
	return 0;
}

V2:
#include <stdio.h>
int main() {
	float basemaior,basemenor,altura,area_trapezio;
   	printf ("Informe Base Maior: ");
   	scanf ("%f",&basemaior);
   	printf ("Informe Base Menor: ");
   	scanf ("%f",&basemenor);
   	printf ("Informe Altura: ");
   	scanf ("%f",&altura);
   	
   	area_trapezio = (basemaior + basemenor)/2*altura;
   	printf ("A Area do Trapezio: %f", area_trapezio);
	return 0;
}

V3:
#include <stdio.h>
#include <locale.h>
#include <iostream>
using namespace std;

int main() {
	setlocale(LC_ALL,"");
	printf("********** Exercicio 8 **********\n\nCriar um programa que calcule a �rea do Trap�zio.\n\n");
	printf("Inserir por Input os valores das bases e altura:\nbasemaior,basemenor,altura\n\n");
	printf("Imprimir o valor da �rea do Trap�zio:\n area_trapezio = ( basemaior + basemenor) / 2 * altura\n\n");
	printf("Imprimir o valor real do Trap�zio\n\n==============================\n\n");
	float basemaior,basemenor,altura,area_trapezio;
   	printf ("Informe Base Maior: ");
   	scanf ("%f",&basemaior);
   	printf ("Informe Base Menor: ");
   	scanf ("%f",&basemenor);
   	printf ("Informe Altura: ");
   	scanf ("%f",&altura);
   	
   	area_trapezio = (basemaior + basemenor)/2*altura;
    cout.precision(2);

   	printf ("A �rea do Trap�zio �: %.2f", area_trapezio);
	printf("\n\n******************************");
	return 0;
}

V4 Explicativo
#include <stdio.h>
	//Biblioteca para criacao das variaveis padrao de numeros
	
#include <locale.h>
	//Biblioteca para liberacao de acentuacao
	
#include <iostream>
	//Biblioteca para limitacao de caractere em float e double
	
using namespace std;
	//Utilizado para limitacao de caractere em float e double

int main() {
	setlocale(LC_ALL,"");
		//Liberacao de acentuacao
		
	printf("********** Exercicio 8 **********\n\nCriar um programa que calcule a �rea do Trap�zio.\n\n");
	printf("Inserir por Input os valores das bases e altura:\nbasemaior,basemenor,altura\n\n");
	printf("Imprimir o valor da �rea do Trap�zio:\n area_trapezio = ( basemaior + basemenor) / 2 * altura\n\n");
	printf("Imprimir o valor real do Trap�zio\n\n==============================\n\n");
		//Texto da solicita��o do exercicio
		
	float basemaior,basemenor,altura,area_trapezio;
		// declaracao de tipo de variavel
		
   	printf ("Informe Base Maior: ");
   		// Texto mostrado para na tela
   		
   	scanf ("%f",&basemaior);
   		// Usado para salvar o valor do texto anterior no printf
   	
   	printf ("Informe Base Menor: ");
   	scanf ("%f",&basemenor);
   	printf ("Informe Altura: ");
   	scanf ("%f",&altura);
   	
   	area_trapezio = (basemaior + basemenor)/2*altura;
   		// Calculo feito dentro do sistema com base nos valores informados
   		
    cout.precision(2);
    	//Limitacao de casas decimais com base no #include <iostream> e using namespace std

   	printf ("A �rea do Trap�zio �: %.2f", area_trapezio);
   		//Visualizacao na tela do valor apos o calculo, com limitacao de 2 casas decimais ".2"
	printf("\n\n******************************");
	return 0;
		//For�ar finaliza��o do programa
}

Exemplo 6:

#include <stdio.h>
#include <locale.h>
int main()
{
	setlocale(LC_ALL,"");
	int n;
	printf("Informe um n�mero: ");
	scanf("%d",&n);
	printf("N�mero: %d",n);
}

Exemplo 7 (limitacao de casa decimal)
#include <stdio.h>
#include <locale.h>
int main()
{
	setlocale(LC_ALL,"");
	float salario;
	printf("Digite o sal�rio: ");
	scanf("%f",&salario);
	printf("O sal�rio informado foi: %.2f",salario);
	return 0;
}

Exerc�cio 1:
#include <stdio.h>
#include <locale.h>
int main()
{
int num1,num2;
int soma;
setlocale(LC_ALL,"");
printf("Informe o n�mero 1: ");
scanf("%d",&num1);
printf("Informe o n�mero 2: ");
scanf("%d",&num2);
soma=num1+num2;

printf("Soma do N�mero 1 + N�mero 2: %d",soma);
	return 0;
}

Exercicio 2:
#include <stdio.h>
#include <locale.h>
int main()
{
int num1,num2;
int soma;
setlocale(LC_ALL,"");
printf("Informe o n�mero 1: ");
scanf("%d",&num1);
printf("Informe o n�mero 2: ");
scanf("%d",&num2);
soma=num1+num2;

printf("N�mero 1 (%d) + N�mero 2 (%d): %d",num1,num2,soma);
	return 0;
}

Exercicio 3
#include <stdio.h>
#include <locale.h>
int main()
{
float p1,p2,p3;
float media;
setlocale(LC_ALL,"");
printf("Informe a Nota 1: ");
scanf("%f",&p1);
printf("Informe o Nota 2: ");
scanf("%f",&p2);
printf("Informe o Nota 3: ");
scanf("%f",&p3);
media=(p1+p2+p3)/3;

printf("--------------------\nNota 1: %.2f pts\nNota 2: %.2f pts\nNota 3: %.2f pts\n\nM�dia: %.2f pts",p1,p2,p3,media);
	return 0;
}

Exercicio 4:
#include <stdio.h>
#include <locale.h>
int main()
{
float p1,p2,p3;
float media;
setlocale(LC_ALL,"");
printf("Informe a Nota 1: ");
scanf("%f",&p1);
printf("Informe a Nota 2: ");
scanf("%f",&p2);
printf("Informe a Nota 3: ");
scanf("%f",&p3);
media=(p1+p2+p3)/3;

printf("\nM�dia = %.2f",media);
	return 0;
}

Exercicio 5:
#include <stdio.h>
#include <locale.h>
int main()
{
float n1,n2;
float media_p;
setlocale(LC_ALL,"");
printf("Informe a Nota 1: ");
scanf("%f",&n1);
printf("Informe a Nota 2: ");
scanf("%f",&n2);

media_p=(2*n1+3*n2)/5;

printf("\nM�dia Ponderada = %.2f",media_p);
	return 0;
}

Exercicio 6:
#include <stdio.h>
#include <locale.h>
int main()
{
float salario,desconto_inss;

setlocale(LC_ALL,"");
printf("Informe Sal�rio: ");
scanf("%f",&salario);

desconto_inss=salario*15/100;

printf("\nDesconto de INSS de um sal�rio de R$ %.2f = R$ %.2f",salario,desconto_inss);
	return 0;
}

Exercicio 7:
#include <stdio.h>
#include <locale.h>
int main()
{
float a,b,c,d,f;

setlocale(LC_ALL,"");
printf("Informe a: ");
scanf("%f",&a);
printf("Informe b: ");
scanf("%f",&b);
printf("Informe c: ");
scanf("%f",&c);
printf("Informe d: ");
scanf("%f",&d);

f=(a+b+c+d)*3;

printf("\n%.0f � o resultado do processamento.",f);
	return 0;
}

Exercicios 09/08/2024
#include <stdio.h>
#include <locale.h>
int main()
{
float peso,altura,imc,n1,n2,n3,media,valor_compra,prestacao,hora_trab,salario,b_maior,b_menor,altura_trap,area_trap,tC,tF,a,b,c,delta;

setlocale(LC_ALL,"");
printf("********** ATIVIDADE 2 **********\n");
printf("- Crie as vari�veis do tipo real: peso, altura e imc\n");
printf("- Fa�a a leitura da vari�vel nome, peso e altura.\n");
printf("- Atribua a vari�vel\n");
printf("	imc = peso/(altura*altura)\n");
printf("- Imprima da seguinte forma:\n");
printf("'Seu �ndice de massa corporal �: valor do imc'\n");
printf("\nInforme peso: ");
scanf("%f",&peso);
printf("Informe altura: ");
scanf("%f",&altura);
imc=peso/(altura*altura);
printf("\nSeu �ndice de massa corporal �: %.2f\n",imc);
printf("******************************\n\n");

printf("********** ATIVIDADE 3 **********\n");
printf("Escrever um algoritmo que leia as notas das tr�s provas de um aluno no semestre. No final informar a sua m�dia (aritm�tica).\n");
printf("\nInforme nota 1: ");
scanf("%f",&n1);
printf("Informe nota 2: ");
scanf("%f",&n2);
printf("Informe nota 3: ");
scanf("%f",&n3);
media=(n1+n2+n3)/3;
printf("\nM�dia Aritm�tica: %.2f\n",media);
printf("******************************\n\n");

printf("********** ATIVIDADE 4 **********\n");
printf("A Loja Mam�o com A��car est� vendendo seus produtos em 5 (cinco) presta��es sem juros. Fa�a um algoritmo que receba um valor de uma compra e mostre o valor das presta��es.\n");
printf("\nInforme Valor da compra: ");
scanf("%f",&valor_compra);
prestacao=valor_compra/5;
printf("\nPresta��es: 5x de R$ %.2f\n",prestacao);
printf("******************************\n\n");
printf("********** ATIVIDADE 5 **********\n");
printf("Elabore um algoritmo que leia as horas trabalhadas e calcule seu sal�rio, sabendo que recebe R$ 63,00 por hora trabalhada. O algoritmo dever� imprimir no formato: Sal�rio:\n");
printf("R$: 23.\n");
printf("\nInforme as horas trabalhadas: ");
scanf("%f",&hora_trab);
salario=63.0*hora_trab;
printf("\nSal�rio: R$ %.0f\n",salario);
printf("******************************\n\n");
printf("********** ATIVIDADE 6 **********\n");
printf("Escrever um algoritmo que leia a base maior, base menor e altura e calcule a �rea do trap�zio.\n");
printf("�rea do trap�zio = (basemaior + basemenor)*altura/2\n");
printf("\nInforme Base Maior: ");
scanf("%f",&b_maior);
printf("Informe Base Menor: ");
scanf("%f",&b_menor);
printf("Informe Altura: ");
scanf("%f",&altura_trap);
area_trap=(b_maior+b_menor)*altura_trap/2;
printf("\n�rea do Trap�zio: %.2f\n",area_trap);
printf("******************************\n\n");
printf("********** ATIVIDADE 7 **********\n");
printf("Criar um programa em C que receba do usu�rio uma temperatura na escala, Celsius (tC) e converter para Fahrenheit (tF).\n");
printf("tF = (tC * 9.0 / 5.0) + 32.0\n");
printf("\nInforme Temperatura em Celsius: ");
scanf("%f",&tC);
tF=(tC*9.0/5.0)+32.0;
printf("\nTemperatura em Fahrenheit: %.2f F�\n",tF);
printf("******************************\n\n");
printf("********** ATIVIDADE 8 **********\n");
printf("Elabora um algoritmo que receba do usu�rio os tr�s coeficientes a, b e c de uma equa��o do 2� grau e calcule o valor de delta.\n");
printf("Delta = b*b-4*a*c\n\n");
printf("Forma de sa�da:\n");
printf("Delta = valor de delta\n");
printf("\nInforme a: ");
scanf("%f",&a);
printf("Informe b: ");
scanf("%f",&b);
printf("Informe c: ");
scanf("%f",&c);
delta=b*b-4*a*c;
printf("\nDelta = %.2f\n",delta);
printf("******************************\n");
	return 0;
}

16/08/2024
Exemplo 1:
	
#include <stdio.h>
#include <locale.h>
#include <math.h>
int main()
{
float a,b,c,delta,x1,x2;

setlocale(LC_ALL,"");

printf("********** Raiz Quadrada e Potencia **********\n");

printf("\nInforme a: ");
scanf("%f",&a);
printf("Informe b: ");
scanf("%f",&b);
printf("Informe c: ");
scanf("%f",&c);
delta=pow(b,2)-4*a*c;

x1=(-b+sqrt(delta))/2*a;
x2=(-b-sqrt(delta))/2*a;
printf("\nDelta = %.2f\n",delta);
printf("x� = %.2f\n",x1);
printf("x� = %.2f\n",x2);
printf("******************************\n");
	return 0;
}

Exemplo 2:
	
#include <stdio.h>
#include <math.h>
int main()
{
float a;
printf("Informe a: ");
scanf("%f",&a);
printf("%.2f",pow(a,3));

}

Exemplo 3:

#include <stdio.h>
#include <math.h>
int main()
{

printf("%.2f",pow(2,3));
printf("%.2f",pow(5,5));

}

Data: 29/08/2024
Exemplo 1:
#include <stdio.h>
#include <locale.h>
int main()
{
float n1,n2,media;
setlocale(LC_ALL,"");
printf("Insira Nota 1: ");
scanf("%f",&n1);
printf("Insira Nota 2: ");
scanf("%f",&n2);

media=(n1+n2)/2;

if (media>=60)
{
	printf("----------\nM�dia: %.2f pts\n\nResultado: Passou!",media);
}
else
{
	printf("----------\nM�dia: %.2f pts\n\nResultado: Reprovou!",media);
}
}

Exemplo 2:
#include <stdio.h>
#include <locale.h>
int main()
{
int idade;
setlocale(LC_ALL,"");
printf("Insira sua idade: ");
scanf("%d",&idade);

if (idade>=18)
{
	printf("----------\nIdade: %d anos\n\nResultado: Adulta!",idade);
}
else
{
	printf("----------\nIdade: %d anos\n\nResultado: Menor de idade!",idade);
}
}

Exemplo 3:
#include <stdio.h>
#include <locale.h>
int main()
{
int idade;
setlocale(LC_ALL,"");
printf("Insira sua idade: ");
scanf("%d",&idade);

if (idade>=18)
{
	printf("----------\nIdade: %d\n\nResultado: Adulta!",idade);
}
else
{
	if (idade<0)
	{
		printf("----------\nIdade: %d\n\nResultado: Idade n�o existe!",idade);
	}
	else
	{
	printf("----------\nIdade: %d\n\nResultado: Menor de idade!",idade);
	}
}
}

Data: 30/08/2024

Exercicio 1
#include <stdio.h>
#include <locale.h>

int main()
{
float compra,compra_desconto;

setlocale(LC_ALL,"");
printf("Insira valor da compra: R$ ");
scanf("%f",&compra);

if (compra>=1500)
{
	compra_desconto=compra-20;
	printf("----------\nValor da Compra: R$ %2.f\nValor do Desconto: R$20,00\n\nValor da Compra com Desconto: R$ %2.f,compra,compra_desconto);
}	
else
{
	compra_desconto=compra-8;
	printf("----------\nValor da Compra: R$ %2.f\nValor do Desconto: R$8,00\n\nValor da Compra com Desconto: R$ %2.f,compra,compra_desconto);
}
}

Exercicio 2
#include <stdio.h>
#include <locale.h>

int main()
{
int numero;

setlocale(LC_ALL,"");
printf("Insira o n�mero: ");
scanf("%d",&numero);

if (numero%2==0)
//se o resto da divis�o do numero digitado por 2 for igual a zero
{
	printf("----------\nN�mero: %d\n\nO n�mero � par!",numero);
}	
else
{
	printf("----------\nN�mero: %d\n\nO n�mero � �mpar!",numero);
}
}

Exercicio 3
#include <stdio.h>
#include <locale.h>

int main()
{
int numero;

setlocale(LC_ALL,"");
printf("Insira o n�mero: ");
scanf("%d",&numero);

if (numero<100)
{
	printf("----------\nN�mero: %d\n\nO n�mero � menor que 100!",numero);
}	
else
{
	if (numero==100)
	{
		printf("----------\nN�mero: %d\n\nO n�mero � igual a 100!",numero);
	}
	else
	{
		printf("----------\nN�mero: %d\n\nO n�mero � maior que 100!",numero);
	}
}
}

Exemplo 4:
#include <stdio.h>
int main()
{
int numero,resto;
printf("Digite um numero: ");
scanf("%i",&numero);

resto=numero%2;
printf("Resto: %d",resto);	
}

Data: 04/09/2024

Exercicio 1:
#include <stdio.h>
#include <locale.h>
int main (){
	float comprimento,largura,altura,volume;
	
	setlocale(LC_ALL,"");
	printf("Informe o comprimento: ");
	scanf("%f",&comprimento);
	printf("Informe o largura: ");
	scanf("%f",&largura);
	printf("Informe o altura: ");
	scanf("%f",&altura);
	
	volume=comprimento*altura*largura;
	
	printf("Volume � igual a %.2f",volume);
}

Exercicio 2.1:
#include <stdio.h>
#include <locale.h>

int main (){
	char sexo;
	float salario,salario_bonus;
	
	setlocale(LC_ALL,"");
	printf("Informe o seu sexo (F/M): ");
	scanf("%c",&sexo);
	printf("Informe o seu sal�rio: R$ ");
	printf("%f",&salario);
	salario_bonus=salario+300;
	
	if (sexo == 'F'){
		printf("Sal�rio: R$ %.2f",salario_bonus);
	}
	else{
		if (sexo == 'M'){
			printf("Sal�rio: R$ %.2f",salario);
		}
		else{
			printf("Sexo n�o reconhecido.");
		}
	}
	printf("Sexo n�o reconhecido.");
}

Exercicio 2.2:
#include <stdio.h>
#include <locale.h>

int main (){
	char sexo;
	float salario,salario_bonus;
	
	setlocale(LC_ALL,"");
	printf("Informe o seu sexo (F/M): ");
	scanf("%c",&sexo);
	printf("Informe o seu sal�rio: R$ ");
	scanf("%f",&salario);
	salario_bonus=salario+300;
	
	if (sexo=='F'||sexo=='f'){
		printf("Sal�rio: R$ %.2f",salario_bonus);
	}
	else{
		if (sexo=='M'||sexo=='m'){
			printf("Sal�rio: R$ %.2f",salario);
		}
		else{
			printf("Sexo n�o reconhecido.");
		}
	}
}

Exemplo 1:
#include <stdio.h>
#include <locale.h>

int main (){
	char sexo;
	float salario,salario_bonus;
	int continuar;
	continuar=1;
	setlocale(LC_ALL,"");
	
	while(continuar){
		printf("Informe o seu sexo (F/M): ");
		scanf("%c",&sexo);
		printf("Informe o seu sal�rio: R$ ");
		scanf("%f",&salario);
		salario_bonus=salario+300;
	
		if (sexo=='F'||sexo=='f'){
			printf("Sal�rio: R$ %.2f",salario_bonus);
		}
		else{
			if (sexo=='M'||sexo=='m'){
				printf("Sal�rio: R$ %.2f",salario);
			}
			else{
				printf("Sexo n�o reconhecido.");
			}
		}
		printf("\n\nDigite 1 para continuar ou 0 para terminar: ");
		scanf("%d",&continuar);
		
		return 0;
	}
}

Data: 12/09/2024
Exemplo 1:
#include <stdio.h>
#include <locale.h>

int main (){
	int num;
	setlocale(LC_ALL,"");
	printf("Digite o n�mero: ");
	scanf("%i",&num);
	
	if (num>=10 && num<=20){
		printf("O n�mero %i est� entre 10 e 20.",num);
	}else{
		printf("O n�mero %i N�O est� entre 10 e 20.",num);
	}
}

Exemplo 2:
#include <stdio.h>
#include <locale.h>

int main (){
	int num;
	setlocale(LC_ALL,"");
	printf("Digite o n�mero: ");
	scanf("%i",&num);
	
	if (num<10 || num>20){
		printf("O n�mero %i � menor que 10 ou maior que 20.",num);
	}else{
		printf("O n�mero %i est� entre 10 e 20.",num);
	}
}

Data: 13/09/2024
Exemplo 1:
#include <stdio.h>
#include <locale.h>

int main (){
	int idade;
	setlocale(LC_ALL,"");
	printf("Me informe a sua idade: ");
	scanf("%i",&idade);
	
	if (idade<5 || idade>60){
		printf("\nIdade: %i\nGratuidade: SIM!",idade);
	}else{
		printf("\nIdade: %i\nGratuidade: N�O!",idade);
	}
}

Exemplo 2:
#include <stdio.h>
#include <locale.h>

int main (){
	int num;
	setlocale(LC_ALL,"");
	printf("Me informe o n�mero: ");
	scanf("%i",&num);
	
	if (num<20 || num>50){
		printf("\nN�mero pode ser menor que 20 ou maior que 50!");
	}else{
		printf("\nN�mero est� entre 20 e 50!");
	}
}

Exemplo:
#include <stdio.h>

int main()
{
int n1,n2;

printf("Insira o numero 1: ");
scanf("%i",&n1);
printf("Insira o numero 2: ");
scanf("%i",&n2);

if (n1%2==0 && n2%2==0)
{
	printf("Soma = %i",n1+n2);
}	
else
{
	printf("Subtracao = %i",n1-n2);
}
}

Data: 17/09/2024
Exemplo 1:
#include <stdio.h>
#include <locale.h>
int main (){
	int n1;
	setlocale(LC_ALL,"");
	printf("Informe o n�mero: ");
	scanf("%i",&n1);
	
	if (n1>=50&&n1<=90)
{
	printf("O n�mero (%i) est� entre 50 e 90",n1);
}else{
	if (n1>=150&&n1<=300){
		printf("O n�mero (%i) est� entre 150 e 300",n1);
	}else{
		printf("O n�mero (%i) n�o est� em nenhuma condi��o",n1);
	}
}
}

Exerc�cio 1:
#include <stdio.h>
#include <locale.h>
int main (){
	int n;
	setlocale(LC_ALL,"");
	printf("Informe o n�mero: ");
	scanf("%i",&n);
	if (n>100 && n<200){
		printf("O n�mero (%i) est� entre 100 e 200",n);
	}else{
		printf("O n�mero (%i) n�o est� entre 100 e 200",n);
	}
}

Exerc�cio 2:
#include <stdio.h>
#include <locale.h>
int main (){
	float media;
	setlocale(LC_ALL,"");
	printf("Informe a m�dia do aluno: ");
	scanf("%f",&media);
	
	if (media>=0 && media<5){
		printf("M�dia: %.2f pts.\nResultado: Reprovado!",media);
	}else{
		if (media>=5 && media<7){
			printf("M�dia: %.2f pts.\nResultado: Recupera��o!",media);
		}else{
			if (media>=7 && media <=10){
			printf("M�dia: %.2f pts.\nResultado: Aprovado!",media);
			}else{
				printf("M�dia: (%.2f pts)\nResultado: Inv�lido!",media);
			}
		}
	}
}

Exercicio 3:
#include <stdio.h>
#include <locale.h>
#include <math.h>
int main (){
	float peso,h,imc;
	setlocale(LC_ALL,"");
	printf("Informe o seu peso (Kg): ");
	scanf("%f",&peso);
	printf("Informe a sua altura (m): ");
	scanf("%f",&h);
	
	imc=peso/(pow(h,2));
	
	if (imc <=18.5){
		printf("\nIMC = %.1f\nCondi��o: Abaixo do peso",imc);
	}else{
		if (imc>18.5 && imc<=25){
			printf("\nIMC = %.1f\nCondi��o: Peso normal",imc);
		}else{
			if (imc>25 && imc<=30){
				printf("\nIMC = %.1f\nCondi��o: Acima do peso",imc);
			}else{
				printf("\nIMC = %.1f\nCondi��o: Obeso",imc);
			}
		}
	}
}

Exerc�cio 4:
#include <stdio.h>
#include <locale.h>
int main (){
	int cod;
	float peso,valor;
	setlocale(LC_ALL,"");
	printf("Informe o peso (Kg): ");
	scanf("%f",&peso);
	printf("Informe o c�digo: ");
	scanf("%i",&cod);
	
	if (cod==3215){
		valor=peso*23.0;
		printf("\nCarne: Ch�o de fora\nValor: R$ %.2f",valor);
	}else{
		if (cod==3214){
			valor=peso*38.0;
			printf("\nCarne: Picanha\nValor: R$ %.2f",valor);	
		}else{
			if (cod==3236){
				valor=peso*13.60;
				printf("\nCarne: Costela\nValor: R$ %.2f",valor);
			}else{
				if (cod==3114){
					valor=peso*9.50;
					printf("\nCarne: Perinl de porco\nValor: R$ %.2f",valor);
				}else{
					if (cod==3112){
						valor=peso*11;
						printf("\nCarne: Peito de frango\nValor: R$ %.2f",valor);
					}else{
						printf("\nC�digo inserido incorretamente!");
					}
				}
			}
		}
	}
}

DATA: 20/09/2024

Exemplo 1:

#include <stdio.h>
int main(){
	int i;//declara a vari�vel exemplo 1
	
	for(i=1;i<=10;i++)
	{
		printf("Estou dentro do for: i= %i\n",i);
	}
}

Exemplo 2:

#include <stdio.h>
#include <locale.h>
int main(){
	int i;
	setlocale(LC_ALL,"");
	
	for(i=50;i<=100;i++)
	{
		printf(" %i\n",i);
	}
}

Exemplo 3:

#include <stdio.h>
#include <locale.h>
int main(){
	int i;
	setlocale(LC_ALL,"");
	
	for(i=0;i<=100;i++)
	{
		if(i%2==0) //se for (i%!=0) imprime n impar
		{
			printf(" %i\n",i);
		}	
	}
}

Exemplo 4:

#include <stdio.h>
#include <locale.h>
int main(){
	int i;
	setlocale(LC_ALL,"");
	
	for(i=0;i<=100;i+=3)
	{
		
			printf(" %i\n",i);
		
	}
}

Exemplo 5:

#include <stdio.h>
#include <locale.h>
int main(){
	int i;
	setlocale(LC_ALL,"");
	
	for(i=1;i<=10;i++)
	{
		
			printf("%d X 5 = %d \n",i,i*5);
		
	}
}

Exemplo 6:
#include <stdio.h>
#include <locale.h>
int main(){
	int i,num,cont;
	cont=0;
	setlocale(LC_ALL,"");
	for(i=1;i<=5;i++){
		printf("\nDigite um n�mero: ");
		scanf("%d",&num);

		if (num>10){
			cont=cont+1;
		}
	}
	printf("Total de n�meros > 10 = %d",cont);
}

Exemplo 7:
#include <stdio.h>
#include <locale.h>
int main(){
	int i,num,cont;
	cont=0;
	setlocale(LC_ALL,"");
	for(i=1;i<=20;i++){
		printf("\nDigite um n�mero: ");
		scanf("%d",&num);

		if (num%2!=0&&num>20&&num<80){
			cont=cont+1;
		}
	}
	printf("Total de n�meros �mpares = %d",cont);
}

Data: 03/10/2024

Exemplo 1:
#include <stdio.h>
#include <locale.h>
int main (){
	int i,s,num;
	s=0;
	setlocale(LC_ALL,"");
	for(i=1;i<=5;i++){
		printf("Digito o n�mero: \n");
		scanf("%i",&num);
		s=s+num;
	}
	printf("Valor: %i",s);
}

Data: 03/10/2024

Exemplo 1:
#include <stdio.h>
#include <locale.h>
int main (){
	int i,somaidade,idade,cont,mediaidade;
	cont=0;
	somaidade=0;
	setlocale(LC_ALL,"");
	for(i=1;i<=5;i++){
		printf("Digito a idade: \n");
		scanf("%i",&idade);
		somaidade=somaidade+idade;
		cont=cont+1;
		mediaidade=somaidade/cont;
	}
	printf("\nIdade m�dia dos %i alunos: %i",cont,mediaidade);
}

Exemplo 2:
#include <stdio.h>
#include <locale.h>
int main (){
	int i,somaidade,idade,cont,mediaidade;
	cont=0;
	somaidade=0;
	setlocale(LC_ALL,"");
	for(i=1;i<=15;i++){
		printf("Digito a idade: \n");
		scanf("%i",&idade);
		somaidade=somaidade+idade;
		cont=cont+1;
		mediaidade=somaidade/cont;
	}
	printf("\nIdade m�dia dos %i alunos: %i",cont,mediaidade);
}

>>>Data: 04/10/2024

Exercicio 1:

#include <stdio.h>
#include <locale.h>
int main (){
	int i,num,soma;
	soma=0;
	setlocale(LC_ALL,"");
	
	for (i=1;i<=10;i++){
		printf("Informe o n�mero: ");
		scanf("%i",&num);
		if(num>5){
			soma=soma+num;
		}
	}
	if(soma!=0){
		printf("\nSoma dos n�meros acima de cinco: %i",soma);
	}else{
		printf("\nN�o h� n�meros maiores que cinco.");
	}
}

Exercicio 2:

#include <stdio.h>
#include <locale.h>
int main (){
	int i,num,soma;
	soma=0;
	setlocale(LC_ALL,"");
	
	for (i=1;i<=10;i++){
		printf("Informe o n�mero: ");
		scanf("%i",&num);
		if(num%2==0){
			soma=soma+num;
		}
	}
	if(soma!=0){
		printf("\nSoma dos n�meros acima de cinco: %i",soma);
	}else{
		printf("\nN�o h� n�meros pares.");
	}
}

Exercicio 3:

#include <stdio.h>
#include <locale.h>
int main (){
	int i,num,soma,cont;
	cont=0;
	soma=0;
	setlocale(LC_ALL,"");
	
	for (i=1;i<=6;i++){
		printf("Informe o n�mero: ");
		scanf("%i",&num);
		if(num>10){
			soma=soma+num;
			cont=cont+1;
		}
	}
	if(soma!=0){
		printf("\nQuantidade de n�meros acima de 10: %i\nSoma dos n�meros acima de 10: %i",cont,soma);
	}else{
		printf("\nN�o h� n�meros acima de 10.");
	}
}

Exercicio 4:

#include <stdio.h>
#include <locale.h>
int main (){
	int i,num,contpar,contimpar;
	contpar=0;
	contimpar=0;
	setlocale(LC_ALL,"");
	
	for (i=1;i<=6;i++){
		printf("Informe o n�mero: ");
		scanf("%i",&num);
		if(num%2==0){
			contpar=contpar+1;
		}else{
			contimpar=contimpar+1;
		}
	}
	if(contpar!=0&&contimpar!=0){
		printf("\nSoma dos n�meros pares: %i\nSoma dos n�meros �mpares: %i",contpar,contimpar);
	}else{
		if(contpar==0){
			printf("\nSoma dos n�meros �mpares: %i\nN�o h� n�meros pares.",contimpar);
		}else{
			printf("\nSoma dos n�meros pares: %i\nN�o h� n�meros �mpares.",contpar);
		}
		
	}
}

Exercicio 5:

#include <stdio.h>
#include <locale.h>
int main(){
	float f,c;
	setlocale(LC_ALL,"");
	printf("Graus em Fahrenheit | Graus em Celsius\n");
	for(f=32;f<=212;f++)
	{
		c=((f-32)*5)/9;
		printf("%.0f			%.1f\n",f,c);
	}
}

Exercicio 6:

#include <stdio.h>
#include <locale.h>
int main (){
	char perf;
	int i,p1,p2,p3;
	p1=0;
	p2=0;
	p3=0;
	setlocale(LC_ALL,"");
	printf("Qual dos 3 perfumes � o melhor?\n[1] P1\n[2] P2\n[3] P3\n------------------------------\n");
	for (i=1;i<=30;i++){
		printf("R: ");
		scanf(" %c",&perf);
		if (perf=='1'){
			p1=p1+1;
		}else{
			if (perf=='2'){
				p2=p2+1;
			}else{
				if (perf=='3'){
					p3=p3+1;
				}else{
					i=i-1;
					printf("ERRO! Digite o n�mero entre colchetes!\n");
				}
			}
		}
	}
	printf("------------------------------\nQuantidade de votantes no P1: %i\nQuantidade de votantes no P2: %i\nQuantidade de votantes no P3: %i\n------------------------------\n",p1,p2,p3);
	
	if (p1>p2&&p1>p3){
		printf("Perfume mais escolhido: P1 (%i votos)",p1);
	}else{
		if (p2>p1&&p2>p3){
			printf("Perfume mais escolhido: P2 (%i votos)",p2);
		}else{
			if (p3>p1&&p3>p2){
				printf("Perfume mais escolhido: P3 (%i votos)",p3);
			}else{
				printf("N�o houve um perfume mais votado!");
			}
		}
	}
}

Exercicio 7:

#include <stdio.h>
#include <locale.h>
int main (){
	int i,num,numMaior,numMenor;
	setlocale(LC_ALL,"");
	for (i=1;i<=10;i++){
		printf("Informe o n�mero: ");
		scanf("%d",&num);
		if (i==1){
			numMaior=num;
			numMenor=num;
		}
		if (num>numMaior){
			numMaior=num;
		}
		if (num<numMenor){
			numMenor=num;
		}
	}
	printf("---------------\nN�mero Maior: %d\nN�mero Menor: %d",numMaior,numMenor);
}


#include <stdio.h>
#include <locale.h>

int main (){
	char validacao;
	setlocale(LC_ALL,"");
	printf("Iniciar o programa? ");
	scanf(" %c",&validacao);
	
	while(validacao=='s'){
		printf("Programa em execu��o...\n\n");
		printf("Deseja continuar? ");
		
	scanf(" %c",&validacao);
	}
	printf("\nPrograma finalizado.");

}

Data: 16/10/2024

Exemplo 1:
#include <stdio.h>
#include <locale.h>
int main (){
	int idade,soma;
	soma=0;
	setlocale(LC_ALL,"");
	printf("Informe a idade do aluno: ");
	scanf("%d",&idade);
	
	
	while(idade>0){
		soma=soma+idade;
		printf("Informe a idade do aluno: ");
		scanf("%d",&idade);
		
	}
	printf("\nPrograma finalizado.\n--------------------\nSoma das idades dos alunos: %d",soma);

}

Exemplo 2:
#include <stdio.h>
#include <locale.h>
int main (){
	float idade,soma,cont,media;
	soma=0;
	cont=0;
	setlocale(LC_ALL,"");
	printf("Informe a idade do aluno: ");
	scanf("%f",&idade);
	
	
	while(idade>0){
		soma=soma+idade;
		cont=cont+1;
		printf("Informe a idade do aluno: ");
		scanf("%f",&idade);
		
	}
	media=soma/cont;
	printf("\nPrograma finalizado.\n--------------------\nSoma das idades dos %.0f alunos: %.0f\nM�dia das idades dos %.0f alunos: %.0f",cont,soma,cont,media);

}

Data: 18/10/2024
Exemplo 1:
#include <stdio.h>
#include <locale.h>
int main (){
	char sexo;
	setlocale(LC_ALL,"");
	printf("Informe o seu sexo: ");
	scanf(" %c",&sexo);
	
	while (num<=12||num>=20){
		printf("Sexo informado � incorreto!\n\nInforme o seu sexo: ");
		scanf(" %c",&sexo);
	}
	if (sexo=='f'){
		printf("Sexo: [%c] Feminino",sexo);
	}else{
		printf("Sexo: [%c] Masculino",sexo);
	}
	
}

Exemplo 2:
#include <stdio.h>
#include <locale.h>
int main (){
	int num;
	setlocale(LC_ALL,"");
	printf("Informe o n�mero: ");
	scanf("%d",&num);
	
	while (num<=12||num>=20){
		printf("N�mero inv�lido!\n\nInforme o n�mero: ");
		scanf("%d",&num);
	}
	printf("--------------------\nN�mero informado: %d",num);
	
}

Data: 25/10/2024

Exercicio 1:
#include <stdio.h>
#include <locale.h>
int main (){
	int alunos,cont;
	float nota,somanota,media;
	somanota=0;
	cont=0;
	setlocale(LC_ALL,"");
	printf("Quantos alunos possuem na sala de aula? ");
	scanf("%d",&alunos);
	
	while (cont < alunos){
		cont=cont+1;
		printf("Digite a nota do aluno: ");
		scanf("%f",&nota);
		somanota=somanota+nota;
	}
	media=somanota/alunos;
	
	printf("M�dia da nota dos %d alunos: %.2f pts",alunos,media);	
}

Exercicio 2:
#include <stdio.h>
#include <locale.h>
int main (){
	int idade,cont,somaidade;
	cont=0;
	somaidade=0;
	setlocale(LC_ALL,"");
	printf("Informe a sua idade: ");
	scanf("%d",&idade);
	
	while(idade > 0){
		if(idade <=0){
			cont=cont-1;
		}else{
			cont=cont+1;
		}
		if(idade>=16&&idade<=20){
			somaidade=somaidade+1;
		}
		printf("Informe a sua idade: ");
		scanf("%d",&idade);
	}
	
	printf("\nN�mero de pessoas participantes: %d\nN�mero de pessoas com idade entre 16 e 20 anos: %d",cont,somaidade);
}

Exerc�cio 3:
#include<stdio.h>
#include<locale.h>
int main (){
	char opiniao;
	int idade,cont,contA,contB,contC,contD,contE;
	
	cont=0;
	contA=0;
	contB=0;
	contC=0;
	contD=0;
	contE=0;
	setlocale(LC_ALL,"");
	printf("Informe a sua idade: ");
	scanf("%d",&idade);
	
	while(idade>0){
		if(idade<=0){
			cont=cont-1;
		}else{
			cont=cont+1;
		}
			
		printf("\nOpini�o  |  Significado\nA    |    �timo\nB    |    Bom\nC    |    Regular\nD    |    Ruim\nE    |    P�ssimo\n");
		printf("Escolha de A a E a sua nota em rela��o ao filme: ");
		scanf(" %c",&opiniao);
			
		if(opiniao=='A'||opiniao=='a'){
			contA=contA+1;		
		}else{
			if(opiniao=='B'||opiniao=='b'){
			contB=contB+1;
			}else{
				if(opiniao=='C'||opiniao=='c'){
				contC=contC+1;
				}else{
					if(opiniao=='D'||opiniao=='d'){
					contD=contD+1;
					}else{
						if(opiniao=='E'||opiniao=='e'){
						contE=contE+1;
						}else{
							printf("Escolha inv�lida.");
							cont=cont-1;
						}
					}
				}
			}
		}
	
		printf("\n\nInforme a sua idade: ");
		scanf("%d",&idade);
	}
		
	printf("\nQuantidade de pessoas que responderam a pesquisa: %d\n",cont);
	printf("Votos para A [�timo]: %d\nVotos para B [Bom]: %d\nVotos para C [Regular]: %d\nVotos para D [Ruim]: %d\nVotos para E [P�ssimo]: %d",contA,contB,contC,contD,contE);	
}

DATA: 01/11/2024

Exemplo 1:
#include<stdio.h>
int main(){
	int x[10];
	int i;
	//leitura
	for (i=0;i<10;i++){
		printf("Informe o vetor %d: \n",i);
		scanf("%d",&x[i]);
	}
	printf("--------------------\n");
	//imprimir
	for (i=0;i<10;i++){
		printf("x[%d] = %d\n",i,x[i]);
		
	}	
}

Exemplo 2:
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
int main(){
	int x[10];
	int i,soma;
	setlocale(LC_ALL,"");
	
	for(i=0;i<10;i++){
		printf("Informe o valor [%d]: ",i);
		scanf("%d",&x[i]);
	}
	
	system ("cls");
	printf("a) O vetor com os valores em cada posi��o;\n");
	for(i=0;i<10;i++){
		printf("\nValor [%d]: %d",i,x[i]);
	}
	
	printf("\n------------------------------\n");
	printf("b) O terceiro valor digitado;\n\nx[2]: %d",x[2]);
	
	printf("\n------------------------------\n");
	printf("c) O valor no �ndice 8;\n\nx[8]: %d",x[8]);
	
	printf("\n------------------------------\n");
	soma=x[5]+x[9];
	printf("d) A soma do valor de �ndice 5 com o valor de �ndice 9;\n\nx[5] + x[9] =  %d",soma);
}

Exemplo 3:
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int main(){
	int idade[15];
	int i,soma,cont;
	soma=0;
	cont=0;
	setlocale(LC_ALL,"");
	for(i=0;i<15;i++){
		printf("Informe a idade %d: ",i);
		scanf("%d",&idade[i]);
	}
	//system("cls");
	printf("\n--------------------\nPosi��es do vetor de idades pares:\n");
	
	for(i=0;i<15;i++){
		if(idade[i]%2==0){
			cont=cont+1;
			printf("Posi��o: %d\n",i);	
		}
	}
	if (cont==0){
		printf("N�o h� idade par.");
	}
	
	printf("\n--------------------\nQuantas pessoas tem idade menor que 18?\n");
	for(i=0;i<15;i++){
		if(idade[i]<18){
			soma=soma+1;	
		}
	}
	if(soma!=0){
		printf("%d Pessoa(s)\n",soma);
	}else{
		printf("N�o h� idade menor que 18.");
	}	

}

Data: 08/11/2024
Exemplo 1:
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main(){
	int i,contA;
	char letra[15];
	contA=0;
	setlocale(LC_ALL,"");
	
	for (i=0;i<15;i++){
		printf("Digite uma letra: ");
		scanf(" %c",&letra[i]);
		
		if (letra[i]=='a'){
			contA=contA+1;
		}
	}
	
	printf("Quantidade de vezes que a letra 'A' foi digitada: %d",contA);
}

Exemplo 2:
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main(){
	int vetA[10],vetB[10],i;
	setlocale(LC_ALL,"");
	
	for (i=0;i<10;i++){
		printf("Informe o %d� valor do Vetor A: ",i);
		scanf("%d",&vetA[i]);
	}
	
	system("cls");
	printf("Vetores de B:\n");
	
	for (i=0;i<10;i++){
		vetB[i]=vetA[i]*2;
		printf("\n%d� Vetor B: %d",i,vetB[i]);
	}
	
	printf("\n---------------\nVetores de A:\n");
	
	for (i=0;i<10;i++){
		printf("\n%d� Vetor A: %d",i,vetA[i]);
	}
}

Exercicio 1:
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int main(){
	int vet[12],i,x,y,soma;
	x=i;
	y=i;
	setlocale(LC_ALL,"");
	for(i=0;i<12;i++){
		printf("Informe o valor do vetor %d: ",i);
		scanf("%d",&vet[i]);
	}
	
	system("cls");
	
	for(i=0;i<12;i++){
		printf("Vetor[%d]: %d\n",i,vet[i]);
	}
	
	printf("--------------------\n");
	
	printf("Informe X: ");
	scanf("%d",&x);
	
	printf("Informe Y: ");
	scanf("%d",&y);
	
	soma=vet[x]+vet[y];
	
	printf("X + Y = %d",soma);
}

Exercicio 2:
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int main(){
	int vetA[2],vetM[2],i,x;
	setlocale(LC_ALL,"");
	
	for(i=0;i<2;i++){
		printf("Informe um n�mero: ");
		scanf("%d",&vetA[i]);
	}
	
	printf("Informe o valor de x: ");
	scanf("%d",&x);
	
	for(i=0;i<2;i++){
		vetM[i]=vetA[i]*x;
	}
	system("cls");
	printf("Valores de M: \n");
	for(i=0;i<2;i++){
		printf("M[%d]: %d\n",i,vetM[i]);
	}
}

Exrcicio 3:
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int main(){
	int vetA[10],vetB[10],i,vetC[10];
	setlocale(LC_ALL,"");
	
	for(i=0;i<10;i++){
		printf("Informe o valor do vetor vetA[%d]: ",i);
		scanf("%d",&vetA[i]);
	}
	printf("---------------\n");
	for(i=0;i<10;i++){
		printf("Informe o valor do vetor vetB[%d]: ",i);
		scanf("%d",&vetB[i]);
	}
	
	for(i=0;i<10;i++){
		vetC[i]=vetA[i]+vetB[i];
	}
	system("cls");
	
	for(i=0;i<10;i++){
		printf("vetA[%d]: %d\n",i,vetA[i]);
	}
	printf("---------------\n");
	for(i=0;i<10;i++){
		printf("vetB[%d]: %d\n",i,vetB[i]);
	}
	printf("---------------\n");
	for(i=0;i<10;i++){
		printf("vetC[%d]: %d\n",i,vetC[i]);
	}
}

Exercicio 4:
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

int main() {
    int i, encontrado = 0;
    char letra[10], letrax;

    setlocale(LC_ALL, "");

    // Leitura do vetor de 10 posi��es
    for (i = 0; i < 10; i++) {
        printf("Informe a letra do vetor letra[%d]: ", i);
        scanf(" %c", &letra[i]);
    }

    system("cls"); // Limpa a tela (somente no Windows)

    // Exibe o vetor lido
    for (i = 0; i < 10; i++) {
        printf("Letra[%d]: %c\n", i, letra[i]);
    }

    // L� a letra X
    printf("Informe a letra X: ");
    scanf(" %c", &letrax);

    // Busca pela letra X no vetor
    for (i = 0; i < 10; i++) {
        if (letrax == letra[i]) {
            printf("\nValor de X [%c] encontrado no vetor letra[%d]!\n", letrax, i);
            encontrado = 1;
        }
    }

    if (encontrado==0) {
        printf("\nValor de X [%c] n�o encontrado no vetor.\n", letrax);
    }

    return 0;
}


Data: 21/11/2024

Exemplo 1:
#include <stdio.h>
#include <locale.h>
void escrevatela(){
	setlocale(LC_ALL,"");
	printf("Estou na fun��o!");
}

int main(){
	escrevatela();
	return 0;
}

Exemplo 2:
#include <stdio.h>
#include <locale.h>
int soma2inteiro(int n1, int n2){
	return (n1+n2);
}

float soma2reais(float n1, float n2){
	return (n1+n2);
}

int main(){
	setlocale(LC_ALL,"");
	printf("Soma de 2 inteiros = %d\n",soma2inteiro(1,2));
	printf("Soma de 2 reais = %.1f",soma2reais(3,4));
}

Exemplo 3:
#include <stdio.h>
#include <locale.h>
void menu(){
	setlocale(LC_ALL,"");
	printf("---------- Sistema em C ----------\nEscolha uma op��o:\n[1] - Calcular �rea\n[2] - Somar 3 n�meros reais\n[3] - Calcular IMC\n[4] - Para sair do sistema\n----------------------------------");
}

int main(){
	menu();
	return 0;
}

Exemplo 4:
#include <stdio.h>
#include <locale.h>
float soma3reais(float a,float b, float c){
	return (a+b+c);
}

int main(){
	float x,y,z;
	
	setlocale(LC_ALL,"");
	printf("Informe o 1� valor: ");
	scanf("%f",&x);
	printf("Informe o 2� valor: ");
	scanf("%f",&y);
	printf("Informe o 3� valor: ");
	scanf("%f",&z);
	
	printf("Soma: %.2f",soma3reais(x,y,z));
}

Exemplo 5:
#include <stdio.h>
#include <locale.h>
#include <math.h>

float imc(float peso, float altura){
	return(peso/pow(altura,2));
}

int main(){
	float n1,n2;
	
	setlocale(LC_ALL,"");
	printf("Informe o seu peso(Kg): ");
	scanf("%f",&n1);
	printf("Informe a sua altura(m): ");
	scanf("%f",&n2);
	
	printf("IMC: %.2f",imc(n1,n2));
}

Exemplo 6:
#include <stdio.h>
#include <locale.h>

float soma(float a,float b,float c){
	return(a+b+c);
}

float subtracao(float a,float b,float c){
	return(a-b-c);
}

float multiplicacao(float a,float b,float c){
	return(a*b*c);
}

float divisao(float a,float b,float c){
	return(a/b/c);
}

int main(){
	char operador;
	float n1,n2,n3;
	
	setlocale(LC_ALL,"");
	
	printf("---------- Escolha do Operador ----------\nEscolha um dos Operdores abaixo:\n[+] - Soma\n[-] - Subtra��o\n[*] - Multiplica��o\n[/] - Divis�o\n\nOperador escolhido: ");
	scanf(" %c",&operador);
	printf("-----------------------------------------\n\n");
	printf("---------- Valida��o dos N�meros  ----------\n");
	printf("Informe o n�mero 1: ");
	scanf("%f",&n1);
	printf("Informe o n�mero 2: ");
	scanf("%f",&n2);
	printf("Informe o n�mero 3: ");
	scanf("%f",&n3);
	printf("--------------------------------------------\n\n");
	
	if(operador=='+'){
		printf("------------------------------ Soma ------------------------------\n\nN�mero 1 [%.2f] + N�mero 2 [%.2f] + N�mero 3 [%.2f] = %.2f\n\n------------------------------------------------------------------",n1,n2,n3,soma(n1,n2,n3));
	}else{
		if(operador=='-'){
			printf("------------------------------ Subtra��o ------------------------------\n\nN�mero 1 [%.2f] - N�mero 2 [%.2f] - N�mero 3 [%.2f] = %.2f\n\n-----------------------------------------------------------------------",n1,n2,n3,subtracao(n1,n2,n3));
		}else{
			if(operador=='*'){
				printf("------------------------------ Multiplica��o ------------------------------\n\nN�mero 1 [%.2f] * N�mero 2 [%.2f] * N�mero 3 [%.2f] = %.2f\n\n---------------------------------------------------------------------------",n1,n2,n3,multiplicacao(n1,n2,n3));
			}else{
				if(operador=='/'){
					printf("------------------------------ Divis�o ------------------------------\n\nN�mero 1 [%.2f] / N�mero 2 [%.2f] / N�mero 3 [%.2f] = %.2f\n\n---------------------------------------------------------------------",n1,n2,n3,divisao(n1,n2,n3));
				}else{
					printf("Valor do operador n�o identificado!");
				}
			}
		}
	}
}

Data: 28/11/2024

Exemplo 1:
#include <stdio.h>
#include <locale.h>

int verificaParImpar(int n1){
	if(n1%2==0){
		return 0;
	}else{
		return 1;
	}
}

int main(){
	int n1;
	
	setlocale(LC_ALL,"");
	printf("Informe o n�mero inteiro: ");
	scanf("%d",&n1);
	
	printf("%d",verificaParImpar(n1));
}

Exemplo 2:
#include <stdio.h>
#include <locale.h>

int verificaParImpar(int n1){
	if(n1%2==0){
		return 0;
	}else{
		return 1;
	}
}

int main(){
	int n1;
	
	setlocale(LC_ALL,"");
	printf("Informe o n�mero inteiro: ");
	scanf("%d",&n1);
	
	if(verificaParImpar(n1)==0){
		printf("Par!");
	}else{
		printf("�mpar!");
	}
}

Data: 29/11/2024

Exercicio 1:
#include <stdio.h>
#include <locale.h>

Exercicio 1.a) Escreva uma fun��o com o nome �menorNumero� que receba como par�metros dois n�meros 
inteiros e retorne o menor n�mero entre eles.
int menorNumero(int n1, int n2){
	if(n1<n2){
		return (n1);
	}
	if(n1>n2){
		return (n2);
	}
}

Exercicio 1.b)
int main(){
	int n1,n2;
	
	setlocale(LC_ALL,"");
	printf("Informe o 1� n�mero: ");
	scanf("%d",&n1);
	printf("Informe o 2� n�mero: ");
	scanf("%d",&n2);
	
	printf("------------------------------\n");
	printf("Menor n�mero: %d",menorNumero(n1,n2));
}

Exercicio 2:
#include <stdio.h>
#include <locale.h>

Exercicio 2.a) Fa�a uma fun��o com o nome �menorMaiorZero� que recebe um valor inteiro e verifica se o 
valor � positivo (>0), negativo (<0) ou zero. A fun��o deve retornar 1 para valores positivos, 
retornar -1 para valores negativos e zero para valor 0.
int menorMaiorZero(int n1){
	if (n1<0){
		return -1;
	}
	if (n1==0){
		return 0;
	}
	if (n1>0){
		return 1;
	}
}

Exercicio 2.b) Elabore um algoritmo que leia um n�mero inteiro e imprimir se o n�mero � negativo, positivo 
ou zero. Utilize a fun��o criada no item a da quest�o.
int main(){
	int n1;
	
	setlocale(LC_ALL,"");
	printf("Informe um n�mero Inteiro: ");
	scanf("%d",&n1);
	
	if(menorMaiorZero(n1)==-1){
		printf("Negativo!");
	}
	if(menorMaiorZero(n1)==0){
		printf("Zero!");
	}
	if(menorMaiorZero(n1)==1){
		printf("Positivo!");
	}
}

Exercicio 3:
#include <stdio.h>
#include <locale.h>

Exercicio 3.a) Construa uma fun��o que recebe como par�metro um caractere e um valor real que ser� o 
comprimento do lado de um quadrado. Essa fun��o dever� retornar �rea do quadrado se o 
caractere for �a� e retornar per�metro do quadrado se o caractere for �p�. �rea = lador*lado | Per�metro=4*lado.
float validar(char letra, float lado){
	if(letra=='a'||letra=='A'){
		printf("----------\nPer�metro do Quadrado: ");
		return (4*lado);
	}
	if(letra=='p'||letra=='P'){
		printf("----------\nPer�metro do Quadrado: ");
		return(lado*lado);
	}
}
Exercicio 3.b) Elabore um algoritmo que leia uma letra e o comprimento do lado de um quadrado, se a letra 
lida for �a�, dever� imprimir a �rea do quadrado e se a letra for �p�, dever� imprimir o 
per�metro do quadrado. Utilize a fun��o que foi constru�da no item anterior da quest�o.
int main(){
	char letra;
	float lado;
	
	setlocale(LC_ALL,"");
	printf("Escolha (a) para C�lculo de Per�metro do Quadrado ou (b) para C�lculo de �rea do Quadrado: ");
	scanf(" %c",&letra);
	printf("Informe o tamanho do lado do quadrado: ");
	scanf("%f",&lado);
	
	printf("%.2f",validar(letra,lado));
}
*/

