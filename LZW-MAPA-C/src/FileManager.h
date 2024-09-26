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
// Archivo .h - FileManager
// ------------------------------------------


// Inclusión de librerías
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FILEMANAGER_H
#define _FILEMANAGER_H

// Estructura manipuladora de archivos de entrada y salida para lectura y escritura 
typedef struct FileManager FileManager;
struct FileManager {
	FILE *input_file;              // Objeto tipo FILE contenedor del archivo de entrada asociado
	FILE *output_file;             // Objeto tipo FILE contenedor del archivo de salida asociado
	const char *input_file_name;   // Cadena constante de caracteres que indican el nombre y ubicación del archivo de entrada
	const char *output_file_name;  // Cadena constante de caracteres que indican el nombre y ubicación del archivo de salida
	const char *ext;               // Extension de archivo	
};

// Método que construye un Objeto tipo FileManger
// Parametros:
// - const char *input_file_name  -> Cadena constante de caracteres que indican el nombre y ubicación del archivo de entrada
// - const char *output_file_name -> Cadena constante de caracteres que indican el nombre y ubicación del archivo de salida
// Retorno:
// - *FileManager
FileManager *createFileManager(const char *input_file_name_, const char *output_file_name_);

// Método que libera la memoria utilizada por un objeto tipo FileManager y sus archivos
// Parametros:
// - FileManager *FileManager  ->  Estructura de tipo FileManger a eliminar
// Retorno:
// - void
void deleteFileManager(FileManager *FileManager);

// Método utilizado para escribir un caracter en el archivo de salida asociado con un manipulador de archivos
// Parametros:
// - FileManager *FileManager  ->  Estructura de tipo FileManger a eliminar
// - char *char2write          ->  Caracter a escribir en el archivo de salida
// Retorno:
// - void
void write(FileManager *fileManager, char *char2write);

// Método utilizado para la apertura del archivo de entrada en modo lectura asociado con un manipulador de archivos
// Parametros:
// - FileManager *FileManager  ->  Estructura de tipo FileManger a eliminar
// Retorno:
// - void
void openInputFile(FileManager *fileManager);

// Método utilizado para cerrar el archivo de entrada asociado con un manipulador de archivos después de su utilización
// Parametros:
// - FileManager *FileManager  ->  Estructura de tipo FileManger a eliminar
// Retorno:
// - void
void closeInputFile(FileManager *fileManager);

// Método utilizado para la apertura del archivo de salida en modo de escritura asociado con un manipulador de archivos
// Parametros:
// - FileManager *FileManager  ->  Estructura de tipo FileManger a eliminar
// Retorno:
// - void
void openOutputFile(FileManager *fileManager);

// Método utilizado para cerrar el archivo de salida asociado con un manipulador de archivos después de su utilización
// Parametros:
// - FileManager *FileManager  ->  Estructura de tipo FileManger a eliminar
// Retorno:
// - void
void closeOutputFile(FileManager *fileManager);

#endif // _FILEMANAGER_H