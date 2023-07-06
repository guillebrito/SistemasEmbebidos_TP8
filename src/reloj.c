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
/* === Headers files inclusions =============================================================== */

#include "reloj.h"
#include "controlbcd.h"
#include <stddef.h>
#include <string.h>

/* === Macros definitions ====================================================================== */

#define Compara(a, b) memcmp(reloj->a, reloj->b, sizeof(reloj->a)) == 0

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

//! Descriptor del reloj
struct clock_s
{
    uint8_t hora_actual[6]; //! Vector de tamaño 6 con la hora actual.
    bool hora_valida : 1;   //! Indicador de hora válida.
    int tics_por_segundo;   //! Cantidad de tics para incrementar la hora en un segundo.
    int tics_actual;        //! Cantidad de tics actuales.

    alarma_event_t ActivarAlarma; //! Función callback para activar la alarma.
    uint8_t alarma[6];            //! Vector de tamaño 6 con la alarma.
    uint8_t alarma_nueva[6];      //! Vector de tamaño 6 con la alarma luego de posponerla.
    bool alarma_valida : 1;       //! Indicador de alarma válida.
    bool alarma_habilitada : 1;   //! Indicador de alarma habilitada.
    bool alarma_pospuesta : 1;    //! Indicador de alarma pospuesta.
};

/* === Private function declarations =========================================================== */

void AlarmCheck(clock_t reloj);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

void AlarmCheck(clock_t reloj)
{
    // Alarma normal
    if (Compara(hora_actual, alarma) && reloj->alarma_habilitada && !(reloj->alarma_pospuesta))
    {
        reloj->ActivarAlarma(true);
    }

    // alarma pospuesta
    if (Compara(hora_actual, alarma_nueva) && reloj->alarma_habilitada && reloj->alarma_pospuesta)
    {
        reloj->ActivarAlarma(true);
        reloj->alarma_pospuesta = false;
    }
}

/* === Public function implementation ========================================================== */

//******Funciones asociadas al reloj*******//

clock_t ClockCreate(int tics_por_segundo, alarma_event_t ActivarAlarma)
{
    static struct clock_s self[1];

    memset(self, 0, sizeof(self));
    self->tics_por_segundo = tics_por_segundo;
    self->ActivarAlarma = ActivarAlarma;

    return self;
}

bool ClockRefresh(clock_t reloj)
{
    reloj->tics_actual++;

    if (reloj->tics_actual >= reloj->tics_por_segundo)
    {
        reloj->tics_actual = 0;
        SecondsIncrement(reloj->hora_actual);
        AlarmCheck(reloj);
    }

    if ((reloj->tics_actual >= (reloj->tics_por_segundo / 2)))
    {
        return true;
    }

    return false;
}

bool ClockSetTime(clock_t reloj, const uint8_t * hora, int size)
{
    reloj->hora_valida = false;

    if (HoraValida(hora))
    {
        memcpy(reloj->hora_actual, hora, size);
        reloj->hora_valida = true;
    }

    return reloj->hora_valida;
}

bool ClockGetTime(clock_t reloj, uint8_t * hora, int size)
{
    memcpy(hora, reloj->hora_actual, size);

    return reloj->hora_valida;
}

//*****Funciones asociadas a la alarma*****//

void AlarmEnamble(clock_t reloj, bool estado)
{
    reloj->alarma_habilitada = estado;

    return;
}

void AlarmPostpone(clock_t reloj, uint8_t minutos)
{
    if (!reloj->alarma_pospuesta) // Se ejecuta solo la primera vez que se pospone
    {
        memcpy(reloj->alarma_nueva, reloj->alarma, sizeof(reloj->alarma_nueva));
        reloj->alarma_pospuesta = true;
        reloj->ActivarAlarma(false);
    }

    for (int index = 0; index < minutos; index++) // Incrementa la alarma pospuesta x minutos
    {
        IncrementarMinuto(reloj->alarma_nueva);
    }

    return;
}

void AlarmCancel(clock_t reloj)
{
    reloj->ActivarAlarma(false);

    return;
}

bool AlarmSetTime(clock_t reloj, const uint8_t * alarma, int size)
{
    reloj->alarma_valida = false;
    AlarmEnamble(reloj, false);

    if (HoraValida(alarma))
    {
        memcpy(reloj->alarma, alarma, size);
        AlarmEnamble(reloj, true);
        reloj->alarma_valida = true;
    }

    return reloj->alarma_valida;
}

bool AlarmGetTime(clock_t reloj, uint8_t * alarma, int size)
{
    memcpy(alarma, reloj->alarma, size);

    return reloj->alarma_valida;
}

bool AlarmGetState(clock_t reloj)
{
    return reloj->alarma_habilitada;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
