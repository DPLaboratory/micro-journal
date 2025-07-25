#include "Clear.h"
#include "../Menu.h"
#include "app/app.h"
#include "display/display.h"
#include "service/Editor/Editor.h"

//
void Clear_setup(TFT_eSPI *ptft, U8g2_for_TFT_eSPI *pu8f)
{
    // when entering the screen
    // clear the screen
    Menu_clear();
}

//
void Clear_render(TFT_eSPI *ptft, U8g2_for_TFT_eSPI *pu8f)
{
    ptft->setCursor(0, 30, 2);
    ptft->setTextSize(1);

    //
    ptft->setTextColor(TFT_WHITE, TFT_BLACK);
    ptft->println();
    ptft->setTextColor(TFT_WHITE, TFT_RED);
    ptft->println(" [Y] ARE YOU SURE?");

    ptft->setTextColor(TFT_WHITE, TFT_BLACK);
    ptft->println();
    ptft->println("WARNING: This action will delete the selected file. Make sure to sync your content before confirming to prevent loss of data.");
    ptft->println();
    ptft->println(" [B] BACK ");
}

//
void Clear_keyboard(char key)
{
    JsonDocument &app = status();

    // delete confirmed
    if (key == 'Y' || key == 'y')
    {
        // empty the file
        Editor::getInstance().clearFile();
        
        // go back to the word processor
        app["screen"] = WORDPROCESSOR;
    }

    // go back to home menu
    //
    app["menu"]["state"] = MENU_HOME;
}
