//Ian Hinze - 2014

//#include <iostream>
#include <gameoflife.h>
using namespace std;

int main(){
    bool run = true;
    gameoflife game(53,78,10);
    while(run){
        //The process here is very simple. Check for and process keyboard/mouse inputs, update the game
        //logic (the position of cells on the grid based on the game of life rules and any user input),
        //and then finally display the updated grid, bringing the game of life - to life.
        game.ProcessInput(run);       
        game.UpdateGameLogic();
        game.DisplayGrid();
    }

    return 0;
}
