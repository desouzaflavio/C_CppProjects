#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

int main(){

    int q_simbolos;
    int q_estados;
    int q_estados_finais;
    int estado_inicial;
    int tipo;
    int i, j, w;

    const char *name[25];

    printf("Quantos simbolos?");
    scanf("%d", &q_simbolos);

    printf("\n");

    char simbolos[q_simbolos];

    for( i = 0; i < q_simbolos; i++ ){

        printf( "Qual o simbolo %i?", i );
        scanf(" %c", &simbolos[i]);
    }

    printf("\n");
    printf("Quantos estados?");
    scanf(" %i", &q_estados);

    printf("\n");
    printf("Quantos estados finais?");
    scanf( " %i", &q_estados_finais );

    printf("\n");

    int estados_finais[q_estados_finais];

    for(i = 0; i < q_estados_finais; i++){

        printf( "Qual o estado final %i?", i );
        scanf(" %i", &estados_finais[i]);
    }

    printf("\n");
    printf("Qual o estado inicial?");
    scanf(" %i", &estado_inicial);

    system("cls");

    printf("TABELA DE ESTADOS:\n");
    printf("Utilize -1 para simbolo sem transicao!\n");

    int tabela_estados[q_simbolos][q_estados];

    for( i = 0; i < q_estados; i++){


        for( j = 0; j < q_simbolos; j++){

            printf("Para o estado e%i e Simbolo %c, qual o proximo estado?", i, simbolos[j]);
            scanf(" %i", &tabela_estados[j][i]);
        }
    }

    printf("\n");

    printf("Para gerar com GOTO digite 1 \nPara Gerar com Funcao digite 2:");
    scanf(" %i", &tipo);

    printf("\n");
    printf("Digite o nome do Arquivo:");

    scanf(" %s", &name);

    FILE *fp;

    if( tipo == 2 ){

        if ((fp = fopen ( name, "wt"))==NULL)
        {
            printf("Erro na criacao do arquivo\n");
            getch();
            exit(0);
        }

        fprintf(fp, "#include <stdio.h>\n");
        fprintf(fp, "#include <conio.h>\n\n");


        fprintf(fp, "void aceita();\n");
        fprintf(fp, "void rejeita();\n");

        for(i =0; i < q_estados; i++)
        {
            fprintf(fp,"void e%d();\n",i);
        }
        fprintf(fp,"\n");

        fprintf(fp,"int p;\n");
        fprintf(fp,"char f[200];\n");

        fprintf(fp,"\n");

        fprintf(fp, "int main(){");
        fprintf(fp, "\n\tprintf(\"Palavra:\");\n");
        fprintf(fp, "\tgets(f);\n");
        fprintf(fp, "\tp = 0;\n");
        fprintf(fp, "\te%d();\n",estado_inicial);
        fprintf(fp, "\treturn(0);\n}\n\n");

        fprintf(fp,"void aceita(){\n\tprintf(\"Aceita!!!\");\n\tgetch();\n}\n\n");
        fprintf(fp,"void rejeita(){\n\tprintf(\"Rejeita!!!\");\n\tgetch();\n}\n\n");

        for(i = 0; i < q_estados; i++){

            fprintf(fp, "void e%d(){",i);

            int cont = 0;

            for(j = 0; j < q_simbolos; j++){

                if( tabela_estados[j][i] != (-1)){

                    if(cont == 0){

                        fprintf(fp, "\n\tif( f[p] == \'%c\'){\n\t",simbolos[j]);
                        fprintf(fp, "\tp++;\n");
                        fprintf(fp, "\t\te%d();\n\t}", tabela_estados[j][i]);
                        cont = 1;
                    }
                    else{

                        fprintf(fp, "\n\telse if( f[p] == \'%c\'){\n\t",simbolos[j]);
                        fprintf(fp, "\tp++;\n");
                        fprintf(fp, "\t\te%d();\n\t}", tabela_estados[j][i]);
                    }

                }

            }

            for( w = 0; w < q_estados_finais; w++ ){

                if( i == estados_finais[w]){
                    fprintf(fp, "\n\telse if( f[p] == 0){\n\t");
                    fprintf(fp, "\taceita();\n");
                    fprintf(fp, "\t}");
                }
            }

            fprintf(fp, "\n\telse{\n\t\trejeita();\n\t}\n}\n");
        }

        fclose(fp);

        printf("Gravado com funcao!!!");
        getch();

    }
    else{

        if ((fp = fopen ( name, "wt"))==NULL)
        {
            printf("Erro na criacao do arquivo\n");
            getch();
            exit(0);
        }

        //vou gravar linhas de texto
        fprintf(fp, "#include <stdio.h>\n");
        fprintf(fp, "#include <conio.h>\n");

        fprintf(fp,"\n");

        fprintf(fp, "int main(){");
        fprintf(fp, "\n\n\tprintf(\"Palavra:\");\n");
        fprintf(fp, "\n\tint p;\n");
        fprintf(fp, "\tchar f[200];\n\n");
        fprintf(fp, "\tgets(f);\n");
        fprintf(fp, "\tp = 0;\n\n");
        fprintf(fp, "\tgoto E%d;\n\n",estado_inicial);

        for(i = 0; i < q_estados; i++){

            fprintf(fp, "\tE%d:",i);

            int cont = 0;

            for(j = 0; j < q_simbolos; j++){

                if( tabela_estados[j][i] != (-1)){

                    if(cont == 0){

                        fprintf(fp, "\n\t\tif( f[p] == \'%c\'){\n\t",simbolos[j]);
                        fprintf(fp, "\t\tp++;\n");
                        fprintf(fp, "\t\t\tgoto E%d;\n\t\t}", tabela_estados[j][i]);
                        cont = 1;
                    }
                    else{

                        fprintf(fp, "\t\n\t\telse if( f[p] == \'%c\'){\n\t",simbolos[j]);
                        fprintf(fp, "\t\tp++;\n");
                        fprintf(fp, "\t\t\tgoto E%d;\n\t\t}", tabela_estados[j][i]);
                    }

                }

            }

            for( w = 0; w < q_estados_finais; w++ ){

                if( i == estados_finais[w]){
                    fprintf(fp, "\t\n\t\telse if( f[p] == 0){\n\t");
                    fprintf(fp, "\t\tgoto ACEITA;\n");
                    fprintf(fp, "\t\t}");
                }
            }

            fprintf(fp, "\n\t\telse{\n\t\t\tgoto REJEITA;\n\t\t}\n\n");
        }

        fprintf(fp,"\tACEITA:\n\n\t\tprintf(\"Aceita!!!\");\n\t\tgetch();\n\t\treturn 0;\n\n");
        fprintf(fp,"\tREJEITA:\n\n\t\tprintf(\"Rejeita!!!\");\n\t\tgetch();\n\t\treturn 0;\n}\n\n");

        fclose(fp);

        printf("Gravado com GOTO!!!");
        getch();

    }

    return 0;
}

