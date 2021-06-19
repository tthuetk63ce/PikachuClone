#include "Board.h"
#include <map>
#include "queue"
#include "time.h"
using namespace std;
Board::Board(int _nRows, int _nColumns, int _nTypes, vector<int> count) :
	_rows(_nRows), _columns(_nColumns),
	_pokemons(vector<vector<int>>(_nRows, vector<int>(_nColumns, -1)))
{
	map<int, int> countType; 
	srand(time(NULL));
	for (int i = 0; i < _nRows; ++i) {
		for (int j = 0; j < _nColumns; ++j) {
			int type;
			do {
				type = rand() % _nTypes;
			} while (countType[type] >= count[type]);
			countType[type] += 1;
			addPokemon(i, j, type + 1);
		}
	}
}

int Board::getNRows()
{
	return _rows;
}

int Board::getNColumns()
{
	return _columns;
}

void Board::addPokemon(int x, int y, int type)
{
	_pokemons[x][y] = type;
}

int Board::getPokemon(int x, int y)
{
	return _pokemons[x][y];
}

void Board::removePokemon(int x, int y)
{
	_pokemons[x][y] = -1;
}

bool Board::selectPokemon(int x, int y) {
	if (_x == -1 && _y == -1 || _pokemons[x][y] != _pokemons[_x][_y] || !canConnect(_x, _y, x, y)) {
		return false;
	}
	return true;
}
bool Board::canConnect(int _x, int _y, int x, int y)
{
	auto path = findPath(_x, _y, x, y);
	return path.size() >= 2 && path.size() <= 4;
}
vector<pair<int, int>> Board::findPath(int _x, int _y, int x, int y)
{
	vector<vector<int>> e(_rows + 2, vector<int>(_columns + 2, 0));
	for (int i = 0; i < _rows; ++i)
	{
		for (int j = 0; j < _columns; ++j)
		{
			e[i + 1][j + 1] = _pokemons[i][j] != -1;
		}
	}
	pair<int, int> s = { _x + 1, _y + 1 };
	pair<int, int> t = { x + 1, y + 1 };

	const int dx[4] = { -1, 0, 1, 0 };
	const int dy[4] = { 0, 1, 0, -1 };
	deque<pair<int, int>> q;
	vector<vector<pair<int, int>>> trace(e.size(), vector<pair<int, int>>(e[0].size(), make_pair(-1, -1)));
	q.push_back(t);
	trace[t.first][t.second] = make_pair(-2, -2);
	e[s.first][s.second] = 0;
	e[t.first][t.second] = 0;
	while (!q.empty()) {
		auto u = q.front();
		q.pop_front();
		if (u == s) break;
		for (int i = 0; i < 4; ++i) {
			int x = u.first + dx[i];
			int y = u.second + dy[i];
			while (x >= 0 && x < e.size() && y >= 0 && y < e[0].size() && e[x][y] == 0) {
				if (trace[x][y].first == -1) {
					trace[x][y] = u;
					q.push_back({ x, y });
				}
				x += dx[i];
				y += dy[i];
			}
		}
	}

	
	vector<pair<int, int>> res;
	if (trace[s.first][s.second].first != -1) {
		while (s.first != -2) {
			res.push_back({ s.first - 1, s.second - 1 });
			s = trace[s.first][s.second];
		}
	}
	return res;
}