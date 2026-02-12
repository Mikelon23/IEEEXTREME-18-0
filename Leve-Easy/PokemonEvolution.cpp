/**
 * SOLUCIÓN: Pokémon Evolution
 * LENGUAJE: C++
 * * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. Tenemos:
 * - N: Número total de Pokémon.
 * - M: Caramelos iniciales.
 * - X: Costo en caramelos para evolucionar uno.
 * - Y: Caramelos que recibes al vender uno (no evolucionado).
 * * 2. Restricción clave: No puedes vender un Pokémon que ya evolucionaste.
 * Esto implica que: (Pokémon Evolucionados) + (Pokémon Vendidos) <= N.
 * * 3. Desafío de escala: Los valores llegan a 10^9. Una solución lineal O(N) fallará.
 * Necesitamos algo más rápido, como O(log N).
 * * ======================================================================================
 * LÓGICA DE BÚSQUEDA BINARIA
 * ======================================================================================
 * Queremos encontrar el mayor valor 'k' (número de evoluciones) que sea posible.
 * * Para un valor 'k' dado, ¿es posible evolucionar 'k' Pokémon?
 * - Necesitamos k * X caramelos en total.
 * - Tenemos M caramelos iniciales.
 * - Si M < k * X, nos faltan (k * X - M) caramelos.
 * - Para obtener los caramelos faltantes, debemos vender otros Pokémon.
 * - ¿Cuántos Pokémon nos quedan para vender? (N - k).
 * - Caramelos extra que podemos obtener: (N - k) * Y.
 * * Condición: Si (M + (N - k) * Y) >= k * X, entonces 'k' es posible.
 */

#include <iostream>
#include <algorithm>

using namespace std;

/**
 * Función: check
 * --------------
 * Determina si es factible evolucionar 'k' Pokémon siguiendo las reglas.
 */
bool canEvolve(long long k, long long n, long long m, long long x, long long y) {
    // Si intentamos evolucionar más de los que tenemos, es imposible.
    if (k > n) return false;

    // Caramelos totales necesarios para evolucionar k Pokémon.
    long long total_needed = k * x;

    // Caramelos que tenemos inicialmente + los que obtenemos vendiendo los restantes.
    // Los restantes son (n - k), ya que no podemos vender los que evolucionamos.
    long long available_resources = m + (n - k) * y;

    return available_resources >= total_needed;
}

int main() {
    // Optimización de entrada y salida para mayor velocidad.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Usamos long long porque N, M, X, Y pueden ser 10^9 y sus productos superan el int.
    long long n, m, x, y;
    if (!(cin >> n >> m >> x >> y)) return 0;

    // Rango de búsqueda para la cantidad de Pokémon evolucionados.
    long long low = 0;
    long long high = n;
    long long answer = 0;

    // BÚSQUEDA BINARIA O(log N)
    // En cada paso reducimos el espacio de búsqueda a la mitad.
    while (low <= high) {
        long long mid = low + (high - low) / 2;

        if (canEvolve(mid, n, m, x, y)) {
            // Si es posible evolucionar 'mid', intentamos con un número mayor.
            answer = mid;
            low = mid + 1;
        } else {
            // Si no es posible, debemos intentar con un número menor.
            high = mid - 1;
        }
    }

    // El resultado final es el valor más alto que pasó la prueba 'canEvolve'.
    cout << answer << endl;

    return 0;
}