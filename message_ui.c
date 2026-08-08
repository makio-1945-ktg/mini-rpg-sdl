#include <string.h>
#include <SDL2/SDL.h>

#include "message_ui.h"

static char message[128] = "";
static Uint32 message_timer = 0;

void show_message(const char *text)
{
    strncpy(
        message,
        text,
        sizeof(message) - 1
    );

    message[sizeof(message) - 1] = '\0';

    message_timer = SDL_GetTicks();
}

const char *get_message(void)
{
    return message;
}

void update_message(void)
{
    if(message[0] != '\0')
    {
        if(SDL_GetTicks() - message_timer > 2000)
        {
            message[0] = '\0';
        }
    }
}
