
#include <iostream>
#include <windows.h>
#include "Stack.h"
#include "Position.h"

using namespace std;

int entryPoint()
{
    const char ENTRANCE = 'I';
    const char EXIT = 'O';
    const char WALL = '#';
    const char ROAD = ' ';
    const char EXPLORED = 'e';

    const int ROW = 8;
    const int COLUMN = 16;

    char maze[ROW][COLUMN] =
    {
        "######I########",
        "### ##  ##   ##",
        "# #  ##    # ##",
        "# ## ### ### ##",
        "#      ###   ##",
        "### ## ##### ##",
        "##  ##       ##",
        "###O###########",
    };

    Position mazeEntrance;
    mazeEntrance.x = 0;
    mazeEntrance.y = 6;

    // Make two copies of the original map
    char mazeCopy[ROW][COLUMN];   // Used to calculate the path
    char mazeDisplay[ROW][COLUMN];   // Used to display the path
    
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            mazeCopy[i][j] = maze[i][j];
            mazeDisplay[i][j] = maze[i][j];
        }
    }

    Stack path(ROW*COLUMN);

    Position currentPosition;

    currentPosition = mazeEntrance;

    while (true)
    {   
        if (mazeCopy[currentPosition.x][currentPosition.y] == EXIT) break;

        // Get the maze element at each direction of the current position
        char positionUp = mazeCopy[currentPosition.x - 1][currentPosition.y];
        char positionRight = mazeCopy[currentPosition.x][currentPosition.y + 1];
        char positionDown = mazeCopy[currentPosition.x + 1][currentPosition.y];
        char positionLeft = mazeCopy[currentPosition.x][currentPosition.y - 1];

        // Mark this position as explored, then go up one position
        if (( positionUp == ROAD || positionUp == EXIT ) && currentPosition.x - 1 >= 0)
        {
            path.Push(currentPosition);
            mazeCopy[currentPosition.x][currentPosition.y] = EXPLORED;
            currentPosition.x--;
        }

        // Mark this position as explored, then go right one position
        else if (( positionRight == ROAD || positionRight == EXIT) && currentPosition.y + 1 < COLUMN)
        {
            path.Push(currentPosition);
            mazeCopy[currentPosition.x][currentPosition.y] = EXPLORED;
            currentPosition.y++;
        }

        // Mark this position as explored, then go down one position
        else if ((positionDown == ROAD || positionDown == EXIT) && currentPosition.x + 1 < ROW)
        {
            path.Push(currentPosition);
            mazeCopy[currentPosition.x][currentPosition.y] = EXPLORED;
            currentPosition.x++;
        }

        // Mark this position as explored, then go left one position
        else if ((positionLeft == ROAD || positionLeft == EXIT) && currentPosition.y >= 0)
        {
            path.Push(currentPosition);
            mazeCopy[currentPosition.x][currentPosition.y] = EXPLORED;
            currentPosition.y--;
        }

        // Mark this position as a WALL, then go back one position
        else
        {
            mazeCopy[currentPosition.x][currentPosition.y] = WALL;
            currentPosition = path.Pop();
        }
    }
    
    int finalSize = path.GetLength();

    Position *rightPath = new Position[ROW*COLUMN];

    for (int i = finalSize - 1; i >= 0; i--)
    {
        rightPath[i] = path.Pop();
    }



    // Output the Animation of Walking the path

    for (int i = 0; i < finalSize; i++)
    {
        cout << "Maze" << endl;
        Position tempPosition = rightPath[i];
        mazeDisplay[tempPosition.x][tempPosition.y] = '*';

        for (int a = 0; a < ROW; a++)
        {
            for (int b = 0; b < COLUMN; b++)
            {
                cout << mazeDisplay[a][b];
            }
            cout << endl;
        }

        Sleep(200);
        system("cls");
        mazeDisplay[tempPosition.x][tempPosition.y] = ' ';
    }



    // Print out the complete path

    cout << "Original Map: " << endl;
    for (int a = 0; a < ROW; a++)
    {
        for (int b = 0; b < COLUMN; b++)
        {
            cout << maze[a][b];
        }
        cout << endl;
    }

    cout << endl;
    cout << "Right Path: " << endl;

    for (int i = 0; i < finalSize; i++)
    {
        Position temp = rightPath[i];
        cout << temp.x + 1 << "," << temp.y + 1 << '\t';
        if ((i + 1) % 5 == 0) cout << endl;
    }

    cout << endl;

    return 0;
}