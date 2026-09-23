#include <iostream>
#include "RLE.h"

using namespace std;

int main()
{
    try
    {
        string texto;

        cout << "Ingrese el texto: ";
        getline(cin, texto);

        string comprimido = comprimir(texto);

        cout << "Original: " << texto << endl;
        cout << "Comprimido: " << comprimido << endl;

        string descomprimido = descomprimir(comprimido);

        cout << "Descomprimido: " << descomprimido << endl;

        if (texto == descomprimido)
            cout << "La descompresion es correcta." << endl;
        else
            throw runtime_error("El texto no coincide");
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
