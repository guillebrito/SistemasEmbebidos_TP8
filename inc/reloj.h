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

#ifndef RELOJ_H
#define RELOJ_H

/** \brief Módulo de funcionamiento del reloj
 **
 ** \addtogroup reloj RELOJ
 ** \brief Funcionamiento del  reloj
 ** @{ */

/* === Headers files inclusions ================================================================ */
#include <stdbool.h>
#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C"
{
#endif

    /* === Public macros definitions =============================================================== */

    /* === Public data type declarations =========================================================== */

    //! Tipo de dato puntero al descriptor del reloj.
    typedef struct clock_s * clock_t;

    //! Tipo de dato puntero a función tipo callback para activar alarma.
    typedef void (*alarma_event_t)(bool estado);

    /* === Public variable declarations ============================================================ */

    /* === Public function declarations ============================================================ */

    //******Funciones asociadas al reloj*******//

    /**
     * @brief Método para crear reloj.
     *
     * @param tics_por_segundo  Cantidad de llamadas a la función para que avance un segundo.
     * @param ActivarAlarma     Función callback para activar alarma.
     * @return clock_t          Puntero al reloj creado.
     */
    clock_t ClockCreate(int tics_por_segundo, alarma_event_t ActivarAlarma);

    /**
     * @brief Método para actualizar la hora del reloj.
     *
     * Incrementa la hora en un segundo al llamarla una cantidad de veces igual al valor de la variable tics.
     *
     * @param reloj     Puntero al reloj.
     * @return true     Paso medio segundo.
     * @return false    No paso medio segundo.
     */
    bool ClockRefresh(clock_t reloj);

    /**
     * @brief Método para fijar la hora del reloj.
     *
     * @param reloj     Puntero al reloj.
     * @param hora      Puntero al vector constante con la hora a fijar.
     * @param size      Tamaño del vector hora.
     * @return true     La hora ingresada válida.
     * @return false    La hora ingresada inválida.
     */
    bool ClockSetTime(clock_t reloj, const uint8_t * hora, int size);

    /**
     * @brief Método para consultar la hora del reloj.
     *
     * @param reloj     Puntero al reloj.
     * @param hora      Puntero al vector donde se guardará la hora consultada.
     * @param size      Tamaño del vector hora.
     * @return true     La hora consultada es válida.
     * @return false    La hora consultada es inválida.
     */
    bool ClockGetTime(clock_t reloj, uint8_t * hora, int size);

    //*****Funciones asociadas a la alarma*****//

    /**
     * @brief Método para habilitar la alarma.
     *
     * La alarma quedará habilitada con el estado True, de lo contrario se deshabilitará.
     *
     * @param reloj     Puntero al reloj.
     * @param estado    Estado de la alarma.
     */
    void AlarmEnamble(clock_t reloj, bool estado);

    /**
     * @brief Método para posponer la alarma cierta cantidad de minutos.
     *
     * @param reloj     Puntero al reloj.
     * @param minutos   Cantidad de minutos a posponer la alarma.
     */
    void AlarmPostpone(clock_t reloj, uint8_t minutos);

    /**
     * @brief Método para cancelar la alarma mientras suena hasta el día siguiente.
     *
     * @param reloj     Puntero al reloj.
     */
    void AlarmCancel(clock_t reloj);

    /**
     * @brief Método para fijar la alarma.
     *
     * @param reloj     Puntero al reloj.
     * @param alarma    Puntero al vector constante con la alarma a fijar.
     * @param size      Tamaño del vector alarma.
     * @return true     La alarma ingresada en válida.
     * @return false    La alarma ingresada es inválida.
     */
    bool AlarmSetTime(clock_t reloj, const uint8_t * alarma, int size);

    /**
     * @brief Método para consultar la alarma.
     *
     * @param reloj     Puntero al reloj.
     * @param alarma    Puntero al vector donde se guardará la alarma consultada.
     * @param size      Tamaño del vector alarma.
     * @return true     La alarma consultada es válida.
     * @return false    La alarma consultada es inválida.
     */
    bool AlarmGetTime(clock_t reloj, uint8_t * alarma, int size);

    /**
     * @brief Método para consultar el estado de la alarma
     *
     * Indica si la alarma está habilidata o no.
     *
     * @param reloj     Puntero al reloj.
     * @return true     La alarma está habilitada.
     * @return false    La alarma está deshabilitada.
     */
    bool AlarmGetState(clock_t reloj);

    /* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* RELOJ_H */
