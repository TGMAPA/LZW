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
// Archivo .c - Bitstream
// ------------------------------------------


// Archivo .h asociado
#include "Bitstream.h"

// Método constructor que devuelve un objeto tipo bitstream asociado con un manipulador de archivos
Bitstream *buildBitstream(FileManager *filemanager_){
  // Rerserva de una cantidad sizeof(Bitstream) de memoria 
  Bitstream *bytemanager= malloc(sizeof(Bitstream));

  // Se asocia el objeto maniuplador de archivos recibido con el objeto bitstream
  bytemanager->filemanager= filemanager_;

  // Retorna un apuntador de tipo Bitstream
  return bytemanager;
}

// Método que afrega los bits contenidos en el buffer al inicio del bin_str_fixed 
void addBuffer(Bitstream *bitstream, char *str) {
  // Variable que almacena el tamaño del buffer 
  int buffersize = strlen(bitstream->buffer);

  if (buffersize < BYTE) {
    // En caso de que el buffer no este lleno, se desplaza la cadena original hacia la derecha para hacer espacio
    for (int i = strlen(str); i >= 0; i--) {
      str[i + buffersize] = str[i]; // Desplazamos los caracteres
    }
    // Una vez desplazados los caracteres, copiamos el bufferla en cadena de bits original (bin_str_fixed) 
    for (int i = 0; i < buffersize; i++) {
      str[i] = bitstream->buffer[i];
    }
  } else {
    // En caso de que el buffer este lleno, se activa la bandera isButterFull 
    bitstream->isBufferFull = true;
  }
}

// Método que separa el primer BYTE de la cadena bin_str_fixed y el resto lo almacena en el buffer
void getByte(Bitstream *bitstream, char *str) {
  for (int i = 0; i < strlen(str); i++) {
    if (i < BYTE) {
      // Sepración de Subcadena inicial de tamaño BYTE
      bitstream->writableByte[i] = str[i];
    } else {
      // Sepración de Subcadena restante almacenada en el buffer
      bitstream->buffer[i - BYTE] = str[i];
    }
  }
  // Escritura del ultimo caracter que indica fin de cadena
  bitstream->buffer[BYTE] = '\0';
}

// Método para volver las cadenas a su estado inicial para su posterior uso
void resetStrings(Bitstream *bitstream){
  emptyStr(bitstream->bin_str_fixed); // Restablecer cadena bin_str_fixed
  emptyStr(bitstream->writableByte);  // Restablecer cadena writableByte
  emptyStr(bitstream->bin_str);       // Restablecer cadena bin_str
}

// Método que revisa liber el buffer si finalizó lleno al terminar el proceso y lo escribe en el archivo
void bufferFinalCheck(Bitstream *bitstream){
  // Variable que contiene el tamaño actual del buffer
  int buffersize = strlen(bitstream->buffer);

  if(buffersize == BYTE){
    // Si el buffer esta lleno, se escribe el buffer en el archivo
    writeInFile(bitstream, bitstream->buffer);

    emptyStr(bitstream->buffer); // Restablecer el buffer
  }else if (buffersize < BYTE && buffersize != 0 ){
    // Si el buffer no esta vacío pero no contiene el tamaño de BYTE, se escribe el buffer en el archivo completando los bits vacios con bits apagados '0' y se escribe en el archivo
    for(int i=buffersize; i<BYTE; i++){
      bitstream->buffer[i] = '0';
    }
    // Escritura del byte del buffer resultante
    writeInFile(bitstream, bitstream->buffer); 

    emptyStr(bitstream->buffer); // Restablecer el buffer
  }
}

// Método principal que recibe un codigo[u_int16_t] y lo procesa para escribirlo finalmente en el archivo
void bitstream(Bitstream *bitstream, u_int16_t *code) {

  // Se inicializa la bandera isButterFull en false
  bitstream->isBufferFull = false;
  
  // Se inicializa la cadena bin_str[16] con el codigo[u_int16_t]
  uint16_to_bin(code, bitstream->bin_str);
  
  // Se inicializa la subcadena bin_str_fixed a partir de la cadena original bin_str[16] 
  fixtoNbits(bitstream->bin_str, bitstream->bin_str_fixed, &N_BITS);
  //printf(" Cadena[12]         : %s\n", bitstream->bin_str_fixed);

  // Se agrega el buffer existente al inicio de la cadena bin_str_fixed
  addBuffer(bitstream, bitstream->bin_str_fixed);

  // Revisar estado de Buffer
  if(bitstream->isBufferFull){
    // En caso de que el buffer este lleno, se escribe el buffer en el archivo antes de procesar el codigo actual
    writeInFile(bitstream, bitstream->buffer);

    // Se restablece el buffer y se apaga la bandera isBufferFull
    emptyStr(bitstream->buffer);
    bitstream->isBufferFull = false;
  }

  // Se procesa la cadena bin_str_fixed para obtener la el wrtiableByte y actualizar el buffer
  getByte(bitstream, bitstream->bin_str_fixed);

  // Se escribe el codigo[BYTE] almacenado en writableByte en el archivo
  writeInFile(bitstream, bitstream->writableByte);
  
  // Se restablecen las cadenas
  resetStrings(bitstream);
}

// Método que recibe un string procesado y lo escribe en el archivo de salida
void writeInFile(Bitstream *bitstream, char *str2write){
  // variable que almacena el valor entero de tamaño BYTE traducido de la cadena binaria recibida
  u_int8_t writablestr = binary2uint8(str2write);

  // Variable que almacena el valor entero de tamaño BYTE expresado como un caracter tamaño BYTE que se escribe en el archivo
  char aux = (char)writablestr;
  
  // EScritura de byte procesado
  write(bitstream->filemanager, &aux);
}

//Método que libera la memoria utilizada por un objeto tipo Bitstream
void deleteBitstream(Bitstream *bitstream){
  free(bitstream);
}