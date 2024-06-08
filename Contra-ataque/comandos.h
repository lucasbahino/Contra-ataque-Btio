#ifndef COMANDOS_H
#define COMANDOS_H

#include <iostream>
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
    cout << "----------------------------" << endl;
    cout << "        Jogo de Gestos      " << endl;
    cout << "----------------------------" << endl;
    cout << "1. Entrar no jogo" << endl;
    cout << "2. Escolher dificuldade" << endl;
    cout << "3. Sobre o jogo" << endl;
    cout << "4. Ver pontuacoes" << endl;
    cout << "5. Sair" << endl;
}

void showDifficultyMenu() {
    clearScreen();
    cout << "----------------------------" << endl;
    cout << "       Escolha Dificuldade   " << endl;
    cout << "----------------------------" << endl;
    cout << "1. Facil" << endl;
    cout << "2. Medio" << endl;
    cout << "3. Dificil" << endl;
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

void showScores() {
    clearScreen();
    cout << "----------------------------" << endl;
    cout << "        Pontuacoes          " << endl;
    cout << "----------------------------" << endl;

    ifstream file("Leaderboard.txt");
    if (!file) {
        cout << "Erro ao abrir o arquivo de pontuacoes." << endl;
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
        cout << "Nome: " << score.first << ", Pontos: " << score.second << endl;
    }

    cout << "Pressione Enter para voltar ao menu.";
    cin.ignore();
    cin.get();
}

#endif // COMANDOS_H
