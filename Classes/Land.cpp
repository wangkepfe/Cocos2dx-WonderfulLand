#include "Land.h"

USING_NS_CC;

bool Land::init()
{
	if(!Layer::init())
		return false;

	createLand();

//	batchNodeSoil = SpriteBatchNode::create("soil.png");
//	this->addChild(batchNodeSoil);

	return true;
}

void Land::createLand()
{
	int i, j, k;
	int position;

	const float mountainRate[5] = {
		0.1f,
		0.05f,
		0.01f,
		0.005f,
		0.001f
	};

	int landHeight[MAP_LENGTH];

	for (i = 0; i < MAP_LENGTH; i++)
	{
		landHeight[i] = MAP_HEIGHT / 2;
	}

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < mountainRate[i] * MAP_LENGTH; j++)
		{
			position = rand() % (MAP_LENGTH - 30) + 10;

			for (k = 1; k < i + 1; k++)
			{
				landHeight[position++] += k;
			}
			for (k = 0; k < rand() % 3 + 3; k++)
			{
				landHeight[position++] += i + 1;
			}
			for (k = i; k > 0; k--)
			{
				landHeight[position++] += k;
			}
		}
	}

	for (i = 0; i < MAP_LENGTH; i++)
	{
		for (j = 0; j < landHeight[i]; j++)
		{
			map[i][j] = 1;
		}
		for (; j < MAP_HEIGHT; j++)
		{
			map[i][j] = 0;
		}
	}
}

void Land::createBlock(int x,int y)
{
	int i, j;
	Node* node = Node::create();
	node->setPosition(Vec2(x * BLOCK_LENGTH * 100, y * BLOCK_HEIGHT * 100));
	node->setTag(x * 10000 + y);
	this->addChild(node);

	for (i = 0; i < BLOCK_LENGTH; i++)
	{
		for (j = 0; j < BLOCK_HEIGHT; j++)
		{
			if (map[x * BLOCK_LENGTH + i][y * BLOCK_HEIGHT + j] == 1)
			{
				Sprite* soil = Sprite::create("soil.png");
				soil->setPosition(Vec2(i * 100, j * 100));
				node->addChild(soil);
			}
		}
	}	
}

void Land::deleteBlock(int x, int y)
{
	Node* node = this->getChildByTag(x * 10000 + y);
	if (node == nullptr)
		return;
	node->removeAllChildren();
	node->removeFromParent();
}

void Land::drawLandUpdate(int playerX, int playerY)
{
	int new_block_position_x = playerX / BLOCK_LENGTH;
	int new_block_position_y = playerY / BLOCK_HEIGHT;

	if (block_position_x == new_block_position_x && block_position_y == new_block_position_y)
		return;

	int i, j;

	new_block_position_x -= BLOCK_DRAW_LENGTH / 2;
	block_position_x -= BLOCK_DRAW_LENGTH / 2;
	new_block_position_y -= BLOCK_DRAW_HEIGHT / 2;
	block_position_y -= BLOCK_DRAW_HEIGHT / 2;

	if (new_block_position_x > block_position_x)
	{
		for (i = block_position_x; i < new_block_position_x; i++)
		{
			for (j = 0; j < BLOCK_DRAW_HEIGHT; j++)
			{
				deleteBlock(i, j);
			}
		}
		for (i = new_block_position_x + BLOCK_DRAW_LENGTH; i > block_position_x + BLOCK_DRAW_LENGTH; i--)
		{
			for (j = 0; j < BLOCK_DRAW_HEIGHT; j++)
			{
				createBlock(i, j);
			}
		}
	}
	else if (new_block_position_x < block_position_x)
	{
		for (i = new_block_position_x; i < block_position_x; i++)
		{
			for (j = 0; j < BLOCK_DRAW_HEIGHT; j++)
			{
				createBlock(i, j);
			}
		}
		for (i = block_position_x + BLOCK_DRAW_LENGTH; i > new_block_position_x + BLOCK_DRAW_LENGTH; i--)
		{
			for (j = 0; j < BLOCK_DRAW_HEIGHT; j++)
			{
				deleteBlock(i, j);
			}
		}
	}

	if (new_block_position_y > block_position_y)
	{
		for (i = block_position_y; i < new_block_position_y; i++)
		{
			for (j = 0; j < BLOCK_DRAW_LENGTH; j++)
			{
				deleteBlock(i, j);
			}
		}
		for (i = new_block_position_y + BLOCK_DRAW_HEIGHT; i > block_position_y + BLOCK_DRAW_HEIGHT; i--)
		{
			for (j = 0; j < BLOCK_DRAW_LENGTH; j++)
			{
				createBlock(i, j);
			}
		}
	}
	else if (new_block_position_y < block_position_y)
	{
		for (i = new_block_position_y; i < block_position_y; i++)
		{
			for (j = 0; j < BLOCK_DRAW_LENGTH; j++)
			{
				createBlock(i, j);
			}
		}
		for (i = block_position_y + BLOCK_DRAW_HEIGHT; i > new_block_position_y + BLOCK_DRAW_HEIGHT; i--)
		{
			for (j = 0; j < BLOCK_DRAW_LENGTH; j++)
			{
				deleteBlock(i, j);
			}
		}
	}

	new_block_position_x += BLOCK_DRAW_LENGTH / 2;
	new_block_position_y += BLOCK_DRAW_HEIGHT / 2;

	block_position_x = new_block_position_x;
	block_position_y = new_block_position_y;
}

void Land::drawLandOnce(int playerX, int playerY)
{
	int i, j;
	int x = playerX / BLOCK_LENGTH;
	int y = playerY / BLOCK_HEIGHT;
	for (i = x - BLOCK_DRAW_LENGTH / 2; i < x - BLOCK_DRAW_LENGTH / 2 + BLOCK_DRAW_LENGTH; i++)
	{
		for (j = y - BLOCK_DRAW_HEIGHT / 2; j < y - BLOCK_DRAW_HEIGHT / 2 + BLOCK_DRAW_HEIGHT; j++)
		{
			createBlock(i, j);
		}
	}
}

void Land::deleteLand(int playerX, int playerY)
{
	int i, j;
	int x = playerX / BLOCK_LENGTH;
	int y = playerY / BLOCK_HEIGHT;
	for (i = x - BLOCK_DRAW_LENGTH / 2; i < x - BLOCK_DRAW_LENGTH / 2 + BLOCK_DRAW_LENGTH; i++)
	{
		for (j = y - BLOCK_DRAW_HEIGHT / 2; j < y - BLOCK_DRAW_HEIGHT / 2 + BLOCK_DRAW_HEIGHT; j++)
		{
			deleteBlock(i, j);
		}
	}
}


