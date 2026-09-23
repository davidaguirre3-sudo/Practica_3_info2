#include "XOR.H"
#include <stdexcept>

using namespace std;

unsigned char rotarIzquierda(unsigned char dato, int n)
{
    if (n <= 0 || n >= 8)
        throw invalid_argument("La rotacion debe estar entre 1 y 7");

    unsigned char resultado;

    resultado = (dato << n) | (dato >> (8 - n));

    return resultado;
}

unsigned char rotarDerecha(unsigned char dato, int n)
{
    if (n <= 0 || n >= 8)
        throw invalid_argument("La rotacion debe estar entre 1 y 7");

    unsigned char resultado;

    resultado = (dato >> n) | (dato << (8 - n));

    return resultado;
}

unsigned char encriptar(unsigned char dato,
                        int n,
                        unsigned char clave)
{
    if (n <= 0 || n >= 8)
        throw invalid_argument("La rotacion debe estar entre 1 y 7");

    if (clave == 0)
        throw out_of_range("La clave no puede ser 0");

    unsigned char rotado;

    rotado = rotarIzquierda(dato, n);

    unsigned char resultado;

    resultado = rotado ^ clave;

    return resultado;
}

unsigned char desencriptar(unsigned char dato,
                           int n,
                           unsigned char clave)
{
    if (n <= 0 || n >= 8)
        throw invalid_argument("La rotacion debe estar entre 1 y 7");

    if (clave == 0)
        throw out_of_range("La clave no puede ser 0");

    unsigned char xorResultado;

    xorResultado = dato ^ clave;

    unsigned char resultado;

    resultado = rotarDerecha(xorResultado, n);

    return resultado;
}