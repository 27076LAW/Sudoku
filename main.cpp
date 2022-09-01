#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;
#define empty 0
#define N 9

bool isGridSafe(int grid[N][N], int row, int col, int num);
bool isEmptyLocation(int grid[N][N], int &row, int &col);
/* assign values to all the zero (not assigned) values for Sudoku solution
 */
bool SolveSudoku(int grid[N][N]){
    for(int row=0; row<N; row++){
        for(int col=0; col<N; col++){
            if(isEmptyLocation(grid, row, col) == true){
                for(int val=1; val<=9; val++){
                    if(isGridSafe(grid, row, col, val)){
                        grid[row][col]=val;
                        if(SolveSudoku(grid)==true){
                            return true;
                        }
                        else{
                            grid[row][col]=empty;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}
/* Check for entries that don't have a value. */
bool isEmptyLocation(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == empty)
                return true;
    return false;
}
/* Returns whether the assigned entry n in the particular row matches
   the given number num. */
bool UsedInRow(int grid[N][N], int prow, int number)
{
    for (int col = 0; col < N; col++)
        if (grid[prow][col] == number)
            return true;
    return false;
}
/* Returns true if the number num matches any number in the column */
bool UsedInCol(int grid[N][N], int pcol, int number)
{
    for (int row = 0; row < N; row++)
        if (grid[row][pcol] == number)
            return true;
    return false;
}
//Check if the entry used already in the grid box
bool UsedInBox(int grid[N][N], int boxBeginRow, int boxBeginCol, int number)

{
    bool tf = false;
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+boxBeginRow][col+boxBeginCol] == number)
                tf = true;
    return tf;
}
/* Checks if num can be assigned to a given prow,pcol location. */
bool isGridSafe(int grid[N][N], int prow, int pcol, int number)
{
    return !UsedInRow(grid, prow, number) && !UsedInCol(grid, pcol, number) &&
           !UsedInBox(grid, prow - prow % 3 , pcol - pcol % 3, number);
}
/* print result  */
void printResult(int finalgrid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
            cout<< finalgrid[row][col]<<"  ";
        cout<<endl;
    }
}
/* Main */
int main()
{
    int grid[N][N];
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            grid[i][j]=0;
        }
    }
    cout<<endl<<endl;
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<"***************************************************************"<<endl<<endl;
    cout<<"Let's start the game of SUDOKU"<<endl;
    cout<<"\n";
    cout<<"***************************************************************"<<endl;
    cout<<"---------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"***************************************************************"<<endl;
    cout<<"Initialize the grid"<<endl;
    cout<<"***************************************************************"<<endl;
    cout<<"Just fill the cells which contain numbers initially..."<<endl;
    cout<<"***************************************************************"<<endl;
    cout<<endl<<endl;
    
    for(int row=1; row<=N; row++){
        cout<<"Enter values for row="<<row<<" :"<<endl<<endl;
        for(int col=1; col<=N; col++){
            cout<<"Fill row="<<row<<" and col="<<col<<" : ";
            int val=-1;
            while(val<0 || val>9){
                cin>>val;
                if(val<0 || val>9) cout<<"Invalid Input! \n Enter again : "<<endl;
            }
            grid[row-1][col-1]=val;
        }
        cout<<endl;
    }
    cout<<"This is initial grid-"<<endl;
    printResult(grid);

    cout<<"Solving SUDOKU..."<<endl;
    bool ans = SolveSudoku(grid);
    cout<<"SOLVED!"<<endl;
    if (ans == true)
          printResult(grid);
    else
        cout<<"No solution found :("<<endl;
    return 0;
}