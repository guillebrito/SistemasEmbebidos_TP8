/************************************************************************************************
Copyright (c) 2023, Guillermo Nicolás Brito <guillermonbrito@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
gpioions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

#ifndef DIGITAL_H
#define DIGITAL_H

/** \brief Definición de entradas y salidas digitales
 **
 ** \addtogroup hal HAL
 ** \brief Capa de abstracción de hardware
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

    //! Puntero al descriptor de cada entrada digital.
    typedef struct digital_input_s * digital_input_t;

    //! Puntero al descriptor de cada salida digital.
    typedef struct digital_output_s * digital_output_t;

    /* === Public variable declarations ============================================================ */

    /* === Public function declarations ============================================================ */

    /*********Entradas**********/

    /**
     * @brief Crea una entrada digital.
     *
     * Esta función crea una entrada digital según el puerto GPIO y bit indicados.
     *
     * @param gpio  Puerto GPIO de la entrada.
     * @param bit   Terminal del puerto GPIO correspondiente a la entrada.
     * @param inverted indica si usa lógica inversa.
     * @return digital_input_t Puntero al descriptor de la entrada creada.
     */
    digital_input_t DigitalInputCreate(uint8_t gpio, uint8_t bit, bool inverted);

    /**
     * @brief Consulta el estado de la entrada digital.
     *
     * @param input  puntero al descriptor de la entrada.
     * @return true  La entrada está activa.
     * @return false La entrada está inactiva.
     */
    bool DigitalInputGetState(digital_input_t input);

    /**
     * @brief Consulta cambios en el estado de una entrada digital.
     *
     * @param input  puntero al descriptor de la entrada.
     * @return true  La entrada cambió desde la última llamada.
     * @return false La entrada no cambió desde la última llamada.
     */
    bool DigitalInputHasChanged(digital_input_t input);

    /**
     * @brief Consulta si la entrada digital fue activada.
     *
     * @param input  puntero al descriptor de la entrada.
     * @return true  La entrada se activó.
     * @return false La entrada no se activó.
     */
    bool DigitalInputHasActivated(digital_input_t input);

    /**
     * @brief Consulta si la entrada digital fue desactivada.
     *
     * @param input  puntero al descriptor de la entrada.
     * @return true  La entrada se desactivó.
     * @return false La entrada no se desactivó.
     */
    bool DigitalInputHasDeactivated(digital_input_t input);

    /*********Salidas**********/

    /**
     * @brief Crea una salida digital.
     *
     * Esta función crea una salida digital según el puerto GPIO y bit indicados.
     *
     * @param gpio  Puerto GPIO de la salida.
     * @param bit   Terminal del puerto GPIO correspondiente a la salida.
     * @param inverted indica si usa lógica inversa.
     * @return digital_output_t Puntero al descriptor de la salida creada.
     */
    digital_output_t DigitalOutputCreate(uint8_t gpio, uint8_t bit, bool inverted);

    /**
     * @brief Activa una salida.
     *
     * @param output Puntero al descriptor de la salida.
     */
    void DigitalOutputActivate(digital_output_t output);

    /**
     * @brief Desactiva una salida.
     *
     * @param output Puntero al descriptor de la salida.
     */
    void DigitalOutputDeactivate(digital_output_t output);

    /**
     * @brief Invierte el estado de una salida.
     *
     * @param output Puntero al descriptor de la salida.
     */
    void DigitalOutputToggle(digital_output_t output);

    /* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* DIGITAL_H */
