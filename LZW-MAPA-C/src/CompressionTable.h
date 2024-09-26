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
// Archivo .h - CompressionTable
// ------------------------------------------


// Inclusión de librerias C
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _COMPRESSIONTABLE_H
#define _COMPRESSIONTABLE_H

// Definición del tamaño de diccionario reservado para los alfabetos del arbol trie implementado
#define alphabetSize 256

// Estructura que almacena el diccionario/tabla de compresión generado con elementos (codigo : patron)
typedef struct CompressionTable CompressionTable;
struct CompressionTable {

  // Codigo asignado al patron actual entre 0-4096
  u_int16_t code;

  // Arreglo (alfabeto) que contiene 256 espacios para los patrones UNICODE / ASCII
  CompressionTable **alphabet;
};

// Método Constructor del nodo raiz de la tabla de compresión
// Parametros:
// - na
// Retorno:
// - *CompressionTable
CompressionTable *initializer();

// Método Constructor de un nodo para la tabla de compresión
// Parametros:
// - na
// Retorno:
// - *CompressionTable
CompressionTable *createTableNode();

// Método que elimina los nodos de la tabla de compresión y reinicializa el nodo Raiz de la tabla
// Parametros:
// - CompressionTable *tableNode -> Nodo Raíz de la tabla de Compresión a quien se regresara a su estado inicial
// Retorno:
// - void
void restartTable(CompressionTable *tableNode);

// Método que elimina recursivamente todas las ramas del árbol desde un nodo del mismo
// Parametros:
// - CompressionTable *tableNode -> Nodo de la tabla de Compresión a quien se regresara a su estado inicial
// Retorno:
// - void
void deleteTableNode(CompressionTable *tableNode);

// Método para añadir un Nuevo Nodo en el alfabeto de un Nodo de la tabla de compresión en específico
// Parametros:
// - CompressionTable *node -> Nodo de la tabla de compresión al cual se le añadira un nuevo Nodo-código en su alfabeto.
// - u_int8_t indx          -> Indice del alfabeto del Nodo indicado en donde se posicionará el nuevo Nodo-código añadido
// - u_int16_t newcode      -> Código que le sera asignado al Nuevo Nodo 
// Retorno:
// - void
void addNode(CompressionTable *node, u_int8_t indx, u_int16_t newcode);

// Método para buscar y devolver una referencia al Nodo buscado en caso de ser encontrado
// Parametros:
// - CompressionTable *node -> Nodo de la tabla de compresión en donde el nodo buscado (indicado por el indice) debería ser encontrado dentro del alfabeto del Nodo principal.
// - u_int8_t indx          -> Posición del arreglo en el alfabeto del Nodo principal donde el Nodo buscado debería encontrarse.
// - CompressionTable &node -> Referencia al nodo buscado.
// Retorno:
// - bool
bool searchNode(CompressionTable *node, u_int8_t indx, CompressionTable **nodeToSearch);

// Método que devuelve el código 0 - 4095 del nodo indicado
// Parametros:
// - CompressionTable *node -> Nodo de la tabla de compresión del cual se obtendra su código de diccionario 0 - 4095
// Retorno:
// - u_int16_t
u_int16_t getCode(CompressionTable *node);

#endif // COMPRESSIONTABLE_H