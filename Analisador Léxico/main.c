#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//Quantidades de palavras reservadas

#define RES_QTD 9

//Quantidade de Simbolos

#define SIMB_QTD 8

//Tamanho da String

#define TempS_Len 20

//Estados do transdutor

void aceita();
void rejeita();
void e0();
void e1();
void e2();
void e3();
void e4();
void e5();
void e6();

//Funcoes de transição

void Sigma1();
void Sigma2();
void Sigma3();
void Sigma4();
void Sigma5();
void Sigma6();
void Sigma7();
void Sigma8();
void Sigma9();
void Sigma10();

//Verifica se a Palavra é reservada

int reservada( char *);

//busca indice de onde se encontra a varial ou palavra

int indice(char *, char *);

//Verifica se os vetores são iguais

int iguais( char *, char *);

//Copia um vetor para outro

void copia(char *, char *);

//Verificar se é caracter

int isChar(char);

//Verificar se é Número

int isNum(char);

//Variavel temporária para analisar comandos

char TempS[TempS_Len];

//indice da variavel TempS

int p_TempS = 0;

char TempC;

int TempN;

//Tabela de variaveis

char *Simb[20];

//Inndice da tabela de variaveis

int p_Simb = 0;

//Verifica se uma variavel esta na tabela de simbolos

int isSimb(char *);

//Busca o indice da variavel na tabela de simbolos

int Simb_indice(char *);

//Palavras reservadas

char *Res[RES_QTD] = {"if", "else", "then", "goto", "let", "print", "read", "end", "of"};

//Array de Variaveis e números

int Num[20];
char *Var[20];

//Vetor para receber valores

char f[100];

//indice do vetor f

int p;


int main(){

    int i = 0;
    int j = 0;

    p = 0;

    printf("PALAVRAS E SIMBOLOS RESERVADOS:\n");

    printf("\n================================================================================\n");

    printf("Palavras: ");

    for( j = 0; j < RES_QTD; j++){

        for(i = 0; Res[j][i] != 0; i++){

            printf("%c", Res[j][i]);
        }

        printf(", ");
    }

    printf("\n\n================================================================================\n");

    printf("Entrada:\n");

    gets(f);

    printf("\nSaida:\n");

    e0();

    printf("\n");

    printf("\nTabela de Variaveis[Simbolos]:\n[");

    for( j = 0; j < p_Simb - 1; j++){

        printf("%s, ", &Simb[j]);
    }

    printf("%s]\n",&Simb[j]);

    getch();

    return 0;
}

int reservada(char *v1){

    int i = 0;

    for( i = 0;  i < RES_QTD; i++ ){

        if( iguais(v1, Res[i])){

            return 1;
        }
    }

    return 0;

}


int Res_indice(char *v1){

    int i = 0;

    for( i = 0;  Res[i] != 0; i++ ){

        if( iguais(v1, Res[i])){

            return i;
        }
    }

    return -1;

}

int isSimb(char *v1){

    int i = 0;

    for( i = 0;  i < p_Simb; i++ ){

        if( iguais(v1, &Simb[i])){

            return 1;
        }
    }

    return 0;

}

int Simb_indice(char *v1){

    int i = 0;

    for( i = 0;  &Simb[i] != 0; i++ ){

        if( iguais(v1, &Simb[i])){

            return i;
        }
    }

    return -1;

}


int iguais( char *v1, char *v2){

    int c;

    for(c = 0; v1[c] != 0; c++){

        if( v1[c] != v2[c]){

            return 0;
        }
    }

    if( v1[c] != v2[c]){

        return 0;
    }

    return 1;

}

void copia(char *ori, char *des){

    int i = 0;

    for(i = 0; ori[i] != 0; i++){

        des[i] = ori[i];
    }

    des[i] = 0;
}

int isChar(char c){


    if( (c > 64 && c < 91) || ( c > 96 && c < 123)){
        return 1;
    }

    return 0;
}

int isNum(char c){

    if( c > 47 && c < 58 ){
        return 1;
    }

    return 0;
}

void aceita(){
	printf("Aceita!!!");
}

void rejeita(){
	printf("Rejeita!!!");
}

void e0(){

    if( f[p] == '\0' ){

    }
    else if( f[p] == '%' ){

        e5();
    }
    else if( isChar(f[p]) ){

        Sigma1();
        e1();
    }
    else if( isNum(f[p]) ){

        Sigma4();
        e2();
    }
    else if( f[p] == ':' ){

        e3();
    }
    else if( f[p] == ' ' ){
        p++;
        e0();
    }
    else{

        e6();
    }

}

void e1(){

    p++;
    p_TempS++;

    if( isChar(f[p]) || isNum(f[p]) ){

        Sigma2();
        e1();
    }
    else{

        Sigma3();

        if(f[p] != 0){

            e0();
        }
    }

}

void e2(){

    p++;

    if(isNum(f[p])){

        Sigma5();
        e2();
    }
    else{

        Sigma6();
        e0();
    }


}

void e3(){

    p++;

    if(f[p] == '='){

        e4();
    }
    else{

        Sigma7();
        e0();
    }
}

void e4(){

    p++;

    Sigma8();
    e0();
}

void e5(){

    p++;

    if(f[p] != 0){

        e5();
    }
    else{

        e0();
    }

}

void e6(){

    Sigma9();
    Sigma10();
    p++;
    e0();
}

void Sigma1(){

    TempS[p_TempS] = f[p];
}

void Sigma2(){

    TempS[p_TempS] = f[p];
}

void Sigma3(){

    TempS[p_TempS] = 0;

    p_TempS = 0;

    if(reservada(TempS)){

        printf("P(%i)", Res_indice(TempS));
    }
    else if(!isSimb(TempS)){

        copia(TempS, &Simb[p_Simb++]);
        printf("V(%i)", Simb_indice(TempS));
    }
    else{

        printf("V(%i)", Simb_indice(TempS));
    }

}

void Sigma4(){

    TempN = f[p] - 48;

}

void Sigma5(){

    TempN = (TempN*10) + (f[p]- 48);
}

void Sigma6(){

    printf("N(%i)", TempN);
}

void Sigma7(){
    printf(":");
}

void Sigma8(){
    printf(":=");
}

void Sigma9(){

    TempC = f[p];
}

void Sigma10(){

    printf("%c", TempC);
}
