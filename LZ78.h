#ifndef LZ78_H
#define LZ78_H

struct Entrada
{
    int prefijo;
    char caracter;
};

int buscar(Entrada* diccionario, int cantidad,
           int prefijo, char caracter);

Entrada* comprimir(char texto[], int& cantidad);

void descomprimir(Entrada* diccionario, int cantidad,
                  char resultado[]);

#endif



