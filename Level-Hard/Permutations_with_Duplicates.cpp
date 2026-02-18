/**
 * SOLUCIÓN: Permutaciones con Duplicados (Permutations with Duplicates)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Dado un arreglo de N enteros (que puede tener números repetidos),
 * imprimir todas las permutaciones ÚNICAS en orden lexicográfico (alfabético/numérico).
 *
 * Ejemplo:
 * Input: [1, 1, 2]
 * Output esperado:
 * 1 1 2
 * 1 2 1
 * 2 1 1
 * (Notar que no generamos "1 1 2" dos veces, aunque haya dos unos distintos).
 *
 * ESTRATEGIA (Backtracking Recursivo + Ordenamiento):
 *
 * 1. ORDENAR EL ARREGLO INICIAL:
 * Esto es CRUCIAL. Para generar las permutaciones en orden lexicográfico
 * y para detectar duplicados fácilmente, los números idénticos deben estar juntos.
 * [2, 1, 1] -> ordenamos a -> [1, 1, 2].
 *
 * 2. RECURSIÓN (BACKTRACKING):
 * Vamos construyendo la permutación número a número.
 * Mantenemos un arreglo 'visited' para saber qué índice del arreglo original
 * ya estamos usando en la rama actual de la recursión.
 *
 * 3. LA REGLA DE ORO PARA DUPLICADOS (PRUNING):
 * Si estamos iterando y encontramos un número que es IDÉNTICO al anterior
 * (nums[i] == nums[i-1]), debemos tener cuidado.
 *
 * La condición clave para saltarlo es:
 * if (i > 0 && nums[i] == nums[i-1] && !visited[i-1]) continue;
 *
 * ¿Qué significa esto?
 * "Si este número es igual al anterior, Y el anterior NO se está usando
 * actualmente en esta recursión, entonces sáltame".
 * Esto fuerza a que, si hay dos '1's, siempre usemos el primero antes que
 * el segundo. Evita que generemos ramas duplicadas permutando '1a' con '1b'.
 *
 * COMPLEJIDAD:
 * Tiempo: O(N * N!) en el peor caso (todos distintos), pero mucho menos con duplicados.
 * Es óptimo O(output_size) porque nunca generamos una rama inválida.
 */

#include <iostream>
#include <vector>
#include <algorithm> // Para sort

using namespace std;

// Variables globales para facilitar el acceso en la recursión
int N;
vector<int> nums;         // Los números originales ordenados
vector<int> current_perm; // La permutación que estamos construyendo
vector<bool> visited;     // Para marcar qué índices ya usamos

void generatePermutations() {
    // CASO BASE:
    // Si la permutación actual tiene el tamaño N, está completa.
    if (current_perm.size() == N) {
        for (int i = 0; i < N; ++i) {
            cout << current_perm[i] << (i == N - 1 ? "" : " ");
        }
        cout << "\n"; // Usar \n es más rápido que endl
        return;
    }

    // PASO RECURSIVO:
    // Probamos agregar cada número disponible a la posición actual.
    for (int i = 0; i < N; ++i) {
        // CONDICIÓN 1: Si este índice ya está en uso, no podemos volver a usarlo.
        if (visited[i]) continue;

        // CONDICIÓN 2 (Manejo de Duplicados):
        // Explicación detallada:
        // Si nums[i] es igual a nums[i-1], son "gemelos".
        // Si visited[i-1] es FALSE, significa que la recursión ya terminó de procesar
        // todas las permutaciones que empezaban con el primer gemelo y ahora "soltó" (backtrack)
        // ese número.
        // Si ahora intentamos usar el segundo gemelo como si fuera el primero,
        // repetiremos exactamente el mismo trabajo. Por eso lo saltamos.
        // Solo usamos el segundo gemelo si el primero YA está dentro de la permutación (visited[i-1] == true).
        if (i > 0 && nums[i] == nums[i-1] && !visited[i-1]) {
            continue;
        }

        // ACCIÓN (DO):
        visited[i] = true;
        current_perm.push_back(nums[i]);

        // RECURSIÓN:
        generatePermutations();

        // DESHACER (BACKTRACK):
        // Quitamos el elemento para probar el siguiente en la próxima iteración del bucle.
        current_perm.pop_back();
        visited[i] = false;
    }
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> N)) return 0;

    nums.resize(N);
    visited.assign(N, false); // Inicializamos todo en false

    for (int i = 0; i < N; ++i) {
        cin >> nums[i];
    }

    // Paso 1: Ordenar para agrupar duplicados y asegurar orden lexicográfico
    sort(nums.begin(), nums.end());

    // Paso 2: Iniciar Backtracking
    generatePermutations();

    return 0;
}