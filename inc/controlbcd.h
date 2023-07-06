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

#ifndef CONTROLBCD_H
#define CONTROLBCD_H

/** \brief Módulo para el control de los minutos y hora en formato bcd
 **
 **
 ** \addtogroup bcd BCD
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdint.h>
#include <stdbool.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C"
{
#endif

    /* === Public macros definitions =============================================================== */

    /* === Public data type declarations =========================================================== */

    /* === Public variable declarations ============================================================ */

    /* === Public function declarations ============================================================ */

    /**
     * @brief Incrementa un minuto.
     *
     * @param entrada Puntero al vector a trabajar.
     */
    void IncrementarMinuto(uint8_t * entrada);

    /**
     * @brief Incrementa una hora.
     *
     * @param entrada Puntero al vector a trabajar.
     */
    void IncrementarHora(uint8_t * entrada);

    /**
     * @brief Decrementa un minuto.
     *
     * @param entrada Puntero al vector a trabajar.
     */
    void DecrementarMinuto(uint8_t * entrada);

    /**
     * @brief Decrementa una hora.
     *
     * @param entrada Puntero al vector a trabajar.
     */
    void DecrementarHora(uint8_t * entrada);

    /**
     * @brief Incrementalos segundos de una hora.
     *
     * @param entrada Puntero al vector a trabajar.
     */
    void SecondsIncrement(uint8_t * entrada);

    /**
     * @brief Verifica la velidez de una hora ingresada.
     *
     * @param hora      Puntero al vector a verificar.
     * @return true     Hora valida.
     * @return false    Hora invalida.
     */
    bool HoraValida(const uint8_t * hora);

    /* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* CONTROLBCD_H */
