/**
 * SOLUCIÓN: Odd Divisor Count
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS MATEMÁTICO (TEORÍA DE NÚMEROS)
 * ======================================================================================
 * 1. Pregunta Clave: ¿Qué números tienen una cantidad IMPAR de divisores?
 *
 * 2. Observación:
 * Los divisores de un número 'n' generalmente vienen en parejas.
 * Si 'd' divide a 'n', entonces 'n/d' también divide a 'n'.
 * Ejemplo: n = 12
 * Parejas: (1, 12), (2, 6), (3, 4).
 * Total de divisores = 6 (Número PAR).
 *
 * 3. La Excepción (Cuadrados Perfectos):
 * ¿Qué pasa si una pareja está formada por el mismo número repetido?
 * Esto ocurre solo si d = n/d, es decir, d * d = n.
 * Ejemplo: n = 36
 * Parejas: (1, 36), (2, 18), (3, 12), (4, 9), (6, 6).
 * El divisor '6' se cuenta una sola vez.
 * Total de divisores = 9 (Número IMPAR).
 *
 * 4. Conclusión:
 * Un número tiene una cantidad IMPAR de divisores SI Y SOLO SI es un
 * CUADRADO PERFECTO (ej. 1, 4, 9, 16, 25, 36, ...).
 *
 * ======================================================================================
 * ESTRATEGIA DE IMPLEMENTACIÓN
 * ======================================================================================
 * - Iteramos desde A hasta B.
 * - Para cada número, verificamos si es un cuadrado perfecto.
 * - Si lo es, aumentamos el contador.
 *
 * Nota: Dado que B <= 1000, una iteración simple es extremadamente rápida.
 * Para límites más grandes (ej. 10^18), usaríamos la fórmula:
 * floor(sqrt(B)) - floor(sqrt(A-1)).
 */

#include <iostream>
#include <cmath> // Para la función sqrt()

using namespace std;

bool isPerfectSquare(int n) {
    // Calculamos la raíz cuadrada entera.
    // Ejemplo: sqrt(25) = 5.0 -> int(5)
    // Ejemplo: sqrt(26) = 5.09 -> int(5)
    int root = static_cast<int>(sqrt(n));
    
    // Comprobamos si al multiplicar la raíz por sí misma obtenemos el original.
    return (root * root == n);
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int A, B;
    
    if (cin >> A >> B) {
        int count = 0;

        // Recorremos el intervalo [A, B]
        for (int i = A; i <= B; ++i) {
            // Aplicamos la propiedad matemática descubierta arriba
            if (isPerfectSquare(i)) {
                count++;
            }
        }

        cout << count << endl;
    }

    return 0;
}