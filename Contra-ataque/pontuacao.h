#ifndef PONTUACAO_H
#define PONTUACAO_H

#include "comandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[50];
    int pontos;
} Leaderboard;

void salvarDados(char* nome, int pontos) {
	Leaderboard lb;
	strcpy(lb.nome, nome);
	lb.pontos = pontos;

	FILE* file = fopen("Leaderboard.txt", "a");
	if (file != NULL) {
		printf("Leaderboard carregada.\n");
		esperar(2);
	}
	else {
		printf("Erro ao abrir Leaderboard.\n");
		esperar(2);
		return;
	}

	fprintf(file, "\nNome: %s, Pontos: %d", lb.nome, lb.pontos);
	fclose(file);
}

int compareScores(const void* a, const void* b) {
    Leaderboard* lbA = (Leaderboard*) a;
    Leaderboard* lbB = (Leaderboard*) b;
    return lbB->pontos - lbA->pontos; // Ordenar do maior para o menor
}

void showScores() {
    system("cls");
    printf("----------------------------\n");
    printf("        Pontuacoes          \n");
    printf("----------------------------\n");

    FILE* file = fopen("Leaderboard.txt", "r");
    if (!file) {
        printf("Erro ao abrir o arquivo de pontuacoes.\n");
        return;
    }

    Leaderboard* scores = (Leaderboard*) malloc(sizeof(Leaderboard));
    int count = 0;
    char line[100];

    while (fgets(line, sizeof(line), file)) {
        char* namePos = strstr(line, "Nome: ");
        char* pointsPos = strstr(line, ", Pontos: ");
        if (namePos && pointsPos) {
            scores = (Leaderboard*) realloc(scores, (count + 1) * sizeof(Leaderboard));
            int nameLength = pointsPos - (namePos + 6);
            strncpy(scores[count].nome, namePos + 6, nameLength);
            scores[count].nome[nameLength] = '\0'; // Adiciona o caractere nulo no final
            scores[count].pontos = atoi(pointsPos + 9);
            count++;
        }
    }

    qsort(scores, count, sizeof(Leaderboard), compareScores);

    for (int i = 0; i < count; i++) {
        printf("Nome: %s, Pontos: %d\n", scores[i].nome, scores[i].pontos);
    }

    free(scores);

    printf("Pressione Enter para voltar ao menu.\n");
    getchar();
    getchar(); 
}


#endif // PONTUACAO_H
