#include <Windows.h>
#include <hgesprite.h>
#include <hge.h>

#include "Player.h"

void Player::draw()
{
	spr->Render(x, y);
}

Player::Player(HTEXTURE texture,float x,float y, float w, float h,float xHot,float yHot,HGE* hge)
{
	this->spr = new hgeSprite(texture,x,y,w,h);
	this->spr->SetHotSpot(xHot,yHot);
	this->spr->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);

	this->hge = hge;

	this->FLOORHEIGHT = (float)hge->System_GetState(HGE_SCREENHEIGHT) - 20.0f;
	GRAVITY = 45.0f;
	this->x=20.0f;
	this->y= (float)hge->System_GetState(HGE_SCREENHEIGHT) - 20.0f - 22.0f;

	this->jumpState = false;
	currentDrop=0.0f;
}

void Player::update()
{

}

void Player::move(float xDiff, float yDiff)
{
	float dt = hge->Timer_GetDelta();

	if (yDiff < 0 && !jumpState)
	{
		jumpState = true;
		y+=yDiff;
		currentDrop+=yDiff;
	}
	else
	{
		if (y < FLOORHEIGHT - 22.0f) 
		{
			currentDrop += GRAVITY*dt;
			y+=currentDrop;
		} 
		else
		{
			yDiff=0.0f;
			currentDrop = 0.0f;
			y=FLOORHEIGHT - 22.0f;
			if (jumpState)
				jumpState = false;
		}
	}

	if(x>784) {x=784-(x-784);xDiff=0;}
	if(x<16) {x=16+16-x;xDiff=0;}
	if(y>584) {y=584-(y-584);yDiff=0;}
	

	x+=xDiff;
}