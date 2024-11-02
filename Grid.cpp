#include "Grid.h"

Grid::Grid() {
	m_realGridType = GridType::GT_EMPTY;
	m_showGridType = GridType::GT_EMPTY;
}
void Grid::setShowGridType(GridType showGridType) {
	m_showGridType = showGridType;
}
void Grid::setRealGridType(GridType realGridType) {
	m_realGridType = realGridType;
}
void Grid::ShowGrid() {
	m_showGridType = m_realGridType;
}

GridType Grid::GetShowGridType() const {
	return m_showGridType;
}

bool Grid::IsEmpty() const {
	return m_realGridType == GridType::GT_EMPTY;
}
bool Grid::IsRealBomb() const {
	return m_realGridType == GridType::GT_BOMB;
}
bool Grid::IsShowBomb() const {
	return m_showGridType == GridType::GT_BOMB;
}