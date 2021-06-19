#include <cocos2d.h>
#include <Board.h>

USING_NS_CC;
using namespace std;
class BoardView : public Layer
{
	Board* board;

	float _squareSize, _width, _height;

	vector<vector<Sprite*>> pokemons;

public:

	static Layer* createBoardView(Board* board);

	void showBoard();

	Sprite* addPokemon(int row, int column, int type);

	Vec2 positionOf(int row, int column);

	pair<int, int> findRowAndColumnOfSprite(Node* node);

	bool removePokemon(int row, int column);

	bool checkTouch(Touch* touch, Event* event);

	CREATE_FUNC(BoardView);
};
