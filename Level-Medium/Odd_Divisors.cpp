/**
 * SOLUCIÓN: Divisores Impares (Odd Divisors)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Dado un rango [A, B], para cada número en ese rango, encontramos su
 * "Mayor Divisor Impar" (Greatest Odd Divisor - GOD).
 * Debemos sumar todos esos resultados.
 *
 * Ejemplo para entender f(x) = GOD(x):
 * - Si x es impar (ej: 7), su mayor divisor impar es él mismo (7).
 * - Si x es par (ej: 12), lo dividimos por 2 hasta que sea impar.
 * 12 -> 6 -> 3. Entonces f(12) = 3.
 * Matemáticamente: f(2*k) = f(k).
 *
 * ESTRATEGIA (Matemática Recursiva - O(log N)):
 * Calcular la suma directamente en [A, B] es difícil.
 * Usamos el truco de sumas de prefijos:
 * Suma(A, B) = Suma(1, B) - Suma(1, A-1).
 *
 * Ahora, enfoquémonos en resolver `suma(n)` para el rango [1, n].
 * Separemos los números en dos grupos: IMPARES y PARES.
 * Rango: 1, 2, 3, 4, 5, 6, ..., n
 *
 * 1. LOS IMPARES (1, 3, 5, ...):
 * Para un impar x, f(x) = x.
 * Así que simplemente sumamos la serie 1 + 3 + 5 + ...
 * ¿Cuántos impares hay hasta n? -> k = (n + 1) / 2.
 * La suma de los primeros k impares es exactamente k^2.
 *
 * 2. LOS PARES (2, 4, 6, ...):
 * Queremos sumar f(2) + f(4) + f(6) + ... + f(2*floor(n/2)).
 * Como sabemos que f(2*k) = f(k), esta suma es equivalente a:
 * f(1) + f(2) + f(3) + ... + f(floor(n/2)).
 * ¡Esto es exactamente una llamada recursiva a nuestra función original!
 * Suma_Pares = suma(n / 2).
 *
 * FÓRMULA FINAL:
 * suma(n) = (k * k) + suma(n / 2)
 * donde k = (n + 1) / 2.
 */

#include <iostream>

using namespace std;

// Usamos long long porque N llega hasta 10^9.
// La suma de divisores hasta 10^9 será aproximadamente (10^9)^2 / 2,
// lo cual es ~5*10^17. Esto cabe en long long (hasta 9*10^18) pero desborda int.
long long sumOddDivisors(long long n) {
    // Caso base: Si n es 0, la suma es 0.
    if (n == 0) return 0;

    // Paso 1: Calcular cuántos números impares hay en el rango [1, n].
    // Si n=5 (1,2,3,4,5), impares son 1,3,5 -> k=3. ((5+1)/2 = 3)
    // Si n=4 (1,2,3,4), impares son 1,3   -> k=2. ((4+1)/2 = 2)
    // División entera hace el trabajo.
    long long k = (n + 1) / 2;

    // Paso 2: Sumar la contribución de los números IMPARES.
    // La suma de 1 + 3 + ... + (2k-1) es siempre k^2.
    long long sumOdds = k * k;

    // Paso 3: Sumar la contribución de los números PARES recursivamente.
    // Los pares en [1, n] son equivalentes a todo el rango [1, n/2].
    long long sumEvens = sumOddDivisors(n / 2);

    return sumOdds + sumEvens;
}

int main() {
    // Optimización de I/O para manejar 10^5 casos de prueba rápidamente.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
        while (T--) {
            long long A, B;
            cin >> A >> B;

            // Calculamos la respuesta usando la resta de rangos.
            // Suma en [A, B] = Suma en [1, B] - Suma en [1, A-1]
            long long result = sumOddDivisors(B) - sumOddDivisors(A - 1);

            cout << result << "\n";
        }
    }
    return 0;
}