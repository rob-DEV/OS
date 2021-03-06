#ifndef OS_KERNEL_HW_COMM_KEYMAP_H
#define OS_KERNEL_HW_COMM_KEYMAP_H

#define KEY_SHIFT_LEFT 42
#define KEY_SHIFT_RIGHT 54
#define KEY_SHIFT_LEFT_RELEASE -86
#define KEY_SHIFT_RIGHT_RELEASE -74
#define KEY_CAPSLOCK 58
#define KEY_PAGEUP 73
#define KEY_PAGEDOWN 81
#define KEY_ESCAPE 1
//#define KEY_ESCAPE 27
#define KEY_BACKSPACE '\b' 
#define KEY_TAB '\t'

namespace OS { namespace KERNEL { namespace HW_COMM {

    //OS KEY MAPPINGS

    

    const unsigned char KB_US_LOWER[128] = {
                0,  KEY_ESCAPE, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
            '9', '0', '-', '=', '\b',	/* Backspace */
            KEY_TAB,			/* Tab */
            'q', 'w', 'e', 'r',	/* 19 */
            't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
                0,			/* 29   - Control */
            'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
            '\'', '`',   0,		/* Left shift */
            '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
            'm', ',', '.', '/',   0,				/* Right shift */
            '*',
                0,	/* Alt */
            ' ',	/* Space bar */
                0,	/* Caps lock */
                0,	/* 59 - F1 key ... > */
                0,   0,   0,   0,   0,   0,   0,   0,
                0,	/* < ... F10 */
                0,	/* 69 - Num lock*/
                0,	/* Scroll Lock */
                0,	/* Home key */
                0,	/* Up Arrow */
                0,	/* Page Up */
            '-',
                0,	/* Left Arrow */
                0,
                0,	/* Right Arrow */
            '+',
                0,	/* 79 - End key*/
                0,	/* Down Arrow */
                0,	/* Page Down */
                0,	/* Insert Key */
                0,	/* Delete Key */
                0,   0,   0,
                0,	/* F11 Key */
                0,	/* F12 Key */
                0,	/* All other keys are undefined */
            };	

    static unsigned char KB_US_UPPER[128] =
    {
        0,  0, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
    '(', ')', '_', '+', 0,	/* Backspace */
    '\t',			/* Tab */
    'Q', 'W', 'E', 'R',	/* 19 */
    'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
        0,			/* 29   - Control */
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
    '|', '~',   0,		/* Left shift */
    '\\', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
    'M', '<', '>', '?',   0,				/* Right shift */
    '*',
        0,	/* Alt */
    ' ',	/* Space bar */
        0,	/* Caps lock */
        0,	/* 59 - F1 key ... > */
        0,   0,   0,   0,   0,   0,   0,   0,
        0,	/* < ... F10 */
        0,	/* 69 - Num lock*/
        0,	/* Scroll Lock */
        0,	/* Home key */
        0,	/* Up Arrow */
        0,	/* Page Up */
    '-',
        0,	/* Left Arrow */
        0,
        0,	/* Right Arrow */
    '+',
        0,	/* 79 - End key*/
        0,	/* Down Arrow */
        0,	/* Page Down */
        0,	/* Insert Key */
        0,	/* Delete Key */
        0,   0,   0,
        0,	/* F11 Key */
        0,	/* F12 Key */
        0,	/* All other keys are undefined */
    };



}}}



#endif