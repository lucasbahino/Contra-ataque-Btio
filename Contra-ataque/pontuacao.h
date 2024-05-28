#ifndef PONTUACAO_H
#define PONTUACAO_H

#include "comandos.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>

typedef struct Leaderboard
{
	char nome;
	int pontos = 0;
}Leaderboard;

void salvarDados(Leaderboard* lb) {
	FILE* file = fopen("Leaderboard.txt", "a");
	if (file == NULL) {
		printf("Não foi possível abrir o arquivo.\n");
		return;
	}
	fprintf(file, "Nome: %s, Pontos: %d\n", lb->nome, lb->pontos);
	fclose(file); // Fecha o arquivo
}

int comparar(const void* a, const void* b) {
	Leaderboard* lbA = (Leaderboard*)a;
	Leaderboard* lbB = (Leaderboard*)b;
	return lbB->pontos - lbA->pontos;
}

void showPontuacao() {
	clearScreen();
	FILE* file = fopen("Leaderboard.txt", "r");
	if (file == NULL) {
		printf("Não foi possível abrir o arquivo.\n");
		return;
	}

	// Carrega os dados do arquivo em um array
	Leaderboard lb[100]; // Supondo que haja no máximo 100 entradas
	int i = 0;
	while (fscanf(file, "Nome: %s, Pontos: %d\n", lb[i].nome, &lb[i].pontos) != EOF) {
		i++;
	}
	int n = i;

	// Classifica o array com base na pontuação
	qsort(lb, n, sizeof(Leaderboard), comparar);

	// Exibe os dados
	for (i = 0; i < n; i++) {
		printf("Nome: %s, Pontos: %d\n", lb[i].nome, lb[i].pontos);
	}

	fclose(file);
}

#endif // PONTUACAO_H