#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_NOTAS 10

typedef struct {
    char nome[MAX_NOME];
    float notas[MAX_NOTAS];
    int num_notas;
    float media;
    char situacao[20];
} Aluno;

void calcularMedia(Aluno *aluno) {
    float soma = 0.0;
    for (int i = 0; i < aluno->num_notas; i++) {
        soma += aluno->notas[i];
    }
    aluno->media = soma / aluno->num_notas;
}

void determinarSituacao(Aluno *aluno) {
    if (aluno->media >= 7.0) {
        strcpy(aluno->situacao, "APROVADO");
    } else {
        strcpy(aluno->situacao, "REPROVADO");
    }
}

int main() {
    FILE *entrada = fopen("DadosEntrada.csv", "r");
    FILE *saida = fopen("SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    // Ignorar a primeira linha do arquivo de entrada
    char ignorar_linha[1000];
    fgets(ignorar_linha, sizeof(ignorar_linha), entrada);

    char linha[1000];
    while (fgets(linha, sizeof(linha), entrada)) {
        Aluno aluno;
        char *token = strtok(linha, ",");
        strcpy(aluno.nome, token);
        aluno.num_notas = 0;

        // Ignorar as colunas Telefone e Curso
        token = strtok(NULL, ",");
        token = strtok(NULL, ",");

        // Ler as notas
        while ((token = strtok(NULL, ",")) != NULL) {
            aluno.notas[aluno.num_notas++] = atof(token);
        }
        calcularMedia(&aluno);
        determinarSituacao(&aluno);
        fprintf(saida, "%s, %.2f, %s\n", aluno.nome, aluno.media, aluno.situacao);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
