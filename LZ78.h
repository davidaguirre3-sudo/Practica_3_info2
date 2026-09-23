#ifndef LZ78_H
#define LZ78_H

struct Entrada{

    int prefijo;
    char caracter;
};

void comprimir(char texto[], Entrada diccionario[], int& cantidad);

void descomprimir(Entrada diccionario[], int cantidad, char resultado[]);

#endif



