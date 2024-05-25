#ifndef COMANDOS_H
#define COMANDOS_H

#include <iostream>
#include <windows.h>

using namespace std;

void clearScreen() {
    system("cls");
}

void esperar(int segundos) {
    Sleep(segundos * 1000);
}

void showMenu() {
    cout << "----------------------------" << endl;
    cout << "        Jogo de Gestos      " << endl;
    cout << "----------------------------" << endl;
    cout << "1. Entrar no jogo" << endl;
    cout << "2. Sobre o jogo" << endl;
    cout << "3. Sair" << endl;
}

void showInstructions() {
    clearScreen();
    cout << "----------------------------" << endl;
    cout << "      Instrucoes do Jogo    " << endl;
    cout << "----------------------------" << endl;
    cout << "1. Cruzar os bracos sobre o peito: DEFESA" << endl;
    cout << "2. Colocar as maos para cima e mover os dedos: CARREGAR" << endl;
    cout << "3. Apontar as maos em formato de arma: ATIRAR" << endl;
    cout << "Perde quem estiver carregando a arma quando o outro estiver atirando." << endl;
    cout << "Cada jogador tem 3 vidas e municao." << endl;
    cout << "Pressione Enter para voltar ao menu.";
    cin.ignore();
    cin.get();
}

#endif // COMANDOS_H
