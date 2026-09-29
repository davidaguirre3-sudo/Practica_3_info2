#include "ENCRIPTACION.h"
#include <stdexcept>

using namespace std;

unsigned char rotarIzquierda(unsigned char dato, int n)
{
    if (n <= 0 || n >= 8)
        throw invalid_argument("La rotacion debe estar entre 1 y 7");

    unsigned char resultado;

    resultado = (unsigned char)(
        (dato << n) | (dato >> (8 - n)) );

    return resultado;
}

unsigned char rotarDerecha(unsigned char dato, int n)
{
    if (n <= 0 || n >= 8)
        throw invalid_argument("La rotacion debe estar entre 1 y 7");

    unsigned char resultado;

    resultado = (unsigned char)(
        (dato >> n) | (dato << (8 - n))
        );

    return resultado;
}


void encriptar(unsigned char datos[], int cantidad,
                    int n, unsigned char clave)
{
    if (datos == nullptr)
        throw invalid_argument("Los datos son nulos");

    if (n <= 0 || n >= 8)
        throw out_of_range("La rotacion debe estar entre 1 y 7");

    if (cantidad < 0)
        throw runtime_error("La cantidad de datos es invalida");

    for (int i = 0; i < cantidad; i++)
    {

        datos[i] = rotarIzquierda(datos[i], n);

        datos[i] = datos[i] ^ clave;
    }
}


void desencriptar(unsigned char datos[], int cantidad,
                       int n, unsigned char clave)
{
    if (datos == nullptr)
        throw invalid_argument("Los datos son nulos");

    if (n <= 0 || n >= 8)
        throw out_of_range("La rotacion debe estar entre 1 y 7");

    if (cantidad < 0)
        throw runtime_error("La cantidad de datos es invalida");

    for (int i = 0; i < cantidad; i++)
    {
        datos[i] = datos[i] ^ clave;

        datos[i] = rotarDerecha(datos[i], n);
    }
}