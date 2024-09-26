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
// Archivo .h - Compressor
// ------------------------------------------


// Inclusión de librerías
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclusión de estructuras utilizadas
#include "FileManager.h"
#include "CompressionTable.h"
#include "Bitstream.h"

#ifndef _COMPRESSOR_H
#define _COMPRESSOR_H

#define DICTSIZE 4096 // 2**12

// Estructura para compresión LZW de archivos
typedef struct Compressor Compressor;
struct Compressor {
	FileManager *filemanager; // Objeto tipo Filemanager que permitira tener acceso a los archivos involucrados
};

// Método que construye un Objeto tipo Compressor
// Parametros:
// - const char *input_file_name  -> Cadena constante de caracteres que indican el nombre y ubicación del archivo de entrada
// - const char *output_file_name -> Cadena constante de caracteres que indican el nombre y ubicación del archivo de salida
// Retorno:
// - *Compressor
Compressor *buildCompressor(const char *input_file_name, const char *output_file_name);

// Método que libera la memoria utilizada por un objeto tipo Compressor y su manipulador de archivos
// Parametros:
// - Compressor *compressor -> Estructura de tipo Compressor a eliminar
// Retorno:
// - void
void deleteCompressor(Compressor *compressor);

// Método que implementa una compresión de archivos LZW
// Parametros:
// - Compressor *compressor -> Estructura de tipo Compressor a eliminar
// - bool memorizable		-> Bool que indica el modo de Memorización para la tabla de compresión/diccionario
// Retorno:
// - void
void LZWCompress(Compressor *compressor, bool memorizable);

#endif // _COMPRESOR_H