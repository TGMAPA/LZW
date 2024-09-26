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
// Archivo .c - CompressionTable
// ------------------------------------------


// Archivo .h asociado
#include "CompressionTable.h"

// Método Constructor del nodo raiz de la tabla de compresión
CompressionTable *initializer() {
  // Rerserva de una cantidad sizeof(CompressionTable) de memoria 
  CompressionTable *primaryNode = malloc(sizeof(CompressionTable));

  // Reserva de memoria para el arreglo[alphabetsize] con malloc
  primaryNode->alphabet = (CompressionTable **)malloc(alphabetSize * sizeof(CompressionTable *));

  // Asignación de codigos y caracteres pora cada alphabet[i] del Nodo raiz
  for (unsigned int i = 0; i < alphabetSize; i++) {
    primaryNode->alphabet[i] = NULL;
    // Adición de un nuevo nodo de modo que primaryNode's alphabet[i] = codigo=int(i)
    addNode(primaryNode, i, i);
  }
  return primaryNode;
}

// Método Constructor de un nodo para la tabla de compresión
CompressionTable *createTableNode() {
  // Rerserva de una cantidad sizeof(CompressionTable) de memoria 
  CompressionTable *newNode = malloc(sizeof(CompressionTable));

  // Reserva de memoria para el arreglo[alphabetsize] con malloc
  newNode->alphabet = (CompressionTable **)malloc(alphabetSize * sizeof(CompressionTable *));

  // Asignación NUlA de modo que  Node's alphabet[i] = null
  for (unsigned int i = 0; i < alphabetSize; i++) {
    newNode->alphabet[i] = NULL;
  }
  return newNode;
}

// Método que elimina los nodos de la tabla de compresión y reinicializa el nodo Raiz de la tabla
void restartTable(CompressionTable *tableNode){
  for (uint i = 0; i < alphabetSize; i++) {
    if (tableNode->alphabet[i] != NULL) {
      // Para cada Nodo válido en el alfabeto del Nodo Raiz se elimina recursivamente todas las ramas del árbol
      // y se libera la memoria utilizada.
      deleteTableNode(tableNode->alphabet[i]);

      // Reinicialización del alfabeto del Nodo Raíz
      tableNode->alphabet[i] = NULL;
      addNode(tableNode, i, i);
    }
  }
}

// Método que elimina recursivamente todas las ramas del árbol desde un nodo del mismo
void deleteTableNode(CompressionTable *tableNode) {
  for (uint i = 0; i < alphabetSize; i++) {
    if (tableNode->alphabet[i] != NULL) {
      // Para cada Nodo válido en el alfabeto del Nodo indicado se elimina recursivamente todas las ramas del árbol
      // y se libera la memoria utilizada.
      deleteTableNode(tableNode->alphabet[i]);
    }
  }
  // Liberación de memoria utilizada por el alfabeto del nodo eliminado y por la tabla de compresión
  free(tableNode->alphabet);
  free(tableNode);
}

// Método para añadir un Nuevo Nodo en el alfabeto de un Nodo de la tabla de compresión en específico
void addNode(CompressionTable *node, u_int8_t indx, u_int16_t newcode) {
  if (node->alphabet[indx] == NULL) {
    // Asignación de un nuevo Nodo a la lista del Nodo indicado en su posición alphabet[indx]
    node->alphabet[indx] = createTableNode();

    // Asignación de del código newcode [char(indx)] al nuevo Nodo añadido
    node->alphabet[indx]->code = newcode;
  }
}

// Método para buscar y devolver una referencia al Nodo buscado en caso de ser encontrado
bool searchNode(CompressionTable *node, u_int8_t indx,  CompressionTable **nodeToSearch) {
  // Nodo existente en el arreglo del Nodo indicado que se encuentra en la posición alphabet[indx]
  if (node->alphabet[indx] != NULL) {
    // Asignación al nodo recibido con la referencia al nodo encontrado para su devolución
    *nodeToSearch = node->alphabet[indx];
    return true;
  }
  return false;
}

// Método que devuelve el código 0 - 4095 del nodo indicado
u_int16_t getCode(CompressionTable *node) {
  return node->code;
}