#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

unsigned char rotarIzquierda(unsigned char dato, int n);
unsigned char rotarDerecha(unsigned char dato, int n);

void encriptar(unsigned char datos[], int cantidad,
                    int n, unsigned char clave);

void desencriptar(unsigned char datos[], int cantidad,
                       int n, unsigned char clave);

#endif // ENCRIPTACION_H
