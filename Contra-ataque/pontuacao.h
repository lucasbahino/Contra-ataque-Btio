#ifndef PONTUACAO_H
#define PONTUACAO_H

#include "comandos.h"
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
		cout << "Leaderboard carregada.\n";
		esperar(2);
	}
	else {
		cout << "Erro ao abrir Leaderboard.\n";
		esperar(2);
		return;
	}

	file << "Nome: " << lb.nome << ", Pontos: " << lb.pontos << "\n";
	file.close();
}

bool comparar(const Leaderboard& a, const Leaderboard& b) {
	return b.pontos < a.pontos;
}

void showPontuacao() {
	clearScreen();
	ifstream file("Leaderboard.txt");
	if (file.is_open()) {
		cout << "Leaderboard carregada.\n";
		esperar(2);
	}
	else {
		cout << "Erro ao abrir Leaderboard.\n";
		esperar(2);
		return;
	}

	vector<Leaderboard> lb;
	Leaderboard temp;
	while (file >> temp.nome >> temp.pontos) {
		lb.push_back(temp);
	}

	sort(lb.begin(), lb.end(), comparar);

	for (const auto& l : lb) {
		cout << "Nome: " << l.nome << ", Pontos: " << l.pontos << endl;
	}
	esperar(2);
	file.close();
}

#endif // PONTUACAO_H
