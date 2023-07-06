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
#include <stdbool.h>
#include <stddef.h>

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */
static board_t board;
/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================= */

int main(void)
{
    SysTick_Init(1000);

    board = BoardCreate();

    while (true)
    {

        if (DigitalInputHasActivated(board->aceptar))
        {
            DigitalOutputActivate(board->buzzer);
            DisplayWriteBCD(board->display, (uint8_t[]){1, 2, 3, 4}, 4);
        }

        if (DigitalInputHasActivated(board->cancelar))
        {
            DigitalOutputDeactivate(board->buzzer);
            DisplayWriteBCD(board->display, NULL, 0);
        }

        if (DigitalInputHasActivated(board->ajustar_tiempo))
        {
            DisplayWriteBCD(board->display, (uint8_t[]){0, 0, 0, 1}, 4);
        }

        if (DigitalInputHasActivated(board->ajustar_alarma))
        {
            DisplayWriteBCD(board->display, (uint8_t[]){0, 0, 1, 0}, 4);
        }

        if (DigitalInputHasActivated(board->decrementar))
        {
            DisplayWriteBCD(board->display, (uint8_t[]){0, 1, 0, 0}, 4);
        }

        if (DigitalInputHasActivated(board->incrementar))
        {
            DisplayWriteBCD(board->display, (uint8_t[]){1, 0, 0, 0}, 4);
        }

        for (int index = 0; index < 100; index++)
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
    DisplayRefresh(board->display);
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
