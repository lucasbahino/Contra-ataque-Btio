#ifndef JOGADORES_H
#define JOGADORES_H

#include "pontuacao.h"
#include <iostream>
#include <cstdlib> // para srand e rand
#include <ctime>   // para time
#include <string>  // para std::string

using namespace std;

enum Gesture { DEFESA, CARREGAR, ATIRAR };
int turnos = 0;

enum Difficulty {
	FACIL,
	MEDIO,
	DIFICIL
};


struct Player {
	int vidas;
	int municao;
};

Gesture escolherGestoJogador(const Player* player) {
	int escolha;
	do {
		cout << "Escolha seu gesto: (0: DEFESA, 1: CARREGAR, 2: ATIRAR): ";
		cin >> escolha;
		if (escolha == 2 && player->municao == 0) {
			cout << "Voce nao tem municao para atirar. Escolha outro gesto." << endl;
		}
	} while (escolha == 2 && player->municao == 0);
	return static_cast<Gesture>(escolha);
}

Gesture escolherGestoComputador(const Player* computer, Difficulty difficulty) {
	int choice;
	switch (difficulty) {
	case FACIL:
		if (computer->municao > 0) {
			choice = rand() % 3; // Random choice among DEFESA, CARREGAR, ATIRAR
		}
		else {
			choice = rand() % 2; // Random choice among DEFESA, CARREGAR
		}
		break;
	case MEDIO:
		if (computer->municao > 0) {
			choice = rand() % 3;
		}
		else {
			choice = rand() % 2;
		}
		break;
	case DIFICIL:
		if (computer->municao > 0) {
			if (computer->vidas < 2) {
				choice = ATIRAR; // Aggressive if low on lives
			}
			else {
				choice = rand() % 3;
			}
		}
		else {
			choice = CARREGAR; // Prefer loading if no ammo
		}
		break;
	}
	return static_cast<Gesture>(choice);
}


void mostrarStatus(const Player* jogador, const Player* computador) {
	cout << "Vidas do Jogador: " << jogador->vidas << " | Municao: " << jogador->municao << endl;
	cout << "Vidas do Computador: " << computador->vidas << " | Municao: " << computador->municao << endl;
}

string gestureToString(Gesture gesture) {
	switch (gesture) {
	case DEFESA: return "DEFESA";
	case CARREGAR: return "CARREGAR";
	case ATIRAR: return "ATIRAR";
	default: return "UNKNOWN";
	}
}

void processarAcoes(Player* jogador, Player* computador, Gesture playerGesto, Gesture computerGesto) {
	if (playerGesto == ATIRAR && computerGesto == CARREGAR) {
		computador->vidas--;
		cout << "Voce acertou o computador!" << endl;
	}
	else if (playerGesto == CARREGAR && computerGesto == ATIRAR) {
		jogador->vidas--;
		cout << "Voce foi atingido pelo computador!" << endl;
	}
	else if (playerGesto == ATIRAR) {
		jogador->municao--;
		if (computerGesto != DEFESA) {
			computador->vidas--;
			cout << "Voce acertou o computador!" << endl;
		}
		else {
			cout << "Computador defendeu seu tiro!" << endl;
		}
	}
	else if (playerGesto == CARREGAR) {
		jogador->municao++;
		cout << "Voce carregou sua arma!" << endl;
	}

	if (computerGesto == ATIRAR && computador->municao > 0) {
		computador->municao--;
		if (playerGesto != DEFESA) {
			jogador->vidas--;
			cout << "Computador acertou voce!" << endl;
		}
		else {
			cout << "Voce defendeu o tiro do computador!" << endl;
		}
	}
	else if (computerGesto == CARREGAR) {
		computador->municao++;
		cout << "Computador carregou a arma!" << endl;
	}
}

void mostrarResultado(const Player* jogador, const Player* computador) {
	string nome;
	int pontos = 9960 - (turnos * 10) + (jogador->vidas * 33);

	if (jogador->vidas == 0) {
		cout << "Voce perdeu!" << endl;
	}
	else if (computador->vidas == 0) {
		cout << "Voce venceu!" << endl;
		cout << "Pontuacao de " << pontos << endl;
		esperar(5);
		clearScreen();
		cout << "Digite seu Nome.";
		cin >> nome;

		salvarDados(nome, pontos);
	}
	cout << "Pressione Enter para voltar ao menu.";
	cin.ignore();
	cin.get();
}

void runGame(Difficulty dificuldade) {
	int jogadorVidasIniciais = 3;
	int jogadorBalasIniciais = 0;

	int computadorVidasIniciais = 3 + dificuldade;
	int computadorBalasIniciais = 0 + dificuldade / 2;

	Player jogador = { jogadorVidasIniciais, jogadorBalasIniciais };
	Player computador = { computadorVidasIniciais, computadorBalasIniciais };

	srand(time(0));

	Player* pJogador = &jogador;
	Player* pComputador = &computador;

	string input;
	while (pJogador->vidas > 0 && pComputador->vidas > 0) {
		clearScreen();
		mostrarStatus(pJogador, pComputador);

		cout << "Digite seu comando (0: DEFESA, 1: CARREGAR, 2: ATIRAR, sair, pause): ";
		cin >> input;

		if (input == "sair") {
			break;
		}
		else if (input == "pause" || input == "pausa") {
			clearScreen();
			cout << "Jogo pausado. Deseja continuar? (sim/nao): ";
			cin >> input;
			if (input == "nao") {
				break;
			}
			else {
				continue;
			}
		}
		else {
			int escolha;
			try {
				escolha = stoi(input);
			}
			catch (...) {
				cout << "Comando invalido. Tente novamente." << endl;
				esperar(2);
				continue;
			}

			if (escolha < 0 || escolha > 2) {
				cout << "Comando invalido. Tente novamente." << endl;
				esperar(2);
				continue;
			}

			if (escolha == 2 && pJogador->municao == 0) {
				cout << "Voce nao tem municao para atirar. Escolha outro gesto." << endl;
				esperar(2);
				continue;
			}

			Gesture playerGesto = static_cast<Gesture>(escolha);
			Gesture computerGesto = escolherGestoComputador(pComputador, dificuldade);

			clearScreen();
			cout << "Voce escolheu: " << gestureToString(playerGesto) << endl;
			cout << "Computador escolheu: " << gestureToString(computerGesto) << endl;

			processarAcoes(pJogador, pComputador, playerGesto, computerGesto);

			esperar(3);
		}
	}

	mostrarResultado(pJogador, pComputador);
}



#endif // JOGADORES_H
