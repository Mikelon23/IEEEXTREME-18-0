/**
 * SOLUCIÓN: Generate Parentheses
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. Objetivo: Generar TODAS las combinaciones de paréntesis válidos para N pares.
 * 2. Entrada: Un entero N (1 <= N <= 12).
 * 3. Salida: Las cadenas deben imprimirse en orden lexicográfico.
 * - Ejemplo N=3: "((()))", "(()())", "(())()", "()(())", "()()()"
 *
 * ======================================================================================
 * ESTRATEGIA: BACKTRACKING (Recursión)
 * ======================================================================================
 * Construiremos la cadena carácter por carácter. En cada paso de la recursión, tenemos
 * dos decisiones posibles: añadir un '(' o añadir un ')'.
 *
 * REGLAS PARA QUE SEA VÁLIDO:
 * 1. Solo podemos añadir un '(' si aún no hemos usado los N disponibles.
 * (open_count < N)
 * 2. Solo podemos añadir un ')' si hay algún '(' abierto que necesite cerrarse.
 * Es decir, si tenemos más abiertos que cerrados actualmente.
 * (close_count < open_count)
 *
 * ORDEN LEXICOGRÁFICO:
 * El problema pide orden lexicográfico. En ASCII, '(' (40) vale menos que ')' (41).
 * Por lo tanto, para obtener la salida ordenada automáticamente, nuestro algoritmo
 * siempre debe intentar poner primero un '(' (si es válido) antes de intentar poner
 * un ')' en la recursión.
 *
 * COMPLEJIDAD:
 * El número de soluciones es el número de Catalan (C_n). Para N=12, es aprox 200,000.
 * Nuestro algoritmo genera cada solución válida exactamente una vez. Es muy eficiente.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Función recursiva para generar los paréntesis.
 * * @param current: La cadena que estamos construyendo en esta rama de recursión.
 * @param open:   Número de paréntesis de apertura '(' usados hasta ahora.
 * @param close:  Número de paréntesis de cierre ')' usados hasta ahora.
 * @param n:      El número total de pares requeridos (meta).
 */
void solve_parentheses(string current, int open, int close, int n) {
    // --- CASO BASE ---
    // Si la cadena tiene longitud 2*N, significa que hemos usado todos los paréntesis
    // necesarios (N abiertos y N cerrados) de forma válida.
    if (current.length() == 2 * n) {
        cout << current << "\n";
        return;
    }

    // --- RAMA 1: Intentar agregar '(' ---
    // Condición: Solo si no hemos gastado todos los '(' disponibles.
    // Hacemos esto PRIMERO para respetar el orden lexicográfico.
    if (open < n) {
        solve_parentheses(current + "(", open + 1, close, n);
    }

    // --- RAMA 2: Intentar agregar ')' ---
    // Condición: Solo si hay paréntesis abiertos pendientes de cerrar.
    // Si 'close' alcanza a 'open', no podemos cerrar más o la cadena sería inválida
    // (ejemplo inválido: "())").
    if (close < open) {
        solve_parentheses(current + ")", open, close + 1, n);
    }
}

int main() {
    // Optimización de I/O para acelerar la impresión de muchas líneas
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    // Leemos N
    if (cin >> N) {
        // Iniciamos la recursión con:
        // - Cadena vacía ""
        // - 0 abiertos usados
        // - 0 cerrados usados
        solve_parentheses("", 0, 0, N);
    }

    return 0;
}