/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut03 - Using helper classes
*/


// Copy the files "particles.png", "menu.wav",
// "font1.fnt", "font1.png" and "trail.psi" from
// the folder "precompiled" to the folder with
// executable file. Also copy hge.dll and bass.dll
// to the same folder.


#include <hge.h>
#include <hgesprite.h>
#include <hgefont.h>
#include <hgeparticle.h>
#include <list>

class Projectile
{
public:
	hgeSprite* sprite;
	float x;
	float y;

	Projectile(HTEXTURE tex, float x,float y,float w, float h,float posx,float posy);
	void render();
};

Projectile::Projectile(HTEXTURE tex, float x,float y,float w, float h,float posx,float posy)
{
	sprite = new hgeSprite(tex,x,y,w,h);
	this->x = posx;
	this->y = posy;
}

void Projectile::render()
{
	sprite->Render(x,y);
}


// Pointer to the HGE interface.
// Helper classes require this to work.
HGE *hge=0;


// Pointers to the HGE objects we will use
hgeSprite*			spr;
hgeSprite*			spt;
hgeFont*			fnt;
hgeParticleSystem*	par;
std::list<Projectile> projList;


// Handles for HGE resourcces
HTEXTURE			tex;
HTEXTURE			pibiTex;
HTEXTURE			projTex;
HEFFECT				snd;

// Some "gameplay" variables
float x=20.0f, y=22.0f,floorHeight;
float dx=0.0f, dy=0.0f;

const float speed=90;
const float friction=0.98f;
const float gravity=45.0f;
const int INTERVAL_SHOOT = 20.0f;

bool jump = false;
int interval = 0;

// Play sound effect
void boom() {
	int pan=int((x-400)/4);
	float pitch=(dx*dx+dy*dy)*0.0005f+0.2f;
	hge->Effect_PlayEx(snd,100,pan,pitch);
}

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();

	if (interval > 0)
		interval--;
	// Process keys
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;
	if (hge->Input_GetKeyState(HGEK_Q)) dx=-speed/20;
	else if (hge->Input_GetKeyState(HGEK_D)) dx=speed/20;
	else dx = 0;
	if (hge->Input_GetKeyState(HGEK_SPACE) && !jump)
	{
		dy-=speed/10;
		jump = true;
		y+=dy;
	}
	if (hge->Input_GetKeyState(HGEK_LBUTTON) && interval == 0) {
		interval = INTERVAL_SHOOT;
		Projectile *proj = new Projectile(projTex,16,16,16,16,x,y);
		projList.push_back(*proj);
	}

	// Do some movement calculations and collision detection	
	if(x>784) {x=784-(x-784);dx=0;}
	if(x<16) {x=16+16-x;dx=0;}
	if(y>584) {y=584-(y-584);dy=0;}
	if (y < floorHeight - 22.0f) 
	{
		dy += gravity*dt;
		y+=dy;
	} 
	else 
	{
		dy=0.0f;
		y=floorHeight - 22.0f;
		if (jump)
			jump = false;
	}

	x+=dx; 

	std::list<Projectile>::iterator i;
	for (i = projList.begin(); i != projList.end();)
	{
		(*i).x+=speed*10*dt;
		if ((*i).x > 784)
			i = projList.erase(i);
		else
			++i;
	}

	// Update particle system
	par->info.nEmission=(int)(dx*dx+dy*dy)*2;
	par->MoveTo(x,y);
	par->Update(dt);

	return false;
}


bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	par->Render();
	spr->Render(x, y);
	std::list<Projectile>::iterator i;
	for (i = projList.begin(); i != projList.end();++i)
	{
		(*i).render();
	}
	fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d (constant)", hge->Timer_GetDelta(), hge->Timer_GetFPS());
	hge->Gfx_EndScene();

	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "hge_tut03.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "HGE Tutorial 03 - Using helper classes");
	hge->System_SetState(HGE_FPS, 100);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate()) {

		// Load sound and texture
		snd=hge->Effect_Load("menu.wav");
		tex=hge->Texture_Load("particles.png");
		pibiTex=hge->Texture_Load("pibi.png");
		projTex=hge->Texture_Load("proj.png");
		if(!snd || !tex || !pibiTex)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load one of the following files:\nMENU.WAV, PARTICLES.PNG, FONT1.FNT, FONT1.PNG, TRAIL.PSI, PIBI.PNG", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		floorHeight = (float)hge->System_GetState(HGE_SCREENHEIGHT) - 20.0f;
		y = floorHeight - 22.0f;

		// Create and set up a sprite
		spr=new hgeSprite(pibiTex, 39, 44, 39, 44);
		spr->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
		spr->SetHotSpot(19,22);

		// Load a font
		fnt=new hgeFont("font1.fnt");

		// Create and set up a particle system
		spt=new hgeSprite(tex, 32, 32, 32, 32);
		spt->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
		spt->SetHotSpot(16,16);
		par=new hgeParticleSystem("trail.psi",spt);
		par->Fire();

		// Let's rock now!
		hge->System_Start();

		// Delete created objects and free loaded resources
		delete par;
		delete fnt;
		delete spt;
		delete spr;
		hge->Texture_Free(tex);
		hge->Effect_Free(snd);
	}

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
