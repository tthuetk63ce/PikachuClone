#include <vector>
using namespace std;

class Board
{
	int _rows, _columns;	

	vector<vector<int>> _pokemons;

public:
	int _x = -1, _y = -1;

	Board(int _nRows, int _nColumns, int _nTypes, std::vector<int> count);

	int getNRows();

	int getNColumns();

	void addPokemon(int x, int y, int type);

	int getPokemon(int x, int y);

	bool selectPokemon(int x, int y);

	bool canConnect(int _x, int _y, int x, int y);

	vector<pair<int, int>> Board::findPath(int _x, int _y, int x, int y);

	void removePokemon(int x, int y);

};
