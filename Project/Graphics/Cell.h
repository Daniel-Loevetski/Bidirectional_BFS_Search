#pragma once
class Cell
{
private:
	int row, col;
	Cell* parent;
	int whoVisited; // 0 = unvisited, 1 = start, 2 = goal
public:
	Cell(int r, int c, Cell* p);
	int getRow() { return row; }
	int getCol() { return col; }
	Cell* getParent() { return parent; }
	void SetWhoVisited(int val) { whoVisited = val; }
	int GetWhoVisited() { return whoVisited; }
};

