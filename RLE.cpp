#include "RLE.h"
#include <stdexcept>

using namespace std;

string comprimir(string texto)
{
    if (texto.empty())
        throw invalid_argument("El texto esta vacio");

    string resultado = "";
    int cantidad = 1;

    for (int i = 0; i < texto.length(); i++)
    {
        if (i + 1 < texto.length() && texto[i] == texto[i + 1])
        {
            cantidad++;
        }
        else
        {
            resultado += to_string(cantidad);
            resultado += texto[i];
            cantidad = 1;
        }
    }

    return resultado;
}

string descomprimir(string texto)
{
    if (texto.empty())
        throw invalid_argument("El texto comprimido esta vacio");

    string resultado = "";
    int cantidad = 0;

    for (int i = 0; i < texto.length(); i++)
    {
        if (texto[i] >= '0' && texto[i] <= '9')
        {
            cantidad = cantidad * 10 + (texto[i] - '0');
        }
        else
        {
            if (cantidad == 0)
                throw runtime_error("Formato RLE incorrecto");

            for (int j = 0; j < cantidad; j++)
            {
                resultado += texto[i];
            }

            cantidad = 0;
        }
    }

    if (cantidad != 0)
        throw out_of_range("Falta un caracter en el texto comprimido");

    return resultado;
}
