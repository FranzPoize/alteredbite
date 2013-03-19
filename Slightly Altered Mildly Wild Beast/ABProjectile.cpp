#include <Windows.h>
#include <hge.h>
#include <hgesprite.h>

#include "ABProjectile.h"

ABProjectile::ABProjectile(HTEXTURE tex, float x,float y,float w, float h,float posx,float posy)
{
	sprite = new hgeSprite(tex,x,y,w,h);
	this->x = posx;
	this->y = posy;
}

void ABProjectile::render()
{
	sprite->Render(x,y);
}