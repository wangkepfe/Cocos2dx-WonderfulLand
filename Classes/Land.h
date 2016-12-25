#ifndef __LAND_H__
#define __LAND_H__

#define BLOCK_LENGTH 10
#define BLOCK_HEIGHT 10

#define BLOCK_DRAW_LENGTH 5
#define BLOCK_DRAW_HEIGHT 5

#define MAP_LENGTH 1000
#define MAP_HEIGHT 500

#include "WonderfulLand.h"

class Land : public cocos2d::Layer
{
public:
	CREATE_FUNC(Land);

	Land() {};
	virtual ~Land() {};

	virtual bool init() override;

	void drawLandUpdate(int playerX, int playerY);
	void drawLandOnce(int playerX, int playerY);
	void deleteLand(int playerX, int playerY);

private:
//	SpriteBatchNode* batchNodeSoil;

	short map[MAP_LENGTH][MAP_HEIGHT];
	short block[25][BLOCK_LENGTH][BLOCK_HEIGHT];

	int block_position_x;
	int block_position_y;

	void createLand();
	void createBlock(int x, int y);
	void deleteBlock(int x, int y);
};

#endif
