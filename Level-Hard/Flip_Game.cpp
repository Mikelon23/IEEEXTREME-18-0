/**
 * SOLUCIÓN: Juego de Voltear (Flip Game)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Nos dan una matriz binaria (N filas, M columnas).
 * Podemos invertir (0->1, 1->0) cualquier fila o columna completa, tantas veces como queramos.
 * Al final, cada fila se interpreta como un número binario.
 * Objetivo: Maximizar la SUMA de todos estos números.
 *
 * ESTRATEGIA (Greedy / Codiciosa):
 * En los números binarios, la posición importa muchísimo.
 * El bit más a la izquierda (Columna 0, el Bit Más Significativo o MSB) aporta
 * 2^(M-1) al valor. La suma de TODOS los bits restantes (2^(M-2) + ... + 1)
 * es menor que ese único bit (2^(M-1) - 1).
 *
 * CONCLUSIÓN CLAVE:
 * La prioridad absoluta es conseguir un 1 en la primera columna de cada fila.
 * Vale la pena sacrificar cualquier configuración de las columnas siguientes
 * con tal de asegurar la primera columna.
 *
 * ALGORITMO:
 * 1. OPTIMIZAR FILAS (Basado en Columna 0):
 * Recorremos cada fila.
 * - Si la fila empieza con 0, la volteamos ENTERA. (Ahora empieza con 1).
 * - Si empieza con 1, la dejamos quieta.
 * Con esto, garantizamos que toda la Columna 0 sean puros 1s.
 *
 * 2. OPTIMIZAR COLUMNAS (Columnas 1 a M-1):
 * Una vez fijadas las filas en el paso 1, ya no podemos tocar las filas
 * (porque romperíamos los MSB que tanto valen).
 * Solo nos queda la libertad de voltear COLUMNAS individuales.
 * Para cada columna vertical (de la 1 a la M-1):
 * - Contamos cuántos 1s tiene actualmente.
 * - Si tiene más 0s que 1s, nos conviene voltearla (los 0s se vuelven 1s).
 * - Tomamos el máximo entre (número de 1s) y (número de 0s).
 * - Sumamos su contribución al total.
 *
 * COMPLEJIDAD:
 * Tiempo: O(N * M). Solo recorremos la matriz un par de veces.
 * N, M <= 50, así que es casi instantáneo.
 */

#include <iostream>
#include <vector>
#include <algorithm> // Para std::max
#include <cmath>     // Para pow (aunque usaremos bit shifting)

using namespace std;

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> grid(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
        }
    }

    // ---------------------------------------------------------
    // PASO 1: Asegurar el Bit Más Significativo (Columna 0)
    // ---------------------------------------------------------
    for (int i = 0; i < N; ++i) {
        // Si el primer bit es 0, volteamos toda la fila.
        // Esto garantiza que grid[i][0] sea siempre 1.
        if (grid[i][0] == 0) {
            for (int j = 0; j < M; ++j) {
                grid[i][j] = 1 - grid[i][j]; // Inversión: 1->0, 0->1
            }
        }
    }

    // ---------------------------------------------------------
    // PASO 2: Calcular Suma Total optimizando columnas restantes
    // ---------------------------------------------------------
    // Usamos long long porque con M=50, el número es enorme (2^50).
    long long total_sum = 0;

    // Iteramos por cada columna j (desde bit más significativo 0 hasta M-1)
    for (int j = 0; j < M; ++j) {
        int count1 = 0;
        
        // Contamos cuántos 1s hay en la columna j actual
        for (int i = 0; i < N; ++i) {
            if (grid[i][j] == 1) {
                count1++;
            }
        }

        int count0 = N - count1;

        // ELEGIR LA MEJOR VERSIÓN DE LA COLUMNA:
        // Si hay más 0s que 1s, imaginamos que volteamos la columna.
        // Así que tomamos el mayor número de coincidencias.
        // Nota: Para la col 0, count1 siempre será N (por el paso 1),
        // así que esto no afecta la lógica.
        int max_ones = max(count1, count0);

        // VALOR POSICIONAL:
        // Si estamos en la col j, el exponente es (M - 1 - j).
        // Ejemplo: M=3, j=0 (primera col) -> exponente 2 (valor 4).
        // Usamos 1LL para asegurar aritmética de 64 bits.
        long long column_value = (1LL << (M - 1 - j));

        // Sumar contribución: (cantidad de 1s) * (valor de esa posición)
        total_sum += max_ones * column_value;
    }

    cout << total_sum << endl;

    return 0;
}