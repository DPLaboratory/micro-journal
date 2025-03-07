#include "Layout.h"
#include "../Menu.h"
#include "app/app.h"
#include "config/config.h"
#include "display/display.h"
#include "../../WordProcessor/WordProcessor.h"

//
void Layout_setup(TFT_eSPI *ptft, U8g2_for_TFT_eSPI *pu8f)
{
    // when entering the screen
    // clear the screen
    Menu_clear();
}

//
void Layout_render(TFT_eSPI *ptft, U8g2_for_TFT_eSPI *pu8f)
{
    //
    JsonDocument &app = app_status();

    ptft->setCursor(0, 30, 2);
    ptft->setTextColor(TFT_WHITE, TFT_BLACK);
    ptft->println(" - Choose Keyboard Layout");
    ptft->println();

    ptft->println("[A] International");
    ptft->println("[B] Belgian");
    ptft->println("[C] Canadian Multiligual");
    ptft->println("[D] Dvorak");
    ptft->println("[G] German");
    ptft->println("[I] Italian");
    ptft->println("[K] UK");
    ptft->println("[L] Latin America");
    ptft->println("[S] Swedish");
    ptft->println("[U] US");
}

//
void Layout_keyboard(char key)
{
    //
    JsonDocument &app = app_status();

    if (key == 'a')
    {
        // us
        app["config"]["keyboard_layout"] = "INT";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else if (key == 'b')
    {
        // canadian multiligual
        app["config"]["keyboard_layout"] = "BE";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else if (key == 'c')
    {
        // canadian multiligual
        app["config"]["keyboard_layout"] = "CA";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else if (key == 'd')
    {
        // us dvorak multiligual
        app["config"]["keyboard_layout"] = "DV";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else if (key == 'g')
    {
        // italian
        app["config"]["keyboard_layout"] = "GE";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else if (key == 'i')
    {
        // italian
        app["config"]["keyboard_layout"] = "IT";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else if (key == 'k')
    {
        // italian
        app["config"]["keyboard_layout"] = "UK";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else if (key == 'l')
    {
        // italian
        app["config"]["keyboard_layout"] = "LAT";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else if (key == 's')
    {
        // italian
        app["config"]["keyboard_layout"] = "SWE";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    else
    {
        // default to 'us' in the case where software is downgraded or the 'u' key was pressed
        app["config"]["keyboard_layout"] = "US";
        config_save();
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    //
    // go back to home menu
    app["menu"]["state"] = MENU_HOME;
}
