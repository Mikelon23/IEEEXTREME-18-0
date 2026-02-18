/**
 * SOLUCIÓN: Closest Pair
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS DEL PROBLEMA Y ESTRATEGIA
 * ======================================================================================
 * 1. Objetivo: Encontrar la diferencia mínima absoluta |a - b| donde 'a' pertenece
 * al array A y 'b' al array B.
 * * 2. Desafío de Eficiencia:
 * - Comparar todos contra todos (Fuerza Bruta) tiene complejidad O(N^2).
 * - Con N=100,000, esto es inaceptable.
 * * 3. Estrategia Óptima (Ordenamiento + Dos Punteros):
 * - Paso A: Ordenamos ambos arrays de menor a mayor.
 * Esto nos permite recorrerlos de forma lógica. Complejidad: O(N log N).
 * - Paso B: Usamos la técnica de "Dos Punteros" (Two Pointers).
 * Mantenemos un índice 'i' para el array A y un índice 'j' para el array B.
 * * Lógica de los punteros:
 * - Calculamos la diferencia actual: diff = abs(A[i] - B[j]).
 * - Si A[i] es menor que B[j], la única forma de reducir la diferencia
 * es buscar un valor más grande en A (avanzamos i).
 * - Si B[j] es menor que A[i], necesitamos un valor más grande en B
 * para acercarnos a A[i] (avanzamos j).
 * - Si encontramos una diferencia de 0, terminamos inmediatamente (es el mínimo posible).
 * * Complejidad Total: O(N log N) debido al ordenamiento.
 */

#include <iostream>
#include <vector>
#include <algorithm> // Para sort y min
#include <cmath>     // Para abs
#include <climits>   // Para INT_MAX

using namespace std;

int main() {
    // Optimización de I/O para manejar grandes volúmenes de datos rápidamente.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    // Leemos el primer array
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // Leemos el segundo array
    vector<int> B(N);
    for (int i = 0; i < N; ++i) {
        cin >> B[i];
    }

    // 1. ORDENAMIENTO (Crucial para la eficiencia)
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    // 2. DOS PUNTEROS
    int i = 0; // Puntero para A
    int j = 0; // Puntero para B
    
    // Inicializamos con el valor máximo posible para ir reduciéndolo.
    // Usamos long long para evitar overflow en restas, aunque el resultado cabe en int.
    long long min_diff = LLONG_MAX;

    while (i < N && j < N) {
        // Calculamos la diferencia absoluta actual
        long long current_diff = abs((long long)A[i] - (long long)B[j]);

        // Actualizamos el mínimo global si encontramos uno menor
        if (current_diff < min_diff) {
            min_diff = current_diff;
        }

        // Optimización: Si la diferencia es 0, no podemos mejorar más.
        if (min_diff == 0) break;

        // Decisión de movimiento de punteros:
        // Siempre movemos el puntero que apunta al valor más pequeño.
        // ¿Por qué? Porque si A[i] < B[j], aumentar B[j] solo alejaría más los valores.
        // La única esperanza de acercarse a B[j] es aumentar A[i].
        if (A[i] < B[j]) {
            i++;
        } else {
            j++;
        }
    }

    cout << min_diff << endl;

    return 0;
}