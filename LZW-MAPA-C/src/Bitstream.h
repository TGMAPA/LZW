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
// Archivo .h - Bitstream
// ------------------------------------------


// Inclusión de librerías
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Inclusión de estructuras utilizadas
#include "Tools.h"
#include "FileManager.h"

#ifndef _BITSTREAM_H
#define _BITSTREAM_H

// Constantes
#define BYTE 8 
static const int N_BITS = 12; // Numero de bits para la fragmentación

// Estructura para manejo y escritura de un tamaño de Bits definido 
typedef struct Bitstream Bitstream;
struct Bitstream{
  char bin_str[16 + 1];        // Cadena de caracteres con el valor binario del codigo [u_int_16]. De tamaño (valor binario de 16 caracteres + caracter nulo)
  char bin_str_fixed[16 + 1];  // Cadena de caracteres que almacena el valor binario de la cadena bin_str, pero con un tamaño ajustado a N_BITS deseados
  char buffer[BYTE + 1];       // Cadena de caracteres que almacena los bits excluidos por el proceso de desplazamiento de bits para el ajuste a un tamaño de BYTE
  char writableByte[BYTE + 1]; // Cadena de caracteres que almacena los bits que se escribiran en el archivo de salida
  bool isBufferFull;           // Valor booleano que indica si el buffer esta lleno o no
  FileManager *filemanager;	   // Objeto tipo Filemanager que permitira realizar la escritura de bits
};


// Método constructor que devuelve un objeto tipo bitstream asociado con un manipulador de archivos
// Parametros:
// - FileManager *filemanager_ -> Estructura manipuladora de archivos que permitira la escritura en un archivo de salida
// Retorno:
// - *Bitstream
Bitstream *buildBitstream(FileManager *filemanager_);

// Método que agrega los bits contenidos en el buffer al inicio del bin_str_fixed 
// Parametros:
// - Bitstream *bitstream -> Estructura que contiene los datos de la bitstream
// - char *str -> Cadena de caracteres a la que se le agregaran los bits del buffer al inicio
// Retorno:
// - void
void addBuffer(Bitstream *bitstream, char *str);

// Método que separa el primer BYTE de la cadena bin_str_fixed y el resto lo almacena en el buffer
// Parametros:
// - Bitstream *bitstream -> Estructura que contiene los datos de la bitstream
// - char *str -> Cadena de caracteres de la que se separaran los bits del primer BYTE y el resto se almacenaran en el buffer
// Retorno:
// - void
void getByte(Bitstream *bitstream, char *str);

// Método para volver las cadenas a su estado inicial para su posterior uso
// Parametros:
// - Bitstream *bitstream -> Estructura que contiene los datos de la bitstream
// Retorno:
// - void
void resetStrings(Bitstream *bitstream);

// Método que revisa si el buffer esta lleno y si lo esta y lo escribe en el archivo
// Parametros:
// - Bitstream *bitstream -> Estructura que contiene los datos de la bitstream
// Retorno:
// - void
void bufferFinalCheck(Bitstream *bitstream);

// Método principal que recibe un codigo[u_int16_t] y lo procesa para escribirlo finalmente en el archivo
// Parametros:
// - Bitstream *bitstream -> Estructura que contiene los datos de la bitstream
// - u_int16_t *code -> Valor entero[16bits] que se procesara mediante el procedimiento bitstream y padding
// Retorno:
// - void
void bitstream(Bitstream *bitstream, u_int16_t *code);

// Método que recibe un string procesado y lo escribe en el archivo de salida
// Parametros:
// - Bitstream *bitstream -> Estructura que contiene los datos de la bitstream
// - char *str2write -> Cadena de caracteres que se escribira en el archivo de salida
// Retorno:
// - void
void writeInFile(Bitstream *bitstream, char *str2write);

//Método que libera la memoria utilizada por un objeto tipo Bitstream
// Parametros:
// - Bitstream *bitstream -> Estructura bitstream a eliminar
// Retorno:
// - void
void deleteBitstream(Bitstream *bitstream);

#endif // _BITSTREAM_H