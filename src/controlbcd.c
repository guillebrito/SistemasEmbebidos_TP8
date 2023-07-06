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

/** \brief Brief description of the file
 **
 ** Full file description
 **
 ** \addtogroup name Module denomination
 ** \brief Brief description of the module
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "controlbcd.h"

/* === Macros definitions ====================================================================== */

#define SEGUNDOS_UNI entrada[5]
#define SEGUNDOS_DEC entrada[4]
#define MINUTOS_UNI  entrada[3]
#define MINUTOS_DEC  entrada[2]
#define HORAS_UNI    entrada[1]
#define HORAS_DEC    entrada[0]

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void IncrementarMinuto(uint8_t * entrada)
{
    MINUTOS_UNI++;

    if (MINUTOS_UNI > 9)
    {
        MINUTOS_UNI = 0;
        MINUTOS_DEC++;
    }

    if (MINUTOS_DEC > 5)
    {
        MINUTOS_DEC = 0;
    }
}

void IncrementarHora(uint8_t * entrada)
{
    HORAS_UNI++;

    if (HORAS_UNI > 9)
    {
        HORAS_UNI = 0;
        HORAS_DEC++;
    }

    if (HORAS_DEC > 1 && HORAS_UNI > 3)
    {
        HORAS_DEC = 0;
        HORAS_UNI = 0;
    }
}

void DecrementarMinuto(uint8_t * entrada)
{
    if (MINUTOS_UNI == 0)
    {
        MINUTOS_UNI = 9;

        if (MINUTOS_DEC == 0)
        {
            MINUTOS_DEC = 5;
        }
        else
        {
            MINUTOS_DEC--;
        }
    }
    else
    {
        MINUTOS_UNI--;
    }
}

void DecrementarHora(uint8_t * entrada)
{
    if (HORAS_UNI == 0)
    {
        HORAS_UNI = 9;

        if (HORAS_DEC == 0)
        {
            HORAS_DEC = 2;
            HORAS_UNI = 3;
        }
        else
        {
            HORAS_DEC--;
        }
    }
    else
    {
        HORAS_UNI--;
    }
}

void SecondsIncrement(uint8_t * entrada)
{
    SEGUNDOS_UNI++;

    if (SEGUNDOS_UNI > 9)
    {
        SEGUNDOS_UNI = 0;
        SEGUNDOS_DEC++;
    }

    if (SEGUNDOS_DEC > 5)
    {
        SEGUNDOS_DEC = 0;
        MINUTOS_UNI++;
    }

    if (MINUTOS_UNI > 9)
    {
        MINUTOS_UNI = 0;
        MINUTOS_DEC++;
    }

    if (MINUTOS_DEC > 5)
    {
        MINUTOS_DEC = 0;
        HORAS_UNI++;
    }

    if (HORAS_UNI > 9)
    {
        HORAS_UNI = 0;
        HORAS_DEC++;
    }

    if (HORAS_DEC > 1 && HORAS_UNI > 3)
    {
        HORAS_DEC = 0;
        HORAS_UNI = 0;
    }
}

bool HoraValida(const uint8_t * entrada)
{
    bool valida = true;

    if (SEGUNDOS_UNI > 9 || SEGUNDOS_DEC > 5 || MINUTOS_UNI > 9 || MINUTOS_DEC > 5 || HORAS_UNI > 9 || HORAS_DEC > 2 ||
        (HORAS_UNI > 3 && HORAS_DEC > 1))
    {
        valida = false;
    }
    return valida;
}
/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
