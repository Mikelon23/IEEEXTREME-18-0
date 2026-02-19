/**
 * Solución para: Consecutive Max Difference
 * Lenguaje: C++
 *
 * -----------------------------------------------------------------------------
 * EXPLICACIÓN DEL ALGORITMO (ENFOQUE BUCKETS / PRINCIPIO DEL PALOMAR)
 * -----------------------------------------------------------------------------
 *
 * OBJETIVO:
 * Dado un arreglo de N elementos, encontrar la diferencia máxima entre dos
 * elementos consecutivos si el arreglo estuviera ordenado.
 *
 * RESTRICCIÓN PRINCIPAL:
 * Debe resolverse en tiempo O(N). Esto descarta métodos de ordenamiento
 * tradicionales como std::sort (QuickSort/MergeSort), ya que toman O(N log N).
 *
 * LÓGICA DE LA SOLUCIÓN O(N):
 * Para resolverlo en O(N), utilizamos la técnica de "Buckets" (Cubetas)
 * basada en el "Principio del Palomar" (Pigeonhole Principle).
 *
 * 1. ENCONTRAR EXTREMOS:
 * Primero, hallamos el valor mínimo (min_val) y máximo (max_val) del arreglo.
 * Si min_val == max_val, todos los elementos son iguales y la respuesta es 0.
 *
 * 2. TAMAÑO Y NÚMERO DE CUBETAS:
 * Si tenemos N elementos, hay (N - 1) "brechas" (espacios) entre ellos en 
 * el arreglo ordenado.
 * La diferencia máxima promedio posible es: gap = (max_val - min_val) / (N - 1).
 * Por el Principio del Palomar, la diferencia máxima REAL en el arreglo 
 * tiene que ser al menos tan grande como este 'gap' promedio.
 * * Sabiendo esto, dividimos el rango desde min_val hasta max_val en cubetas 
 * (buckets) de tamaño 'gap'.
 * - Tamaño de cada cubeta (bucket_size) = max(1, (max_val - min_val) / (N - 1))
 * - Número total de cubetas = ((max_val - min_val) / bucket_size) + 1
 *
 * 3. DISTRIBUIR Y FILTRAR:
 * Al distribuir los N números en estas cubetas, sabemos que la diferencia 
 * MÁXIMA nunca ocurrirá entre dos números que caigan en la misma cubeta 
 * (porque la capacidad máxima de la cubeta es 'gap', y sabemos que la 
 * diferencia máxima total es >= 'gap').
 * * Por lo tanto, solo necesitamos guardar el valor MÍNIMO y MÁXIMO dentro 
 * de cada cubeta. Los valores intermedios no nos importan.
 *
 * 4. CALCULAR LA DIFERENCIA MÁXIMA:
 * Iteramos a través de las cubetas de izquierda a derecha.
 * La máxima diferencia se encontrará restando el "mínimo de la cubeta actual" 
 * menos el "máximo de la última cubeta no vacía".
 *
 * COMPLEJIDAD:
 * - Tiempo: O(N) porque iteramos sobre el arreglo un par de veces sin anidaciones.
 * - Memoria: O(N) para almacenar los mínimos y máximos de las cubetas.
 */

#include <iostream>
#include <vector>
#include <algorithm> // Para std::max y std::min
#include <climits>   // Para INT_MAX e INT_MIN

using namespace std;

int consecutiveMaxDifference(const vector<int>& nums) {
    int n = nums.size();
    
    // Casos base
    if (n < 2) return 0;

    // 1. Encontrar min_val y max_val en O(N)
    int min_val = nums[0];
    int max_val = nums[0];
    for (int i = 1; i < n; i++) {
        min_val = min(min_val, nums[i]);
        max_val = max(max_val, nums[i]);
    }

    // Si todos los elementos son idénticos
    if (min_val == max_val) return 0;

    // 2. Calcular tamaño y cantidad de cubetas
    // Nos aseguramos de que el tamaño de la cubeta sea al menos 1 para evitar división por 0.
    int bucket_size = max(1, (max_val - min_val) / (n - 1));
    int bucket_count = ((max_val - min_val) / bucket_size) + 1;

    // Inicializamos las cubetas con valores extremos
    vector<int> bucket_min(bucket_count, INT_MAX);
    vector<int> bucket_max(bucket_count, INT_MIN);

    // 3. Llenar las cubetas con los valores mínimos y máximos O(N)
    for (int i = 0; i < n; i++) {
        // En qué índice de cubeta cae el número actual
        int idx = (nums[i] - min_val) / bucket_size;
        
        // Actualizamos el min y max solo para esa cubeta
        bucket_min[idx] = min(bucket_min[idx], nums[i]);
        bucket_max[idx] = max(bucket_max[idx], nums[i]);
    }

    // 4. Calcular la diferencia máxima entre cubetas adyacentes no vacías O(N)
    int max_diff = 0;
    
    // 'prev_max' guarda el elemento más grande de la última cubeta visitada.
    // Inicialmente es el min_val del arreglo completo.
    int prev_max = min_val; 

    for (int i = 0; i < bucket_count; i++) {
        // Si la cubeta se quedó con el valor inicial, significa que está vacía. La ignoramos.
        if (bucket_min[i] == INT_MAX) {
            continue;
        }

        // Calculamos la diferencia entre el mínimo de esta cubeta y el máximo de la anterior
        max_diff = max(max_diff, bucket_min[i] - prev_max);
        
        // Actualizamos prev_max para la siguiente iteración
        prev_max = bucket_max[i];
    }

    return max_diff;
}

int main() {
    // Optimización de I/O para C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // Leemos la cantidad de elementos
    if (cin >> n) {
        vector<int> nums(n);
        // Leemos los N elementos del arreglo
        for (int i = 0; i < n; i++) {
            cin >> nums[i];
        }

        // Ejecutamos la función e imprimimos el resultado
        cout << consecutiveMaxDifference(nums) << "\n";
    }

    return 0;
}