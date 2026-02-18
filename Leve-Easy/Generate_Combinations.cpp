/**
 * SOLUCIÓN: Generate Combinations
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. Objetivo: Generar todos los subconjuntos de tamaño K usando números del 1 al N.
 * 2. Requisitos de Orden:
 * a) Los valores dentro del subconjunto deben estar ordenados (creciente).
 * b) Los subconjuntos deben imprimirse en orden lexicográfico.
 * (Ej: "1 2" va antes que "1 3").
 *
 * ======================================================================================
 * ESTRATEGIA: BACKTRACKING (Recursión)
 * ======================================================================================
 * Usaremos una función recursiva que construye el subconjunto paso a paso.
 *
 * Parámetros de la recursión:
 * - `start`: El número más pequeño que podemos elegir en este paso.
 * (Para evitar duplicados y mantener el orden creciente, si elegimos
 * el número 'x', el siguiente debe ser al menos 'x+1').
 * - `current`: El vector que guarda los números elegidos hasta el momento.
 *
 * Lógica:
 * 1. Caso Base: Si el vector `current` tiene tamaño K, hemos terminado un subconjunto.
 * Lo imprimimos y "volvemos" (return) para buscar otros.
 *
 * 2. Paso Recursivo: Iteramos desde `start` hasta `N`.
 * - Añadimos el número `i` al vector.
 * - Llamamos recursivamente pidiendo el siguiente número (i + 1).
 * - Al volver de la recursión, sacamos el número `i` (Backtracking) para
 * dejar el vector limpio para la siguiente iteración del bucle.
 *
 * Optimización (Poda):
 * No es necesario iterar hasta N siempre. Si nos faltan 3 números por elegir
 * y solo quedan 2 números disponibles en el rango [start, N], no tiene sentido seguir.
 * Límite del bucle: i <= N - (K - elementos_actuales) + 1
 */

#include <iostream>
#include <vector>

using namespace std;

// Variables globales para facilitar el acceso en la recursión
int N, K;
vector<int> combination;

void generate(int start) {
    // --- CASO BASE ---
    // Si ya hemos seleccionado K elementos, imprimimos la combinación.
    if (combination.size() == K) {
        for (int i = 0; i < K; ++i) {
            // Imprimimos espacio solo si no es el último elemento
            cout << combination[i] << (i == K - 1 ? "" : " ");
        }
        cout << "\n";
        return;
    }

    // --- PASO RECURSIVO ---
    // Calculamos cuántos elementos nos faltan por añadir
    int remaining = K - combination.size();
    
    // OPTIMIZACIÓN DEL BUCLE:
    // Solo iteramos hasta donde sea matemáticamente posible completar el grupo.
    // Por ejemplo: Si N=5, K=3 y estamos eligiendo el primer número, 
    // no podemos elegir el 4 o 5, porque no quedarían suficientes números después
    // para completar el trío. El límite es N - remaining + 1.
    for (int i = start; i <= N - remaining + 1; ++i) {
        
        // 1. Elegir (Make move)
        combination.push_back(i);
        
        // 2. Explorar (Recurse)
        // El siguiente número debe ser al menos i + 1
        generate(i + 1);
        
        // 3. Deshacer (Backtrack)
        // Quitamos el elemento para probar con el siguiente valor del bucle.
        combination.pop_back();
    }
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Lectura de entrada
    if (cin >> N >> K) {
        // Iniciamos la generación buscando desde el número 1
        generate(1);
    }

    return 0;
}