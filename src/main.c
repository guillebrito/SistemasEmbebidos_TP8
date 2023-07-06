/* Copyright 2022, Laboratorio de Microprocesadores
 * Facultad de Ciencias Exactas y Tecnología
 * Universidad Nacional de Tucuman
 * http://www.microprocesadores.unt.edu.ar/
 * Copyright 2023, Guillermo Nicolás Brito <guillermonbrito@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/** \brief Ejemplo del uso de HAL y board support.
 *
 ** \addtogroup main MAIN
 ** \brief En este trabajo pŕactico se diseña una gestión para el poncho de la placa EDU-CIAA-NXP
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include "bspreloj.h"
#include "reloj.h"
#include "controlbcd.h"
#include <stdbool.h>
#include <stddef.h>

/* === Macros definitions ====================================================================== */
#define ParpadearDigitos(from, to, frec) DisplayFlashDigits(board->display, from, to, frec)
#define AlternarPunto(punto)             DisplayToggleDot(board->display, punto)
/* === Private data type declarations ========================================================== */

typedef enum
{
    SIN_CONFIGURAR,
    MOSTRANDO_HORA,
    AJUSTANDO_MINUTOS_ACTUAL,
    AJUSTANDO_HORAS_ACTUAL,
    AJUSTANDO_MINUTOS_ALARMA,
    AJUSTANDO_HORAS_ALARMA,
} modo_t;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

void ActivarAlarma(bool estado);

/* === Public variable definitions ============================================================= */

static board_t board;
static clock_t reloj;
static modo_t modo;

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

void ActivarAlarma(bool estado)
{
}
void CambiarModo(modo_t valor)
{
    modo = valor;
    switch (modo)
    {
    case SIN_CONFIGURAR:
        ParpadearDigitos(0, 3, 100);
        break;
    case MOSTRANDO_HORA:
        ParpadearDigitos(0, 0, 0);
        break;
    case AJUSTANDO_MINUTOS_ACTUAL:
        ParpadearDigitos(2, 3, 100);
        break;
    case AJUSTANDO_HORAS_ACTUAL:
        ParpadearDigitos(0, 1, 100);
        break;
    case AJUSTANDO_MINUTOS_ALARMA:
        ParpadearDigitos(2, 3, 100);
        AlternarPunto(0);
        AlternarPunto(1);
        AlternarPunto(2);
        AlternarPunto(3);
        break;
    case AJUSTANDO_HORAS_ALARMA:
        ParpadearDigitos(0, 1, 100);
        AlternarPunto(0);
        AlternarPunto(1);
        AlternarPunto(2);
        AlternarPunto(3);
        break;
    default:
        break;
    }
}

/* === Public function implementation ========================================================= */

int main(void)
{
    uint8_t entrada[6] = {0, 0, 0, 0, 0, 0};

    board = BoardCreate();
    reloj = ClockCreate(1000, ActivarAlarma);

    SysTick_Init(1000);
    CambiarModo(SIN_CONFIGURAR);

    while (true)
    {
        if (DigitalInputHasActivated(board->aceptar))
        {
            if (modo == AJUSTANDO_MINUTOS_ACTUAL)
            {
                CambiarModo(AJUSTANDO_HORAS_ACTUAL);
            }
            else if (modo == AJUSTANDO_HORAS_ACTUAL)
            {
                ClockSetTime(reloj, entrada, sizeof(entrada));
                CambiarModo(MOSTRANDO_HORA);
            }
        }

        if (DigitalInputHasActivated(board->cancelar))
        {
            if (ClockGetTime(reloj, entrada, sizeof(entrada)))
            {
                CambiarModo(MOSTRANDO_HORA);
            }
            else
            {
                CambiarModo(SIN_CONFIGURAR);
            }
        }
        // Falta 3 seg
        if (DigitalInputHasActivated(board->ajustar_tiempo))
        {
            CambiarModo(AJUSTANDO_MINUTOS_ACTUAL);
            ClockGetTime(reloj, entrada, sizeof(entrada));
            DisplayWriteBCD(board->display, entrada, sizeof(entrada));
        }

        if (DigitalInputHasActivated(board->ajustar_alarma))
        {
        }

        if (DigitalInputHasActivated(board->decrementar))
        {
            if (modo == AJUSTANDO_MINUTOS_ACTUAL)
            {
                DecrementarMinuto(entrada);
            }
            else if (modo == AJUSTANDO_HORAS_ACTUAL)
            {
                DecrementarHora(entrada);
            }
            DisplayWriteBCD(board->display, entrada, sizeof(entrada));
        }

        if (DigitalInputHasActivated(board->incrementar))
        {
            if (modo == AJUSTANDO_MINUTOS_ACTUAL)
            {
                IncrementarMinuto(entrada);
            }
            else if (modo == AJUSTANDO_HORAS_ACTUAL)
            {
                IncrementarHora(entrada);
            }
            DisplayWriteBCD(board->display, entrada, sizeof(entrada));
        }

        for (int index = 0; index < 1000; index++)
        {
            for (int delay = 0; delay < 250; delay++)
            {
                __asm("NOP");
            }
        }
    }
}

void SysTick_Handler(void)
{
    static bool last_value = false;
    bool current_value;
    uint8_t hora[6];

    DisplayRefresh(board->display);
    current_value = ClockRefresh(reloj);

    if (current_value != last_value)
    {
        last_value = current_value;

        if (modo <= MOSTRANDO_HORA)
        {
            ClockGetTime(reloj, hora, sizeof(hora));
            DisplayWriteBCD(board->display, hora, sizeof(hora));
            if (current_value)
            {
                AlternarPunto(1);
            }
        }
    }
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
