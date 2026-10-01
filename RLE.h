#ifndef RLE_H
#define RLE_H

#include <string>

using namespace std;

char* comprimirRLE(const char* texto, int cantidad, int& cantidadComprimida);
char* descomprimirRLE(const char* texto, int cantidad, int& cantidadDescomprimida);

#endif // RLE_H
