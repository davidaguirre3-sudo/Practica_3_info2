#ifndef XOR_H
#define XOR_H

unsigned char rotarIzquierda(unsigned char dato, int n);

unsigned char rotarDerecha(unsigned char dato, int n);

unsigned char encriptar(unsigned char dato,
                        int n,
                        unsigned char clave);

unsigned char desencriptar(unsigned char dato,
                           int n,
                           unsigned char clave);

#endif // XOR_H
