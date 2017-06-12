/* 
 * Snakes and ladders game.
*/
#include "tut_headers.h"

void initBoard(int [10][10][2]);
void move(int [10][10][2], int &, int &);

int main(){
    int board[10][10][2];
    //player position row and column values for the game matrix
    int uRow = 0, uCol = 0, cRow = 0, cCol = 0;
    bool won = 0, computer = 1; //flags for game control
    srand(static_cast<unsigned int>(time(NULL)));
    char c; //dummy var to allow game to pause for user input
    
    initBoard(board);
    cout << "\nSnakes and Ladders: your move...";
    
    do {
      //play snakes and ladders
        if(computer && !won){
          //change player to user; move
            computer = 0;
            cout << "\n\nYou are on square " << board[uRow][uCol][0]+1 << 
                    "; press any key + 'Enter' to throw the die: ";
            cin >> c;
            move(board, uRow, uCol);
        } else if(!computer && !won){
          //change player to computer; move
            computer = 1;
            cout << "\n\nComputer is on square " << board[cRow][cCol][0]+1 << endl;
            move(board, cRow, cCol);
        }
        
        //determine game winner
        if(board[uRow][uCol][0] == 99){
                won = 1;
                cout << "\nUser won!" << endl;
        }
        if(board[cRow][cCol][0] == 99){
            won = 2;
            cout << "\nComputer won!" << endl;
        }
    } while(!won);
    
    return 0;
}

//Initialises the snakes and ladders board array.
//Each square has two numbers: the square number
//and the destination square number if the square
//is a snake or ladder square; the numbers are
//the same for ordinary squares.
void initBoard(int board[10][10][2]){
    int count = 0;
    for(int i = 0; i < 10; ++i){
      //rows
        for(int j = 0; j < 10; ++j){
          //columns
            for(int k = 0; k < 2; ++k){
              //square numbers
                board[i][j][k] = count;
            }
            ++count;
        }
    }
    //set ladder destination squares
    board[0][3][1] = 38;
    board[2][5][1] = 74;
    board[3][2][1] = 51;
    board[4][4][1] = 82;
    board[5][8][1] = 62;
    board[7][2][1] = 93;
    //set snake destination squares
    board[2][9][1] = 11;
    board[3][5][1] = 7;
    board[4][0][1] = 21;
    board[6][9][1] = 49;
    board[8][5][1] = 56;
    board[9][8][1] = 42;
}

//Moves counters on the snakes and ladders board
//and reports on the move.
void move(int board[10][10][2], int &row, int &col){
    int sq = board[row][col][0], msq, temp;
    int thrw = rand() % 6 + 1; //throw 6-sided die
    if(sq + thrw > 99){
      //can only reach square 100 with exact throw
        temp = 99 - sq;
        temp = thrw - temp;
        sq = 99 - temp;
    } else {
        if(col + thrw > 9){
          //new square is on next row on board
            sq = board[row + 1][(col + thrw) % 10][0];
        } else {
            sq = board[row][col + thrw][0];
        }
    }
    msq = board[sq / 10][sq % 10][1];
    cout << "Die throw was " << thrw << "; moving to " << sq + 1 << ".";
    if(sq != msq){
      //snake or ladder square
        if(sq < msq){
            cout << " Ladder! Climbing up to " << msq + 1 << ".";
        } else if(sq > msq){
            cout << " Snake! Sliding down to " << msq + 1 << ".";
        }
        sq = msq;
    }
    row = sq / 10;
    col = sq % 10;
}
