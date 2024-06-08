#include <iostream>
#include "comandos.h"
#include "jogadores.h"

Difficulty escolherDificuldade() {
    int escolha;
    showDifficultyMenu();
    cout << "Escolha uma opcao: ";
    cin >> escolha;
    switch (escolha) {
    case 1:
        return FACIL;
    case 2:
        return MEDIO;
    case 3:
        return DIFICIL;
    default:
        cout << "Opcao invalida. Escolhendo dificuldade media por padrao." << endl;
        return MEDIO;
    }
}

int main() {
    int choice;
    Difficulty dificuldade = MEDIO; // Default difficulty

    do {
        clearScreen();
        showMenu();
        cout << "Escolha uma opcao: ";
        cin >> choice;

        switch (choice) {
        case 1:
            runGame(dificuldade); // Passar a dificuldade escolhida
            break;
        case 2:
            dificuldade = escolherDificuldade();
            break;
        case 3:
            showInstructions();
            break;
        case 4:
            showScores();
            break;
        case 5:
            cout << "Saindo do jogo..." << endl;
            break;
        default:
            cout << "Opcao invalida. Tente novamente." << endl;
            esperar(2);
        }
    } while (choice != 5);

    return 0;
}
