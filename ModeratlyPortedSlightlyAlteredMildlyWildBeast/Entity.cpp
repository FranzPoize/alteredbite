#include "Entity.h"

#include "Controller.h"
#include "Drawer.h"

#include "constants.h"
#include <ClanLib/core.h>

using namespace AB;

Entity::Entity(std::shared_ptr<Controller> aController, std::shared_ptr<Drawer> aDrawer):
    mController(aController),
    mDrawer(aDrawer),
    mXpos(0.f),
    mYpos(FLOOR_YPOS),
	vSpeed(0.f),
	vRatio(0.f),
	btnJumpPower(0)
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
    float mv = aXInput*TOP_SPEED*dt;
    cl_log_event("info", "move result : %1 (%2 x %3)", mv, aXInput, dt);
    mXpos += mv;
    if(mXpos<0.)
    {
        mXpos = 0.;
    }
    if(mXpos>WIN_WIDTH-PIBI_WIDTH)
    {
        mXpos=WIN_WIDTH-PIBI_WIDTH;
    }

	// Le awesome jumping algo courtesy of PiBi
	if(aJump)
	{
		btnJumpPower++;
	}
	else if(btnJumpPower != 0)
	{	
		vSpeed = 200.0f * (1 + (btnJumpPower * 0.02));
		vRatio = 20.0f;
		btnJumpPower = 0;
	}

	float ratioErosionCoeffFromMyButt = 1.01f;
	if(vSpeed > 0)
	{
		float jump = vSpeed*dt;
		mYpos -= jump;

		vSpeed -= vRatio;
		vRatio /= ratioErosionCoeffFromMyButt;
	}
	else if(vSpeed < 0)
	{
		float jump = vSpeed*dt;
		mYpos -= jump;

		vSpeed -= vRatio;
		vRatio *= ratioErosionCoeffFromMyButt;

		if(mYpos >= FLOOR_YPOS)
		{
			vSpeed = 0; // LOL stop condition
			mYpos = FLOOR_YPOS;
		}
	}
}