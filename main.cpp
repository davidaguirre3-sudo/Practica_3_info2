#include <iostream>
#include "lz78.h"

using namespace std;

int main()
{
    try
    {
        char texto[100];

        cout << "Ingrese el texto: ";
        cin.getline(texto, 100);

        int cantidad = 0;

        Entrada* diccionario = comprimir(texto, cantidad);

        char resultado[500];

        descomprimir(
            diccionario,
            cantidad,
            resultado
            );

        cout << endl;

        cout << "Original: "<< texto << endl;

        cout << "Descomprimido: " << resultado << endl;

        int i = 0;

        while (texto[i] != '\0' &&
               resultado[i] != '\0')
        {
            if (texto[i] != resultado[i])
            {
                throw runtime_error(
                    "El texto descomprimido no coincide"
                    );
            }
          i++;
        }

        if (texto[i] != '\0' ||
            resultado[i] != '\0')
        {
            throw runtime_error(
                "El texto descomprimido no coincide"
                );
        }

        cout << "La descompresion es correcta."<< endl;

        delete[] diccionario;
    }
    catch (invalid_argument& e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (out_of_range& e)
    {
        cout << "Error: "<< e.what() << endl;
    }
    catch (runtime_error& e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}