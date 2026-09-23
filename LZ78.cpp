#include "lz78.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int buscar(Entrada diccionario[], int cantidad,
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

void comprimir(char texto[], Entrada diccionario[], int& cantidad)
{
    if (texto[0] == '\0')
        throw invalid_argument("El texto esta vacio");

    int i = 0;
    int prefijo = 0;

    while (texto[i] != '\0')
    {
        int posicion = buscar(diccionario, cantidad,
                              prefijo, texto[i]);

        if (posicion != 0)
        {
            prefijo = posicion;
            i++;
        }
        else
        {
            if (cantidad >= 100)
                throw out_of_range("El diccionario esta lleno");

            diccionario[cantidad].prefijo = prefijo;
            diccionario[cantidad].caracter = texto[i];

            cout << "(" << prefijo << ", "
                 << texto[i] << ")" << endl;

            cantidad++;

            prefijo = 0;
            i++;
        }
    }

    // Si queda una frase completa al final,
    // se agrega usando su ultimo caracter.
    if (prefijo != 0)
    {
        if (cantidad >= 100)
            throw out_of_range("El diccionario esta lleno");

        int indice = prefijo;

        char temporal[100];
        int cantidadTemporal = 0;

        while (indice != 0)
        {
            temporal[cantidadTemporal] =
                diccionario[indice - 1].caracter;

            cantidadTemporal++;

            indice = diccionario[indice - 1].prefijo;
        }

        for (int j = cantidadTemporal - 1; j >= 0; j--)
        {
            if (j == 0)
            {
                diccionario[cantidad].prefijo =
                    diccionario[indice].prefijo;

                diccionario[cantidad].caracter =
                    temporal[j];

                cout << "("
                     << diccionario[cantidad].prefijo
                     << ", "
                     << diccionario[cantidad].caracter
                     << ")" << endl;

                cantidad++;
            }
        }
    }
}

void descomprimir(Entrada diccionario[], int cantidad,
                  char resultado[])
{
    if (cantidad <= 0)
        throw invalid_argument("El diccionario esta vacio");

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
                throw runtime_error("Frase demasiado larga");
        }

        for (int j = cantidadTemporal - 1; j >= 0; j--)
        {
            resultado[posicionResultado] =
                temporal[j];

            posicionResultado++;
        }
    }

    resultado[posicionResultado] = '\0';

    if (posicionResultado == 0)
        throw runtime_error("No se pudo descomprimir");
}