/**
 * @file algoritmo.cpp
 * @brief Implementación del algoritmo para encontrar la subcadena con la mayor suma de diferencias.
 *
 * Este archivo implementa las funciones declaradas en algoritmo.hpp:
 * - MaxVentana: Función recursiva que divide el vector de diferencias y combina los resultados.
 * - MaxDiferenciaDyV: Construye el vector de diferencias a partir de la cadena A y utiliza MaxVentana.
 * - MaxDiferenciaDirecto: Método directo que recorre todas las subcadenas para encontrar la solución.
 *
 * @author Eduardo Blázquez Verdejo
 * @date 28/03/2025
 */

 #include "algoritmo.hpp"
 #include <iostream>
 #include <vector>
 #include <cstdlib>
 #include <algorithm>
 #include <climits>
 
 using namespace std;
 
 Resultado MaxVentana(const vector<int>& D, int d, int offset) {
     int n = D.size();
     // Caso base: si no hay suficientes elementos para formar la ventana
     if (n < d) {
         return { -1, INT_MIN };
     }
     // Caso base: sólo existe una ventana (tamaño de D es igual a d)
     if (n == d) {
         int total = sumaVector(D, 0, d);
         return { offset, total };
     }
     
     // Dividir el vector D en dos mitades
     int mid = n / 2;
     vector<int> D_left(D.begin(), D.begin() + mid);
     vector<int> D_right(D.begin() + mid, D.end());
     
     // Resolver recursivamente en cada mitad
     Resultado ResultadoL = MaxVentana(D_left, d, offset);
     Resultado ResultadoR = MaxVentana(D_right, d, offset + mid);
     
     //Evaluar la ventana que cruza la frontera entre las dos mitades.
     int mejorCruzado = INT_MIN;
     int mejorK = 0;
     int startK = max(1, d - (int)D_right.size());
     int endK = min(d, (int)D_left.size());
     
     for (int k = startK; k <= endK; k++) {
         // Sumar los últimos k elementos de D_left
         int sumaCL = sumaVector(D_left, D_left.size() - k, D_left.size());
         // Sumar los primeros (d - k) elementos de D_right
         int sumaCR = sumaVector(D_right, 0, d - k);
         int sumaTotal = sumaCL + sumaCR;
         if (sumaTotal > mejorCruzado) {
             mejorCruzado = sumaTotal;
             mejorK = k;
         }
     }
     
     // Calcular el índice de inicio de la ventana combinada.
     int indiceC = offset + (D_left.size() - mejorK);
     
     // Seleccionar la mejor solución entre las dos mitades y la combinada.
     if (mejorCruzado >= ResultadoL.sumaMax && mejorCruzado >= ResultadoR.sumaMax)
         return { indiceC, mejorCruzado };
     else if (ResultadoL.sumaMax >= ResultadoR.sumaMax)
         return ResultadoL;
     else
         return ResultadoR;
 }
 
 Resultado MaxDiferenciaDyV(const string &A, int m) {
     int n = A.size();
     vector<int> D(n - 1);
     // Construir el vector D con las diferencias absolutas entre caracteres consecutivos.
     for (int i = 0; i < n - 1; i++) {
         D[i] = abs(charToValue(A[i+1]) - charToValue(A[i]));
     }
     
     int d = m - 1;
     return MaxVentana(D, d, 0);
 }
 
 Resultado MaxDiferenciaDirecto(const string &A, int m) {
     int n = A.size();
     vector<int> D(n - 1);
     if(m > n) return { -1, INT_MIN };
 
     int mejorSuma = INT_MIN;
     int mejorPos = 0;
     
     // Construir el vector D
     for (int i = 0; i < n - 1; i++) {
         D[i] = abs(charToValue(A[i+1]) - charToValue(A[i]));
     }
     
     // Recorrer todas las subcadenas de longitud m para encontrar la máxima suma.
     for (int i = 0; i <= n - m; i++) {
         int sumaAct = 0;
         for (int j = i; j < i + m - 1; j++) {
             sumaAct += abs(charToValue(A[j+1]) - charToValue(A[j]));
         }
         if(sumaAct > mejorSuma) {
             mejorSuma = sumaAct;
             mejorPos = i;
         }
     }
     return { mejorPos, mejorSuma };
 }
 

