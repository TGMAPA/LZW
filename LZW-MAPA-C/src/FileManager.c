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
// Archivo .c - FileManager
// ------------------------------------------


// Archivo .h asociado
#include "FileManager.h"

// Método que construye un Objeto tipo FileManger
FileManager *createFileManager(const char *input_file_name_, const char *output_file_name_) {
  // Rerserva de una cantidad sizeof(FileManager) de memoria 
  FileManager *filemanager = malloc(sizeof(FileManager));

  // Se intenta abrir el archivo de entrada con la ruta y nombre especificados en modo lectura
  FILE *input_file_ = fopen(input_file_name_, "rb");
  
  // Verificación de una correcta apertura del archivo de entrada
  if (!input_file_) {
    // Archivo de entrada inaccesible -> Cortar ejecución
    printf("Failed opening input file.\n");
    exit(1);

  } else if (!feof(input_file_)) {
    // Generación de archivo de salida con el nombre especificado
    FILE *output_file_ = fopen(output_file_name_, "wb");

    // Verificación de una correcta generación del archivo de salida
    if (!output_file_) {
      // Archivo de salida inaccesible -> Cortar ejecución
      fclose(input_file_); // Cerrar archivo de entrada
      printf("Failed opening output file.\n");
      exit(1);
    }

    // Declaración de cadena que almacenara la extension del archivo
    const char *extension;

    // Extracción de la extensión del archivo de entrada
    extension = strrchr(input_file_name_, '.');

    // Asociar la extensión encontrada con el manipulador de archivos
    filemanager->ext = strchr(extension, '.');
    
    // Asociar el nombre del archivo de entrada con el manipulador de archivos
    filemanager->input_file_name = input_file_name_;

    // Asociar el nombre del archivo de salida con el manipulador de archivos
    filemanager->output_file_name = output_file_name_;

    // Cierre de archivos abiertos
    fclose(input_file_);
    fclose(output_file_);

    // Retorno de objeto tipo FileManager
    return filemanager;

  }else if(feof(input_file_)){
    // Archivo de entrada vacío -> Cortar ejecución
    printf("Input File is empty...\n");
    exit(1);
  }
}

// Método que libera la memoria utilizada por un objeto tipo FileManager y sus archivos
void deleteFileManager(FileManager *fileManager){
  free(fileManager);
}

// Método utilizado para escribir un caracter en el archivo de salida asociado con un manipulador de archivos
void write(FileManager *fileManager, char *char2write){
  // Escritura del caracter especificado en el archivo de salida
  fwrite(char2write, sizeof(char), 1, fileManager->output_file);
}

// Método utilizado para la apertura del archivo de entrada en modo lectura asociado con un manipulador de archivos
void openInputFile(FileManager *fileManager){
  // Construcción de objeto FILE con el archivo de entrada abierto en modo lectura
  FILE *input = fopen(fileManager->input_file_name, "rb");

  //Asociación del objeto FILE creado con el manipulador de archivos para su utilización
  fileManager->input_file = input;
}

// Método utilizado para cerrar el archivo de entrada asociado con un manipulador de archivos después de su utilización
void closeInputFile(FileManager *fileManager){
  fclose(fileManager->input_file);
}

// Método utilizado para la apertura del archivo de salida en modo de escritura asociado con un manipulador de archivos
void openOutputFile(FileManager *fileManager){
  // Construcción de objeto FILE con el archivo de salida abierto en modo de escritura binaria
  FILE *output = fopen(fileManager->output_file_name, "wb");

  //Asociación del objeto FILE creado con el manipulador de archivos para su utilización
  fileManager->output_file = output;
}

// Método utilizado para cerrar el archivo de salida asociado con un manipulador de archivos después de su utilización
void closeOutputFile(FileManager *fileManager){
  fclose(fileManager->output_file);
}