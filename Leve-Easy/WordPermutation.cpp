/**
 * SOLUCIÓN: Word Permutation
 * LENGUAJE: C++
 * * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. Alex tiene N palabras distintas que inicialmente están ordenadas lexicográficamente.
 * 2. Se aplica una permutación σ: la palabra que estaba en la posición i (original) 
 * ahora se encuentra en la posición σ(i) en la lista resultante.
 * 3. Nuestra tarea es encontrar qué posición original tenía cada palabra de la lista 
 * que nos entregan.
 * * ESTRATEGIA:
 * - Necesitamos saber el orden alfabético original de las palabras que recibimos.
 * - Para ello, almacenamos cada palabra junto con su "índice de entrada" (su posición 
 * actual en la lista que nos dan, de 1 a N).
 * - Ordenamos esta lista de pares (palabra, índice_actual) alfabéticamente.
 * - Al ordenar alfabéticamente, la palabra que quede en la primera posición de la 
 * lista ordenada será la que originalmente estaba en la posición 1.
 * - El índice de entrada de esa palabra nos dirá en qué posición σ(1) terminó.
 * * COMPLEJIDAD:
 * - Lectura y almacenamiento: O(S), donde S es la suma de longitudes de las palabras.
 * - Ordenamiento: O(S log N) en el peor de los casos (comparando strings).
 * - Espacio: O(S) para almacenar las palabras.
 * - Dados los límites (N y S <= 10^5), esta solución es óptima.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Estructura para mantener la palabra y su posición en la entrada (1-based)
struct WordEntry {
    string text;
    int inputIndex;
};

/**
 * Función de comparación para ordenar alfabéticamente.
 * Si las palabras son iguales (aunque el problema dice que son distintas),
 * mantenemos la estabilidad con el índice.
 */
bool compareWords(const WordEntry& a, const WordEntry& b) {
    return a.text < b.text;
}

int main() {
    // Optimización de entrada/salida para manejar grandes volúmenes de texto
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    // Guardaremos las palabras tal como vienen en la entrada
    vector<WordEntry> words(N);
    for (int i = 0; i < N; ++i) {
        cin >> words[i].text;
        words[i].inputIndex = i + 1; // Guardamos su posición actual (1 a N)
    }

    /**
     * PASO CLAVE:
     * Al ordenar alfabéticamente, reconstruimos el "orden inicial" que Alex tenía.
     * La palabra en la posición 'i' del vector ordenado es la i-ésima palabra
     * lexicográfica. Su 'inputIndex' es el valor σ(i) que buscamos.
     */
    sort(words.begin(), words.end(), compareWords);

    // La salida debe ser la secuencia de posiciones actuales de las palabras
    // en su orden alfabético original.
    for (int i = 0; i < N; ++i) {
        cout << words[i].inputIndex << (i == N - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}