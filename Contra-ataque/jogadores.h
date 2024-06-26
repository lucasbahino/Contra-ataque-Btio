#ifndef JOGADORES_H
#define JOGADORES_H

#include "pontuacao.h"
#include "imagens.h" 
#include <stdio.h>
#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <string>  
#include <string.h>
#include "comandos.h"

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
        printf("Escolha seu gesto: (0: DEFESA, 1: CARREGAR, 2: ATIRAR): ");
        scanf("%d", &escolha);
        if (escolha == 2 && player->municao == 0) {
            printf("Voce nao tem municao para atirar. Escolha outro gesto.\n");
        }
    } while (escolha == 2 && player->municao == 0);
    return static_cast<Gesture>(escolha);
}

Gesture escolherGestoComputador(const Player* computer, Difficulty difficulty) {
    int choice;
    switch (difficulty) {
    case FACIL:
        if (computer->municao > 0) {
            choice = rand() % 3; 
        }
        else {
            choice = rand() % 2; 
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
                choice = ATIRAR; 
            }
            else {
                choice = rand() % 3;
            }
        }
        else {
            choice = CARREGAR; 
        }
        break;
    }
    return static_cast<Gesture>(choice);
}

void mostrarStatus(const Player* jogador, const Player* computador) {
    printf("Vidas do Jogador: %d | Municao: %d\n", jogador->vidas, jogador->municao);
    printf("Vidas do Computador: %d | Municao: %d\n", computador->vidas, computador->municao);
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
    
    printf("Acao do jogador: ");
    switch (playerGesto) {
        case ATIRAR:
            exibirAtirar();
            break;
        case CARREGAR:
            exibirCarregar();
            break;
        case DEFESA:
            exibirDefesa();
            break;
    }

    
    printf("Acao do computador: ");
    switch (computerGesto) {
        case ATIRAR:
            exibirAtirar();
            break;
        case CARREGAR:
            exibirCarregar();
            break;
        case DEFESA:
            exibirDefesa();
            break;
    }

  
    if (playerGesto == ATIRAR) {
        jogador->municao--;
        if (computerGesto == CARREGAR || computerGesto == ATIRAR) {
            computador->vidas--;
        }
    } else if (playerGesto == CARREGAR) {
        jogador->municao++;
    }

    if (computerGesto == ATIRAR && computador->municao > 0) {
        computador->municao--;
        if (playerGesto != DEFESA) {
            jogador->vidas--;
        }
    } else if (computerGesto == CARREGAR) {
        computador->municao++;
    }
}


void mostrarResultado(const Player* jogador, const Player* computador, int pontos) {
    char nome[50];

    if (jogador->vidas == 0) {
        clearScreen();
        printf("Voce perdeu!");
        esperar(5);
    }
    else if (computador->vidas == 0) {
        printf("Voce venceu!\n");
        printf("Pontuacao de %d\n", pontos);
        esperar(5);
        clearScreen();
        printf("Digite seu Nome:");
        scanf("%s", nome);

        salvarDados(nome, pontos);
    }
    clearScreen();
    printf("Pressione Enter para voltar ao menu.");
    getchar();
    getchar();
}

void runGame(Difficulty dificuldade) {
    turnos = 0;
    int jogadorVidasIniciais = 3;
    int jogadorBalasIniciais = 0;
    int pontos = 0 + (120 * dificuldade);

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

        printf("\nTurno = %d", turnos + 1); 
        printf("\nPontuacao = %d", pontos);
        printf("\nDigite seu comando (0: DEFESA, 1: CARREGAR, 2: ATIRAR, sair, pause): ");
        cin >> input;

        if (input == "sair") {
            break;
        }
        else if (input == "pause" || input == "pausa") {
            clearScreen();
            printf("Jogo pausado. Deseja continuar? (sim/nao): ");
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
                printf("Comando invalido. Tente novamente.\n");
                esperar(2);
                continue;
            }

            if (escolha < 0 || escolha > 2) {
                printf("Comando invalido. Tente novamente.\n");
                esperar(2);
                continue;
            }

            if (escolha == 2 && pJogador->municao == 0) {
                printf("Voce nao tem municao para atirar. Escolha outro gesto.\n");
                esperar(2);
                continue;
            }

            turnos++; 

            pontos += turnos * 15 + pJogador->vidas * 33; 
            if(turnos == 1){
                pontos = 0;
            }

            Gesture playerGesto = static_cast<Gesture>(escolha);
            Gesture computerGesto = escolherGestoComputador(pComputador, dificuldade);

            clearScreen();
           
            
            processarAcoes(pJogador, pComputador, playerGesto, computerGesto);
			
			pressCtrlHome();
			
            esperar(3);
        }
    }

    mostrarResultado(pJogador, pComputador, pontos);
}


#endif 
