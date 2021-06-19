#include "BoardView.h"
#include "algorithm"

Layer* BoardView::createBoardView(Board* board)
{
	auto boardView = BoardView::create();
	boardView->board = board;
	boardView->showBoard();
	return boardView;
}

void BoardView::showBoard()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	_squareSize = visibleSize.width / (board->getNColumns() + 2);
	_width = _squareSize * board->getNColumns();
	_height = _squareSize * board->getNRows();
	setContentSize({ _width, _height });

	pokemons.resize(board->getNRows());
	for (int i = 0; i < board->getNRows(); ++i) {
		pokemons[i].resize(board->getNColumns());
		for (int j = 0; j < board->getNColumns(); ++j) {	
		pokemons[i][j] = addPokemon(i, j, board->getPokemon(i, j));
		addChild(pokemons[i][j]);	
		}
	}
}

Sprite* BoardView::addPokemon(int row, int column, int type)
{
	auto pokemon = Sprite::create("res/" + to_string(type) + ".png");
	pokemon->setScaleX(_squareSize / (pokemon->getContentSize().width));
	pokemon->setScaleY(_squareSize / (pokemon->getContentSize().height));
	Vec2 position = positionOf(row, column);
	pokemon->setPosition(position);

	auto touchListen = EventListenerTouchOneByOne::create();
	touchListen->setSwallowTouches(true);
	touchListen->onTouchBegan = CC_CALLBACK_2(BoardView::checkTouch, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListen, pokemon);


	return pokemon;
}

Vec2 BoardView::positionOf(int row, int column)
{
	return Vec2(column * _squareSize + _squareSize / 2, _height - row * _squareSize - _squareSize / 2);
}

pair<int, int> BoardView::findRowAndColumnOfSprite(Node* node)
{
	for (int i = 0; i < board->getNRows(); ++i) {
		for (int j = 0; j < board->getNColumns(); ++j) {
			if (pokemons[i][j] == node) {
				return { i, j };
			}
		}
	}
	return { -1, -1 };
}

bool BoardView::removePokemon(int row, int column)
{
	if (pokemons[row][column] == nullptr) return false;
	board->removePokemon(row, column);
	removeChild(pokemons[row][column]);
	return true;
}
bool BoardView::checkTouch(Touch* touch, Event* event) {
	auto touchLocation = touch->getLocation() - this->getPosition();
	auto target = event->getCurrentTarget();
	if (target->getBoundingBox().containsPoint(touchLocation)) {
		auto p = findRowAndColumnOfSprite(target);
		if (board->selectPokemon(p.first, p.second)) {
			BoardView::removePokemon(board->_x, board->_y);
			BoardView::removePokemon(p.first, p.second);
			board->_x = -1;
			board->_y = -1;
			CCLOG("CURRENTLY SELECTED: row = %d , column = %d", -1, -1);
		}
		else {
			board->_x = p.first;
			board->_y = p.second;
			CCLOG("CURRENTLY SELECTED: row = %d , column = %d", p.first, p.second);
		}
		return true;
	}
	return false;

}