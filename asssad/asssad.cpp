#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int BOARD_SIZE = 10;
const char EMPTY = '-';
const char SHIP = '+';
const char MISS = 'O';
const char HIT = 'X';

struct Ship {
    int size;
    int hits;
    bool sunk;
};

struct Player {
    char board[BOARD_SIZE][BOARD_SIZE];
    char visibleBoard[BOARD_SIZE][BOARD_SIZE];
    Ship ships[10];
};

void hideComputerShips(Player& computer) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if (computer.board[i][j] == SHIP) {
                computer.visibleBoard[i][j] = EMPTY;
            }
            else {
                computer.visibleBoard[i][j] = computer.board[i][j];
            }
        }
    }
}


int main() {
    Player human, computer;
    initializeBoard(human.board);
    initializeBoard(computer.board);

    setupPlayerShips(human);
    setupComputerShips(computer);

    bool gameOver = false;
    bool humanTurn = true;

    hideComputerShips(computer);


    while (!gameOver) {
        printBoards(human.board, computer.visibleBoard);

        if (humanTurn) {
            cout << "Your turn!" << endl;
            cout << "Take a shot (row column): ";
            int row, col;
            cin >> row >> col;

            if (row < 0  row >= BOARD_SIZE  col < 0 || col >= BOARD_SIZE) {
                cout << "Invalid move, try again." << endl;
                continue;
            }

            if (makeMove(computer.board, row, col)) {
                cout << "Hit!" << endl;
                computer.visibleBoard[row][col] = HIT;
            }
            else {
                cout << "Miss!" << endl;
                computer.visibleBoard[row][col] = MISS;
            }

            if (hasPlayerWon(computer)) {
                printBoards(human.board, computer.visibleBoard);
                cout << "Congratulations! You win!" << endl;
                gameOver = true;
            }
        }
        else {
            cout << "Computer's turn!" << endl;
            computerMove(human.board);

            if (hasPlayerWon(human)) {
                printBoards(human.board, computer.visibleBoard);
                cout << "Computer wins! Better luck next time." << endl;
                gameOver = true;
            }
        }

        humanTurn = !humanTurn;
    }

    return 0;
}
