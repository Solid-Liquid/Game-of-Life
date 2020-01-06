//Ian Hinze - 2014

#include "gameoflife.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

gameoflife::gameoflife(){
    //Initializes the game with default grid dimensions and prints instructions in the command window.
    GameSetup(53,78,10);
    GameSignature();
    DisplayCommandsList();
}

gameoflife::gameoflife(int rowSquares, int colSquares, int lifeWidth){
    //Initializes the game with grid dimensions that are set within main, and prints instructions in the
    //command window
    GameSetup(rowSquares, colSquares, lifeWidth);
    GameSignature();
    DisplayCommandsList();
}

void gameoflife::GameSetup(int rowSquares, int colSquares, int lifeWidth){
    //Arguements: (# squares for row, # squares for column, width of squares in pixels)
    //Sets up the game. I created this function so that I wouldn't repeat code
    //in the constructors for the gameoflife class. Variables are explained in the .h
    cell = lifeWidth;
    gridLines = cell + 2;  //Each +2 is there to make room for the gridlines, which are 2 pixels thick.
    row = (rowSquares*gridLines) + 2;
    column = (colSquares*gridLines) + 2;
    pause = true;
    colCells = colSquares;
    rowCells = rowSquares;
    window.create(sf::VideoMode(column, row), "Game of Life");
    frameRate = 10;
    window.setFramerateLimit(30);
    sf::Vector2f size(cell,cell);
    rectangle.setSize(size);
    rectangle.setFillColor(sf::Color::Blue);
    InitializeArray(grid);
    InitializeArray(gridCopy);
    DefaultPattern();
    srand((unsigned)time(0));
}

void gameoflife::InitializeArray(int array[][501]){
    //Fills an array with 0's (which indicates a dead square) and a terminating -1 for each column.
    for(int r=0; r<rowCells; r++){
        for(int c=0; c<colCells; c++){
            array[r][c] = 0;
        }
        array[r][colCells] = -1;
    }
}

void gameoflife::GameSignature(){
    cout<<"== Game of Life ==    (Ian Hinze, 2014. Implements SFML v.2.1)";
    cout<<"\nThis program offers a computer simulation of John Conway's original 1970"
        <<"\nconcept for the Game of Life. Within the grid, green cells represent \"life\","
        <<"\nwhereas blue cells can be thought of as \"dead\", or the absence of \"life.\""
        <<"\nEvery cell in the grid follows a set of rules for how \"life\" evolves:"
        <<"\n(1) A live cell with 2 or 3 neighbors will remain alive"
        <<"\n(2) A live cell with fewer than 2 live neighbors will die"
        <<"\n(3) A live cell with more than 3 live neighbors will die"
        <<"\n(4) A dead cell with exactly 3 live neighbors will become alive";
}

void gameoflife::DisplayCommandsList(){
    cout<<"\n\nCommands List:"
        <<"\n -----------------------------------------------------------------------------"
        <<"\n | [Space]-Pause/Play the Game                                               |"
        <<"\n | [Left Arrow]-Slow Down   [Right Arrow]-Speed Up                           |"
        <<"\n | [G]-Close the current grid and set up a new one (opens in this window)    |"
        <<"\n |                                                                           |"
        <<"\n | While the game is paused, you can:                                        |"
        <<"\n | [Mouse]-Click any cell on the grid to toggle it alive/dead                |"
        <<"\n | [C]-Clear all live cells on the grid                                      |"
        <<"\n | [R]-Fill the grid with random live cells                                  |"
        <<"\n | [S]-Save your current grid, including dimensions and alive/dead cells     |"
        <<"\n | [L]-Load your previously grid (even after closing)                        |"
        <<"\n -----------------------------------------------------------------------------\n\n";
}

void gameoflife::DefaultPattern(){
    //Simply loads a pattern that the user can begin playing with immedietly.
    grid[26][31]=1;
    grid[26][34]=1;
    grid[26][35]=1;
    grid[26][37]=1;
    grid[26][38]=1;
    grid[26][39]=1;
    grid[26][40]=1;
    grid[26][42]=1;
    grid[27][31]=1;
    grid[27][32]=1;
    grid[27][33]=1;
    grid[27][34]=1;
    grid[27][35]=1;
    grid[27][36]=1;
    grid[27][38]=1;
    grid[27][39]=1;
    grid[27][42]=1;

}

void gameoflife::CreateCopy(){
    //Creates a copy of "grid" in "gridcopy."
    for(int r=0; r<rowCells; r++){
        for(int c=0; c<colCells; c++){
            gridCopy[r][c] = grid[r][c];
        }
    }
}

void gameoflife::ReturnCopy(){
    //Copies the new values (after updating game logic) into "grid."
    for(int r=0; r<rowCells; r++){
        for(int c=0; c<colCells; c++){
            grid[r][c] = gridCopy[r][c];
        }
    }
}

int gameoflife::NumberAbove(int row, int col){
    //Determines the number of live cells above a cell.
    //Before adding to the count, the game adjusts for offscreen spaces in the grid by
    //changing the position it's looking at to the opposite side of the grid.
    int count=0;
    int leftR = row-1, leftC = col-1;
    if(leftR<0){
        leftR=rowCells-1;
    }
    if(leftC<0){
        leftC=colCells-1;
    }
    if(grid[leftR][leftC]==1){
        count++;
    }


    int midR = row-1, midC = col;
    if(midR<0){
        midR=rowCells-1;
    }
    if(grid[midR][midC]==1){
        count++;
    }


    int rightR = row-1, rightC = col+1;
    if(rightR<0){
        rightR=rowCells-1;
    }
    if(rightC>colCells-1){
        rightC=0;
    }
    if(grid[rightR][rightC]==1){
        count++;
    }


    return count;
}

int gameoflife::NumberBelow(int row, int col){
    //Determines the number of live cells below a cell.
    int count=0;
    int leftR = row+1, leftC = col-1;
    if(leftR>rowCells-1){
        leftR=0;
    }
    if(leftC<0){
        leftC=colCells-1;
    }
    if(grid[leftR][leftC]==1){
        count++;
    }


    int midR = row+1, midC = col;
    if(midR>rowCells-1){
        midR=0;
    }
    if(grid[midR][midC]==1){
        count++;
    }


    int rightR = row+1, rightC = col+1;
    if(rightR>rowCells-1){
        rightR=0;
    }
    if(rightC>colCells-1){
        rightC=0;
    }
    if(grid[rightR][rightC]==1){
        count++;
    }


    return count;
}

int gameoflife::NumberLeftRight(int row, int col){
    //Determines the number of live cells to left and right of a cell.
    int count=0;
    int leftR = row, leftC = col-1;
    if(leftC<0){
        leftC=colCells-1;
    }
    if(grid[leftR][leftC]==1){
        count++;
    }


    int rightR = row, rightC = col+1;
    if(rightC>colCells-1){
        rightC=0;
    }
    if(grid[rightR][rightC]==1){
        count++;
    }


    return count;
}

void gameoflife::UpdateGameLogic(){
    //Processes game logic and updates the "grid" array accordingly.
    if(pause){
        //This is how I pause the game. If pause=true, then the cells will not change.
        return;
    }

    //After having the grid copied, the below checks the game rules by referencing
    //the number of neighbors that each cell has.
    CreateCopy();
    for(int r=0; r<rowCells; r++){
        for(int c=0; c<colCells; c++){
            int neighbors=0;
            neighbors+=NumberAbove(r,c);
            neighbors+=NumberBelow(r,c);
            neighbors+=NumberLeftRight(r,c);

            if(grid[r][c]==1){
                if(neighbors<2){
                    gridCopy[r][c]=0;
                }
                else if(neighbors>3){
                    gridCopy[r][c]=0;
                }
            }
            else if(grid[r][c]==0 && neighbors==3){
                gridCopy[r][c]=1;
            }
        }
    }
    ReturnCopy();
}

void gameoflife::IncreaseSpeed(){
    //Moves the framerate up to increase speed within a range of settings (1,5,10,15,20).
    if(frameRate==1){
        frameRate=5;
        window.setFramerateLimit(frameRate);
    }
    else if(frameRate==5){
        frameRate=10;
        window.setFramerateLimit(frameRate);
    }
    else if(frameRate==10){
        frameRate=15;
        window.setFramerateLimit(frameRate);
    }
    else if(frameRate==15){
        frameRate=30;
        window.setFramerateLimit(frameRate);
    }
}

void gameoflife::DecreaseSpeed(){
    //Moves the framerate down to decrease speed within a range of settings (1,5,10,15,20).
    if(frameRate == 30){
        frameRate=15;
        window.setFramerateLimit(frameRate);
    }
    if(frameRate == 15){
        frameRate=10;
        window.setFramerateLimit(frameRate);
    }
    else if(frameRate == 10){
        frameRate=5;
        window.setFramerateLimit(frameRate);
    }
    else if(frameRate == 5){
        frameRate=1;
        window.setFramerateLimit(frameRate);
    }
}

void gameoflife::ToggleLife(int rowCoord, int colCoord){
    //Toggles life on/off based on the position of a mouseclick (the coordinates are passed in as args).
    //It does this by checking if the mouseclick is within a range of pixels that make up a cell.
    //Each cell on the grid corresponds to a 1/0 in the "grid" array, and will change if that cell
    //corresponds to the area of pixels that was clicked.
    int arrayR=0;
    int arrayC=0;
    for(int r=0; r<row; r=r+gridLines){
        arrayC=0;
        for(int c=0; c<column; c=c+gridLines){
            if( (rowCoord>=r+2 && rowCoord<=r+2+cell) && (colCoord>=c+2 && colCoord<=c+2+cell) ){
               if(grid[arrayR][arrayC]==1){
                   grid[arrayR][arrayC]=0;
               }
               else if(grid[arrayR][arrayC]==0){
                   grid[arrayR][arrayC]=1;
               }
            }
            arrayC++;
        }
        arrayR++;
    }
}

int gameoflife::Random(int lo, int hi) {
    //Generates a random number from lo to hi.
    int range = hi-lo+1;
    int randomNumber = lo + (rand() % range);
    return randomNumber;
}

void gameoflife::RandomLife(){
    //Places random live cells within the grid. Triple filters the generation of live cells
    //so that they appear less often.
    for(int r=0; r<rowCells; r++){
        for(int c=0; c<colCells; c++){
            grid[r][c] = Random(0,1);
            if(grid[r][c]==1){
                grid[r][c] = Random(0,1);
                if(grid[r][c]==1){
                    grid[r][c] = Random(0,1);
                }
            }
        }
    }
}

bool gameoflife::SaveLifeState(){
    //Saves the state of the game in a text file.
    ofstream outFile;
    outFile.open("LifeSaveState.txt");
    if(outFile.fail()){
        return false;
    }

    //The next three lines store the current grid dimensions in the file.
    outFile<<rowCells<<" ";
    outFile<<colCells<<" ";
    outFile<<cell<<" ";

    //This loop stores the status of the "grid" array in the file.
    for(int r=0; r<rowCells; r++){
        outFile<<endl;
        for (int c=0; c<colCells; c++){
            outFile<<grid[r][c]<<" ";
        }
    }
    outFile.close();
    return true;
}

bool gameoflife::LoadLifeState(){
    //Loads the state of a previous game from a text file, including the grid dimensions and
    //the status of the "grid" array.
    ifstream inFile;
    inFile.open("LifeSaveState.txt");
    if(inFile.fail()){
        return false;
    }

    int x,y,z;
    inFile>>x;
    inFile>>y;
    inFile>>z;

    if(x!=rowCells || y!=colCells || z!=cell){
        window.clear();
        GameSetup(x,y,z);
    }

    for(int r=0; r<rowCells; r++){
        for (int c=0; c<colCells; c++){
            inFile>>grid[r][c];
        }

    }
    inFile.close();
    return true;
}

void gameoflife::Options(){
    //Opens an options menu for changing the dimensions of the grid.
    cout<<"\nChange the dimensions of the grid:";
    bool valid=false;
    int newCol, newRow, newSquare;
    while(valid==false){
        cout<<"\nEnter the new width for each cell (10=default): ";
        cin>>newSquare;
        cout<<"Enter the new number of cells by row (53=default, 500=max): ";
        cin>>newRow;
        cout<<"Enter the new number of cells by column (78=default, 500=max): ";
        cin>>newCol;

        if(newSquare>0 && newRow>0 && newRow<=500 && newCol>0 && newCol<=500){
            //Ensures that the inputted grid dimensions are valid.
            valid=true;
        }
        else{
            cout<<"\nInvalid input! All values must be greater than zero.\n";
        }
    }
    window.clear();
    GameSetup(newRow,newCol,newSquare);
}

void gameoflife::ProcessInput(bool &run){
    //This function detects and processes key presses and mouse clicks.
    //If this button is clicked, do this. For further explanation, see
    //the function or variable that each "if" corresponds to.
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            run = false;
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Escape){
                run = false;
            }
            if(event.key.code == sf::Keyboard::Space){
                if(pause == true){
                    window.setFramerateLimit(frameRate);
                    pause = false;
                }
                else if(pause == false){
                    window.setFramerateLimit(30);
                    pause = true;
                }
            }
            if(event.key.code == sf::Keyboard::Right){
                IncreaseSpeed();
            }
            if(event.key.code == sf::Keyboard::Left){
                DecreaseSpeed();
            }
            if(event.key.code == sf::Keyboard::C && pause==true){
                InitializeArray(grid);
            }
            if(event.key.code == sf::Keyboard::R && pause==true){
                RandomLife();
            }
            if(event.key.code == sf::Keyboard::G && pause==true){
                window.close();
                Options();
            }
            if(event.key.code == sf::Keyboard::S && pause==true){
                if(SaveLifeState()){
                    cout<<"File Successfully Saved!\n\n";
                }
                else{
                    cout<<"File not found.\n\n";
                }
            }
            if(event.key.code == sf::Keyboard::L && pause==true){
                if(LoadLifeState()){
                    cout<<"File Successfully Loaded!\n\n";
                }
                else{
                    cout<<"File not found.\n\n";
                }
            }
        }
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && pause==true){
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            int colCoord = localPosition.x;
            int rowCoord = localPosition.y;
            //cout<<rowCoord<<" "<<colCoord<<endl;
            //Use the above line of code to debug any problems with mouse tracking.
            ToggleLife(rowCoord,colCoord);
        }
    }
}

void gameoflife::DisplayGrid(){
    //Displays all of the visual pieces that make up the grid.
    //The color of the squares change depending on if each value of
    //the "field" array is 0 or 1, dead or alive. The loop is set up so that
    //each iteration corresponds to a different position (in coordinates) on the
    //grid, which corresponds to a different row/column in the "grid" array.
    window.clear();
    int arrayR=0;
    int arrayC=0;
    for(int r=0; r<row; r=r+gridLines){
        arrayC=0;
        for(int c=0; c<column; c=c+gridLines){
            rectangle.setPosition(c+2,r+2);
            window.draw(rectangle);
            if(grid[arrayR][arrayC] == 1){
                rectangle.setFillColor(sf::Color::Green);
                window.draw(rectangle);
                rectangle.setFillColor(sf::Color::Blue);
            }
            arrayC++;
        }
        arrayR++;
    }
    window.display();
}
