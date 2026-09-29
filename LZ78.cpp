#include "lz78.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int buscar(Entrada* diccionario, int cantidad,
           int prefijo, char caracter)
{
    for (int i = 0; i < cantidad; i++)
    {
        if (diccionario[i].prefijo == prefijo && diccionario[i].caracter == caracter)
        {
            return i + 1;
        }
    }

    return 0;
}


Entrada* agregar(Entrada* diccionario, int& cantidad,
                 int prefijo, char caracter)
{
    Entrada* nuevo = new Entrada[cantidad + 1];

    for (int i = 0; i < cantidad; i++)
    {
        nuevo[i] = diccionario[i];
    }

    nuevo[cantidad].prefijo = prefijo;
    nuevo[cantidad].caracter = caracter;

    delete[] diccionario;

    cantidad++;

    return nuevo;
}


Entrada* comprimir(char texto[], int& cantidad)
{
    if (texto == nullptr)
        throw invalid_argument("El texto no puede ser nulo");

    if (texto[0] == '\0')
        throw invalid_argument("El texto esta vacio");

    cantidad = 0;

    Entrada* diccionario = nullptr;

    int i = 0;
    int prefijo = 0;

    while (texto[i] != '\0')
    {
        int posicion = buscar(
            diccionario,cantidad, prefijo, texto[i]);

        if (posicion != 0)
        {
            prefijo = posicion;
            i++;
        }
        else
        {
            diccionario = agregar(
                diccionario,cantidad, prefijo,texto[i]
                );

            cout << "(" << prefijo<< ", " << texto[i] << ")"<< endl;

            prefijo = 0;
            i++;
        }
    }

    return diccionario;
}


void descomprimir(Entrada* diccionario, int cantidad,
                  char resultado[])
{
    if (diccionario == nullptr)
        throw invalid_argument("El diccionario es nulo");

    if (cantidad <= 0)
        throw out_of_range("El diccionario esta vacio");

    int posicionResultado = 0;

    for (int i = 0; i < cantidad; i++)
    {
        int indice = i + 1;

        char temporal[100];
        int cantidadTemporal = 0;

        while (indice != 0)
        {
            if (indice < 1 || indice > cantidad)
                throw out_of_range("Indice incorrecto");

            temporal[cantidadTemporal] =
                diccionario[indice - 1].caracter;

            cantidadTemporal++;

            indice =
                diccionario[indice - 1].prefijo;

            if (cantidadTemporal >= 100)
                throw runtime_error(
                    "Frase demasiado larga"
                    );
        }

        for (int j = cantidadTemporal - 1;
             j >= 0;
             j--)
        {
            resultado[posicionResultado] =
                temporal[j];

            posicionResultado++;
        }
    }

    resultado[posicionResultado] = '\0';

    if (posicionResultado == 0)
        throw runtime_error( "No se pudo descomprimir");
}

