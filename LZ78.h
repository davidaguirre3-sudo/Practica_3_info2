#ifndef LZ78_H
#define LZ78_H

struct Entrada
{
    int prefijo;
    char caracter;
};


int buscar(Entrada* diccionario, int cantidad,
           int prefijo, char caracter);

Entrada* agregarEntrada(Entrada* diccionario, int& cantidad,
                        int prefijo, char caracter);

Entrada* comprimir(const char* texto, int cantidadTexto, int& cantidadPares);

unsigned char* serializar(Entrada* pares, int cantidad,
                              int& cantidadBytes);

Entrada* deserializar(const unsigned char* datos, int cantidadBytes,
                          int& cantidadPares);

void descomprimir(Entrada* pares, int cantidadPares, char resultado[], int capacidadResultado, int& cantidadResultado);

#endif



