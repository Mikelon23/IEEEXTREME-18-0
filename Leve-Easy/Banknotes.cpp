/**
 * SOLUCIÓN: Banknotes
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS MATEMÁTICO
 * ======================================================================================
 * 1. Definición de variables:
 * - A: Valor del billete tipo 1.
 * - B: Valor del billete tipo 2.
 * - S: Suma total deseada.
 * - N: Cantidad total de billetes.
 *
 * Incógnitas:
 * - x: Cantidad de billetes de valor A.
 * - y: Cantidad de billetes de valor B.
 *
 * 2. Planteamiento del Sistema de Ecuaciones:
 * Tenemos dos restricciones que deben cumplirse simultáneamente:
 * (Ec. 1)  x + y = N            (Total de billetes)
 * (Ec. 2)  A*x + B*y = S        (Suma total del valor)
 *
 * 3. Resolución del Sistema (Método de Sustitución):
 * Despejamos 'y' de la Ec. 1:
 * y = N - x
 *
 * Sustituimos 'y' en la Ec. 2:
 * A*x + B*(N - x) = S
 *
 * Desarrollamos:
 * A*x + B*N - B*x = S
 *
 * Agrupamos los términos con 'x':
 * x * (A - B) = S - (B * N)
 *
 * Despejamos 'x':
 * x = (S - B * N) / (A - B)
 *
 * 4. Condiciones de Validez:
 * Para que la solución sea válida en el mundo real, deben cumplirse 3 cosas:
 * a) División Exacta: (S - B*N) debe ser divisible por (A - B).
 * Si hay residuo, significa que necesitamos una fracción de billete (imposible).
 * b) No Negatividad: x >= 0. No podemos tener -3 billetes.
 * c) Límite Superior: x <= N. No podemos usar más billetes de los que tenemos en total.
 *
 * 5. Tipos de Datos:
 * Los valores pueden llegar a 10^9. Al multiplicar B*N, podemos obtener 10^18.
 * Esto excede la capacidad de un 'int' estándar (2*10^9).
 * IMPORTANTE: Usar 'long long' para evitar desbordamiento (overflow).
 */

#include <iostream>

using namespace std;

void solve() {
    long long A, B, S, N;
    
    // Leemos los 4 valores.
    // Usamos cin >> variable para verificar que la lectura sea correcta.
    if (!(cin >> A >> B >> S >> N)) return;

    // --- PASO 1: Calcular el numerador y denominador de la fórmula ---
    // Fórmula derivada: x = (S - B * N) / (A - B)
    
    long long numerator = S - (B * N);
    long long denominator = A - B;

    // --- PASO 2: Verificar si existe una solución entera ---
    // Si la división no es exacta (el resto no es 0), no hay solución.
    // También manejamos el caso hipotético A == B, aunque el problema dice A != B.
    if (denominator == 0 || numerator % denominator != 0) {
        cout << -1 << endl;
        return;
    }

    // Calculamos el valor candidato para x
    long long x = numerator / denominator;

    // --- PASO 3: Verificar restricciones lógicas ---
    // x debe ser positivo y no puede exceder el total de billetes N.
    // (Si x > N, implicaría que 'y' es negativo, lo cual es imposible).
    if (x >= 0 && x <= N) {
        cout << x << endl;
    } else {
        // Matemáticamente tiene solución, pero físicamente es imposible
        // (ej. requiere billetes negativos).
        cout << -1 << endl;
    }
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}