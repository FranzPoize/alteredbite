#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#include <ClanLib/application.h>
#include <string>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

class Entity
{
public:
    Entity(CL_GraphicContext &gc, CL_SpriteDescription &description):
        mGc(gc),
        mSprite(gc, description),
        mXPos(20.),
        mYPos(20.)
    {
    }

    void update(CL_InputDevice &aInputDevice)
    {
        mXPos += aInputDevice.get_axis(0);
    }

    void draw()
    {
        mSprite.draw(mGc, mXPos, mYPos);
    }

private:
    CL_GraphicContext &mGc;
    CL_Sprite mSprite;
    float mXPos, mYPos;
};

class ConsoleProgram
{
public:
    static int main(const std::vector<CL_String> &args)
    {
        CL_SetupCore setup_core;
        CL_SetupDisplay setup_display;
        CL_SetupGL setup_opengl;

        CL_DisplayWindow window("ModeratlyPortedSlightlyAlteredMildlyWildBeast", WIN_WIDTH, WIN_HEIGHT);
        CL_GraphicContext gc = window.get_gc();
        CL_InputContext ic = window.get_ic();

        
        CL_InputDevice gamepad = ic.get_joystick_count() ? ic.get_joystick() : ic.get_keyboard();

        //Business starts here
        try
        {
            CL_SpriteDescription pibiDescription;
            pibiDescription.add_frame("./pibi.png");
            Entity pibi(gc, pibiDescription);

            while (ic.get_keyboard().get_keycode(CL_KEY_ESCAPE) == false)
            {
                gc.clear(CL_Colorf::whitesmoke);
                pibi.update(gamepad);
                pibi.draw();
                window.flip();


                CL_KeepAlive::process();
                CL_System::sleep(10);
            }
        }
        catch(CL_Exception &exception)
        {
            // Create a console window for text-output if not available
            CL_ConsoleWindow console("Console", 80, 160);
            CL_Console::write_line("Error: " + exception.get_message_and_stack_trace());

            console.display_close_message();

            return -1;
        }

        return 0;
    }
};

// Create global application object, you MUST include this line or
// the application start-up will fail to locate your application object.
CL_ClanApplication app(&ConsoleProgram::main);