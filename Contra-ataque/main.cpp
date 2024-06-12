#include <stdio.h>
#include "comandos.h"
#include "jogadores.h"

Difficulty escolherDificuldade() {
    int escolha;
    showDifficultyMenu();
    printf("Escolha uma opcao: ");
    scanf("%d", &escolha);
    switch (escolha) {
    case 1:
        return FACIL;
    case 2:
        return MEDIO;
    case 3:
        return DIFICIL;
    default:
        printf("Opcao invalida. Escolhendo dificuldade media por padrao.\n");
        return MEDIO;
    }
}

int main() {
    int choice;
    Difficulty dificuldade = MEDIO; 

    do {
        clearScreen();
        showMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

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
            printf("Saindo do jogo...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            esperar(2);
        }
    } while (choice != 5);

    return 0;
}
