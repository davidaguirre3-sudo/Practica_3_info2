#include <iostream>
#include <cstring>
#include "lz78.h"

using namespace std;

int main()
{
    try
    {
        char texto[100];

        cout << "Ingrese el texto: ";
        cin.getline(texto, 100);

        Entrada* diccionario = new Entrada[100];

        int cantidad = 0;

        cout << "\nPares generados:\n";

        comprimir(texto, diccionario, cantidad);

        char* resultado = new char[100];

        descomprimir(diccionario, cantidad, resultado);

        cout << "\nOriginal: " << texto << endl;
        cout << "Descomprimido: " << resultado << endl;

        if (strcmp(texto, resultado) == 0)
        {
            cout << "La descompresion es correcta." << endl;
        }
        else
        {
            throw runtime_error("Los textos no coinciden");
        }

        delete[] diccionario;
        delete[] resultado;
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