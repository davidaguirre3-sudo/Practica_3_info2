#include <iostream>
#include <stdexcept>
#include "integracion.h"

using namespace std;

int main()
{
    try
    {
        int metodo;
        int n;
        int claveEntera;
        char archivoEntrada[100];
        char archivoSalida[100];

        cout << "------- PRACTICA 3--------" << endl;
        cout << "1. RLE" << endl;
        cout << "2. LZ78" << endl;
        cout << "Seleccione el metodo: ";

        if (!(cin >> metodo))
            throw invalid_argument("Debe ingresar un numero");

        if (metodo < 1 || metodo > 2)
            throw out_of_range("El metodo debe ser 1 o 2");

        cout << "Archivo de entrada: ";
        cin >> archivoEntrada;

        cout << "Archivo de salida: ";
        cin >> archivoSalida;

        cout << "Rotacion (1-7): ";
        if (!(cin >> n))
            throw invalid_argument("La rotacion debe ser un numero");

        cout << "Clave (0-255): ";
        if (!(cin >> claveEntera))
            throw invalid_argument("La clave debe ser un numero");

        if (claveEntera < 0 || claveEntera > 255)
            throw out_of_range("La clave debe estar entre 0 y 255");

        unsigned char clave = (unsigned char)claveEntera;

        if (metodo == 1)
        {
            integrarRLE(archivoEntrada,
                        archivoSalida,
                        n,
                        clave);
        }
        else
        {
            integrarLZ78(archivoEntrada,
                         archivoSalida,
                         n,
                         clave);
        }
    }
    catch (invalid_argument& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (out_of_range& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
