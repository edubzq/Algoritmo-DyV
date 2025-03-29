/**
 * @file algoritmo.hpp
 * @brief Declaración de funciones principales del algoritmo de DyV y por resolución directa.
 *
 * Este archivo declara las funciones que implementan el algoritmo para encontrar
 * la subcadena con la mayor suma de diferencias en una cadena:
 * - MaxVentana: función recursiva que, dado un vector de diferencias, encuentra la
 *   ventana de longitud d con la suma máxima.
 * - MaxDiferenciaDyV: utiliza MaxVentana para procesar la cadena y obtener el resultado
 *   mediante DyV.
 * - MaxDiferenciaDirecto: implementa un método directo que recorre todas las
 *   subcadenas de longitud m para encontrar la que tiene la suma máxima de diferencias.
 * @author Eduardo Blázquez Verdejo
 * @date 28/03/2025
 */

 #ifndef ALGORITMO_HPP
 #define ALGORITMO_HPP
 
 #include <vector>
 #include <string>
 #include "funcAux.hpp"
 
 using namespace std;
 /**
  * @brief Encuentra la ventana con la suma máxima de diferencias mediante DyV.
  *
  * @param D Vector de diferencias.
  * @param d Longitud de la ventana (d = m - 1).
  * @param offset Posición base para ajustar el índice en el vector original.
  * @return Resultado que contiene el índice de inicio y la suma máxima encontrada.
  */
 Resultado MaxVentana(const vector<int>& D, int d, int offset);
 
 /**
  * @brief Calcula la subcadena óptima usando el método de DyV.
  *
  * Construye el vector de diferencias a partir de la cadena A y llama a MaxVentana.
  *
  * @param A Cadena de entrada.
  * @param m Longitud de la subcadena a buscar.
  * @return Resultado que contiene el índice de inicio y la suma máxima.
  */
 Resultado MaxDiferenciaDyV(const string &A, int m);
 
 /**
  * @brief Calcula la subcadena óptima usando un método directo.
  *
  * Recorre todas las subcadenas de longitud m para determinar la que tiene la suma máxima
  * de diferencias entre caracteres consecutivos.
  *
  * @param A Cadena de entrada.
  * @param m Longitud de la subcadena a buscar.
  * @return Resultado que contiene el índice de inicio y la suma máxima.
  */
 Resultado MaxDiferenciaDirecto(const string &A, int m);
 
 #endif
 
