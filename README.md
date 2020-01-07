# Game-of-Life
2014 Ian Hinze, Solo School Project, PCC
Graphical implementation of John Conway's 1970 concept for "Game of Life"

Build Dependencies: SFML

Portable Version: There is a standalone portable version if you want to quickly try this game. 
Simply download the zip file from the repo, and run Game_of_Life.exe


GAME OF LIFE:
"Game of life" is a computer simulation of John Conway's original 1970 concept for the game.
The rules for how the game works can be viewed upon launching the game.
This program implements SFML to easily create a graphical user interface for the game to be played
and displayed. The biggest challenge of bringing the graphics to life was associating each cell on
the screen with a position in an array. I managed to place both of them into a loop that changes
the position of the squares being printed along with the position of the array, allowing each
square to be blue or green, depending on the state of the array. The logic of the game was fairly
easy to implement, as I just had to design functions that would count up the number of live cells
around each individual cell by looking at different positions of the array. Then the rest was just
four "if"  statements for the rules of the game. Example: If live cell and neighbors>3, stop living.
SFML made it easy to manage the window and implement buttons. The logic here was also simple.
For example, if the space key is pressed, then the boolean "pause" = true. When "pause" = true,
the game logic is set to not update, making the game stand still. The biggest button challenge
was getting the position of the mouse to correspond to values in the array. Fortunately, SFML has
a function that returns the position of the mouse. Then I just had to reverse engineer the loop I
use for printing the grid to change the array based on mouse position. Whenever possible, I recycled
code to make things more efficient. There were pieces of code that I reworked, as mentioned above,
and then there were also functions, such as the gamesetup() function, which I needed to use in
multiple places (in this case, for both of the gameoflife constructors). The main runs off of three
functions: Process input, update game logic, and display grid. These three functions collectively
bring together all of the other functions within the class, giving it a simple top-down design.
When I was designing the save/load functions, I ran into conceptual problems because I also
wanted to add a way to change the grid dimensions. Therefore I made sure that both the status
of the array and the current dimensions of the grid were saved to a text file. Then when a user
tried to load a save state that had used a different set of grid dimensions, the program would simply
close the current window and open up a new one with the appropriate settings. The fact that the borders
in my version of game of life loop around to the other side is something that was implemented later in
my program. For the cases where the neighbors of a certain cell were off the border off the grid, I had
to redesign my code to adjust which cells are being looked at as "neighbors". This was done by seeing if
the cell you should be looking at is out of bounds (a position of -1 or over max value for an array) and
then adjusting the array coordinates to be looking at the opposite side of the grid.
Overall, sfml really made this project easy to come together. The graphics library had all I needed and
managing a window is really easy with the Renderwindow object. You can use limitframerate() to change
the speed of your game in a simple way, and it's very simple to figure out what other functions do what
because they all have pretty straightforward names. I also only had to use one rectangle object for my
entire grid. This was easy to accomplish because I just had to keep changing the position of the shape
in a loop and then change which squares get printed in green to represent live cells. The SFML tutorials
are pretty good and will help you easily get started on a project like this. It's been made very simple
to dive right into.
