/**
 * SOLUCIÓN: Bit Count
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. Objetivo: Contar cuántos bits están en '1' (set bits) en un entero N.
 * 2. Restricción de diseño: "Intenta encontrar algo más rápido que iterar a través
 * de todos los bits".
 *
 * ESTRATEGIAS POSIBLES:
 * A) Iteración simple (Ingenua):
 * - Hacer un bucle 32 veces.
 * - Verificar el último bit (n & 1) y desplazar (n >>= 1).
 * - Complejidad: O(32) siempre, sin importar el número.
 *
 * B) Algoritmo de Brian Kernighan (OPTIMIZADO):
 * - Este método salta directamente de un bit '1' al siguiente.
 * - Si el número tiene solo 2 bits encendidos, el bucle solo corre 2 veces.
 * - Truco: La operación n = n & (n - 1) elimina el bit '1' menos significativo.
 * - Complejidad: O(k), donde k es el número de bits encendidos.
 *
 * C) Built-in (Para Competencia):
 * - En C++ moderno (GCC/Clang), existe __builtin_popcount(n).
 * - Esto suele mapear a una instrucción de hardware directa (muy rápido).
 * - Implementaremos la opción B para demostrar la lógica algorítmica.
 *
 * ======================================================================================
 * EXPLICACIÓN MATEMÁTICA: n & (n - 1)
 * ======================================================================================
 * Supongamos N = 40 (Binario: 101000)
 * 1. Restamos 1: 40 - 1 = 39 (Binario: 100111)
 * Notar que el bit '1' más bajo se apagó y los ceros a su derecha se volvieron 1.
 * 2. AND Bitwise:
 * 101000 (40)
 * & 100111 (39)
 * --------
 * 100000 (32) -> ¡El bit '1' más bajo de 40 ha desaparecido!
 */

#include <iostream>

using namespace std;

// Función que implementa el Algoritmo de Brian Kernighan
int countSetBits(int n) {
    int count = 0;
    
    // Mientras n tenga algún bit encendido
    while (n > 0) {
        // Esta operación elimina el bit '1' más a la derecha en cada paso.
        n = n & (n - 1);
        
        // Cada vez que logramos hacer esto, significa que había un bit '1'.
        count++;
    }
    
    return count;
}

int main() {
    // Optimización estándar de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    // Leemos la entrada
    if (cin >> N) {
        // Llamamos a nuestra función optimizada
        cout << countSetBits(N) << endl;
    }

    return 0;
}