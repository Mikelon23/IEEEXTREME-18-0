/**
 * Solución para: Longest Parenthesised Substring
 * Lenguaje: C++
 *
 * -----------------------------------------------------------------------------
 * EXPLICACIÓN DEL ALGORITMO (ENFOQUE DE DOS PASADAS / TWO-PASS)
 * -----------------------------------------------------------------------------
 *
 * OBJETIVO:
 * Encontrar la subcadena contigua más larga que tenga paréntesis correctamente balanceados.
 * Si no existe ninguna, retornar -1.
 *
 * PROBLEMA CON EL ENFOQUE INGENUO:
 * Simplemente contar paréntesis abiertos y cerrados no es suficiente, porque
 * una cadena como ")(()" tiene 2 abiertos y 2 cerrados, pero no es válida.
 * El orden importa estrictamente.
 *
 * LÓGICA DE LA SOLUCIÓN O(N):
 * Para resolver esto en tiempo lineal O(len(S)) y sin usar memoria extra excesiva (como una pila),
 * podemos recorrer la cadena dos veces:
 *
 * 1. DE IZQUIERDA A DERECHA (Left to Right scan):
 * - Mantenemos contadores para '(' (izquierda) y ')' (derecha).
 * - Avanzamos por la cadena:
 * a) Si izquierda == derecha: Hemos encontrado una subcadena válida cerrada.
 * Calculamos su longitud (2 * derecha) y actualizamos nuestro máximo.
 * b) Si derecha > izquierda: La cadena es inválida. Ejemplo: "())".
 * En este punto, no importa lo que venga después, el prefijo actual ya se rompió.
 * Reiniciamos ambos contadores a 0.
 * - LIMITACIÓN: Este escaneo falla si hay paréntesis de apertura extra que nunca se cierran.
 * Ejemplo: "(()". Aquí izq=2, der=1. Nunca son iguales, el algoritmo diría longitud 0,
 * pero la respuesta correcta es 2 por el "()" interno.
 *
 * 2. DE DERECHA A IZQUIERDA (Right to Left scan):
 * - Hacemos lo mismo pero recorriendo la cadena al revés para solucionar la limitación anterior.
 * - Contamos '(' y ')'.
 * - Si izquierda == derecha: Actualizamos el máximo.
 * - Si izquierda > derecha: La cadena es inválida (hay demasiados abiertos mirando desde el final).
 * Reiniciamos contadores.
 *
 * COMPLEJIDAD:
 * - Tiempo: O(N) porque recorremos la cadena 2 veces (2N sigue siendo lineal).
 * - Memoria: O(1) variables simples, sin estructuras de datos complejas.
 */

#include <iostream>
#include <string>
#include <algorithm> // Para std::max

using namespace std;

// Función principal de lógica
int longestParenthesisedSubstring(string s) {
    int n = s.length();
    int max_len = 0; // Almacena la longitud máxima encontrada

    // ---------------------------------------------------------
    // PASO 1: Escaneo de Izquierda a Derecha
    // Detecta cadenas válidas, pero es sensible a excesos de ')'
    // ---------------------------------------------------------
    int open = 0;  // Contador de paréntesis de apertura '('
    int close = 0; // Contador de paréntesis de cierre ')'

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            open++;
        } else {
            close++;
        }

        // Caso A: Equilibrio encontrado
        // Tenemos la misma cantidad de abiertos y cerrados.
        // Es una subcadena válida candidata.
        if (open == close) {
            max_len = max(max_len, 2 * close);
        }
        // Caso B: Cadena rota
        // Si hay más cerrados que abiertos (ej: "())"), la subcadena actual
        // ya no puede ser válida. Reiniciamos contadores para empezar de nuevo
        // desde el siguiente caracter.
        else if (close > open) {
            open = 0;
            close = 0;
        }
    }

    // ---------------------------------------------------------
    // PASO 2: Escaneo de Derecha a Izquierda
    // Detecta cadenas válidas, pero es sensible a excesos de '('
    // Necesario para casos como "((()" donde el paso 1 falla.
    // ---------------------------------------------------------
    open = 0;
    close = 0; // Reiniciamos contadores

    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '(') {
            open++;
        } else {
            close++;
        }

        // Caso A: Equilibrio encontrado
        if (open == close) {
            max_len = max(max_len, 2 * open);
        }
        // Caso B: Cadena rota (Inverso al paso 1)
        // Si hay más abiertos que cerrados mirando desde el final,
        // la cadena es inválida. Reiniciamos.
        else if (open > close) {
            open = 0;
            close = 0;
        }
    }

    // REQUISITO DEL EJERCICIO:
    // "If there is no solution return -1"
    // Si max_len sigue siendo 0, significa que no hallamos ninguna subcadena válida.
    if (max_len == 0) {
        return -1;
    }

    return max_len;
}

int main() {
    // Optimización de E/S para C++ (habitual en programación competitiva)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    // Leemos la cadena de entrada desde la consola
    if (cin >> s) {
        // Ejecutamos la función e imprimimos el resultado
        cout << longestParenthesisedSubstring(s) << endl;
    }

    return 0;
}