/**
 * SOLUCIÓN: Bit Removal
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. El objetivo es tomar dos enteros, X e Y.
 * 2. Debemos identificar qué bits están encendidos (son 1) en AMBOS números.
 * 3. En el número X, debemos "voltear" (flip) esos bits específicos.
 * - Si un bit es 1 en X y 1 en Y -> Lo volteamos en X (se vuelve 0).
 * - Si un bit es 1 en X y 0 en Y -> No cumple la condición "ambos", se queda igual (1).
 * - Si un bit es 0 en X -> No está "set to 1", así que no se toca.
 *
 * ======================================================================================
 * LÓGICA BITWISE (O(1))
 * ======================================================================================
 * Paso 1: Encontrar los bits comunes.
 * La operación AND (&) nos da un número donde solo los bits activos en ambos operandos son 1.
 * MASCARA_COMUN = (x & y)
 *
 * Paso 2: Voltear esos bits en X.
 * La operación XOR (^) funciona como un interruptor controlado.
 * - Si el bit de la máscara es 1, el bit correspondiente en X cambia de valor.
 * - Si el bit de la máscara es 0, el bit correspondiente en X se mantiene.
 *
 * FÓRMULA FINAL:
 * Resultado = x ^ (x & y)
 *
 * (Nota: Matemáticamente, como estamos apagando bits que sabemos que son 1,
 * esto también es equivalente a la resta: x - (x & y) o a la limpieza de bits: x & ~y).
 */

#include <iostream>

using namespace std;

void solve() {
    int x, y;
    // Leemos x e y
    if (!(cin >> x >> y)) return;

    // 1. Calculamos la intersección de bits (bits encendidos en ambos)
    int common_bits = x & y;

    // 2. Aplicamos XOR para voltear esos bits específicos en x
    //    Como sabemos que en 'x' esos bits son 1, al hacer XOR 1 se volverán 0.
    int result = x ^ common_bits;

    cout << result << "\n";
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    // Leemos el número de casos de prueba
    if (cin >> T) {
        while (T--) {
            solve();
        }
    }
    return 0;

}
