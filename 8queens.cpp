#include <iostream>

using namespace std;

const int ROWS = 8, COLS = 8;

void display(const char board[][COLS]){
    cout << "   1  2  3  4  5  6  7  8\n";
    for(int row = 0; row < ROWS; row++){
        cout << row +1 << "  ";
        for(int col = 0; col < COLS;col++){
            cout << board[row][col] << "  "; 
        }
        cout << endl;
    }

}

bool check(const char board[][COLS], int row, int col){

    for(int i = 0; i < ROWS; i++){ // check column
        if(board[i][col] == 'Q'){return false;}
        if(board[row][i] == 'Q'){return false;}
    }

    for(int r = row + 1, c = col + 1; r < ROWS && c < ROWS; r++,c++){
        if(board[r][c] == 'Q'){return false;}
    }
    for(int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--,c--){
        if(board[r][c] == 'Q'){return false;}
    }
    for(int r = row + 1, c = col - 1; r < ROWS && c >= 0; r++,c--){
        if(board[r][c] == 'Q'){return false;}
    }
    for(int r = row - 1, c = col + 1; r >= 0 && c < ROWS; r--,c++){
        if(board[r][c] == 'Q'){return false;}
    }
    
    return true;
}

bool nQueens(char board[][COLS],int row,int initial){
    bool status = false;
    if(row == ROWS){
        return true;
    }

    if(row == initial && row == ROWS -1){
        return true;
    }

    if(row == initial){
        row++;
    }

    for(int col = 0; col < COLS; col++){
        if(check(board, row, col)){

            board[row][col] = 'Q';
            status = nQueens(board, row+1,initial);
            
            if(!status){
                board[row][col] = '-';

            }else{
                return true;
            }
            
        }
    }
    return false;

}

int main(int argc, char* argv[]){

    char board[ROWS][COLS] = {};

    int row, column;

    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS;col++){
            board[row][col] = '-';
        }
    }

    do{
        
        cout << "Give inital coordinates: ";
        cin >> row >> column;

    }while(row < 1 || column < 1 || row > ROWS || column > COLS);


    board[row -1][column -1] = 'Q';
    nQueens(board,0,row - 1);

    display(board);

    return 0;
}
