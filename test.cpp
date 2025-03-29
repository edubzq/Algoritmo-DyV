/**
 * @file test.cpp
 * @brief Programa principal para generar casos de prueba, ejecutar los algoritmos
 *        (DyV y Directo) y registrar resultados, tiempos y uso de memoria.
 *
 * Este programa:
 * - Lee un archivo de parámetros con líneas en el formato:
 *       n=10000;m=20
 *       n=1000000;m=500
 * - Por cada línea, genera un caso de prueba:
 *       A = <cadena generada>
 *       m = <entero>
 * - Ejecuta ambos métodos:
 *       - MaxDiferenciaDyV (método Divide y Vencerás)
 *       - MaxDiferenciaDirecto (método Directo)
 * - Mide los tiempos de ejecución y el uso de memoria (usando mem_total).
 * - Registra todos los resultados en un archivo "log.txt".
 * 
 * @author Eduardo Blázquez Verdejo
 * @date 28/03/2025
 */

 #include <iostream>
 #include <fstream>
 #include <sstream>
 #include <string>
 #include <vector>
 #include <random>
 #include <chrono>
 #include <cstdlib>
 #include <algorithm>
 #include "algoritmo.hpp"
 #include "memcount.hpp"
 #include "funcAux.hpp"
 
 using namespace std;
 
 string generarNombreLog() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[100];
    strftime(buffer, sizeof(buffer), "log_%m%d_%H%M.txt", ltm);
    return string(buffer);
}
 
 int main(int argc, char* argv[]) {
     if (argc < 2) {
         cerr << "Uso: " << argv[0] << " <archivo_parametros.txt>" << endl;
         return 1;
     }
     srand(1234); // Inicializar la semilla para la generación de números aleatorios
     // Leer el archivo de parámetros (cada línea: "n=valor;m=valor")
     ifstream paramFile(argv[1]);
     if (!paramFile.is_open()) {
         cerr << "Error: No se pudo abrir el archivo de parámetros." << endl;
         return 1;
     }
     
     // Alacenamos los casos de prueba en un vector
     vector<TestCase> testCases;
     string line;
     while(getline(paramFile, line)) {
         if (line.empty())
             continue;
         int n, m;
         if (parseTestCaseLine(line, n, m)) {
             TestCase tc;
             tc.n = n;
             tc.m = m;
             tc.description = " ";
             testCases.push_back(tc);
         } else {
             cerr << "Error al parsear la línea: " << line << endl;
         }
     }
     paramFile.close();
     
     // Abrir el archivo log.txt para registrar los resultados
     string nameLog = generarNombreLog();
     ofstream logFile(nameLog, ios::app);
     if (!logFile.is_open()) {
         cerr << "Error: No se pudo abrir log.txt para escritura." << endl;
         return 1;
     }
     
    logFile << "-------------------------------------\n";
    logFile << "Inicio de ejecución de casos de prueba:\n";
     
    const int REPETICIONES = 10;  // Número de veces que se ejecuta cada caso para promediar
    int caseNumber = 1;
    
    for (const auto &tc : testCases) {
        logFile << "-------------------------------------\n";
        logFile << "Caso " << caseNumber << ": " << tc.description << "\n";
        logFile << "n = " << tc.n << ", m = " << tc.m << "\n";
        
        // Variables para acumular tiempos y memoria para cada método
        long long totalTimeDyV = 0, totalTimeDirect = 0;
        long long totalMemDyV = 0, totalMemDirect = 0;
        long long totalDataDyV = 0, totalDataDirect = 0;
        long long totalStackDyV = 0, totalStackDirect = 0;
        
        for (int rep = 0; rep < REPETICIONES; rep++) {
            // Generar cadena aleatoria A de longitud n
            string A = generateRandomString(tc.n);
            // Ejecutar método DyV
            auto startDyV = chrono::steady_clock::now();
            Resultado resDyV = MaxDiferenciaDyV(A, tc.m);
            auto endDyV = chrono::steady_clock::now();
            auto timeDyV = chrono::duration_cast<chrono::milliseconds>(endDyV - startDyV).count();
            int dataDyV, stackDyV;
            int memDyV = mem_total(dataDyV, stackDyV);
            
            totalTimeDyV += timeDyV;
            totalMemDyV += memDyV;
            totalDataDyV += dataDyV;
            totalStackDyV += stackDyV;
            
            // Ejecutar método Directo
            auto startDirect = chrono::steady_clock::now();
            Resultado resDirect = MaxDiferenciaDirecto(A, tc.m);
            auto endDirect = chrono::steady_clock::now();
            auto timeDirect = chrono::duration_cast<chrono::milliseconds>(endDirect - startDirect).count();
            int dataDirect, stackDirect;
            int memDirect = mem_total(dataDirect, stackDirect);
            
            totalTimeDirect += timeDirect;
            totalMemDirect += memDirect;
            totalDataDirect += dataDirect;
            totalStackDirect += stackDirect;
        }
        
        // Calcular promedios
        long long avgTimeDyV = totalTimeDyV / REPETICIONES;
        long long avgTimeDirect = totalTimeDirect / REPETICIONES;
        long long avgMemDyV = totalMemDyV / REPETICIONES;
        long long avgMemDirect = totalMemDirect / REPETICIONES;
        long long avgDataDyV = totalDataDyV / REPETICIONES;
        long long avgStackDyV = totalStackDyV / REPETICIONES;
        long long avgDataDirect = totalDataDirect / REPETICIONES;
        long long avgStackDirect = totalStackDirect / REPETICIONES;
        
        logFile << "Promedio Método DyV: Tiempo = " << avgTimeDyV << " ms, Memoria = " << avgMemDyV << " KB (Datos: " 
                << avgDataDyV << " KB, Pila: " << avgStackDyV << " KB)\n";
        logFile << "Promedio Método Directo: Tiempo = " << avgTimeDirect << " ms, Memoria = " << avgMemDirect 
                << " KB (Datos: " << avgDataDirect << " KB, Pila: " << avgStackDirect << " KB)\n";
        
        caseNumber++;
    }
    
    logFile << "Fin de ejecución de casos de prueba.\n";
    logFile << "-------------------------------------\n";
    logFile.close();
    
    cout << "Ejecución completada. Revisa log.txt para ver los resultados." << endl;
    return 0;
}
 
