#ifndef PONTUACAO_H
#define PONTUACAO_H

#include "comandos.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Leaderboard {
	string nome = "";
	int pontos = 0;
};

void salvarDados(string nome, int pontos) {
	Leaderboard lb;
	lb.nome = nome;
	lb.pontos = pontos;

	ofstream file("Leaderboard.txt", std::ios::app);
	if (file.is_open()) {
		printf("Leaderboard carregada.\n");
		esperar(2);
	}
	else {
		printf("Erro ao abrir Leaderboard.\n");
		esperar(2);
		return;
	}

	file << "\n" <<"Nome: " << lb.nome << ", Pontos: " << lb.pontos;
	file.close();
}

bool comparar(const Leaderboard& a, const Leaderboard& b) {
	return b.pontos < a.pontos;
}


#endif // PONTUACAO_H
