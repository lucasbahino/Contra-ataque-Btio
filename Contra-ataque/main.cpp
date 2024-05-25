#include <iostream>
#include "comandos.h"
#include "jogadores.h"

int main() {
    int choice;

    do {
        clearScreen();
        showMenu();
        std::cout << "Escolha uma opcao: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            runGame();
            break;
        case 2:
            showInstructions();
            break;
        case 3:
            std::cout << "Saindo do jogo..." << std::endl;
            break;
        default:
            std::cout << "Opcao invalida. Tente novamente." << std::endl;
            esperar(2);
        }
    } while (choice != 3);

    return 0;
}
