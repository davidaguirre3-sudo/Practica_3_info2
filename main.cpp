#include <iostream>
#include "XOR.H"

using namespace std;

int main()
{
    try
    {
        int dato;
        int n;
        int clave;

        cout << "Ingrese un dato entre 0 y 255: ";
        cin >> dato;

        cout << "Ingrese la cantidad de posiciones a rotar (1-7): ";
        cin >> n;

        cout << "Ingrese la clave entre 1 y 255: ";
        cin >> clave;

        if (dato < 0 || dato > 255)
            throw out_of_range("El dato debe estar entre 0 y 255");

        if (n <= 0 || n >= 8)
            throw invalid_argument("La rotacion debe estar entre 1 y 7");

        if (clave < 1 || clave > 255)
            throw runtime_error("La clave debe estar entre 1 y 255");

        unsigned char original = dato;
        unsigned char llave = clave;

        unsigned char cifrado =
            encriptar(original, n, llave);

        unsigned char recuperado =
            desencriptar(cifrado, n, llave);

        cout << endl;

        cout << "Original: "
             << (int)original << endl;

        cout << "Encriptado: "
             << (int)cifrado << endl;

        cout << "Desencriptado: "
             << (int)recuperado << endl;

        if (original == recuperado)
        {
            cout << "La desencriptacion es correcta."
                 << endl;
        }
        else
        {
            throw runtime_error(
                "El dato original y el recuperado no coinciden");
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