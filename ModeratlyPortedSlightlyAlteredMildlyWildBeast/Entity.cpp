#include "Entity.h"

#include "Controller.h"
#include "Drawer.h"

#include "constants.h"

using namespace AB;

Entity::Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer):
    mController(aController),
    mDrawer(aDrawer),
    mXpos(0.f),
    mYpos(FLOOR_YPOS)
{
}

void Entity::update(float dt)
{
    mController->update(*this, dt);
}

void Entity::draw()
{
    mDrawer->draw(*this);
}

void Entity::move(float dt, float aXInput, bool aJump)
{
    mXpos += aXInput*TOP_SPEED*dt;
    if(mXpos<0.)
    {
        mXpos = 0.;
    }
    if(mXpos>WIN_WIDTH-PIBI_WIDTH)
    {
        mXpos=WIN_WIDTH-PIBI_WIDTH;
    }
}