#include "INTEGRACION.h"
#include "ARCHIVOS.h"
#include "RLE.h"
#include "LZ78.h"
#include "ENCRIPTACION.h"
#include <iostream>
#include <stdexcept>

using namespace std;

bool textosIguales(const char* texto1, int cantidad1,
                   const char* texto2, int cantidad2)
{
    if (texto1 == nullptr || texto2 == nullptr)
        throw invalid_argument("Texto nulo al comparar");

    if (cantidad1 != cantidad2)
        return false;

    for (int i = 0; i < cantidad1; i++)
    {
        if (texto1[i] != texto2[i])
            return false;
    }

    return true;
}

void integrarRLE(const char* archivoEntrada,
                 const char* archivoSalida,
                 int n, unsigned char clave)
{
    char* original = nullptr;
    char* comprimido = nullptr;
    char* desencriptado = nullptr;
    char* resultado = nullptr;
    char* resultadoArchivo = nullptr;
    unsigned char* datos = nullptr;

    try
    {
        int cantidadOriginal = 0;
        original = leerArchivo(archivoEntrada, cantidadOriginal);


        int cantidadComprimida = 0;
        comprimido = comprimirRLE(original, cantidadOriginal, cantidadComprimida);

        if (cantidadComprimida < 0)
            throw runtime_error("cantidadComprimida invalida");

        cout << "\nTexto comprimido con RLE:\n";
        cout.write(comprimido, cantidadComprimida);
        cout << endl;

        datos = new unsigned char[cantidadComprimida];

        for (int i = 0; i < cantidadComprimida; i++)
            datos[i] = (unsigned char)comprimido[i];

        encriptar(datos, cantidadComprimida, n, clave);
        desencriptar(datos, cantidadComprimida, n, clave);

        desencriptado = new char[cantidadComprimida + 1];

        for (int i = 0; i < cantidadComprimida; i++)
            desencriptado[i] = (char)datos[i];

        desencriptado[cantidadComprimida] = '\0';

        delete[] datos;
        datos = nullptr;

        int cantidadResultado = 0;
        resultado = descomprimirRLE(desencriptado, cantidadComprimida,cantidadResultado);

        if (!textosIguales(original, cantidadOriginal,
                           resultado, cantidadResultado))
        {
            throw runtime_error("La verificacion antes de guardar fallo");
        }

        escribirArchivo(archivoSalida,
                        resultado,
                        cantidadResultado);

        int cantidadResultadoArchivo = 0;
        resultadoArchivo = leerArchivo(archivoSalida,
                                       cantidadResultadoArchivo);

        if (!textosIguales(original, cantidadOriginal,
                           resultadoArchivo,
                           cantidadResultadoArchivo))
        {
            throw runtime_error("El archivo final no coincide con el original");
        }

        cout << "RLE: compresion, encriptacion, "
             << "desencriptacion y descompresion correctas." << endl;
        cout << "El archivo final coincide con el original." << endl;

        delete[] original;
        delete[] comprimido;
        delete[] desencriptado;
        delete[] resultado;
        delete[] resultadoArchivo;
    }
    catch (...)
    {
        delete[] original;
        delete[] comprimido;
        delete[] desencriptado;
        delete[] resultado;
        delete[] resultadoArchivo;
        delete[] datos;
        throw;
    }
}

void integrarLZ78(const char* archivoEntrada,
                  const char* archivoSalida,
                  int n, unsigned char clave)
{
    char* original = nullptr;
    Entrada* pares = nullptr;
    unsigned char* datos = nullptr;
    Entrada* paresRecuperados = nullptr;
    char* resultado = nullptr;
    char* resultadoArchivo = nullptr;

    try
    {
        int cantidadOriginal = 0;
        original = leerArchivo(archivoEntrada, cantidadOriginal);

        int cantidadPares = 0;
        pares = comprimir(original,cantidadOriginal, cantidadPares);

        int cantidadBytes = 0;
        datos = serializar(pares, cantidadPares,cantidadBytes);

        delete[] pares;
        pares = nullptr;

        encriptar(datos, cantidadBytes, n, clave);
        desencriptar(datos, cantidadBytes, n, clave);

        int cantidadParesRecuperados = 0;
        paresRecuperados = deserializar(datos,cantidadBytes,cantidadParesRecuperados);

        delete[] datos;
        datos = nullptr;

        resultado = new char[cantidadOriginal + 1];

        int cantidadResultado = 0;
        descomprimir(paresRecuperados, cantidadParesRecuperados,resultado, cantidadOriginal + 1,cantidadResultado);

        if (!textosIguales(original, cantidadOriginal,
                           resultado, cantidadResultado))
        {
            throw runtime_error("La verificacion antes de guardar fallo");
        }

        escribirArchivo(archivoSalida,resultado, cantidadResultado);

        int cantidadResultadoArchivo = 0;
        resultadoArchivo = leerArchivo(archivoSalida, cantidadResultadoArchivo);

        if (!textosIguales(original, cantidadOriginal, resultadoArchivo, cantidadResultadoArchivo))
        {
            throw runtime_error("El archivo final no coincide con el original");
        }

        cout << "LZ78: compresion, encriptacion, "
             << "desencriptacion y descompresion correctas." << endl;
        cout << "El archivo final coincide con el original." << endl;

        delete[] original;
        delete[] paresRecuperados;
        delete[] resultado;
        delete[] resultadoArchivo;
    }
    catch (...)
    {
        delete[] original;
        delete[] pares;
        delete[] datos;
        delete[] paresRecuperados;
        delete[] resultado;
        delete[] resultadoArchivo;
        throw;
    }
}
