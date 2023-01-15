#include <conio.h>
#include <stdio.h>

#include "quizpages.h"

/**
 * Starts the quiz game loop.
 */
void startGame() {
    helpPage();

    int topicIndex = topicPage();
    int difficultyIndex = difficultyPage();
    int total = 0, correct = 0, questionsDone[5];

    for (int i = 0; i < 5; i++) {
        qu_Question *question = qu_getRandomQuestion(
            categories[topicIndex],
            difficulties[difficultyIndex],
            total,
            questionsDone);

        int choice = questionPage(question);
        if (answerPage(question, choice))
            correct++;

        questionsDone[i] = question->questionIndex;
        total++;
    }

    resultPage(total, correct);
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
