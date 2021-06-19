#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "BoardView.h"
USING_NS_CC;
using namespace std;
int x = 16;
int y = 4;
int _gRow = 8;
int _gColumns = 8;


Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
  /*  auto sprite = Sprite::create("res/pikachu_bg1.jpg");
    sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(sprite, 0);*/
    showBoard();

    return true;
}


Layer* GameScene::showBoard()
{
    vector<int> count(x, y);
    Board* board = new Board(_gRow, _gColumns, x, count);
    auto boardView = BoardView::createBoardView(board);
    this->addChild(boardView, 1);
    float x = (Director::getInstance()->getVisibleSize().width - boardView->getContentSize().width) / 2;
    float y = (Director::getInstance()->getVisibleSize().height - boardView->getContentSize().height) / 2;
    boardView->setPosition({ x, y });
    return boardView;
}