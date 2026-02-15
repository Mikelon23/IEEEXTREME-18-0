/**
 * SOLUCIÓN: Look and Say
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. Definición de la secuencia:
 * - Comienza con "1".
 * - Cada término siguiente se genera "leyendo en voz alta" el término anterior.
 * - Se agrupan los dígitos consecutivos iguales y se dice "cantidad" + "dígito".
 * Ejemplo: "21" se lee como "un 2, luego un 1" -> "1211".
 *
 * 2. Objetivo:
 * - Dado un entero N, encontrar el N-ésimo término de esta secuencia.
 *
 * 3. Estrategia de Implementación:
 * - Comenzamos con la cadena base `current = "1"`.
 * - Necesitamos simular el proceso de transformación N-1 veces.
 * - En cada paso, recorremos la cadena actual para construir la siguiente:
 * a) Identificamos un grupo de caracteres idénticos consecutivos.
 * b) Contamos cuántos son (ej. tres '1').
 * c) Añadimos a la nueva cadena el contador seguido del carácter (ej. "31").
 * d) Repetimos hasta terminar la cadena actual.
 *
 * ======================================================================================
 * COMPLEJIDAD
 * ======================================================================================
 * - La longitud de la secuencia crece exponencialmente (aproximadamente x1.3 cada paso).
 * - El algoritmo recorre la cadena generada una sola vez por nivel.
 * - Complejidad temporal: Proporcional a la longitud total de la cadena final.
 * - Para N <= 50-60, es computacionalmente viable en < 1000ms.
 */

#include <iostream>
#include <string>

using namespace std;

/**
 * Función: getNextTerm
 * --------------------
 * Recibe un término de la secuencia (ej. "1211") y genera el siguiente (ej. "111221").
 */
string getNextTerm(const string& s) {
    string next_term = "";
    // Optimización: Reservamos memoria aproximada para evitar realocaciones constantes.
    // La nueva cadena suele ser más larga, así que reservar s.length() * 2 es seguro.
    next_term.reserve(s.length() * 2);

    // Iteramos a través de la cadena actual
    for (int i = 0; i < s.length(); ++i) {
        int count = 1;

        // Bucle interno: Mientras el siguiente carácter exista y sea igual al actual
        while (i + 1 < s.length() && s[i] == s[i+1]) {
            count++;
            i++; // Saltamos el índice porque ya contamos este carácter
        }

        // Construcción del nuevo término:
        // 1. Agregamos la cantidad de repeticiones.
        next_term += to_string(count);
        // 2. Agregamos el dígito que se repitió.
        next_term += s[i];
    }
    
    return next_term;
}

int main() {
    // Optimización de I/O para velocidad
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (cin >> N) {
        // El primer término de la secuencia siempre es "1"
        string current = "1";

        // Iteramos N-1 veces para llegar al término N-ésimo.
        // Si N=1, el bucle no se ejecuta y se imprime "1".
        for (int i = 1; i < N; ++i) {
            current = getNextTerm(current);
        }

        cout << current << endl;
    }

    return 0;
}