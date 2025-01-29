#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Function prototypes
void printBoard(char *chessBoard[8][8]);
void movePiece(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int *turn, bool *bKingMoved, bool *wKingMoved);
bool validMove(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn, bool bKingMoved, bool wKingMoved);
bool rook(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn);
bool rowEmpty(char *chessBoard[8][8], int startRow, int startCol, int endCol);
bool colEmpty(char *chessBoard[8][8], int startRow, int startCol, int endRow);
bool knight(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn);
bool bishop(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol);
bool diagonal(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol);
bool queen(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn);
bool king(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn, bool *bKingMoved, bool *wKingMoved);
bool bPawn(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn);
bool wPawn(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn);
bool validCapture(char *chessBoard[8][8], int turn, int endRow, int endCol);
bool oneByOneMove(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn);
bool isKingPresent(char *chessBoard[8][8], const char *king);
void printScores();
int getPieceValue(const char *piece);

int whiteScore = 0, blackScore = 0;
char *whiteCaptured[16]; 
char *blackCaptured[16];
int whiteCapturedCount = 0, blackCapturedCount = 0;
int main() {
    int turn = -1;
    bool checkmate = false;
    char start[6], end[6];
    bool bKingMoved = false;
    bool wKingMoved = false;
    char gameMode[4];

    char *chessBoard[8][8] = {
        {"♖", "♘", "♗", "♕", "♔", "♗", "♘", "♖"},
        {"♙", "♙", "♙", "♙", "♙", "♙", "♙", "♙"},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
        {"♟", "♟", "♟", "♟", "♟", "♟", "♟", "♟"},
        {"♜", "♞", "♝", "♛", "♚", "♝", "♞", "♜"}
    };

    while (!checkmate) {
        if (turn==-1){
            printf("Enter the game mode you want to play. Options are player vs player(\"PVP\") or 1 player(\"PVE\"). If you dont know how to play chess type \"INFO\"   \n");
            scanf("%s", gameMode);
            if(strcmp(gameMode, "PVP")==0||strcmp(gameMode, "pvp")==0){
                printf("game mode selected, game starting\n");
                turn++;
            }
            else if(strcmp(gameMode, "INFO")==0||strcmp(gameMode, "info")==0){
                printf("\nTutorial starting\n\n\n");
                
            printf("Welcome to Chess 101!\n");
            printf("Chess is a two-player strategy game played on an 8x8 board.\n");
            printf("Each player has 16 pieces: 1 King, 1 Queen, 2 Rooks, 2 Bishops, 2 Knights, and 8 Pawns.\n");
            printf("Your goal is to checkmate your opponent's King.\n\n");

            printf("Here is how a chessboard is set up:\n");
            printf("   a b c d e f g h\n");
            printf("  +--------------+\n");
            printf("8 |♖♘♗♕♔♗♘♖| 8\n");
            printf("7 |♙♙♙♙♙♙♙♙| 7\n");
            printf("6 | # # # # # # # | 6\n");
            printf("5 |# # # # # # # #| 5\n");
            printf("4 | # # # # # # # | 4\n");
            printf("3 |# # # # # # # #| 3\n");
            printf("2 |♟♟♟♟♟♟♟♟| 2\n");
            printf("1 |♜♞♝♛♚♝♞♜| 1\n");
            printf("  +--------------+\n");
            printf("   a b c d e f g h\n\n");

            printf("Let's learn how each piece moves:\n");
            printf("1. King (♔/♚): Moves 1 square in any direction.\n");
            printf("2. Queen (♕/♛): Moves any number of squares in any direction.\n");
            printf("3. Rook (♖/♜): Moves any number of squares horizontally or vertically.\n");
            printf("4. Bishop (♗/♝): Moves any number of squares diagonally.\n");
            printf("5. Knight (♘/♞): Moves in an 'L' shape: two squares in one direction and one square perpendicular.\n");
            printf("6. Pawn (♙/♟): Moves forward 1 square. On its first move, it can move forward 2 squares.\n");
            printf("   Pawns capture diagonally, not straight ahead.\n\n");

            printf("There are a few special moves in chess:\n");
            printf("1. Castling: The King and a Rook move simultaneously. The King moves two squares towards a Rook, and the Rook jumps over the King.\n");
            printf("   - Conditions: Neither piece has moved before, the squares between them are empty, and the King is not in check.\n");
            printf("3. Pawn Promotion: When a pawn reaches the opponent's back row, it is promoted to a Queen, Rook, Bishop, or Knight.\n\n");

            printf("The game ends in one of three ways:\n");
            printf("1. Checkmate: The opponent's King is in check and cannot escape. In this game just take the oppponents piece to win the game\n");
            printf("2. Draw: The game ends in a tie if no legal moves are possible or by mutual agreement. \n");
            printf("3. Resignation: A player gives up. type resign at any time to give up\n\n");

            printf("Example of a turn:\n");
            printf("1. White moves a pawn from e2 to e4.\n");
            printf("2. Black moves a pawn from e7 to e5.\n");
            printf("3. White moves a knight from g1 to f3 to attack the pawn on e5.\n");
            printf("4. Black moves a bishop from f8 to c5.\n\n");

            printf("That's the basics of chess! Practice your moves and strategies to become a better player.\n");
            printf("Remember, chess is as much about patience and planning as it is about execution.\n");
            printf("Good luck, and enjoy the game!\n\n");

            continue;

            }
            else if(strcmp(gameMode, "PVE")==0||strcmp(gameMode, "pve")==0){
                printf("\nGame mode not currently working\n\n");
                continue;
            }
        }
        printBoard(chessBoard);


        printScores();
                // Check for game over
        if (!isKingPresent(chessBoard, "♔")) {
            printf("White wins! Black's king has been captured.\n");
            break;
        }
        if (!isKingPresent(chessBoard, "♚")) {
            printf("White wins! White's king has been captured.\n");
            break;
        }
        if (turn % 2 == 0) {
            printf("White's Turn. Enter the starting position of a piece (e.g., a2, d6): ");
        } else {
            printf("Black's Turn. Enter the starting position of a piece (e.g., a2, d6): ");
        }

        scanf("%s", start);
        printf("Enter a destination position or \"back\" to choose another piece: ");
        scanf("%s", end);

        if (strcmp(end, "back") == 0 || strcmp(end, "Back") == 0) {
            continue;
        }

        int startRow = 8 - (start[1] - '0');
        int startCol = start[0] - 'a';
        int endRow = 8 - (end[1] - '0');
        int endCol = end[0] - 'a';

        movePiece(chessBoard, startRow, startCol, endRow, endCol, &turn, &bKingMoved, &wKingMoved);

        
    }

    return 0;
}

void printBoard(char *chessBoard[8][8]) {
    printf("\n   abcdefgh\n");
    printf("  +--------+\n");
    for (int row = 0; row < 8; row++) {
        printf("%d |", 8 - row);
        for (int col = 0; col < 8; col++) {
            if (chessBoard[row][col] == NULL) {
                if ((row + col) % 2 == 0) {
                    printf(" "); // Light square
                } else {
                    printf("#"); // Dark square
                }
            } else {
                printf("%s", chessBoard[row][col]);
            }
        }
        printf("| %d\n", 8 - row);
    }
    printf("  +--------+\n");
    printf("   abcdefgh\n");
}

void movePiece(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int *turn, bool *bKingMoved, bool *wKingMoved) {
    if (validMove(chessBoard, startRow, startCol, endRow, endCol, *turn, *bKingMoved, *wKingMoved)) {
        char *capturedPiece = chessBoard[endRow][endCol];

        
        if (capturedPiece != NULL) {
            int pieceValue = getPieceValue(capturedPiece);

            
            if (*turn % 2 == 0) {
                whiteScore += pieceValue;
                whiteCaptured[whiteCapturedCount++] = capturedPiece;
            } else { 
                blackScore += pieceValue;
                blackCaptured[blackCapturedCount++] = capturedPiece;
            }
        }
        chessBoard[endRow][endCol] = chessBoard[startRow][startCol];
        chessBoard[startRow][startCol] = NULL;
        (*turn)++;
    } else {
        printf("\nInvalid move!\n\n");
    }
}

bool validMove(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn, bool bKingMoved, bool wKingMoved) {
    char *currentPiece = chessBoard[startRow][startCol];
    printf("Turn: %d\n", turn);
    printf("Selected piece: %s\n", chessBoard[startRow][startCol]);  
    if (startRow < 0 || startCol < 0 || endRow < 0 || endCol < 0 ||
        startRow > 7 || startCol > 7 || endRow > 7 || endCol > 7) {
        printf("Move is out of bounds.\n");
        return false;
    }

    if (chessBoard[startRow][startCol] == NULL) {
        printf("No piece at the starting position.\n");
        return false;
    }

        

    if (turn % 2 == 0) { // White's turn
        
        if (strcmp(currentPiece, "♙" ) == 0) {
            printf("You must move a white piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♖") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♘") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♗") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♕") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♔") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
    } else { // Black's turn
        printf("test1\n");
        if (strcmp(currentPiece, "♟") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♜") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♞") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♝") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♛") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }
        if (strcmp(currentPiece, "♚") == 0) {
            printf("You must move a black piece.\n");
            return false;
        }

    }
    
    

    if (strcmp(currentPiece, "♜") == 0 || strcmp(currentPiece, "♖") == 0) {
        return rook(chessBoard, startRow, startCol, endRow, endCol, turn);
    }
    if (strcmp(currentPiece, "♞") == 0 || strcmp(currentPiece, "♘") == 0) {
        return knight(chessBoard, startRow, startCol, endRow, endCol, turn);
    }
    if (strcmp(currentPiece, "♝") == 0 || strcmp(currentPiece, "♗") == 0) {
        return bishop(chessBoard, startRow, startCol, endRow, endCol);
    }
    if (strcmp(currentPiece, "♛") == 0 || strcmp(currentPiece, "♕") == 0) {
        return queen(chessBoard, startRow, startCol, endRow, endCol, turn);
    }
    if (strcmp(currentPiece, "♚") == 0 || strcmp(currentPiece, "♔") == 0) {
        return king(chessBoard, startRow, startCol, endRow, endCol, turn, &bKingMoved, &wKingMoved);
    }
    if (strcmp(currentPiece, "♟") == 0) {
        return wPawn(chessBoard, startRow, startCol, endRow, endCol, turn);
    }
    if (strcmp(currentPiece, "♙") == 0) {
        return bPawn(chessBoard, startRow, startCol, endRow, endCol, turn);
    }

    return false;
}
bool knight(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn) {

    int rowDiff = abs(endRow - startRow);
    int colDiff = abs(endCol - startCol);

    // Check if the move matches an L-shape
    if ((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)) {
        if (chessBoard[endRow][endCol] == NULL) {
            printf("Valid knight move to an empty square.\n");
            return true; // Moving to an empty square
        } else if (validCapture(chessBoard, turn, endRow, endCol)) {
            printf("Valid knight capture.\n");
            return true; // Valid capture
        } else {
            printf("Invalid knight move: destination square occupied by friendly piece.\n");
        }
    } else {
        printf("Invalid knight move: not an L-shape.\n");
    }

    return false; // Invalid move
}
bool rook(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn) {
    // Validate horizontal movement
    if (startRow == endRow) {
        // Check if the path is empty and destination is valid
        if (rowEmpty(chessBoard, startRow, startCol, endCol) &&
            (chessBoard[endRow][endCol] == NULL || validCapture(chessBoard, turn, endRow, endCol))) {
            return true;
        }
    }
    // Validate vertical movement
    else if (startCol == endCol) {
        // Check if the path is empty and destination is valid
        if (colEmpty(chessBoard, startRow, startCol, endRow) &&
            (chessBoard[endRow][endCol] == NULL || validCapture(chessBoard, turn, endRow, endCol))) {
            return true;
        }
    }
    // Invalid move for a rook
    return false;
}
bool rowEmpty(char *chessBoard[8][8], int startRow, int startCol, int endCol) {
    int direction = (endCol > startCol) ? 1 : -1;
    for (int col = startCol + direction; col != endCol; col += direction) {
        if (chessBoard[startRow][col] != NULL) {
            return false;
        }
    }
    return true;
}

bool colEmpty(char *chessBoard[8][8], int startRow, int startCol, int endRow) {
    int direction = (endRow > startRow) ? 1 : -1;
    for (int row = startRow + direction; row != endRow; row += direction) {
        if (chessBoard[row][startCol] != NULL) {
            return false;
        }
    }
    return true;
}

bool bishop(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol) {
    return diagonal(chessBoard, startRow, startCol, endRow, endCol);
}

bool diagonal(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol) {
    printf("Diag\n");
    int colDirection = (endCol > startCol) ? 1 : -1;
    int rowDirection = (endRow > startRow) ? 1 : -1;

    if (abs(endCol - startCol) != abs(endRow - startRow)) {
        return false;
    }

    int currRow = startRow + rowDirection;
    int currCol = startCol + colDirection;

    while (currRow != endRow && currCol != endCol) {
        if (chessBoard[currRow][currCol] != NULL) {
            return false;
        }
        currRow += rowDirection;
        currCol += colDirection;
    }

    return true;
}

bool queen(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn) {
    
    if (diagonal(chessBoard, startRow, startCol, endRow, endCol) &&(chessBoard[endRow][endCol] == NULL || validCapture(chessBoard, turn, endRow, endCol))) {
        
        return true;
    }

    
    if (startRow == endRow &&rowEmpty(chessBoard, startRow, startCol, endCol) &&
        (chessBoard[endRow][endCol] == NULL || validCapture(chessBoard, turn, endRow, endCol))) {
        
        return true;
    }

    
    if (startCol == endCol &&colEmpty(chessBoard, startRow, startCol, endRow) &&
        (chessBoard[endRow][endCol] == NULL || validCapture(chessBoard, turn, endRow, endCol))) {
        
        return true;
    }

    return false;
}

bool king(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn, bool *bKingMoved, bool *wKingMoved) {
    printf("check1");
    if (abs(endRow - startRow) <= 1 && abs(endCol - startCol) <= 1&&validCapture(chessBoard, turn, endRow, endCol)) {
        return true;
    }
    printf("check2");
     if (turn % 2 == 1 && !*bKingMoved && startRow == 7 && startCol == 4) {
        if (endCol == 6 && chessBoard[7][5] == NULL && chessBoard[7][6] == NULL &&
            chessBoard[7][7] != NULL && strcmp(chessBoard[7][7], "♖") == 0) {
            chessBoard[7][5] = chessBoard[7][7];
            chessBoard[7][7] = NULL;
            *bKingMoved = true;
            return true;
        }
        if (endCol == 2 && chessBoard[7][3] == NULL && chessBoard[7][2] == NULL && chessBoard[7][1] == NULL &&
            chessBoard[7][0] != NULL && strcmp(chessBoard[7][0], "♖") == 0) {
            chessBoard[7][3] = chessBoard[7][0];
            chessBoard[7][0] = NULL;
            *bKingMoved = true;
            return true;
        }
    }
    
     if (turn % 2 == 0 && !*wKingMoved && startRow == 0 && startCol == 4) {
        if (endCol == 6 && chessBoard[0][5] == NULL && chessBoard[0][6] == NULL &&
            chessBoard[0][7] != NULL && strcmp(chessBoard[0][7], "♜") == 0) {
            chessBoard[0][5] = chessBoard[0][7];
            chessBoard[0][7] = NULL;
            *wKingMoved = true;
            return true;
        }
        if (endCol == 2 && chessBoard[0][3] == NULL && chessBoard[0][2] == NULL && chessBoard[0][1] == NULL &&
            chessBoard[0][0] != NULL && strcmp(chessBoard[0][0], "♜") == 0) {
            chessBoard[0][3] = chessBoard[0][0];
            chessBoard[0][0] = NULL;
            *wKingMoved = true;
            return true;
        }
    }

    printf("fail");
    return false;
}

bool bPawn(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn) {
    printf("bPawn called: startRow=%d, startCol=%d, endRow=%d, endCol=%d\n", startRow, startCol, endRow, endCol);

    // Single-space forward move (down)
    if (startCol == endCol && endRow - startRow == 1) {
        if (chessBoard[endRow][endCol] == NULL) {
            return true;
        }
    }

    // Double-space forward move from starting position
    if (startRow == 1 && startCol == endCol && endRow - startRow == 2) {
        if (chessBoard[startRow + 1][startCol] == NULL && chessBoard[endRow][endCol] == NULL) {
            return true;
        }
    }

    // Diagonal capture
    if ((endRow - startRow == 1 && abs(startCol - endCol) == 1) && validCapture(chessBoard, turn, endRow, endCol)) {
        return true;
    }
    printf("Bpawn invalid");
    return false; // Invalid move
}

bool wPawn(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn) {
    printf("wPawn called: startRow=%d, startCol=%d, endRow=%d, endCol=%d\n", startRow, startCol, endRow, endCol);
    // Single forward move (up)
    if (startCol == endCol && startRow - endRow == 1) {
        if (chessBoard[endRow][endCol] == NULL) {
            return true;
        }
    }

    // Double forward move from starting position
    if (startRow == 6 && startCol == endCol && startRow - endRow == 2) {
        if (chessBoard[startRow - 1][startCol] == NULL && chessBoard[endRow][endCol] == NULL) {
            return true;
        }
    }

    // Diagonal capture
    if ((startRow - endRow == 1 && abs(startCol - endCol) == 1) && validCapture(chessBoard, turn, endRow, endCol)) {
        return true;
    }
    printf("Wpawn invalid");
    return false; // Invalid move
}

bool validCapture(char *chessBoard[8][8], int turn, int endRow, int endCol) {
    const char *targetPosition= chessBoard[endRow][endCol];
    if (targetPosition == NULL) {
        return false; // Nothing to capture
    }
    if (turn%2 == 1) { 
        if ( (strcmp(targetPosition, "♟") == 0 || strcmp(targetPosition, "♜") == 0 || 
        strcmp(targetPosition, "♞") == 0 || strcmp(targetPosition, "♝") == 0 || 
        strcmp(targetPosition, "♛") == 0 || strcmp(targetPosition, "♚") == 0)) {
            return true; 
        }
    } else if (turn % 2 == 0) { 
        if ((strcmp(targetPosition, "♙") == 0 || strcmp(targetPosition, "♖") == 0 || 
            strcmp(targetPosition, "♘") == 0 || strcmp(targetPosition, "♗") == 0 || 
            strcmp(targetPosition, "♕") == 0 || strcmp(targetPosition, "♔") == 0)) {
            return true; 
            }
        }
    return false;
    
}
bool oneByOneMove(char *chessBoard[8][8], int startRow, int startCol, int endRow, int endCol, int turn) {
    int rDiff = abs(startRow - endRow);
    int cDiff = abs(startCol - endCol);
    if ((rDiff <= 1 && cDiff <= 1) && (startCol != endCol || startRow != endRow)) {
        return true;
    } else {
        return false;
    }
}

bool isKingPresent(char *chessBoard[8][8], const char *king) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (chessBoard[row][col] != NULL && strcmp(chessBoard[row][col], king) == 0) {
                return true; // King is still present
            }
        }
    }
    return false; // King not found
}

void printScores() {
    printf("\nScores:\n");
    printf("White: %d\n", whiteScore);
    printf("Black: %d\n", blackScore);

    printf("\nCaptured Pieces:\n");
    printf("White's Captured: ");
    for (int i = 0; i < whiteCapturedCount; i++) {
        printf("%s ", whiteCaptured[i]);
    }
    printf("\nBlack's Captured: ");
    for (int i = 0; i < blackCapturedCount; i++) {
        printf("%s ", blackCaptured[i]);
    }
    printf("\n");
}
int getPieceValue(const char *piece) {
    if (strcmp(piece, "♙") == 0 || strcmp(piece, "♟") == 0){ 
    return 1;} 
    if (strcmp(piece, "♘") == 0 || strcmp(piece, "♞") == 0) { 
    return 3;}  
    if (strcmp(piece, "♗") == 0 || strcmp(piece, "♝") == 0) { 
    return 3;}  
    if (strcmp(piece, "♖") == 0 || strcmp(piece, "♜") == 0) { 
    return 5;}   
    if (strcmp(piece, "♕") == 0 || strcmp(piece, "♛") == 0) { 
    return 9;}  
    if (strcmp(piece, "♔") == 0 || strcmp(piece, "♚") == 0) return 0; 
    return 0;
}