/**
 * @file funcAux.cpp
 * @brief Implementación de funciones auxiliares para el proyecto.
 *
 * Este archivo implementa las funciones declaradas en funcAux.hpp:
 * - charToValue: convierte un carácter en su valor numérico.
 * - sumaVector: suma elementos de un vector en un rango dado.
 * - generateRandomString: genera una cadena aleatoria de longitud n.
 * - parseTestCaseLine: parsea una línea con formato "n=valor;m=valor".
 *
 * @author Eduardo Blázquez Verdejo
 * @date 27/03/2025
 */

 #include "funcAux.hpp"
 #include <fstream>
 #include <sstream>
 #include <iostream>
 #include <algorithm>
 #include <cctype>
 
 using namespace std;
 
 int charToValue(char c) {
     return c - 'a' + 1;
 }
 
 int sumaVector(const vector<int>& vec, int start, int end) {
     int sum = 0;
     for (int i = start; i < end; i++) {
         sum += vec[i];
     }
     return sum;
 }
 
 bool parseTestCaseLine(const string &line, int &n, int &m) {
     size_t pos_n = line.find("n=");
     size_t pos_m = line.find("m=");
     if (pos_n == string::npos || pos_m == string::npos)
         return false;
     size_t pos_sep = line.find(";", pos_n);
     if (pos_sep == string::npos)
         return false;
     
     string n_str = line.substr(pos_n + 2, pos_sep - (pos_n + 2));
     string m_str = line.substr(pos_m + 2);
     try {
         n = stoi(n_str);
         m = stoi(m_str);
     } catch (...) {
         return false;
     }
     return true;
 }
 
 string generateRandomString(int n) {
     static const string letters = "abcdefghijklmnopqrstuvwxyz";
     string result(n, ' ');
     for (int i = 0; i < n; i++) {
         result[i] = letters[rand() % letters.size()];
     }
     return result;
 }
 
