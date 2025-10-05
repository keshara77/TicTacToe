#include "tictactoe.h"

// -------------------- Function Implementations --------------------
char** initBoard(int n) {
    char** board = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        board[i] = (char*)malloc(n * sizeof(char));
        for (int j = 0; j < n; j++) {
            board[i][j] = ' ';
        }
    }
    return board;
}

void displayBoard(char** board, int n) {
    printf("\n   ");
    for (int i = 0; i < n; i++) printf("%d ", i);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d  ", i);
        for (int j = 0; j < n; j++) {
            printf("%c", board[i][j]);
            if (j < n - 1) printf("|");
        }
        printf("\n   ");
        if (i < n - 1) {
            for (int k = 0; k < n * 2 - 1; k++) printf("-");
            printf("\n");
        }
    }
    printf("\n");
}

int isValidMove(char** board, int n, int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n && board[row][col] == ' ');
}

void getUserMove(int* row, int* col, int n, char player) {
    printf("Player %c, enter row and col (0..%d): ", player, n - 1);
    scanf("%d %d", row, col);
}

void computerMove(char** board, int n, int* row, int* col) {
    do {
        *row = rand() % n;
        *col = rand() % n;
    } while (!isValidMove(board, n, *row, *col));
    printf("Computer chooses: %d %d\n", *row, *col);
}

int checkWinner(char** board, int n, char player) {
    for (int i = 0; i < n; i++) {
        int win = 1;
        for (int j = 0; j < n; j++) {
            if (board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }

    for (int j = 0; j < n; j++) {
        int win = 1;
        for (int i = 0; i < n; i++) {
            if (board[i][j] != player) {
                win = 0;
                break;
            }
        }
        if (win) return 1;
    }

    int win = 1;
    for (int i = 0; i < n; i++) {
        if (board[i][i] != player) {
            win = 0;
            break;
        }
    }
    if (win) return 1;

    win = 1;
    for (int i = 0; i < n; i++) {
        if (board[i][n - 1 - i] != player) {
            win = 0;
            break;
        }
    }
    return win;
}

int checkDraw(char** board, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (board[i][j] == ' ')
                return 0;
    return 1;
}

void logMove(FILE* logFile, int playerIndex, char player, int row, int col) {
    fprintf(logFile, "Player %c -> (%d, %d)\n", player, row, col);
}

// -------------------- Main Function --------------------
int main() {
    srand(time(NULL));

    int n, mode;
    printf("Enter board size N (3 <= N <= 10): ");
    scanf("%d", &n);

    if (n < 3 || n > 10) {
        printf("Invalid board size.\n");
        return 1;
    }

    printf("\nSelect Game Mode:\n");
    printf("1. Two Players (User vs User)\n");
    printf("2. User vs Computer\n");
    printf("3. Three Players\n");
    printf("Enter choice (1-3): ");
    scanf("%d", &mode);

    char** board = initBoard(n);
    FILE* logFile = fopen("tictactoe_log.txt", "w");

    char players[3] = {'X', 'O', 'Z'};
    int totalPlayers = (mode == 3) ? 3 : 2;
    int playerType[3] = {0, 0, 0};

    if (mode == 2) {
        playerType[1] = 1; // computer as O
    } else if (mode == 3) {
        printf("\nConfigure Players (0 = Human, 1 = Computer):\n");
        for (int i = 0; i < 3; i++) {
            printf("Player %c: ", players[i]);
            scanf("%d", &playerType[i]);
        }
    }

    int turn = 0, row, col;

    while (1) {
        displayBoard(board, n);

        if (playerType[turn] == 0)
            getUserMove(&row, &col, n, players[turn]);
        else
            computerMove(board, n, &row, &col);

        if (!isValidMove(board, n, row, col)) {
            if (playerType[turn] == 0)
                printf("Invalid move! Try again.\n");
            continue;
        }

        board[row][col] = players[turn];
        logMove(logFile, turn, players[turn], row, col);

        if (checkWinner(board, n, players[turn])) {
            displayBoard(board, n);
            if (playerType[turn] == 0)
                printf("Player %c wins!\n", players[turn]);
            else
                printf("Computer (%c) wins!\n", players[turn]);
            break;
        }

        if (checkDraw(board, n)) {
            displayBoard(board, n);
            printf("Game is a draw!\n");
            break;
        }

        turn = (turn + 1) % totalPlayers;
    }

    fclose(logFile);
    for (int i = 0; i < n; i++) free(board[i]);
    free(board);

    return 0;
}

