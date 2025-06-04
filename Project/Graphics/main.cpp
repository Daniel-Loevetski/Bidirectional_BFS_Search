
// Submitters:
//
// Yuval Hoffman - 206202533
// Daniel Loevetski - 209059120


#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "glut.h"
#include "Cell.h"
#include <queue>
#include <iostream>

using namespace std;

const int MSZ = 100;
const int WALL = 1;
const int SPACE = 0;
const int START = 2;
const int TARGET = 3;
const int BLACK = 4;
const int GRAY = 5;       
const int PATH = 6;
const int START_COLOR = 7; 
const int GOAL_COLOR = 8;  

int maze[MSZ][MSZ] = { 0 };
int visitedBy[MSZ][MSZ] = { 0 }; // 0 = unvisited, 1 = visited by start, 2 = visited by goal

queue<Cell*> startFrontier;
queue<Cell*> goalFrontier;

bool runStartBFS = false;
bool runGoalBFS = false;
bool foundPath = false;

Cell* meetingCellStart = nullptr;
Cell* meetingCellGoal = nullptr;

// Helper function: find a cell in a frontier matching (row, col)
Cell* FindCellInFrontier(queue<Cell*> frontier, int row, int col)
{
    while (!frontier.empty())
    {
        Cell* temp = frontier.front();
        frontier.pop();
        if (temp->getRow() == row && temp->getCol() == col)
            return temp;
    }
    return nullptr;
}

void InitMaze()
{
    int i, j;

    // Set frame of WALLS
    for (i = 0; i < MSZ; i++)
    {
        maze[0][i] = WALL;
        maze[MSZ - 1][i] = WALL;
        maze[i][0] = WALL;
        maze[i][MSZ - 1] = WALL;
    }

    // Random maze interior
    for (i = 1; i < MSZ - 1; i++)
    {
        for (j = 1; j < MSZ - 1; j++)
        {
            if (i % 2 == 1)
            {
                if (rand() % 10 < 2)
                    maze[i][j] = WALL;
                else
                    maze[i][j] = SPACE;
            }
            else
            {
                if (rand() % 10 < 7)
                    maze[i][j] = WALL;
                else
                    maze[i][j] = SPACE;
            }
        }
    }

    int startRow = MSZ / 2;
    int startCol = MSZ / 2;
    maze[startRow][startCol] = START;
    visitedBy[startRow][startCol] = 1;

    int targetRow, targetCol;
    do {
        targetRow = rand() % MSZ;
        targetCol = rand() % MSZ;
    } while (maze[targetRow][targetCol] != SPACE);

    maze[targetRow][targetCol] = TARGET;
    visitedBy[targetRow][targetCol] = 2;

    Cell* startCell = new Cell(startRow, startCol, nullptr);
    startCell->SetWhoVisited(1);
    startFrontier.push(startCell);

    Cell* goalCell = new Cell(targetRow, targetCol, nullptr);
    goalCell->SetWhoVisited(2);
    goalFrontier.push(goalCell);
}

void init()
{
    srand((unsigned int)time(0));

    glClearColor(0.5, 0.5, 0.5, 0);
    glOrtho(0, MSZ, 0, MSZ, -1, 1);

    InitMaze();
}

void DrawMaze()
{
    int i, j;

    for (i = 0; i < MSZ; i++)
    {
        for (j = 0; j < MSZ; j++)
        {
            switch (maze[i][j])
            {
            case WALL:
                glColor3d(0.4, 0, 0); 
                break;
            case SPACE:
                glColor3d(1, 1, 1); 
                break;
            case START:
                glColor3d(0.5, 0.5, 1); 
                break;
            case TARGET:
                glColor3d(1, 0, 0); 
                break;
            case BLACK:
                glColor3d(0.5, 0.5, 0.5); 
                break;
            case START_COLOR:
                glColor3d(0.5, 0.5, 0.6); // blue color (start search)
                break;
            case GOAL_COLOR:
                glColor3d(0.6, 0.4, 0.4); // red color (goal search)
                break;
            case PATH:
                glColor3d(1, 0.5, 1); 
                break;
            }
            glBegin(GL_POLYGON);
            glVertex2d(j, i);
            glVertex2d(j, i + 1);
            glVertex2d(j + 1, i + 1);
            glVertex2d(j + 1, i);
            glEnd();
        }
    }
}

void RestorePath()
{
    if (meetingCellStart == nullptr || meetingCellGoal == nullptr)
        return;

    // Walk back from meetingCellStart to START
    Cell* temp = meetingCellStart;
    while (temp != nullptr)
    {
        int row = temp->getRow();
        int col = temp->getCol();
        if (maze[row][col] != START && maze[row][col] != TARGET)
            maze[row][col] = PATH;
        temp = temp->getParent();
    }

    // Walk back from meetingCellGoal to TARGET
    temp = meetingCellGoal;
    while (temp != nullptr)
    {
        int row = temp->getRow();
        int col = temp->getCol();
        if (maze[row][col] != START && maze[row][col] != TARGET)
            maze[row][col] = PATH;
        temp = temp->getParent();
    }
}

void Expand(queue<Cell*>& frontier, int myVisitID, int otherVisitID, bool& pathFound)
{
    if (frontier.empty())
        return;

    Cell* current = frontier.front();
    frontier.pop();

    int row = current->getRow();
    int col = current->getCol();

    int dRow[4] = { 1, -1, 0, 0 };
    int dCol[4] = { 0, 0, 1, -1 };

    for (int i = 0; i < 4; i++)
    {
        int newRow = row + dRow[i];
        int newCol = col + dCol[i];

        if (maze[newRow][newCol] == WALL)
            continue;

        if (visitedBy[newRow][newCol] == 0)
        {
            Cell* neighbor = new Cell(newRow, newCol, current);
            neighbor->SetWhoVisited(myVisitID);
            frontier.push(neighbor);
            visitedBy[newRow][newCol] = myVisitID;

            // Set different colors for start path and goal path
            if (myVisitID == 1)
                maze[newRow][newCol] = START_COLOR;
            else
                maze[newRow][newCol] = GOAL_COLOR;
        }
        else if (visitedBy[newRow][newCol] == otherVisitID)
        {
            // Meeting point found
            meetingCellStart = current;

            if (myVisitID == 1)
                meetingCellGoal = FindCellInFrontier(goalFrontier, newRow, newCol);
            else
                meetingCellGoal = FindCellInFrontier(startFrontier, newRow, newCol);

            // Update the meeting cell color properly
            if (maze[newRow][newCol] != START && maze[newRow][newCol] != TARGET && maze[newRow][newCol] != PATH)
            {
                if (otherVisitID == 1)
                    maze[newRow][newCol] = START_COLOR;
                else
                    maze[newRow][newCol] = GOAL_COLOR;
            }

            pathFound = true;
            return;
        }
    }
}

void idle()
{
    if (foundPath || (!runStartBFS && !runGoalBFS))
    {
        glutPostRedisplay();
        return;
    }

    if (!foundPath)
    {
        for (int i = 0; i < 5 && !startFrontier.empty() && !foundPath; i++)
            Expand(startFrontier, 1, 2, foundPath);

        for (int i = 0; i < 5 && !goalFrontier.empty() && !foundPath; i++)
            Expand(goalFrontier, 2, 1, foundPath);

        if (foundPath)
        {
            cout << "Meeting point found! Drawing path...\n";
            RestorePath();
            runStartBFS = false;
            runGoalBFS = false;
        }
    }

    if (startFrontier.empty() && goalFrontier.empty() && !foundPath)
    {
        cout << "No solution: No more ways to advance!\n";
        runStartBFS = false;
        runGoalBFS = false;
    }

    glutPostRedisplay();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    DrawMaze();
    glutSwapBuffers();
}

void menu(int option)
{
    switch (option)
    {
    case 1: 
        runStartBFS = true;
        runGoalBFS = true;
        break;
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(400, 100);
    glutCreateWindow("Bidirectional BFS");

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutCreateMenu(menu);
    glutAddMenuEntry("Bidirectional BFS", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();

    glutMainLoop();

    return 0;
}
