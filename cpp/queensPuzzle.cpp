#include<iostream>
#include<fstream>
using namespace std;

class queensPuzzle
{
private:
    int size;   //puzzle size
    int *queens;    //queens[i]=j means place queen at row i and column j
    int solutionCounter = 0;
public:
    queensPuzzle(); //clear queensPuzzle_out.txt
    void setSize(const int);  //set size and renew queens
    void printOut();    //print to queensPuzzle_out.txt
    int checkValid(const int);  //valid=1, invalid=0
    void placeQueen(const int);
};

int main()
{
    queensPuzzle queen;
    queen.setSize(8);
    queen.placeQueen(0);
    return 0;
}

queensPuzzle::queensPuzzle(){
    fstream FILE;
    FILE.open("queensPuzzle_out.txt", ios::out | ios::trunc);
    if(!FILE){
        cerr<<"open file error at constructor";
        exit(1);
    }
    FILE.close();
}

void queensPuzzle::setSize(const int size){
    delete [](this->queens);
    this->size = size;
    this->queens = new int[size];
}

void queensPuzzle::printOut(){
    fstream FILE;
    int i, j;
    FILE.open("queensPuzzle_out.txt", ios::out | ios::app);
    if(!FILE){
        cerr<<"open file error";
        exit(1);
    }
    FILE<<solutionCounter<<"-th Solution:"<<endl;
    for(i=0; i<size; i++){
        for(j=0; j<size; j++){
            if(queens[i]==j)
                FILE<<'1'<<' ';
            else
                FILE<<'0'<<' ';
        }
        FILE<<endl;
    }
    FILE<<endl;
    FILE.close();
}

int queensPuzzle::checkValid(const int rowIndex){   //queens[rowIndex]=columnIndex
    int i;
    for(i=0; i<rowIndex; i++){
        if(queens[i] == queens[rowIndex])    //a column contains two queens
            return 0;   //invalid
        if((rowIndex-i) == abs(queens[rowIndex]-queens[i]))   //a diagonal contains two queens
            return 0;   //invalid
    }
    return 1;   //valid
}

void queensPuzzle::placeQueen(const int rowIndex){
    int columnIndex;
    for(columnIndex=0; columnIndex<size; columnIndex++){
        if(rowIndex==size){ //if find a solution
            solutionCounter++;
            printOut();
            return;
        }
        queens[rowIndex] = columnIndex;
        if(checkValid(rowIndex))    //if valid, place the queen at next row
            placeQueen(rowIndex+1);
        // if not valid, continue loop, which places row i queen at next column
    }
}