#pragma once

#include <hge.h>
#include <hgesprite.h>

class Player
{
public:
	Player(HTEXTURE texture,float x,float y, float w, float h,float xHot,float yHot,HGE* hge);
	void draw();
	void update();
	void move(float xDiff,float yDiff);
private:
	hgeSprite*			spr;
	HGE *hge;
	float FLOORHEIGHT;
	float GRAVITY;
	float currentDrop;
	bool jumpState;
	float x;
	float y;
};