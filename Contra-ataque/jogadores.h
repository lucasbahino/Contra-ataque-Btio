#ifndef JOGADORES_H
#define JOGADORES_H

#include <iostream>
#include <cstdlib> // para srand e rand
#include <ctime>   // para time
#include <string>  // para std::string

using namespace std;

enum Gesture { DEFESA, CARREGAR, ATIRAR };

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

Gesture escolherGestoComputador(const Player* computer) {
    if (computer->municao > 0) {
        return static_cast<Gesture>(rand() % 3);
    }
    else {
        return static_cast<Gesture>(rand() % 2); // Apenas DEFESA ou CARREGAR
    }
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
    if (jogador->vidas == 0) {
        cout << "Voce perdeu!" << endl;
    }
    else if (computador->vidas == 0) {
        cout << "Voce venceu!" << endl;
    }
    cout << "Pressione Enter para voltar ao menu.";
    cin.ignore();
    cin.get();
}

void runGame() {
    Player jogador = { 3, 0 };
    Player computador = { 3, 0 };
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
            Gesture computerGesto = escolherGestoComputador(pComputador);

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
