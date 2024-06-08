#ifndef COMANDOS_H
#define COMANDOS_H

#include <stdio.h>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>

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
    printf("Pressione Enter para voltar ao menu.\n");
    getchar(); 
    getchar(); 

}

void showScores() {
    clearScreen();
    printf("----------------------------\n");
    printf("        Pontuacoes          \n");
    printf("----------------------------\n");

    ifstream file("Leaderboard.txt");
    if (!file) {
        printf("Erro ao abrir o arquivo de pontuacoes.\n");
        return;
    }

    vector<pair<string, int>> scores;
    string line;

    while (getline(file, line)) {
        size_t namePos = line.find("Nome: ");
        size_t pointsPos = line.find(", Pontos: ");
        if (namePos != string::npos && pointsPos != string::npos) {
            string name = line.substr(namePos + 6, pointsPos - (namePos + 6));
            int points = stoi(line.substr(pointsPos + 9));
            scores.push_back(make_pair(name, points));
        }
    }

    sort(scores.begin(), scores.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return b.second < a.second; // Ordenar do maior para o menor
    });

    for (const auto& score : scores) {
        printf("Nome: %s, Pontos: %d\n", score.first.c_str(), score.second);
    }

    printf("Pressione Enter para voltar ao menu.\n");
    getchar();
    getchar(); 
}

#endif // COMANDOS_H
