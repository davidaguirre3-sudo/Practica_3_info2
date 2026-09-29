#include <iostream>
#include <stdexcept>
#include "ENCRIPTACION.h"

using namespace std;

int main()
{
    try
    {
        char mensaje[500];

        int n;   int claveEntera;

        cout << "Ingrese el mensaje: ";
        cin.getline(mensaje, 500);

        cout << "Ingrese la rotacion (1-7): ";
        cin >> n;

        cout << "Ingrese la clave (0-255): ";
        cin >> claveEntera;

        if (claveEntera < 0 || claveEntera > 255)
            throw out_of_range("La clave debe estar entre 0 y 255");

        unsigned char clave =
            (unsigned char)claveEntera;

        int cantidad = 0;

        while (mensaje[cantidad] != '\0')
        {
            cantidad++;
        }

        unsigned char* datos =new unsigned char[cantidad];

        for (int i = 0; i < cantidad; i++)
        {
            datos[i] = (unsigned char)mensaje[i];
        }

        encriptar(
            datos,
            cantidad,
            n,
            clave );

        cout << endl;
        cout << "Mensaje encriptado en bytes:" << endl;

        for (int i = 0; i < cantidad; i++)
        {
            cout << (int)datos[i] << " ";
        }

        cout << endl;

        desencriptar(
            datos,
            cantidad,
            n,
            clave );

        cout << "Mensaje desencriptado: ";

        for (int i = 0; i < cantidad; i++)
        {
            cout << (char)datos[i];
        }

        cout << endl;

        for (int i = 0; i < cantidad; i++)
        {
            if ((unsigned char)mensaje[i] != datos[i])
                throw runtime_error( "El mensaje recuperado no coincide" );
        }

        cout << "La desencriptacion es correcta."
             << endl;

        delete[] datos;
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