#include <iostream>
#include <cstdlib>
#include <ncurses.h>

using namespace std;

bool gameOver;
const int width = 20, height = 20;
int x, y, FruitX, FruitY, score;
enum eDirection { STOP, LEFT, RIGHT, UP, DOWN };

eDirection dir;

int TailX[100], TailY[100];
int nTail = 0;

void Setup();
void Draw();
void Input();
void Logic();
void DisplaygameOver();
void DisplaygameStart();

int main() {

    Setup();

    DisplaygameStart();

    Draw();

    while (!gameOver) {

        Draw();
        Input();
        Logic();
    }

    DisplaygameOver();

    getch();
    endwin();

    return 0;

}

void Setup() {

    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    FruitX = (rand() % width) + 1;
    FruitY = (rand() % height) + 1;

    score = 0;

}

void Draw() {

    clear();

    for (int i = 0; i < width + 2; i++)
        mvprintw(0, i, "+");

    for (int i = 0; i < height + 2; i++) {

        for (int j = 0; j < width + 2; j++) {

            if (i == 0 || i == 21)
                mvprintw(i, j, "#");

            else if (j == 0 || j == 21)
                mvprintw(i, j, "#");

            else if (i == y && j == x)
                mvprintw(i, j, "O");

            else if (i == FruitY && j == FruitX)
                mvprintw(i, j, "A");

            else {

                for (int k = 0; k < nTail; k++) {

                    if (TailX[k] == j && TailY[k] == i) {
                        mvprintw(i, j, "o");
                    }
                }
            }
        }
    }

    mvprintw(23, 21, "%d", score);
    mvprintw(23, 0, "Score");

    refresh();

}

void Input() {

    keypad(stdscr, true);
    halfdelay(1);

    int c = getch();

    switch (c) {

    case KEY_LEFT:
        dir = LEFT;
        break;
    case KEY_RIGHT:
        dir = RIGHT;
        break;
    case KEY_UP:
        dir = UP;
        break;
    case KEY_DOWN:
        dir = DOWN;
        break;
    case 'q':
        gameOver = true;
        break;
    }
}

void Logic() {

    int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = x;
    TailY[0] = y;


    for (int i = 1; i < nTail; i++) {

        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }


    //LVL 1
    if (score < 5) {

        if (x > width || x < 1 || y < 1 || y > height)
            gameOver = true;

        switch (dir) {

        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        default:
            break;

        }

        if (x == FruitX && y == FruitY) {

            score++;
            FruitX = (rand() % width) + 1;
            FruitY = (rand() % height) + 1;
            nTail++;
        }

        for (int i = 0; i < nTail; i++)
            if (TailX[i] == x && TailY[i] == y)
                gameOver = true;

        //LVL 2
    }
    else if (score >= 5 && score < 20) {

        if (x > width || x < 1 || y < 1 || y > height) {

            x = 11;
            y = 11;
            score--;
            nTail--;

        }

        switch (dir) {

        case LEFT:
            x++;
            break;

        case RIGHT:
            x--;
            break;

        case UP:
            y++;
            break;

        case DOWN:
            y--;
            break;

        default:
            break;

        }

        if (x == FruitX && y == FruitY) {

            score++;
            FruitX = (rand() % width) + 1;
            FruitY = (rand() % height) + 1;
            nTail++;
        }

        for (int i = x; i < nTail; i++)
            if (TailX[i] == x && TailY[i] == y)
                gameOver = true;

        //LVL IMPOSSIBLE
    }
    else if (score >= 20) {


        switch (dir) {

        case LEFT:
            x++;
            break;

        case RIGHT:
            x--;
            break;

        case UP:
            y++;
            break;

        case DOWN:
            y--;
            break;

        default:
            break;
        }

        if (x > width || x < 1 || y < 1 || y > height) {

            x = -x;
            y = -y;

            if (nTail > 0) {
                score--;
                nTail--;
                x = 11;
                y = 11;

            }
            else if (nTail == 0) {
                nTail = 0;
                x = 11;
                y = 11;

            }
        }

        if (x == FruitX && y == FruitY) {

            score++;
            FruitX = (rand() % width) + 1;
            FruitY = (rand() % height) + 1;
            nTail++;
            x = (rand() % width) + 1;
            y = (rand() % height) + 1;
        }

        for (int i = x && y; i < nTail; i++)
            if (TailX[i] == x && TailY[i] == y)
                gameOver = true;

    }
    else if (score >= 35) {

        clear();
        mvprintw(11, 11, "YOU WIN!");
        getch();
        gameOver = true;
        endwin();
    }
}

void DisplaygameStart() {

    mvprintw(7, 12, "-----------------------------------------------");
    mvprintw(8, 12, "|                                               |");
    mvprintw(9, 12, "|    ******   *     *      *     *  *  *****    |");
    mvprintw(10, 12, "|   *         * *   *     * *    * *   *        |");
    mvprintw(11, 12, "|    ******   *  *  *    *   *   **    ****     |");
    mvprintw(12, 12, "|    ******   *  *  *    *   *   **    ****     |");
    mvprintw(13, 12, "|          *  *   * *   *******  * *   *        |");
    mvprintw(14, 12, "|    ******   *     *  *       * *  *  *****    |");
    mvprintw(15, 12, "|                                               |");
    mvprintw(16, 12, "-----------------------------------------------");
    mvprintw(19, 26, "PRESS ANYTHING TO PLAY");

    getch();

}

void DisplaygameOver() {

    clear();

    mvprintw(7, 3, " ------------------------------------------------------------------------- ");
    mvprintw(8, 3, "|    *****      *     *       * ******       ****  *       ****** ****    |");
    mvprintw(9, 3, "|   *          * *    * *   * * *           *    *  *     * *     *   *   |");
    mvprintw(10, 3, "|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |");
    mvprintw(11, 3, "|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |");
    mvprintw(12, 3, "|    *****  *       * *       * ******       ****      *    ***** *   *   |");
    mvprintw(13, 3, " ------------------------------------------------------------------------- ");
    mvprintw(15, 35, "YOUR SCORE %d", score);
    mvprintw(18, 30, "GOOD LUCK NEXT TIME :)");

    for (int i = 0; i < 50; i++)
        getch();

}