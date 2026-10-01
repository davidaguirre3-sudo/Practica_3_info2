#include "lz78.h"
#include <stdexcept>
#include <climits>
#include <iostream>

using namespace std;

int buscar(Entrada* diccionario, int cantidad,
           int prefijo, char caracter)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (diccionario[i].prefijo == prefijo &&
            diccionario[i].caracter == caracter)
        {
            return i + 1;
        }
    }

    return 0;
}

Entrada* agregarEntrada(Entrada* diccionario, int& cantidad,
                        int prefijo, char caracter)
{
    Entrada* nuevo = new Entrada[cantidad + 1];

    for (int i = 0; i < cantidad; i++)
        nuevo[i] = diccionario[i];

    nuevo[cantidad].prefijo = prefijo;
    nuevo[cantidad].caracter = caracter;

    delete[] diccionario;

    cantidad++;
    return nuevo;
}

Entrada* comprimirLZ78(const char* texto, int cantidadTexto,
                       int& cantidadPares)
{
    if (texto == nullptr)
        throw invalid_argument("El texto es nulo");

    if (cantidadTexto <= 0)
        throw invalid_argument("El texto esta vacio");

    cantidadPares = 0;
    Entrada* diccionario = nullptr;

    int posicion = 0;
    int prefijo = 0;

    while (posicion < cantidadTexto)
    {
        int indice = buscar(diccionario, cantidadPares,
                            prefijo, texto[posicion]);

        if (indice != 0)
        {
            prefijo = indice;
            posicion++;
        }
        else
        {
            diccionario = agregarEntrada(diccionario,
                                         cantidadPares,
                                         prefijo,
                                         texto[posicion]);

            cout << "(" << prefijo << ", "
                 << texto[posicion] << ")" << endl;

            prefijo = 0;
            posicion++;
        }
    }
    if (prefijo != 0)
    {
        diccionario = agregarEntrada(diccionario,
                                     cantidadPares,
                                     prefijo,
                                     '\0');

        cout << "(" << prefijo << ", FIN)" << endl;
    }

    return diccionario;
}


void descomprimirLZ78(Entrada* pares, int cantidadPares,
                      char resultado[], int capacidadResultado,
                      int& cantidadResultado)
{
    if (pares == nullptr || resultado == nullptr)
        throw invalid_argument("Datos de LZ78 nulos");

    if (cantidadPares <= 0)
        throw invalid_argument("No hay pares para descomprimir");

    if (capacidadResultado <= 0)
        throw out_of_range("Capacidad del resultado invalida");

    char* temporal = new char[cantidadPares + 1];
    cantidadResultado = 0;

    for (int i = 0; i < cantidadPares; i++)
    {
        int indice;

        if (pares[i].caracter == '\0')
            indice = pares[i].prefijo;
        else
            indice = i + 1;

        int cantidadTemporal = 0;

        while (indice != 0)
        {
            if (indice < 1 || indice > i + 1)
            {
                delete[] temporal;
                throw out_of_range("Indice de LZ78 incorrecto");
            }

            temporal[cantidadTemporal] =
                pares[indice - 1].caracter;

            cantidadTemporal++;
            indice = pares[indice - 1].prefijo;

            if (cantidadTemporal > cantidadPares)
            {
                delete[] temporal;
                throw runtime_error("Cadena LZ78 demasiado larga");
            }
        }

        for (int j = cantidadTemporal - 1; j >= 0; j--)
        {
            if (cantidadResultado >= capacidadResultado - 1)
            {
                delete[] temporal;
                throw out_of_range("El resultado no cabe en memoria");
            }

            resultado[cantidadResultado] = temporal[j];
            cantidadResultado++;
        }
    }

    resultado[cantidadResultado] = '\0';
    delete[] temporal;

    if (cantidadResultado == 0)
        throw runtime_error("No se pudo reconstruir el texto");
}

unsigned char* serializar(Entrada* pares, int cantidad,
                              int& cantidadBytes)
{
    if (pares == nullptr)
        throw invalid_argument("Los pares son nulos");

    if (cantidad <= 0)
        throw invalid_argument("No hay pares para serializar");

    if (cantidad > INT_MAX / 5)
        throw out_of_range("Demasiados pares para serializar");

    cantidadBytes = cantidad * 5;
    unsigned char* datos = new unsigned char[cantidadBytes];

    int posicion = 0;

    for (int i = 0; i < cantidad; i++)
    {
        if (pares[i].prefijo < 0)
        {
            delete[] datos;
            throw out_of_range("Prefijo negativo");
        }

        unsigned int prefijo = (unsigned int)pares[i].prefijo;

        datos[posicion++] = (unsigned char)((prefijo >> 24) & 255);
        datos[posicion++] = (unsigned char)((prefijo >> 16) & 255);
        datos[posicion++] = (unsigned char)((prefijo >> 8) & 255);
        datos[posicion++] = (unsigned char)(prefijo & 255);
        datos[posicion++] = (unsigned char)pares[i].caracter;
    }

    return datos;
}

Entrada* deserializar(const unsigned char* datos, int cantidadBytes,
                          int& cantidadPares)
{
    if (datos == nullptr)
        throw invalid_argument("Los datos son nulos");

    if (cantidadBytes <= 0)
        throw invalid_argument("No hay datos para deserializar");

    if (cantidadBytes % 5 != 0)
        throw runtime_error("Los datos LZ78 estan incompletos");

    cantidadPares = cantidadBytes / 5;
    Entrada* pares = new Entrada[cantidadPares];

    int posicion = 0;

    for (int i = 0; i < cantidadPares; i++)
    {
        unsigned int prefijo = 0;

        prefijo = (prefijo << 8) | datos[posicion++];
        prefijo = (prefijo << 8) | datos[posicion++];
        prefijo = (prefijo << 8) | datos[posicion++];
        prefijo = (prefijo << 8) | datos[posicion++];

        if (prefijo > (unsigned int)INT_MAX)
        {
            delete[] pares;
            throw out_of_range("Prefijo fuera del rango de int");
        }

        pares[i].prefijo = (int)prefijo;
        pares[i].caracter = (char)datos[posicion++];
    }

    return pares;
}
