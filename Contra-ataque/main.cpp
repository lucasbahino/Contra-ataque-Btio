#include "comandos.h"

using namespace std;

enum Gesture { DEFESA, CARREGAR, ATIRAR };

class Player {
public:
	Player(int vidas) : vidas(vidas), municao(0) {}
	virtual Gesture escolherGesto() = 0;
	void perderVida() { vidas--; }
	void carregarArma() { municao++; }
	void usarMunicao() { if (municao > 0) municao--; }
	int getVidas() const { return vidas; }
	int getMunicao() const { return municao; }

protected:
	int vidas;
	int municao;
};

class HumanPlayer : public Player {
public:
	HumanPlayer(int vidas) : Player(vidas) {}
	Gesture escolherGesto() override {
		int escolha;
		do {
			cout << "Escolha seu gesto: (0: DEFESA, 1: CARREGAR, 2: ATIRAR): ";
			cin >> escolha;
			if (escolha == 2 && municao == 0) {
				cout << "Voce nao tem municao para atirar. Escolha outro gesto." << endl;
			}
		} while (escolha == 2 && municao == 0);
		return static_cast<Gesture>(escolha);
	}
};

class ComputerPlayer : public Player {
public:
	ComputerPlayer(int vidas) : Player(vidas) {}
	Gesture escolherGesto() override {
		if (municao > 0) {
			return static_cast<Gesture>(rand() % 3);
		}
		else {
			return static_cast<Gesture>(rand() % 2); // Apenas DEFESA ou CARREGAR
		}
	}
};

class Game {
public:
	Game() : player(new HumanPlayer(3)), computer(new ComputerPlayer(3)) {
		srand(time(0));
	}
	~Game() {
		delete player;
		delete computer;
	}
	void run() {
		string input;
		while (player->getVidas() > 0 && computer->getVidas() > 0) {
			clearScreen();
			mostrarStatus();

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
					mostrarMensagem("Comando invalido. Tente novamente.");
					continue;
				}

				if (escolha < 0 || escolha > 2) {
					mostrarMensagem("Comando invalido. Tente novamente.");
					continue;
				}

				if (escolha == 2 && player->getMunicao() == 0) {
					mostrarMensagem("Voce nao tem municao para atirar. Escolha outro gesto.");
					continue;
				}

				Gesture playerGesto = static_cast<Gesture>(escolha);
				Gesture computerGesto = computer->escolherGesto();

				clearScreen();
				cout << "Voce escolheu: " << gestureToString(playerGesto) << endl;
				cout << "Computador escolheu: " << gestureToString(computerGesto) << endl;

				processarAcoes(playerGesto, computerGesto);

				esperar(3);
			}
		}

		mostrarResultado();
	}

private:
	Player* player;
	Player* computer;

	void mostrarStatus() const {
		cout << "Vidas do Jogador: " << player->getVidas() << " | Municao: " << player->getMunicao() << endl;
		cout << "Vidas do Computador: " << computer->getVidas() << " | Municao: " << computer->getMunicao() << endl;
	}

	void mostrarMensagem(const string& mensagem) const {
		clearScreen();
		cout << mensagem << endl;
		esperar(2);
	}

	void processarAcoes(Gesture playerGesto, Gesture computerGesto) {
		if (playerGesto == ATIRAR && computerGesto == CARREGAR) {
			computer->perderVida();
			cout << "Voce acertou o computador!" << endl;
		}
		else if (playerGesto == CARREGAR && computerGesto == ATIRAR) {
			player->perderVida();
			cout << "Voce foi atingido pelo computador!" << endl;
		}
		else if (playerGesto == ATIRAR) {
			player->usarMunicao();
			if (computerGesto != DEFESA) {
				computer->perderVida();
				cout << "Voce acertou o computador!" << endl;
			}
			else {
				cout << "Computador defendeu seu tiro!" << endl;
			}
		}
		else if (playerGesto == CARREGAR) {
			player->carregarArma();
			cout << "Voce carregou sua arma!" << endl;
		}

		if (computerGesto == ATIRAR && computer->getMunicao() > 0) {
			computer->usarMunicao();
			if (playerGesto != DEFESA) {
				player->perderVida();
				cout << "Computador acertou voce!" << endl;
			}
			else {
				cout << "Voce defendeu o tiro do computador!" << endl;
			}
		}
		else if (computerGesto == CARREGAR) {
			computer->carregarArma();
			cout << "Computador carregou a arma!" << endl;
		}
	}

	string gestureToString(Gesture gesture) const {
		switch (gesture) {
		case DEFESA: return "DEFESA";
		case CARREGAR: return "CARREGAR";
		case ATIRAR: return "ATIRAR";
		default: return "UNKNOWN";
		}
	}

	void mostrarResultado() const {
		clearScreen();
		if (player->getVidas() == 0) {
			cout << "Voce perdeu!" << endl;
		}
		else if (computer->getVidas() == 0) {
			cout << "Voce venceu!" << endl;
		}
		cout << "Pressione Enter para voltar ao menu.";
		cin.ignore();
		cin.get();
	}
};

int main() {
	int choice;

	do {
		clearScreen();
		showMenu();
		cout << "Escolha uma opcao: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			Game game;
			game.run();
			break;
		}
		case 2:
			showInstructions();
			break;
		case 3:
			cout << "Saindo do jogo..." << endl;
			break;
		default:
			cout << "Opcao invalida. Tente novamente." << endl;
			esperar(2);
		}
	} while (choice != 3);

	return 0;
}