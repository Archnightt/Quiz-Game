#include "quizutils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

const char *categories[] = {"Computers", "Games", "General", "Geography", "History", "Sports", "Television"};
const char *difficulties[] = {"Easy", "Medium", "Hard"};

const size_t categoriesCount = sizeof(categories) / sizeof(categories[0]);
const size_t difficultiesCount = sizeof(difficulties) / sizeof(difficulties[0]);

/**
 * Fetch a random question based on the choosen category and difficulty.
 *
 * @param category the category of the question.
 * @param difficulty the difficulty level of the question.
 * @param questionsDone the number of questions completed by the user.
 * @param questionIndices the index number of the questions completed.
 * @return char* the un-parsed question.
 */
char *qu_getRawQuestion(const char *category, const char *difficulty, int questionsDone, int questionIndices[]) {
    char command[1024];
    int written = snprintf(command, sizeof(command), "python fetch_question.py %s %s", category, difficulty);

    for (int i = 0; i <= questionsDone; i++)
        written += snprintf(command + written, sizeof(command) - written, " %d", questionIndices[i]);

    FILE *process_ptr = popen(command, "r");
    int size = sizeof(char) * 1024;

    char *output = malloc(size);
    while (fgets(output, size, process_ptr)) continue;

    int exitCode = pclose(process_ptr);
    if (exitCode == 0) {
        output = realloc(output, sizeof(char) * (strlen(output) + 1));
        return output;
    }

    free(output);
    return NULL;
}

/**
 * Fetches a random question and returns a qu_Question struct parsed using
 * the raw question received from qu_getRawQuestion.
 *
 * @param category the category of the question.
 * @param difficulty the difficulty of the question.
 * @param questionsDone the number of questions completed by the user.
 * @param questionIndices the index number of the questions completed.
 * @return qu_Question* the parsed question struct.
 */
qu_Question *qu_getRandomQuestion(const char *category, const char *difficulty, int questionsDone, int questionIndices[]) {
    char *rawQuestion = qu_getRawQuestion(category, difficulty, questionsDone, questionIndices);
    if (rawQuestion == NULL)
        return NULL;

    qu_Question *qu_question = malloc(sizeof(qu_Question));

    char *question = strtok(rawQuestion, ";");
    qu_question->question = question;

    char **options = malloc(sizeof(char *) * 4);
    for (int i = 0; i < 4; i++)
        options[i] = strtok(NULL, ";");

    qu_question->options = options;

    char *correctOption = strtok(NULL, ";");
    qu_question->correctOption = atoi(correctOption);

    char *questionIndex = strtok(NULL, ";");
    qu_question->questionIndex = atoi(questionIndex);

    return qu_question;
}

/**
 * Sets the location of the cursor to the specified position on the
 * console screen.
 *
 * @param row the row number to set the cursor to.
 * @param column the column number to set the cursor to.
 *
 * @return true if the cursor was moved successfully.
 * @return false if an error occured while moving the cursor.
 */
bool gotoRowCol(int row, int column) {
    COORD coord;
    coord.X = column;
    coord.Y = row;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    return SetConsoleCursorPosition(hConsole, coord);
}

/**
 * Print dividing lines to seperate blocks of text or indicate the start
 * and end of a block.
 *
 * @param width the width of the divider.
 * @param row the row to print the divider on.
 */
void printDividers(int width, int row) {
    gotoRowCol(row, 0);

    char divider[width + 1];

    divider[0] = '+';
    for (int i = 1; i < width - 1; i++) {
        if (i % 2 != 0)
            divider[i] = ' ';
        else
            divider[i] = '-';
    }

    divider[width - 1] = '+';
    divider[width] = '\0';

    printf(divider);
}

/**
 * Print text centered on the row number specified.
 *
 * @param width the width of the text.
 * @param row the row to print the text on.
 * @param text the text to print.
 */
void printTextCentered(int width, int row, char *text) {
    gotoRowCol(row, 0);
    printf("|");

    gotoRowCol(row, width / 2 - strlen(text) / 2);
    printf(text);

    gotoRowCol(row, width - 1);
    printf("|");
}

/**
 * Print text left justified on the row number specified.
 *
 * @param width the width of the text.
 * @param row the row to print the text on.
 * @param text the text to print.
 */
void printTextLeft(int width, int row, char *text) {
    gotoRowCol(row, 0);
    printf("|");

    gotoRowCol(row, 2);
    printf(text);

    gotoRowCol(row, width - 1);
    printf("|");
}

/**
 * Print text right justified on the row number specified.
 *
 * @param width the width of the text.
 * @param row the row to print the text on.
 * @param text the text to print.
 */
void printTextRight(int width, int row, char *text) {
    gotoRowCol(row, 0);
    printf("|");

    gotoRowCol(row, width - strlen(text) - 2);
    printf(text);

    gotoRowCol(row, width - 1);
    printf("|");
}
