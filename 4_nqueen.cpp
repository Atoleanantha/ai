
#include<iostream>
using namespace std;

class QueenPlace{

    public:
    int N;
    int board[10][10];
    QueenPlace(int n){
        N=n;
        for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
             board[i][j]=0;
        }
       
    }


    }

    bool isSafe(int i, int j) {
        //check in row or column
    for(int m = 0; m < N; m++) {
        if(board[i][m] == 1 || board[m][j] == 1) {
            return false;
        }
    }
    //check in diagonal
    for(int m = 0; m < N; m++) {
        for(int n = 0; n < N; n++) {
            if(i + j == n + m || i - j == m - n) {
                if(board[m][n] == 1) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool NQueen(int n) {
    if(n == 0) {
        return true;
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(board[i][j] != 1 && isSafe(i, j)) {
                board[i][j] = 1;
                if(NQueen(n - 1) == true) {
                    return true;
                }
                board[i][j] = 0;
            }
        }
    }
    return false;
}

    void display(){
         for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
             cout<<board[i][j]<<"\t";
        }
       cout<<"\n";
    }
    }
};
int main(){
    int N;
    cout<<"Enter number of queens: ";
    cin>>N;
   QueenPlace q(N);
   q.display();
   q.NQueen(N);
   cout<<"After placing N queens: "<<endl;
   q.display();
    return 0;
}

