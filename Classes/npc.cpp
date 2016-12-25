#include"npc.h"

bool Npc::init()
{
	moveMode = STAND;
	lastMoveMode = STAND;
	jumpMode = FALL;
	npcState = DO_NOTHING;

	walkSpeed = 3.f;
	jumpSpeed = 5.f;
	gravity = -0.1f;

	_layer = 0;

	this->scheduleUpdate();

	stateCount = 0;
	return true;
}

void Npc::update(float dt)
{
	NpcScheduleUpdate();
	stateUpdate(dt);
	moveUpdate();
	spriteUpdate(dt);
}

void Npc::stateUpdate(float dt)
{
	float randNum;

	switch (npcState)
	{
	case DO_NOTHING:
		break;
	case WANDER:
		{
			if (moveMode == STAND)
			{
				stateCount += dt;
				if (stateCount >= 2.f + CCRANDOM_0_1() * 10.f)
				{
					stateCount = 0;
				
					randNum = CCRANDOM_0_1() * 100;
					if (randNum < 40)
						moveMode = WALK_RIGHT; // 30%
					else if (randNum < 80)
						moveMode = WALK_LEFT; // 30%
					else
						moveMode = STAND;
				}
			}
			else
			{
				stateCount+= dt;
				if (stateCount >= 1.f + CCRANDOM_0_1() * 5.f)
				{
					stateCount = 0;
					moveMode = STAND;
				}
			}
		}
		break;
	case EXCITED:
		break;
	case MOVING:
		break;
	default:
		break;
	}
}

void Npc::NpcScheduleUpdate()
{
}

void Npc::setState(NpcState setNpcState)
{
	npcState = setNpcState;
}
