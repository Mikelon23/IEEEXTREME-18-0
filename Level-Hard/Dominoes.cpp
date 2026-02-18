/**
 * SOLUCIÓN: Dominoes
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Tenemos N dominós en coordenadas fijas ordenadas.
 * Tenemos K dominós comodín.
 * Queremos formar la secuencia consecutiva más larga posible.
 *
 * ESTRATEGIA (Sliding Window / Two Pointers):
 * Interpretamos el problema como buscar el subsegmento más largo del array original
 * que podamos "unir" usando a lo sumo K fichas.
 *
 * FÓRMULA DE HUECOS:
 * Entre dos dominós en las posiciones arr[L] y arr[R], la cantidad de números
 * enteros que faltan (huecos) es:
 * Huecos = (Diferencia de valores) - (Diferencia de índices)
 * Huecos = (arr[R] - arr[L]) - (R - L)
 *
 * ALGORITMO O(N):
 * 1. Usamos dos punteros: 'left' y 'right'.
 * 2. Expandimos 'right' hacia la derecha en cada paso.
 * 3. Calculamos cuántos huecos necesitamos para mantener conectado el rango [left, right].
 * 4. Si los huecos superan K, avanzamos 'left' para encoger la ventana hasta que sea válida.
 * 5. En cada paso válido, guardamos el tamaño de la ventana (right - left + 1).
 * 6. La respuesta final es (Tamaño Máximo de Ventana + K).
 *
 * COMPLEJIDAD:
 * Tiempo: O(N) - Cada puntero recorre el array una sola vez.
 * Espacio: O(N) - Para almacenar la entrada.
 */

#include <iostream>
#include <vector>
#include <algorithm> // Para std::max

using namespace std;

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    if (!(cin >> N >> K)) return 0;

    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    int left = 0;
    int max_window_size = 0;

    // Expandimos la ventana con el puntero 'right'
    for (int right = 0; right < N; ++right) {
        
        // CÁLCULO DE HUECOS (GAPS):
        // La distancia física es (arr[right] - arr[left]).
        // La cantidad de fichas que tenemos es (right - left).
        // Los huecos son la diferencia.
        // Ejemplo: Fichas en 1 y 4 (índices 0 y 1).
        // Distancia física: 4 - 1 = 3.
        // Distancia índices: 1 - 0 = 1.
        // Huecos: 3 - 1 = 2 (faltan el 2 y el 3).
        
        // Mientras la ventana actual requiera más de K fichas para unirse,
        // encogemos desde la izquierda.
        while ((arr[right] - arr[left]) - (right - left) > K) {
            left++;
        }

        // Ahora la ventana [left, right] es válida (se puede unir con <= K fichas).
        // Actualizamos el récord de cuántas fichas ORIGINALES logramos conectar.
        int current_window_size = right - left + 1;
        if (current_window_size > max_window_size) {
            max_window_size = current_window_size;
        }
    }

    // El resultado final es la cantidad de fichas originales que logramos unir
    // MÁS las K fichas extra que tenemos disponibles.
    // (Las que no se usaron para rellenar huecos se ponen en los extremos).
    cout << max_window_size + K << endl;

    return 0;
}