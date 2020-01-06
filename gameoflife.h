//Ian Hinze - 2014

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H
#include <SFML/Graphics.hpp>

class gameoflife
{
public:
    //Each function is explained within the .cpp
    gameoflife();
    gameoflife(int rSquares, int cSquares, int lifeW);
    void GameSignature();
    void DisplayCommandsList();
    void IncreaseSpeed();
    void DecreaseSpeed();
    void UpdateGameLogic();
    void ProcessInput(bool &pause);
    void DisplayGrid();
    void DefaultPattern();

private:
    int row;               //Number of pixels for the row
    int column;            //Number of pixels for the column
    int gridLines;         //The width of each square in the grid plus room for gridlines
    int cell;              //The width of each square in the grid
    int colCells;          //The number of column positions (for life)
    int rowCells;          //The number of row positions (for life)
    int grid[501][501];            //The array containing 0s and 1s for life
    int gridCopy[501][501];        //Used to store a copy of the field array
    sf::RenderWindow window;       //RenderWindow object used for all window activies
    sf::RectangleShape rectangle;  //RectangleShape object used for printing squares in the window
    bool pause;         //Boolean variable used for pausing the game
    int frameRate;      //Stores what the framerate is currently set to

    //The below functions are under private because either there's no reason for the user to
    //access them, or accessing outside of the .cpp would cause errors.
    void GameSetup(int rowSquares, int colSquares, int lifeWidth);
    void InitializeArray(int array[][501]);
    void CreateCopy();
    void ReturnCopy();
    int NumberAbove(int row, int col);
    int NumberBelow(int row, int col);
    int NumberLeftRight(int row, int col);
    void ToggleLife(int rowCoord, int colCoord);
    int Random(int lo, int hi);
    void RandomLife();
    bool SaveLifeState();
    bool LoadLifeState();
    void Options();
};

#endif // GAMEOFLIFE_H
