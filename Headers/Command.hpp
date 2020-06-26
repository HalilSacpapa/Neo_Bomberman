/*
** EPITECH PROJECT, 2020
** indie
** File description:
** Command
*/

#ifndef COMMAND_HPP_
#define COMMAND_HPP_

#include <irrlicht.h>
#include <iostream>
using namespace irr;

class MyEventReceiver : public IEventReceiver
{
public:
    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_KEY_INPUT_EVENT) {
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            KeyChar = event.KeyInput.Char;
        }
        return false;
    }

    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        KeyChar = 0;
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

    int LastKeyDown()
    {
        for (int i = 0; i < KEY_KEY_CODES_COUNT; i++)
            if (KeyIsDown[i])
                return i;
        return -1;
    }

    wchar_t *CharLastKeyDown()
    {
        return &KeyChar;
    }

private:
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
    wchar_t KeyChar;
};

#endif /* !COMMAND_HPP_ */
