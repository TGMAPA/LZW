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
// Archivo .c - Tools
// ------------------------------------------


// Archivo .h asociado
#include "Tools.h"

// Función que restablece una cadena de caracteres
void emptyStr(char *str) {
  // Itera la cadena restableciendo sus valores a fin de cadena lo que equivale a vacear el arreglo
  for (int i = 0; i < sizeof(str); i++) {
    str[i] = '\0';
  }
}

// Función que recibe un codigo[u_int16_t] y devuelve su expresión binaria[16bits]
void uint16_to_bin(u_int16_t *num, char *str){
  // Itera la cadena y asigna los valores correspondientes a la cadena binaria de acuerdo con el cociente de las divisiones entre 2 (Conversión básica decimal/binario)
  for (int i = 15; i >= 0; i--) {
    if (*num % 2 == 0) {
      str[i] = '0';
    } else if (*num % 2 == 1) {
      str[i] = '1';
    }
    *num = *num / 2; // Dividimos el número entre 2 para obtener el siguiente bit
  }
  str[16] = '\0'; // Terminamos la cadena con el carácter nulo de fin de cadena
}

// Función que ajusta una cadena de bits a un tamaño N_bits deseado
void fixtoNbits(char *str, char *finalstr, const int *n_bits){ // Ajustar arreglo de bits a N_Bits
  int auxIterator = 0;
  // Iterar la cadena desde el indice (16-12 para el ejemplo de cadena[BYTE] a cadena[N_BITS:12bits])) y almacenar los valores en una cadena nueva 
  for (int i = (strlen(str) - *n_bits); i < strlen(str); i++) {
    strcpy(&finalstr[auxIterator], &str[i]);
    auxIterator++;
  }
}

// Función que recibe una cadena[8] para devolver su equivalencia en un int[8bits]
u_int8_t binary2uint8( char *byte_str){
    u_int8_t uint8 = 0;

    // Recorrer la cadena binaria
    for (int i = 0; i < strlen(byte_str); i++) {
        // Multiplicar el valor acumulado por 2 (desplazando los bits a la izquierda implícitamente)
        uint8 *= 2;

        // Si el bit es '1', sumamos 1 al valor acumulado
        if (byte_str[i] == '1') {
            uint8 += 1;
        }
    }
    return uint8;
}