// ------------------------------------------
// Miguel Ángel Pérez Ávila   25/09/2024 - Algoritmos Avanzados
// 
//  GitHub: https://github.com/TGMAPA
//
//  "Compresión-LZW para archivos"
//
// Compilado en:
//      - Ubuntu  - g++ 9.5.0
//      - Suse    - g++ 7.5.0
// ------------------------------------------
// Archivo .c - MAIN
// ------------------------------------------

// ------------------------------------------
// Para compilar el programa utilizar en la carpeta src: 
//    gcc *.c -o <nombre_del_archivo_compilado> 
// 
// Para ejecutar el programa especificando archivos de entrada y salida utilizar : 
//    ./<nombre_del_archivo_compilado> <archivo_de_entrada> <archivo_de_salida> <modo de memorización de compresión: 'true' (Reutilización de tabla de compresión) | 'false' (No reutilización de la tabla de compresión)>
// ------------------------------------------


// Inlusión de librerias C
#include <stdio.h>

// Inlusión de herramientas utilizadas
#include "FileManager.h"
#include "Compressor.h"


// Función principal del proceso
// Parametros:
// - int   argc     -> Cantidad de parametros leidos en la terminal linux
// - char *argv[4]  -> Arreglo de 4 entradas ingresadas en la terminal Linux
// Retorno:
// - int
int main(int argc, char *argv[4]){

  // Verificamos la cantidad de archivos de entrada en la cmd linux
  if( argc == 4){
    const char *input_file_name;  // Cadena que almacena el nombre del archivo de entrada indicado desde la terminal Linux
    const char *output_file_name; // Cadena que almacena el nombre del archivo de salida indicado desde la terminal Linux
    const char *memorizationChar; // Cadena que almacena el modo de Memorización para la Compresión indicado desde la terminal Linux
    bool memorization;            // Booleano que indica el modo de Memorización para la Compresión

    // Asignación y casteo de las entradas indicadas desde la terminal Linux a las variables declaradas
    input_file_name  = (char*)argv[1];
    output_file_name = (char*)argv[2];
    memorizationChar = (char*)argv[3];

    // Validación del modo de Memorización para la Compresión
    if( strcmp(memorizationChar,"false") == 0 ){
      // Establecimiento de Compresión SIN Memorización 
      memorization = false;
    }else if( strcmp(memorizationChar,"true") == 0 ){
      // Establecimiento de Compresión CON Memorización 
      memorization = true;
    }else{
      // Argumento booleano ingresado incorrectamente -> Cortar ejecución
      printf(" Wrong argument[2]: \n");
      printf("  - Compressor Active Memorization: <'true' | 'false'> \n");
      exit(1);
    }
    
    // Construcción de Objeto de tipo Compresor asociado con un archivo de entrada y un archivo de salida
    Compressor *compressor = buildCompressor(input_file_name, output_file_name);

    // Ejecución de Compresión-LZW del archivo de entrada asociado con el objeto tipo Compressor
    LZWCompress(compressor, memorization);

    // Liberación de la memoria utilizada por el objeto tipo Compresor
    deleteCompressor(compressor);
    
  
  }else{
    // Cantidad de archivos de entrada en la cmd linux incorrecta
    // Información de uso para Compresor-LZW
    printf("=== LZW-Compressor Usage === \n");
    printf(" - gcc compile:                     gcc *.c -o <executable> \n");
    printf(" - to execut  :                     ./<executable> <input_file_pathName> <output_file_pathName> <'true' (Reutilización de tabla de compresión) | 'false' (No Reutilización de tabla de compresión)>\n");
    printf("Parameters:  \n");
    printf(" - <executable>           : executable file's name \n");
    printf(" - <input_file_pathName>  : input file name and path \n");
    printf(" - <output_file_pathName> : output file name and path \n\n");
    printf("=== Miguel Ángel Pérez Ávila === \n");
    printf(" GitHub: https://github.com/TGMAPA \n");
  }

  return 0;
}