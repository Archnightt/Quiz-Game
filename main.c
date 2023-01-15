#include <conio.h>
#include <stdio.h>

#include "quizpages.h"

/**
 * Starts the quiz game loop.
 */
void startGame() {
    helpPage();
    int topic = topicPage() - 1;

    if (topic < 0 || topic >= categoriesCount) {
        clrscr();

        int width = 61;
        printDividers(width, 4);
        printTextCentered(width, 5, "Topic Error");
        printDividers(width, 6);

        printTextCentered(width, 7, "Please make sure you enter a valid topic number.");
        printDividers(width, 8);

        gotoRowCol(10, 4);
        printf("Press any key to continue.");

        getch();
        return;
    }

    int total = 0, correct = 0, questionsDone[20];
}

int main(void) {
    while (1) {
        char selected = homePage();
        switch (selected) {
            case 'S':
                startGame();
                break;
            case 'H':
                helpPage();
                break;
        }

        if (selected == 'Q') {
            clrscr();
            break;
        }
    }

    return 0;
}
