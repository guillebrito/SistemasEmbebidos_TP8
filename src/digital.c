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

/** \brief Definición de entradas y salidas digitales
 **
 ** \addtogroup hal HAL
 ** \brief Capa de abstracción de hardware
 ** @{ */

/* === Headers files inclusions =============================================================== */

#include <stdint.h>
#include <stdbool.h>
#include "chip.h"
#include "digital.h"

/* === Macros definitions ====================================================================== */

#ifndef OUTPUT_INSTANCES
#define OUTPUT_INSTANCES 1
#endif

#ifndef INPUT_INSTANCES
#define INPUT_INSTANCES 6
#endif
/* === Private data type declarations ========================================================== */

// Estructura para almacenar el descriptor de cada entrada digital.
struct digital_input_s
{
    uint8_t gpio;        // Puerto GPIO de la entrada digital.
    uint8_t bit;         // Terminal del puerto GPIO de la entrada digital.
    bool inverted : 1;   // Bandera que indica si funciona con logica inversa.
    bool last_state : 1; // Bandera con el último estado reportado de la entrada.
    bool allocated : 1;  // Bandera para indicar que el descriptor está en uso.
};

// Estructura para almacenar el descriptor de cada salida digital.
struct digital_output_s
{
    uint8_t gpio;       // Puerto GPIO de la salida digital.
    uint8_t bit;        // Terminal del puerto GPIO de la salida digital.
    bool inverted : 1;  // Bandera que indica si funciona con logica inversa.
    bool allocated : 1; // Bandera para indicar que el descriptor está en uso.
};

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

digital_output_t DigitalOutputAllocate(void);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

digital_input_t DigitalInputAllocate(void)
{
    digital_input_t input = NULL;

    static struct digital_input_s instances[INPUT_INSTANCES] = {0};

    for (int i = 0; i < INPUT_INSTANCES; i++)
    {
        if (!instances[i].allocated) // El descriptor no esta en uso
        {
            instances[i].allocated = true;
            input = &instances[i];
            break;
        }
    }

    return input;
}

digital_output_t DigitalOutputAllocate(void)
{
    digital_output_t output = NULL;

    static struct digital_output_s instances[OUTPUT_INSTANCES] = {0};

    for (int i = 0; i < OUTPUT_INSTANCES; i++)
    {
        if (!instances[i].allocated) // El descriptor no esta en uso
        {
            instances[i].allocated = true;
            output = &instances[i];
            break;
        }
    }

    return output;
}

/* === Public function implementation ========================================================== */

/*********Entradas**********/

digital_input_t DigitalInputCreate(uint8_t gpio, uint8_t bit, bool inverted)
{
    digital_input_t input = DigitalInputAllocate();

    if (input) // Si input=NULL no crea entrada y retorna NULL
    {
        input->gpio = gpio;
        input->bit = bit;
        input->inverted = inverted;
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, input->gpio, input->bit, false);
    }

    return input;
}

bool DigitalInputGetState(digital_input_t input)
{
    bool resultado = 0;

    if (input)
    {
        resultado = input->inverted ^ Chip_GPIO_ReadPortBit(LPC_GPIO_PORT, input->gpio, input->bit);
    }

    return resultado;
}

bool DigitalInputHasChanged(digital_input_t input)
{
    bool resultado = 0;

    if (input)
    {
        bool state = DigitalInputGetState(input); // ==0 porque las
        resultado = state != input->last_state;
        input->last_state = state;
    }

    return resultado;
}

bool DigitalInputHasActivated(digital_input_t input)
{
    bool resultado = 0;

    if (input)
    {
        bool state = DigitalInputGetState(input);
        resultado = state && !input->last_state;
        input->last_state = state;
    }

    return resultado;
}

bool DigitalInputHasDeactivated(digital_input_t input)
{
    bool resultado = 0;

    if (input)
    {
        bool state = DigitalInputGetState(input);
        resultado = !state && input->last_state;
        input->last_state = state;
    }

    return resultado;
}

/*********Salidas**********/

digital_output_t DigitalOutputCreate(uint8_t gpio, uint8_t bit, bool inverted)
{
    digital_output_t output = DigitalOutputAllocate();

    if (output) // Si output=NULL no crea salida y retorna NULL
    {
        output->gpio = gpio;
        output->bit = bit;
        output->inverted = inverted;
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->gpio, output->bit, false);
        Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, output->gpio, output->bit, true);
    }

    return output;
}

void DigitalOutputActivate(digital_output_t output)
{
    if (output)
    {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->gpio, output->bit, output->inverted ^ true);
    }

    return;
}

void DigitalOutputDeactivate(digital_output_t output)
{
    if (output)
    {
        Chip_GPIO_SetPinState(LPC_GPIO_PORT, output->gpio, output->bit, output->inverted ^ false);
    }

    return;
}

void DigitalOutputToggle(digital_output_t output)
{
    if (output)
    {
        Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, output->gpio, output->bit);
    }

    return;
}

/* === End of documentation ==================================================================== */

/** @} End of module definition for doxygen */
