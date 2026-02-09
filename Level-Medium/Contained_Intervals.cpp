/**
 * SOLUCIÓN: Intervalos Contenidos (Contained Intervals)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Dados N intervalos [L, R], contar cuántos están "contenidos" dentro de
 * al menos otro intervalo.
 * Un intervalo A está contenido en B si: B.L <= A.L  y  A.R <= B.R.
 * (B empieza antes o igual y termina después o igual que A).
 *
 * ESTRATEGIA (Sorting Greedy):
 * La fuerza bruta comparando todos contra todos sería O(N^2), muy lento para N=10^5.
 * Usaremos ordenamiento O(N log N) para hacerlo en una sola pasada lineal O(N).
 *
 * 1. ORDENAMIENTO PERSONALIZADO:
 * Ordenamos los intervalos por inicio (L) Ascendente.
 * TRUCO CLAVE: Si dos intervalos tienen el mismo inicio (L), ordenamos por
 * fin (R) Descendente (del más largo al más corto).
 *
 * Ejemplo: [1, 5], [1, 10] -> Se ordenan como [1, 10], [1, 5].
 *
 * ¿Por qué esto ayuda?
 * Al recorrer la lista, como L es ascendente, ya sabemos que el intervalo actual
 * empieza después (o igual) que todos los anteriores.
 * Solo nos falta chequear el fin (R).
 * Si el intervalo actual termina ANTES (o igual) que el "mayor final visto hasta ahora",
 * significa que cabe perfectamente dentro de ese intervalo anterior.
 *
 * 2. MANEJO DE DUPLICADOS:
 * El problema pide contar intervalos contenidos. Si tenemos [1, 2] y [1, 2],
 * ambos se contienen mutuamente, así que ambos deben contarse.
 * Nuestro algoritmo detecta naturalmente el segundo como contenido en el primero.
 * Agregamos una pequeña verificación para marcar también al primero si son idénticos.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int l, r;
    // No necesitamos el ID original para el conteo total, 
    // pero conceptualmente trabajamos con las posiciones del array ordenado.
};

// Función de comparación para el sort
bool compareIntervals(const Interval& a, const Interval& b) {
    if (a.l != b.l) {
        return a.l < b.l; // 1. Ordenar por L ascendente
    }
    return a.r > b.r;     // 2. Si L es igual, ordenar por R descendente
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<Interval> intervals(N);
    for (int i = 0; i < N; ++i) {
        cin >> intervals[i].l >> intervals[i].r;
    }

    // Paso 1: Ordenar
    sort(intervals.begin(), intervals.end(), compareIntervals);

    // Usamos un vector booleano para marcar qué índices (del array ordenado) están contenidos.
    vector<bool> is_contained(N, false);
    
    // 'max_r' guarda el final más lejano que hemos visto en los intervalos procesados.
    // Inicializamos con el primer intervalo.
    int max_r = intervals[0].r;

    for (int i = 1; i < N; ++i) {
        // CASO A: Contención por un intervalo previo más grande
        // Como ordenamos por L ascendente, intervals[i] empieza después o igual que 
        // cualquier intervalo anterior que haya establecido 'max_r'.
        // Si su R es menor o igual a max_r, ¡está contenido!
        if (intervals[i].r <= max_r) {
            is_contained[i] = true;
        } else {
            // Si no está contenido y llega más lejos, actualizamos el alcance máximo.
            max_r = intervals[i].r;
        }

        // CASO B: Duplicados exactos (Contención simétrica)
        // Si intervals[i] es idéntico a intervals[i-1], entonces se contienen mutuamente.
        // El algoritmo de arriba ya marcó al actual (is_contained[i]) porque R <= max_r.
        // Pero debemos asegurarnos de marcar al anterior también.
        if (intervals[i].l == intervals[i-1].l && intervals[i].r == intervals[i-1].r) {
            is_contained[i-1] = true;
        }
    }

    // Paso Final: Contar los marcados
    int count = 0;
    for (bool c : is_contained) {
        if (c) count++;
    }

    cout << count << endl;

    return 0;
}