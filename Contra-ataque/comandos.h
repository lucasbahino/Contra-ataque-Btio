#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include "imagens.h" 

using namespace std;

void clearScreen() {
    system("cls");
}

void esperar(int segundos) {
    Sleep(segundos * 1000);
}

void showMenu() {
    printf("----------------------------\n");
    printf("        Jogo de Gestos      \n");
    printf("----------------------------\n");
    printf("1. Entrar no jogo\n");
    printf("2. Escolher dificuldade\n");
    printf("3. Sobre o jogo\n");
    printf("4. Ver pontuacoes\n");
    printf("5. Sair\n");
}

void showDifficultyMenu() {
    clearScreen();
    printf("----------------------------\n");
    printf("       Escolha Dificuldade   \n");
    printf("----------------------------\n");
    printf("1. Facil\n");
    printf("2. Medio\n");
    printf("3. Dificil\n");
}

void showInstructions() {
    clearScreen();
    printf("----------------------------\n");
    printf("      Instrucoes do Jogo    \n");
    printf("----------------------------\n");
    printf("1. Cruzar os bracos sobre o peito: DEFESA\n");
    printf("2. Colocar as maos para cima e mover os dedos: CARREGAR\n");
    printf("3. Apontar as maos em formato de arma: ATIRAR\n");
    printf("Perde quem estiver carregando a arma quando o outro estiver atirando.\n");
    printf("Cada jogador tem 3 vidas e municao.\n");
    esperar(1);
    printf("IMAGENS DOS GESTOS\n");
    esperar(1);
    printf("ATIRAR:\n");
    exibirAtirar();
    esperar(3);
    printf("CARREGAR:\n");
    exibirCarregar();
    esperar(3);
	printf("DEFENDER:\n");
    exibirDefesa();
    printf("Pressione Enter para voltar ao menu.\n");
	getchar(); 
    getchar(); 

}

#endif // COMANDOS_H
