#pragma once

#include <hge.h>
#include <hgesprite.h>

class ABProjectile
{
public:
	hgeSprite* sprite;
	float x;
	float y;

	ABProjectile(HTEXTURE tex, float x,float y,float w, float h,float posx,float posy);
	void render();
};