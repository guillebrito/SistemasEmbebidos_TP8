/************************************************************************************************
Copyright (c) 2023, Guillermo Nicolás Brito <guillermonbrito@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** \brief Declaraciones de la abtracción del hardware de la pantalla
 **
 ** \addtogroup pantalla PANTALLA
 ** \brief Hardware Abstraction Layer
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "pantalla.h"
#include <string.h>

/* === Macros definitions ====================================================================== */

#define BorrarMemoria() memset(display->memory, 0, sizeof(display->memory))
#define CopiarDrivers() memcpy(display->driver, driver, sizeof(display->driver))

#ifndef DISPLAY_MAX_DIGITS
#define DISPLAY_MAX_DIGITS 8
#endif

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

struct display_s
{
    uint8_t digits;
    uint8_t active_digit;
    uint8_t flashing_from;
    uint8_t flashing_to;
    uint16_t flashing_count;
    uint16_t flashing_factor;
    uint8_t memory[DISPLAY_MAX_DIGITS];
    struct display_driver_s driver[1];
};

static const uint8_t IMAGES[] = {
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C | SEGMENTO_D | SEGMENTO_E | SEGMENTO_F,              //!< 0
    SEGMENTO_B | SEGMENTO_C,                                                                  //!< 1
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_D | SEGMENTO_E | SEGMENTO_G,                           //!< 2
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C | SEGMENTO_D | SEGMENTO_G,                           //!< 3
    SEGMENTO_B | SEGMENTO_C | SEGMENTO_F | SEGMENTO_G,                                        //!< 4
    SEGMENTO_A | SEGMENTO_C | SEGMENTO_D | SEGMENTO_F | SEGMENTO_G,                           //!< 5
    SEGMENTO_A | SEGMENTO_C | SEGMENTO_D | SEGMENTO_E | SEGMENTO_F | SEGMENTO_G,              //!< 6
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C,                                                     //!< 7
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C | SEGMENTO_D | SEGMENTO_E | SEGMENTO_F | SEGMENTO_G, //!< 8
    SEGMENTO_A | SEGMENTO_B | SEGMENTO_C | SEGMENTO_F | SEGMENTO_G,                           //!< 9
};

/* === Private function declarations =========================================================== */

static display_t DisplayAllocate(void);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

static display_t DisplayAllocate(void)
{
    static struct display_s instances[1] = {0};

    return &instances[0];
}

/* === Public function implementation ========================================================== */

display_t DisplayCreate(uint8_t digits, display_driver_t driver)
{
    display_t display = DisplayAllocate();

    if (display)
    {
        display->digits = digits;
        display->active_digit = digits - 1;
        display->flashing_from = 0;
        display->flashing_to = 0;
        display->flashing_count = 0;
        display->flashing_factor = 0;
        CopiarDrivers();
        BorrarMemoria();
        display->driver->ScreenTurnOff();
    }

    return display;
}

void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size)
{
    BorrarMemoria();
    for (int index = 0; index < size; index++)
    {
        if (index >= display->digits)
            break;
        display->memory[index] = IMAGES[number[index]];
    }

    return;
}

void DisplayRefresh(display_t display)
{
    uint8_t segments;

    display->driver->ScreenTurnOff();                                      // Borra pantalla
    display->active_digit = (display->active_digit + 1) % display->digits; // Cambia el digito avtivo entre 0 y 4.

    segments = display->memory[display->active_digit];
    if (display->flashing_factor)
    {
        if (display->active_digit == 0)
        {
            display->flashing_count = (display->flashing_count + 1) % display->flashing_factor;
        }

        if ((display->active_digit >= display->flashing_from) && (display->active_digit <= display->flashing_to))
        {
            if (display->flashing_count > (display->flashing_factor / 2))
            {
                segments = 0;
            }
        }
    }

    display->driver->SegmentsTurnOn(segments);           // Enciende segmentos
    display->driver->DigitTurnOn(display->active_digit); // Enciende dígito

    return;
}

void DisplayFlashDigits(display_t display, uint8_t from, uint8_t to, uint16_t frec)
{
    display->flashing_from = from;
    display->flashing_to = to;
    display->flashing_count = 0;
    display->flashing_factor = frec;
}

void DisplayToggleDot(display_t display, uint8_t position)
{
    display->memory[position] ^= (1 << 7);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
