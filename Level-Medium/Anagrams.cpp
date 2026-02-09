/**
 * SOLUCIÓN: Anagramas (Largest Subset of Equivalent Words)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Nos dan una lista de palabras y debemos agruparlas si son "equivalentes".
 * Dos palabras son equivalentes si tienen las mismas letras (son anagramas).
 * Ejemplo: "caller", "cellar", "recall" -> Todas usan 1 'a', 1 'c', 1 'e', 2 'l', 1 'r'.
 *
 * ESTRATEGIA (Canonical Representation):
 * Para que la computadora sepa que "cats" y "acts" son lo mismo, necesitamos
 * convertirlas a una forma idéntica.
 * EL TRUCO: Si ordenamos alfabéticamente las letras de cualquier anagrama,
 * obtendremos siempre la misma cadena.
 * - "caller" ordenado -> "acellr"
 * - "cellar" ordenado -> "acellr"
 * - "recall" ordenado -> "acellr"
 *
 * Esta cadena ordenada ("acellr") será nuestra "clave" (key) o "firma".
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>    // Necesario para std::sort
#include <unordered_map> // Usamos un mapa hash para contar eficientemente

using namespace std;

int main() {
    // -----------------------------------------------------------------
    // OPTIMIZACIÓN DE ENTRADA/SALIDA (I/O)
    // -----------------------------------------------------------------
    // En programación competitiva (C++), 'cin' y 'cout' pueden ser lentos
    // porque se sincronizan con las librerías de C. Desactivamos esto
    // para que la lectura de datos grandes sea rápida.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    // Leemos el número de palabras.
    // Verificamos si la lectura fue exitosa (buena práctica).
    if (!(cin >> N)) return 0;

    // -----------------------------------------------------------------
    // ESTRUCTURA DE DATOS: HASH MAP (Diccionario)
    // -----------------------------------------------------------------
    // Clave (Key): string -> La versión ordenada de la palabra (la "firma").
    // Valor (Value): int -> Cuántas veces hemos visto esa firma.
    //
    // Usamos unordered_map porque las operaciones son en promedio O(1),
    // lo cual es muy rápido para 100,000 caracteres.
    unordered_map<string, int> conteo_anagramas;

    // Variable para rastrear el grupo más grande encontrado hasta el momento.
    int maximo_grupo = 0;

    // Procesamos cada palabra una por una
    for (int i = 0; i < N; ++i) {
        string palabra_original;
        cin >> palabra_original;

        // 1. Copiamos la palabra para no perder la original (aunque aquí no la necesitamos imprimir,
        //    es buena práctica conceptual).
        string firma = palabra_original;

        // 2. ORDENAMIENTO (El núcleo del algoritmo)
        // Convertimos la palabra en su "forma canónica".
        // Ejemplo: entra "parrots", sale "aoprrst".
        // Complejidad: O(K log K) donde K es la longitud de la palabra.
        // Dado que las palabras son cortas, esto es extremadamente rápido.
        sort(firma.begin(), firma.end());

        // 3. ACTUALIZACIÓN DEL CONTEO
        // Buscamos esta 'firma' en el mapa y le sumamos 1.
        // Si no existía, C++ la crea automáticamente con valor 0 y luego suma 1.
        conteo_anagramas[firma]++;

        // 4. MANTENER EL MÁXIMO
        // En lugar de recorrer todo el mapa al final para buscar el mayor,
        // comparamos el valor actual que acabamos de actualizar con nuestro récord.
        if (conteo_anagramas[firma] > maximo_grupo) {
            maximo_grupo = conteo_anagramas[firma];
        }
    }

    // Imprimimos el resultado final
    cout << maximo_grupo << endl;

    return 0;
}