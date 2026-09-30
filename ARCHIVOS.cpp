#include "archivos.h"
#include <fstream>
#include <stdexcept>

using namespace std;

char* leerArchivo(const char* nombre, int& cantidad)
{
    if (nombre == nullptr)
        throw invalid_argument("El nombre del archivo es nulo");

    ifstream archivo(nombre, ios::binary);

    if (!archivo)
        throw runtime_error("No se pudo abrir el archivo de entrada");

    int capacidad = 100;
    cantidad = 0;
    char* texto = new char[capacidad];

    char caracter;

    while (archivo.get(caracter))
    {
        if (cantidad + 1 >= capacidad)
        {
            int nuevaCapacidad = capacidad * 2;
            char* nuevo = new char[nuevaCapacidad];

            for (int i = 0; i < cantidad; i++)
                nuevo[i] = texto[i];

            delete[] texto;
            texto = nuevo;
            capacidad = nuevaCapacidad;
        }

        texto[cantidad] = caracter;
        cantidad++;
    }

    archivo.close();

    if (cantidad == 0)
    {
        delete[] texto;
        throw out_of_range("El archivo esta vacio");
    }

    texto[cantidad] = '\0';
    return texto;
}

void escribirArchivo(const char* nombre, const char* texto, int cantidad)
{
    if (nombre == nullptr || texto == nullptr)
        throw invalid_argument("Nombre o texto nulo");

    if (cantidad < 0)
        throw out_of_range("Cantidad de caracteres invalida");

    ofstream archivo(nombre, ios::binary);

    if (!archivo)
        throw runtime_error("No se pudo abrir el archivo de salida");

    archivo.write(texto, cantidad);

    if (!archivo)
    {
        archivo.close();
        throw runtime_error("No se pudo escribir el archivo de salida");
    }

    archivo.close();
}
