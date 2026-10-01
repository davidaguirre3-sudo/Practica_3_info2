#ifndef INTEGRACION_H
#define INTEGRACION_H

void integrarRLE(const char* archivoEntrada,
                 const char* archivoSalida,
                 int n, unsigned char clave);

void integrarLZ78(const char* archivoEntrada,
                  const char* archivoSalida,
                  int n, unsigned char clave);

#endif // INTEGRACION_H
