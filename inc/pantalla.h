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

#ifndef PANTALLA_H
#define PANTALLA_H

/** \brief Declaraciones de la abtracción del hardware de la pantalla
 **
 ** \addtogroup pantalla PANTALLA
 ** \brief Hardware Abstraction Layer
 ** @{ */

/* === Headers files inclusions ================================================================ */

#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C"
{
#endif

/* === Public macros definitions =============================================================== */

//! Definición de bits del segmento A
#define SEGMENTO_A (1 << 0)
//! Definición de bits del segmento B
#define SEGMENTO_B (1 << 1)
//! Definición de bits del segmento C
#define SEGMENTO_C (1 << 2)
//! Definición de bits del segmento D
#define SEGMENTO_D (1 << 3)
//! Definición de bits del segmento E
#define SEGMENTO_E (1 << 4)
//! Definición de bits del segmento F
#define SEGMENTO_F (1 << 5)
//! Definición de bits del segmento G
#define SEGMENTO_G (1 << 6)
//! Definición de bits del segmento P
#define SEGMENTO_P (1 << 7)

    /* === Public data type declarations =========================================================== */

    //! Puntero a un descriptor para gestionar la pantalla.
    typedef struct display_s * display_t;

    //! Función de callback para apagar los segmentos y digitos de la pantalla.
    typedef void (*display_screen_off_t)(void);

    //! Función de callback para prender los ssegmentos de la pantalla.
    typedef void (*display_segments_on_t)(uint8_t segments);

    //! Función de callback para prender un digito de la pantalla.
    typedef void (*display_digit_on_t)(uint8_t digit);

    //! Estructura con las funciones de bajo nivel para el manejo de la pantalla
    typedef struct display_driver_s
    {
        display_screen_off_t ScreenTurnOff;   //!< Función para apagar los segmentos y los digitos.
        display_segments_on_t SegmentsTurnOn; //!< Función para prender determinados segmentos.
        display_digit_on_t DigitTurnOn;       //!< Función para prender un dígito.
    } const * const display_driver_t;         //!< Puntero al controlador de la pantalla.

    /* === Public variable declarations ============================================================ */

    /* === Public function declarations ============================================================ */

    /**
     * @brief Método para crear una pantalla multiplexada de 7 segmentos.
     *
     * @param digits Cantidad de dígitos que forman la pantalla.
     * @param driver Puntero a la estructura con las funciones de bajo nivel.
     * @return display_t Puntero al descriptor de la pantalla creada.
     */
    display_t DisplayCreate(uint8_t digits, display_driver_t driver);

    /**
     * @brief Función para escribir un número BCD en la pantalla de 7 segmenentos.
     *
     * @param display Puntero al descriptor de la pantalla a escribir.
     * @param number Puntero al primer elemento del número BCD a escribir.
     * @param size Cantidad de elementos en el vector que contiene al numero BCD.
     */
    void DisplayWriteBCD(display_t display, uint8_t * number, uint8_t size);

    /**
     * @brief Función para refrescar la pantalla.
     *
     * @param display Puntero al descriptor de la pantalla a refrescar.
     */
    void DisplayRefresh(display_t display);

    /**
     * @brief Función para hacer parpadear los dígitos de la pantalla
     *
     * @param display   Puntero al descriptor de la pantalla a parpadear.
     * @param from      El primer dígito que se quiere hacer parpadear.
     * @param to        El último dígito que ser quiere hacer apagar.
     * @param frec      Factor de división de ka frecuencía de parapadeo.
     */
    void DisplayFlashDigits(display_t display, uint8_t from, uint8_t to, uint16_t frec);

    /**
     * @brief Función para encender y apagar puntos
     *
     * @param display   Puntero al descriptor de la pantalla.
     * @param position  Posición del punto.
     */
    void DisplayToggleDot(display_t display, uint8_t position);

    /* === End of documentation ==================================================================== */

#ifdef __cplusplus
}
#endif

/** @} End of module definition for doxygen */

#endif /* PANTALLA_H */
