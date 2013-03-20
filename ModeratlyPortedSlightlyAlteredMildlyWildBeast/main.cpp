#include "constants.h"

#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#include <ClanLib/application.h>
#include <string>

#include <memory>

#include "Entity.h"
#include "DrawerSprite.h"
#include "XBoxController.h"

class ConsoleProgram
{
public:
    static int main(const std::vector<CL_String> &args)
    {
        CL_SetupCore setup_core;
        CL_SetupDisplay setup_display;
        CL_SetupGL setup_opengl;

        CL_ConsoleWindow console("Console", 80, 160);
        CL_DisplayWindowDescription windowDescription;
        //Fucked up default value of "client area" to false... so this line is very important to get sensible behavior.
        windowDescription.set_size(CL_Size(WIN_WIDTH, WIN_HEIGHT), true);
        windowDescription.set_title("ModeratlyPortedSlightlyAlteredMildlyWildBeast");
        CL_DisplayWindow window(windowDescription);
        CL_GraphicContext gc = window.get_gc();
        CL_InputContext ic = window.get_ic();

        //gc.set_map_mode(cl_map_2d_upper_left);

        //CL_InputDevice gamepad = ic.get_joystick_count() ? ic.get_joystick() : ic.get_keyboard();

        //Business starts here
        try
        {
            CL_SpriteDescription pibiDescription;
            pibiDescription.add_frame("./pibi.png");
            CL_Sprite pibiSprite(gc, pibiDescription);
            pibiSprite.set_alignment(origin_bottom_left);
            std::shared_ptr<AB::Drawer> pibiDrawer = std::make_shared<AB::DrawerSprite>(gc, pibiSprite);

            std::shared_ptr<AB::Controller> pibiController = std::make_shared<AB::XBoxController>();

            AB::Entity pibi(pibiController, pibiDrawer);

            unsigned int current_time=CL_System::get_time(), last_time=current_time-1;
            while (ic.get_keyboard().get_keycode(CL_KEY_ESCAPE) == false)
            {
                current_time = CL_System::get_time();
                float delta = (current_time-last_time)/1000.f;
                last_time = current_time;
                CL_Console::write_line("dt : %1", delta);

                gc.clear(CL_Colorf::whitesmoke);
                pibi.update(delta);
                pibi.draw();
                window.flip(1);


                CL_KeepAlive::process();
                CL_System::sleep(10);
            }
        }
        catch(CL_Exception &exception)
        {
            // Create a console window for text-output if not available
            //CL_ConsoleWindow console("Console", 80, 160);
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