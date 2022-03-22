#define INTERNAL_SRC_CODE_PADUTILS_C
#include "global.h"
#include "padmgr.h"
#include "def/padutils.h"

void PadUtils_Init(Input* input) {
    bzero(input, sizeof(Input));
}

void func_800FCB70(void) {
}

void PadUtils_ResetPressRel(Input* input) {
    input->press.button = 0;
    input->rel.button = 0;
}

u32 PadUtils_CheckCurExact(Input* input, u16 value) {
    return value == input->cur.button;
}

u32 PadUtils_CheckCur(Input* input, u16 key) {
    return key == (input->cur.button & key);
}

u32 PadUtils_CheckPressed(Input* input, u16 key) {
    return key == (input->press.button & key);
}

u32 PadUtils_CheckReleased(Input* input, u16 key) {
    return key == (input->rel.button & key);
}

u16 PadUtils_GetCurButton(Input* input) {
    return input->cur.button;
}

u16 PadUtils_GetPressButton(Input* input) {
    return input->press.button;
}

s8 PadUtils_GetCurX(Input* input) {
    return input->cur.stick_x;
}

s8 PadUtils_GetCurY(Input* input) {
    return input->cur.stick_y;
}

void PadUtils_SetMouseRelXY(Input* input, s32 x, s32 y)
{
	input->rel.mouse_x = x;
	input->rel.mouse_y = y;
}

void PadUtils_SetRelXY(Input* input, s32 x, s32 y) {
    input->rel.stick_x = x;
    input->rel.stick_y = y;
}

s8 PadUtils_GetRelXImpl(Input* input) {
    return input->rel.stick_x;
}

s8 PadUtils_GetRelYImpl(Input* input) {
    return input->rel.stick_y;
}

s8 PadUtils_GetRelX(Input* input) {
    return PadUtils_GetRelXImpl(input);
}

s8 PadUtils_GetRelY(Input* input) {
    return PadUtils_GetRelYImpl(input);
}

void PadUtils_UpdateRelXY(Input* input) {
    s32 curX = PadUtils_GetCurX(input);
    s32 curY = PadUtils_GetCurY(input);
    s32 relX;
    s32 relY;

    if (curX > 7) {
        relX = (curX < 0x43) ? curX - 7 : 0x43 - 7;
    } else if (curX < -7) {
        relX = (curX > -0x43) ? curX + 7 : -0x43 + 7;
    } else {
        relX = 0;
    }

    if (curY > 7) {
        relY = (curY < 0x43) ? curY - 7 : 0x43 - 7;

    } else if (curY < -7) {
        relY = (curY > -0x43) ? curY + 7 : -0x43 + 7;
    } else {
        relY = 0;
    }

    s32 curMouseX = input->cur.mouse_x;
    s32 curMouseY = input->cur.mouse_y;
    s32 relMouseX;
    s32 relMouseY;

    if(curX > 7)
    {
	    relMouseX = (curMouseX < 0x43) ? curMouseX - 7 : 0x43 - 7;
    }
    else if(curX < -7)
    {
	    relMouseX = (curMouseX > -0x43) ? curMouseX + 7 : -0x43 + 7;
    }
    else
    {
	    relMouseX = 0;
    }

    if(curY > 7)
    {
	    relMouseY = (curMouseY < 0x43) ? curMouseY - 7 : 0x43 - 7;
    }
    else if(curY < -7)
    {
	    relMouseY = (curMouseY > -0x43) ? curMouseY + 7 : -0x43 + 7;
    }
    else
    {
	    relMouseY = 0;
    }

    PadUtils_SetRelXY(input, relX, relY);
    PadUtils_SetMouseRelXY(input, relMouseX, relMouseY);
}
