/**
 * @file funcAux.hpp
 * @brief Declaraciones de funciones y estructuras auxiliares para el algoritmo y el test.
 *
 * Este archivo contiene:
 * - La estructura Resultado, que almacena el índice de inicio y la suma máxima
 *   de diferencias obtenida en una ventana.
 * - La estructura TestCase, que se utiliza para almacenar los parámetros de un caso de prueba.
 * - Funciones auxiliares:
 *    - charToValue: Convierte un carácter en minúscula ('a-z') en su valor numérico (a=1, b=2, ...).
 *    - sumaVector: Suma los elementos de un vector en un rango dado.
 *    - generateRandomString: Genera una cadena aleatoria de longitud n.
 *    - parseTestCaseLine: Parsea una línea en formato "n=valor;m=valor" y extrae n y m.
 *
 * @author Eduardo Blázquez Verdejo
 * @date 27/03/2025
 */

 #ifndef AUXILIARES_HPP
 #define AUXILIARES_HPP
 
 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <vector>
 #include <string>
 #include <cstdlib>
 #include <algorithm>
 #include <climits>
 
 using namespace std;
 
 /**
  * @brief Estructura Resultado.
  *
  * Almacena el resultado de la ejecución del algoritmo, incluyendo:
  * - indice: Índice de inicio de la ventana en el vector de diferencias.
  * - sumaMax: Suma máxima de las diferencias en dicha ventana.
  */
 struct Resultado {
     int indice;
     int sumaMax;
 };
 
 /**
  * @brief Estructura TestCase.
  *
  * Almacena los parámetros de un caso de prueba.
  * - description: Descripción del caso (se puede generar a partir de n y m).
  * - n: Tamaño de la cadena a generar.
  * - m: Valor m, que indica la longitud de la subcadena a analizar.
  */
 struct TestCase {
     string description;
     int n;
     int m;
 };
 
 /**
  * @brief Convierte un carácter a su valor numérico.
  *
  * Se espera que el carácter c sea una letra minúscula (de 'a-z').
  *
  * @param c Carácter a convertir.
  * @return int Valor numérico correspondiente (a=1, b=2, ...).
  */
 int charToValue(char c);
 
 /**
  * @brief Suma los elementos de un vector en un rango.
  *
  * Suma los elementos del vector vec desde el índice start hasta end (excluyendo end).
  *
  * @param vec Vector de enteros.
  * @param start Índice de inicio.
  * @param end Índice final.
  * @return int Suma de los elementos en el rango [start, end).
  */
 int sumaVector(const vector<int>& vec, int start, int end);
 
 /**
  * @brief Genera una cadena aleatoria de longitud n.
  *
  * La cadena se compone de letras minúsculas.
  *
  * @param n Longitud de la cadena a generar.
  * @return string Cadena aleatoria generada.
  */
 string generateRandomString(int n);
 
 /**
  * @brief Parsea una línea de parámetros en formato "n=valor;m=valor".
  *
  * Extrae los valores numéricos para n y m a partir de la línea dada.
  *
  * @param line Cadena de entrada con el formato "n=valor;m=valor".
  * @param n Variable donde se almacenará el valor de n.
  * @param m Variable donde se almacenará el valor de m.
  * @return true Si se pudo parsear correctamente.
  * @return false Si ocurre algún error en el formato.
  */
 bool parseTestCaseLine(const string &line, int &n, int &m);
 
 #endif
 
