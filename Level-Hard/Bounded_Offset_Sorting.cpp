/**
 * SOLUCIÓN: Ordenamiento con Desplazamiento Acotado (Bounded Offset Sorting)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Tenemos un arreglo donde cada elemento está "casi" en su lugar correcto.
 * Específicamente, un elemento que debería ir en la posición 'i' (ordenado),
 * se encuentra actualmente en algún lugar entre [i-M, i+M].
 *
 * Objetivo: Ordenar el arreglo en O(N log M).
 *
 * ESTRATEGIA (Min-Heap / Ventana Deslizante):
 * Un ordenamiento normal (QuickSort/MergeSort) toma O(N log N).
 * Aquí M suele ser mucho menor que N, así que podemos hacerlo mejor.
 *
 * La regla nos dice que el elemento más pequeño del arreglo (el que va en la pos 0)
 * TIENE que estar en las primeras M+1 posiciones del input (índices 0 a M).
 * ¿Por qué? Si estuviera en la posición M+1, su desplazamiento sería > M, lo cual
 * viola la regla.
 *
 * ALGORITMO:
 * 1. Mantenemos un Min-Heap (Cola de Prioridad) de tamaño M + 1.
 * 2. Insertamos los primeros M+1 elementos en el Heap.
 * 3. El mínimo de ese Heap es GARANTIZADO ser el mínimo global del arreglo
 * (el que va en la posición 0). Lo extraemos y lo colocamos en el resultado.
 * 4. "Deslizamos la ventana": Insertamos el siguiente elemento del arreglo (índice M+1)
 * en el Heap y extraemos el nuevo mínimo para la posición 1.
 * 5. Repetimos hasta terminar.
 *
 * Complejidad:
 * Insertar/Extraer en un Heap de tamaño K toma O(log K).
 * Aquí K = M. Hacemos esto N veces.
 * Total: O(N log M).
 */

#include <iostream>
#include <vector>
#include <queue> // Necesario para priority_queue

using namespace std;

// Usamos 'greater<int>' para que la priority_queue funcione como un Min-Heap
// (por defecto en C++ es un Max-Heap).
void sortBoundedArray(vector<int>& arr, int N, int M) {
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // 1. Fase de Inicialización:
    // Llenamos el heap con los primeros M + 1 elementos.
    // Este subconjunto contiene seguro al elemento más pequeño de todo el arreglo.
    // Nota: Manejamos el caso borde donde M >= N (simplemente metemos todo).
    for (int i = 0; i <= M && i < N; ++i) {
        minHeap.push(arr[i]);
    }

    // Índice donde vamos a colocar el siguiente número ordenado en el arreglo original.
    int index_to_fill = 0;

    // 2. Fase de Ventana Deslizante:
    // Recorremos el resto de los elementos del arreglo (desde M+1 hasta el final).
    for (int i = M + 1; i < N; ++i) {
        // a. Extraemos el mínimo actual del heap. Este es el siguiente elemento en orden.
        arr[index_to_fill++] = minHeap.top();
        minHeap.pop();

        // b. Insertamos el nuevo elemento que entra en nuestra "ventana de visión".
        minHeap.push(arr[i]);
    }

    // 3. Fase de Vaciado:
    // Ya no hay elementos nuevos para agregar, pero el heap todavía tiene datos.
    // Simplemente extraemos todo lo que queda; saldrán en orden ascendente.
    while (!minHeap.empty()) {
        arr[index_to_fill++] = minHeap.top();
        minHeap.pop();
    }
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    sortBoundedArray(arr, N, M);

    // Imprimir el arreglo ordenado
    for (int i = 0; i < N; ++i) {
        cout << arr[i] << (i == N - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}