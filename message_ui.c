#include <string.h>
#include <SDL2/SDL.h>

#include "message_ui.h"

#define MESSAGE_QUEUE_SIZE 3

static char queue[MESSAGE_QUEUE_SIZE][128];
static int queue_count = 0;

static char message[128] = "";
static Uint32 message_timer = 0;

void show_message(const char *text)
{
    if(queue_count < MESSAGE_QUEUE_SIZE)
    {
        strncpy(queue[queue_count], text, sizeof(queue[0]) - 1);
        queue[queue_count][sizeof(queue[0]) - 1] = '\0';
        queue_count++;
    }
}

const char *get_message(void)
{
    return message;
}

void update_message(void)
{
    if(message[0] == '\0' && queue_count > 0)
    {
        strcpy(message, queue[0]);
        message_timer = SDL_GetTicks();

        for(int i = 1; i < queue_count; i++)
        {
            strcpy(queue[i - 1], queue[i]);
        }
        queue_count--;
    }

    if(message[0] != '\0' && SDL_GetTicks() - message_timer > 2000)
    {
        message[0] = '\0';
    }
}
