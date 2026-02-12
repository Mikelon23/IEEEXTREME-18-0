/**
 * SOLUCIÓN: One Letter
 * LENGUAJE: C++
 * * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. Se nos dan N palabras.
 * 2. De cada palabra debemos elegir exactamente UNA letra.
 * 3. Con esas N letras elegidas (una por palabra), debemos formar la palabra 
 * más pequeña posible lexicográficamente (orden de diccionario).
 * * ESTRATEGIA:
 * - Para que una palabra sea la menor posible en orden lexicográfico, sus letras 
 * deben estar ordenadas de la 'a' a la 'z'.
 * - Para que la palabra resultante sea la mínima, la elección de la letra de cada 
 * palabra individual también debe ser la mínima posible de esa palabra.
 * - Por lo tanto, el algoritmo consiste en:
 * a) Para cada palabra, encontrar su letra más pequeña (ej. de "stop" es 'o').
 * b) Guardar todas estas letras mínimas en una lista o contenedor.
 * c) Ordenar esa lista de letras de forma ascendente.
 * d) Concatenar y mostrar el resultado.
 * * COMPLEJIDAD:
 * - Sea S la suma de las longitudes de todas las cadenas (S <= 10^5).
 * - Encontrar el mínimo de cada cadena toma O(S).
 * - Ordenar las N letras resultantes toma O(N log N).
 * - Dado que N <= 10^5, esta solución es muy eficiente para el límite de 1000ms.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Para std::sort y std::min_element

using namespace std;

int main() {
    // Optimización de I/O para procesar grandes volúmenes de datos rápidamente.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    // Usaremos un vector de caracteres para almacenar la mejor letra de cada palabra.
    vector<char> chosenLetters;
    chosenLetters.reserve(N); // Reservamos memoria para evitar realocaciones.

    for (int i = 0; i < N; ++i) {
        string word;
        cin >> word;

        /**
         * Lógica de selección:
         * De la palabra actual, la mejor letra que podemos aportar al resultado 
         * final es su carácter más pequeño. 
         * Ejemplo: "cross" -> 'c', "stop" -> 'o', "arm" -> 'a'.
         */
        char minChar = word[0];
        for (char c : word) {
            if (c < minChar) {
                minChar = c;
            }
        }
        
        chosenLetters.push_back(minChar);
    }

    /**
     * Lógica de ordenamiento:
     * Una vez que tenemos las mejores letras (ej. 'c', 'o', 'a'), para obtener 
     * el string lexicográficamente menor, simplemente las ordenamos.
     * Ejemplo: {'c', 'o', 'a'} -> ordena a {'a', 'c', 'o'} -> "aco".
     */
    sort(chosenLetters.begin(), chosenLetters.end());

    // Construcción de la cadena resultante.
    for (char c : chosenLetters) {
        cout << c;
    }
    cout << endl;

    return 0;
}