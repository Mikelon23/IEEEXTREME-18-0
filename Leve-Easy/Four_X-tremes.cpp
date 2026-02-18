/**
 * SOLUCIÓN: Four X-tremes
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. Objetivo: Dados 4 números enteros, encontrar la "diferencia máxima" entre
 * cualquiera de ellos.
 *
 * 2. Lógica Matemática:
 * - Si tienes un conjunto de números, la distancia más grande posible siempre
 * está entre los dos extremos: el número más pequeño (mínimo) y el número
 * más grande (máximo).
 * - Cualquier otra combinación de números estará "dentro" de este rango, por lo
 * que su diferencia será menor.
 *
 * 3. Fórmula:
 * Resultado = Valor_Máximo - Valor_Mínimo
 *
 * 4. Ejemplo con negativos (Input: -10 4 -9 -5):
 * - El menor es -10.
 * - El mayor es 4.
 * - Diferencia = 4 - (-10) = 4 + 10 = 14.
 *
 * ======================================================================================
 * IMPLEMENTACIÓN
 * ======================================================================================
 * - Usaremos un `std::vector` o un `array` para guardar los 4 números.
 * - Usaremos las funciones estándar `std::min_element` y `std::max_element`
 * de la librería <algorithm> para encontrar los extremos sin necesidad de escribir
 * múltiples condiciones `if`.
 */

#include <iostream>
#include <algorithm> // Necesario para min_element y max_element
#include <vector>

using namespace std;

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Creamos un vector de tamaño 4 para almacenar los enteros.
    vector<int> nums(4);

    // Leemos los 4 números de la entrada estándar.
    // Verificamos que la lectura sea exitosa antes de continuar.
    if (cin >> nums[0] >> nums[1] >> nums[2] >> nums[3]) {
        
        // Buscamos el elemento MÍNIMO en el rango del vector.
        // min_element devuelve un iterador (puntero), así que usamos '*' para obtener el valor.
        int min_val = *min_element(nums.begin(), nums.end());

        // Buscamos el elemento MÁXIMO de la misma forma.
        int max_val = *max_element(nums.begin(), nums.end());

        // Calculamos la diferencia máxima.
        // Nota: Como restamos (Grande - Pequeño), el resultado siempre es positivo.
        int max_diff = max_val - min_val;

        // Imprimimos el resultado.
        cout << max_diff << endl;
    }

    return 0;
}
