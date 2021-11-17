

bool isValidSudoku(char** board, int boardSize, int* boardColSize){
    int i, j, _row, _column, appeared[10];
    char current;
    for(_row=0; _row<9; _row++){
        for(i=1; i<=9; i++)
            appeared[i] = 0;
        for(j=0; j<9; j++){ //scan the row
            current = board[_row][j];
            if(current == '.')
                continue;
            if(appeared[current-'0'])
                return false;
            appeared[current-'0'] = 1;
        }
    }
    for(_column=0; _column<9; _column++){
        for(i=1; i<=9; i++)
            appeared[i] = 0;
        for(i=0; i<9; i++){ //scan the column
            current = board[i][_column];
            if(current == '.')
                continue;
            if(appeared[current-'0'])
                return false;
            appeared[current-'0'] = 1;
        }
    }
    for(_row=0; _row<9; _row+=3){
        for(_column=0; _column<9; _column+=3){
            for(i=1; i<=9; i++)
                appeared[i] = 0;
            for(i=0; i<3; i++){
                for(j=0; j<3; j++){
                    current = board[_row+i][_column+j];
                    if(current == '.')
                        continue;
                    if(appeared[current-'0'])
                        return false;
                    appeared[current-'0'] = 1;
                }
            }
        }
    }
    return true;
}