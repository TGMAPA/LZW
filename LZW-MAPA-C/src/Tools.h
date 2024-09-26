// ------------------------------------------
// Miguel Ángel Pérez Ávila A01369908   25/09/2024 - Algoritmos Avanzados
// 
//  GitHub: https://github.com/TGMAPA
//
//  "Compresión-LZW para archivos"
//
// Compilado en:
//		- Ubuntu  - g++ 9.5.0
//		- Suse	  - g++ 7.5.0
// ------------------------------------------
// Archivo .h - Tools
// ------------------------------------------


// Inclusión de librerías
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef _TOOLS_H
#define _TOOLS_H

// Función que restablece una cadena de caracteres
// Parametros:
// - char *str -> Cadena de caracteres que se busca restablecer
// Retorno:
// - void
void emptyStr(char *str);

// Función que recibe un codigo[u_int16_t] y devuelve su expresión binaria[16bits]
// Parametros:
// - u_int16_t *num -> Entero de 16 bits a procesar
// - char *str -> Cadena de caracteres[16] donde se almacenará la expresión binaria
// Retorno:
// - void
void uint16_to_bin(u_int16_t *num, char *str);

// Función que ajusta una cadena de bits a un tamaño N_bits deseado
// Parametros:
// - char *str -> Cadena de caracteres[16] a ajustar
// - char *finalstr -> Cadena de caracteres[n_bits] donde se almacenará la cadena binaria ajustada
// - const int *n_bits -> Tamaño de bits desado para ajustar el tamaño de la cadena binaria
// Retorno:
// - void
void fixtoNbits(char *str, char *finalstr, const int *n_bits);

// Función que recibe una cadena[8] para devolver su equivalencia en un int[8bits]
// Parametros:
// - char *byte_str -> Cadena de caracteres[8]
// Retorno:
// - u_int8_t Resultado binario[8bits]
u_int8_t binary2uint8( char *byte_str);

#endif //_TOOLS_H