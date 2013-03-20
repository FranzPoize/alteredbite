#include "DrawerSprite.h"

#include "Entity.h"

using namespace AB;

DrawerSprite::DrawerSprite(CL_GraphicContext &gc, CL_Sprite aSprite):
    mGc(gc),
    mSprite(aSprite)
{

}

void DrawerSprite::draw(const Entity &aEntity)
{
    mSprite.draw(mGc, aEntity.x(), aEntity.y());
}