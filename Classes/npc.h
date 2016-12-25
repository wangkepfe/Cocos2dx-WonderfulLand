#ifndef __NPC_H__
#define __NPC_H__

#include "human.h"

enum NpcState {
	DO_NOTHING,
	WANDER,
	EXCITED,
	MOVING
};

class Npc : public Human
{
public:
	CREATE_FUNC(Npc);
	virtual bool init();
	virtual void update(float dt);
	void stateUpdate(float dt);
	void NpcScheduleUpdate();
	void setState(NpcState setNpcState);
	
private:
	NpcState npcState;
	float stateCount;
};



#endif