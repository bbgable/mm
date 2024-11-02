#include "Map.h"

void Map::init(RenderWindow* win, Sprite* sprite) {
	pwin = win;
	psprite = sprite;
	initGame();
}

void Map::initGame(){
	isRunning = true;
	for (int i = 1; i <= MAP_COL; ++i) {
		for (int j = 1; j <= MAP_ROW; ++j) {
			grid[i][j].setShowGridType(GridType::GT_HIDE);
			if (rand() % 6 == 0) {
				grid[i][j].setRealGridType(GridType::GT_BOMB);
			}
			else {
				grid[i][j].setRealGridType(GridType::GT_EMPTY);
			}
		}
	}
	for (int i = 1; i <= MAP_COL; ++i) {
		for (int j = 1; j <= MAP_ROW; ++j) {
			if (grid[i][j].IsEmpty()) {
				int cnt = 0;
				for (int k = 0; k < 8; ++k) {
					int ti = i + DIR[k][0];
					int tj = j + DIR[k][1];
					if (grid[ti][tj].IsRealBomb()) {
						cnt++;
					}
				}
				grid[i][j].setRealGridType((GridType)cnt);
			}
		}
	}
}

void Map::handleMouseEvent(Event& e, int x, int y) {
	if (e.type == Event::MouseButtonPressed) {
		if (e.key.code == Mouse::Left) {
			if (isRunning) {
				grid[x][y].ShowGrid();
				if (grid[x][y].IsShowBomb()) {
					isRunning = false;
				}
				else if (grid[x][y].IsEmpty()) {
					 for (int k = 0; k < 8; ++k) {
						int ti = x + DIR[k][0];
						int tj = y + DIR[k][1];
						if (grid[ti][tj].GetShowGridType() == GridType::GT_HIDE) {
							handleMouseEvent(e, ti, tj);
						}
					 }
				}
			}
			else {
				initGame();
			}
		}
		else if (e.key.code == Mouse::Right) {
			if (grid[x][y].GetShowGridType() == GridType::GT_HIDE) {
				grid[x][y].setShowGridType(GridType::GT_FLAG);
			}
			else if (grid[x][y].GetShowGridType() == GridType::GT_FLAG) {
				grid[x][y].setShowGridType(GridType::GT_HIDE);
			}
		}
	}
}

void Map::draw(int x, int y) {
	psprite->setScale(Vector2f(GRID_SIZE * 1.0 / ORI_GRID_SIZE, GRID_SIZE * 1.0 / ORI_GRID_SIZE));
	for (int i = 1; i <= MAP_COL; ++i) {
		for (int j = 1; j <= MAP_ROW; ++j) {
			if (!isRunning) {
				grid[i][j].ShowGrid();
			}
			psprite->setTextureRect(IntRect(ORI_GRID_SIZE * grid[i][j].GetShowGridType(), 0, ORI_GRID_SIZE, ORI_GRID_SIZE));
			psprite->setPosition(0.0f + i * GRID_SIZE, 0.0f + j * GRID_SIZE);
			pwin->draw(*psprite);
		}
	}
}