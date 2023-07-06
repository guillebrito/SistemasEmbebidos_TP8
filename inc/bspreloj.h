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

#ifndef BSPRELOJ_H
#define BSPRELOJ_H

/** \brief Board hardware support
 *
 ** Este módulo brinda las configuraciones de entradas, salidasy pantalla del poncho para la placa EDU-CIAA-NXP
 **
 ** \addtogroup bsp BSP
 ** \brief Hardware abstraction layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include "digital.h"
#include "pantalla.h"

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C"
{
#endif

    /* === Public macros definitions =============================================================== */

    /* === Public data type declarations =========================================================== */

    /**
     * @brief Descriptor de la placa EDU-CIAA-NXP
     *
     * Define un tipo de dato struct que almacena los punteros a los descriptores de cada entrada y
     * salida digital.
     *
     */
    typedef struct board_s
    {
        digital_input_t ajustar_tiempo; //!< Puntero al descriptor de la entrada tec_f1.
        digital_input_t ajustar_alarma; //!< Puntero al descriptor de la entrada tec_f2.
        digital_input_t decrementar;    //!< Puntero al descriptor de la entrada tec_f3.
        digital_input_t incrementar;    //!< Puntero al descriptor de la entrada tec_f4.
        digital_input_t aceptar;        //!< Puntero al descriptor de la entrada tec_acep.
        digital_input_t cancelar;       //!< Puntero al descriptor de la entrada tec_cancel.

        digital_output_t buzzer; //!< Puntero al descriptor de la salida led_r.

        display_t display; //!< Puntero al descriptor de la pantalla.
    } const * board_t;

    /* === Public variable declarations ============================================================ */

    /* === Public function declarations ============================================================ */

    /**
     * @brief Crea descriptor de la placa.
     *
     * Crea e inicializa las entradas y salidas de la placa
     *
     * @return board_t Retorna un puntero constante al descriptor creado.
     */
    board_t BoardCreate(void);

    /**
     * @brief Función para inicializar el SysTick
     *
     * @param ticks Cantidad de ticks por segundo
     */
    void SysTick_Init(int ticks);
    /* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* BSPRELOJ_H */
