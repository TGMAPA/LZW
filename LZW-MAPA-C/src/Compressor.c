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
// Archivo .c - Compressor
// ------------------------------------------


// Archivo .h asociado
#include "Compressor.h"

#define DICTSIZE 4096 // 2**12

// Método que construye un Objeto tipo Compressor
Compressor *buildCompressor(const char *input_file_name, const char *output_file_name){
	// Rerserva de una cantidad sizeof(Compressor) de memoria 
	Compressor *compressor = malloc(sizeof(Compressor));

	// Construcción de objeto manipulador del archivo de entrada y de salida indicados
	FileManager *filemanager_ = createFileManager(input_file_name, output_file_name);

	// Asociar el manipulador de archivos con el objeto tipo Compressor
	compressor->filemanager= filemanager_;
	
	// Retrono de un apuntador de tipo Compressor
	return compressor;
}

// Método que libera la memoria utilizada por un objeto tipo Compressor y su manipulador de archivos
void deleteCompressor(Compressor *compressor){
	deleteFileManager(compressor->filemanager);
	free(compressor);
}

// Método que implementa una compresión de archivos LZW
void LZWCompress(Compressor *compressor, bool memorizable){

	//Abrir archivos de entrada y salida para asegurar lectura y escritura de los mismos
	openInputFile(compressor->filemanager);
	openOutputFile(compressor->filemanager);

	// Variable apuntadora auxiliar para acceder al objeto FILE que apunta al archivo de entrada abierto
	FILE *input_file = compressor->filemanager->input_file;

	// Obtener el primer byte (caracter) del archivo de entrada
	unsigned char c = fgetc(input_file);

	// Variable de control que almacena el código actual del diccionario
	u_int16_t current_code = 256;

	// Construcción de objeto tipo CompressionTable, inicializando un nodo raiz
	CompressionTable *tree = initializer();

	// Declaración de nodo para el diccionario/tabla de compresión
	CompressionTable *p;

	// Busqueda inicial del caracter P dentro del alfabeto del Nodo raiz del arbol
	bool char_found = searchNode(tree, (unsigned int)c, &p);

	// Construcción de objeto manipulador de bytes que se utilizara para la escritura de los codigos del diccionario en el archivo de salida
	Bitstream *bytemanager = buildBitstream(compressor->filemanager);

	// === LZW 
	// Ciclo de lectura hasta encontrar el End of File del archivo de entrada
	while (!feof(input_file)) {
		// Caracter de entrada SIGUIENTE
		c = fgetc(input_file); 

		// Creación de nodo con patron P + C para el diccionario/tabla de compresión
		CompressionTable *p_plus_c;

		if (searchNode(p, (unsigned int)c, &p_plus_c) == true){
			// Si P + C esten en el diccionario/tabla de compresión:  P = P + C
		 	p = p_plus_c; 

		} else {
			if(current_code < DICTSIZE && memorizable){
				// Insertar Nodo P + C al diccionario/tabla de compresión
				addNode(p, (unsigned int)c, current_code++); 
			}
			
			// Se obtiene el codigo del diccionario asociado con P
			u_int16_t actualCode = getCode(p);

			// Si el diccionario excede los 2**12 codigos se detiene la inclusión de patrones en el diccionario/tabla de compresión
			if(current_code >= DICTSIZE && memorizable){
				// Reiniciar tabla de compresión
				restartTable(tree);

				// Restablecer el codigo actual del diccionario 
				current_code = 256;
			}

			// Se envía el codigo asociado con P a escritura con manipulador de bits
			bitstream(bytemanager, &actualCode);
			  
			// Se asigna P = C (siguiente caracter)
			bool char_found = searchNode(tree, (unsigned int)c, &p);
		}
	}

	// Se realiza una última inspección del buffer de bits para escribir en caso de existir bits sobrantes
	bufferFinalCheck(bytemanager);

	// Cerrrar archivo de entrada y de salida
	closeInputFile(compressor->filemanager);
	closeOutputFile(compressor->filemanager);

	// Se libera la memoria utilizada por el manipulador de bits
	deleteBitstream(bytemanager);
}