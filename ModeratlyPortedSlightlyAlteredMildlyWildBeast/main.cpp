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


        CL_FileLogger file_logger("logfile.txt");
        file_logger.enable();

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

            unsigned int current_time=CL_System::get_time(), last_time=current_time-1, flip_time;
            while (ic.get_keyboard().get_keycode(CL_KEY_ESCAPE) == false)
            {
                current_time = CL_System::get_time();
                float delta = (current_time-last_time)/1000.f;
                last_time = current_time;
                CL_Console::write_line("dt : %1", delta);

                gc.clear(CL_Colorf::whitesmoke);
                int clear_time = CL_System::get_time();
                pibi.update(delta);
                int update_time = CL_System::get_time();
                pibi.draw();
                int draw_time = CL_System::get_time();
                window.flip(1);


                flip_time = CL_System::get_time();
                CL_KeepAlive::process();

                current_time = CL_System::get_time();
                if(current_time-last_time>19)
                    cl_log_event("info", "ABNORMAL time : %1 ms (upd:%2, process:%3)", current_time-last_time, flip_time-last_time, current_time-flip_time);
                else
                    cl_log_event("info", "render time : %1 ms (upd:%2, process:%3)", current_time-last_time, flip_time-last_time, current_time-flip_time);
                cl_log_event("info", "##DETAILS   Clear:%1, Update:%2, Draw:%3, Flip:%4 ", clear_time-last_time, update_time-clear_time, draw_time-update_time, flip_time-draw_time);
                int timeToSleep = 10 - (current_time-last_time);
                if(timeToSleep > 0)
                    CL_System::sleep(timeToSleep);
                //CL_System::sleep(10);
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