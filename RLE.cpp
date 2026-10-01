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
            resultado += texto[i];
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

char* descomprimirRLE(const char* texto, int cantidad,
                      int& cantidadDescomprimida)
{
    if (texto == nullptr)
        throw invalid_argument("El texto comprimido es nulo");

    if (cantidad <= 0)
        throw invalid_argument("El texto comprimido esta vacio");

    string resultado = "";

    int repetidas = 0;
    bool leyendoCantidad = true;
    bool hayNumero = false;

    for (int i = 0; i < cantidad; i++)
    {
        if (leyendoCantidad)
        {
            if (texto[i] >= '0' && texto[i] <= '9')
            {
                hayNumero = true;
                repetidas = repetidas * 10 + (texto[i] - '0');
            }
            else if (texto[i] == ':')
            {
                if (!hayNumero || repetidas <= 0)
                    throw runtime_error("Cantidad invalida en RLE");

                if (repetidas > 100000000)
                    throw out_of_range("Cantidad de repeticiones demasiado grande");

                leyendoCantidad = false;
                hayNumero = false;
            }
            else
            {
                throw runtime_error("Formato RLE incorrecto");
            }
        }
        else
        {
            if (texto[i] == ';')
            {
                throw runtime_error("Falta el caracter en RLE");
            }

            char caracter = texto[i];

            for (int j = 0; j < repetidas; j++)
                resultado += caracter;

            repetidas = 0;
            leyendoCantidad = true;

            if (i + 1 < cantidad && texto[i + 1] != ';')
                throw runtime_error("Falta el separador ';'");

            i++;
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
