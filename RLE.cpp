#include "RLE.h"
#include <string>
#include <stdexcept>

using namespace std;

char* comprimirRLE(const char* texto, int cantidad, int& cantidadComprimida)
{
    if (texto == nullptr)
        throw invalid_argument("El texto es nulo");

    if (cantidad <= 0)
        throw invalid_argument("El texto esta vacio");

    string resultado = "";
    int repetidas = 1;

    for (int i = 0; i < cantidad; i++)
    {
        if (i + 1 < cantidad && texto[i] == texto[i + 1])
        {
            repetidas++;
        }
        else
        {
            resultado += to_string(repetidas);
            resultado += ":";
            resultado += to_string((int)(unsigned char)texto[i]);
            resultado += ";";
            repetidas = 1;
        }
    }

    cantidadComprimida = (int)resultado.length();
    char* comprimido = new char[cantidadComprimida + 1];

    for (int i = 0; i < cantidadComprimida; i++)
        comprimido[i] = resultado[i];

    comprimido[cantidadComprimida] = '\0';

    return comprimido;
}

char* descomprimirRLE(const char* texto, int cantidad, int& cantidadDescomprimida)
{
    if (texto == nullptr)
        throw invalid_argument("El texto comprimido es nulo");

    if (cantidad <= 0)
        throw invalid_argument("El texto comprimido esta vacio");

    string resultado = "";
    int repetidas = 0;
    int ascii = 0;
    bool leyendoCantidad = true;
    bool hayNumero = false;

    for (int i = 0; i < cantidad; i++)
    {
        if (texto[i] >= '0' && texto[i] <= '9')
        {
            hayNumero = true;

            if (leyendoCantidad)
                repetidas = repetidas * 10 + (texto[i] - '0');
            else
                ascii = ascii * 10 + (texto[i] - '0');
        }
        else if (texto[i] == ':')
        {
            if (!leyendoCantidad || !hayNumero || repetidas <= 0)
                throw runtime_error("Formato RLE incorrecto");

            if (repetidas > 100000000)
                throw out_of_range("Cantidad de repeticiones demasiado grande");

            leyendoCantidad = false;
            hayNumero = false;
        }
        else if (texto[i] == ';')
        {
            if (leyendoCantidad || !hayNumero)
                throw runtime_error("Falta el codigo del caracter");

            if (ascii < 0 || ascii > 255)
                throw out_of_range("Codigo fuera del rango de un byte");

            for (int j = 0; j < repetidas; j++)
                resultado += (char)ascii;

            repetidas = 0;
            ascii = 0;
            leyendoCantidad = true;
            hayNumero = false;
        }
        else
        {
            throw runtime_error("Caracter invalido en el texto RLE");
        }
    }

    if (!leyendoCantidad || hayNumero)
        throw runtime_error("El texto RLE termino incompleto");

    cantidadDescomprimida = (int)resultado.length();
    char* original = new char[cantidadDescomprimida + 1];

    for (int i = 0; i < cantidadDescomprimida; i++)
        original[i] = resultado[i];

    original[cantidadDescomprimida] = '\0';

    return original;
}
