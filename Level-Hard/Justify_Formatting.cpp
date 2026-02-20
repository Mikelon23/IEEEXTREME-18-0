/**
 * Solución para: Justify Formatting
 * Lenguaje: C++
 *
 * -----------------------------------------------------------------------------
 * EXPLICACIÓN DEL ALGORITMO (EMPAQUETADO VORAZ Y DISTRIBUCIÓN DE ESPACIOS)
 * -----------------------------------------------------------------------------
 *
 * OBJETIVO:
 * Tomar una lista de N palabras y organizarlas en líneas de longitud exacta K.
 * Se debe aplicar justificación completa, salvo a la última línea (que va 
 * alineada a la izquierda). Los espacios sobrantes se distribuyen
 * equitativamente y, si sobra, se asignan a los huecos de la izquierda.
 *
 * LÓGICA DE LA SOLUCIÓN:
 * El problema se divide en dos fases principales por cada línea que armamos:
 *
 * 1. FASE DE EMPAQUETADO (¿Cuántas palabras caben?):
 * - Usamos un enfoque "Greedy" (Voraz). Desde nuestra posición actual, 
 * intentamos añadir tantas palabras como sea posible en la línea.
 * - Una palabra cabe si: 
 * (Longitud actual de caracteres) + (Longitud de la nueva palabra) + 
 * (Espacios mínimos requeridos entre palabras) <= K.
 *
 * 2. FASE DE JUSTIFICACIÓN (¿Cómo repartimos los espacios?):
 * - Una vez que sabemos qué palabras van en la línea, calculamos cuántos 
 * espacios en blanco TOTALES necesitamos agregar: 
 * Espacios Totales = K - (Suma de las longitudes de las palabras de la línea).
 * * - CASO A: Es la ÚLTIMA LÍNEA o la línea tiene UNA SOLA PALABRA.
 * Regla: Alineación a la izquierda.
 * Solución: Ponemos exactamente 1 espacio entre cada palabra y luego 
 * rellenamos el final de la cadena con espacios hasta alcanzar la longitud K.
 *
 * - CASO B: Líneas normales (Justificación completa).
 * Regla: Distribuir los 'Espacios Totales' en los 'Huecos' entre palabras.
 * - Número de huecos = (Cantidad de palabras en la línea) - 1.
 * - Espacios Base por hueco = Espacios Totales / Número de huecos.
 * - Espacios Extra (el residuo) = Espacios Totales % Número de huecos.
 * Solución: Agregamos los 'Espacios Base' a todos los huecos, pero a los 
 * primeros 'Espacios Extra' huecos (de izquierda a derecha) les sumamos 
 * 1 espacio adicional.
 *
 * COMPLEJIDAD:
 * - Tiempo: O(N * K), donde N es la cantidad de palabras y K la longitud de 
 * la línea. Cada palabra se visita para agruparla y luego para construir el
 * string resultante, lo cual es muy eficiente y cumple holgadamente el límite.
 * - Memoria: O(N * K) para almacenar el texto justificado final resultante.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> justifyFormatting(int k, const vector<string>& words) {
    vector<string> result;
    int n = words.size();
    int i = 0; // Puntero a la palabra actual

    while (i < n) {
        // -----------------------------------------------------------------
        // PASO 1: Descubrir cuántas palabras caben en la línea actual
        // -----------------------------------------------------------------
        int j = i;
        int current_words_length = 0; // Suma de los caracteres (sin espacios)
        
        // Mientras no nos pasemos de las palabras totales y las palabras
        // más los espacios mínimos obligatorios quepan en K
        while (j < n && current_words_length + words[j].length() + (j - i) <= k) {
            current_words_length += words[j].length();
            j++;
        }

        // Las palabras que formarán esta línea van desde el índice 'i' hasta 'j - 1'
        int num_words_on_line = j - i;
        string line = "";

        // -----------------------------------------------------------------
        // PASO 2: Formatear la línea construida
        // -----------------------------------------------------------------
        
        // CASO A: Es la última línea de todo el texto, o solo cabe 1 palabra
        if (j == n || num_words_on_line == 1) {
            for (int w = i; w < j; w++) {
                line += words[w];
                // Ponemos un solo espacio entre palabras
                if (w < j - 1) {
                    line += " ";
                }
            }
            // Rellenamos con espacios al final para cumplir con la longitud K
            while (line.length() < k) {
                line += " ";
            }
        } 
        // CASO B: Justificación completa estándar
        else {
            int total_spaces = k - current_words_length;
            int num_gaps = num_words_on_line - 1; // Cantidad de huecos entre palabras
            
            // ¿Cuántos espacios tocan equitativamente por hueco?
            int base_spaces = total_spaces / num_gaps;
            // ¿Cuántos espacios sobran y deben ir a la izquierda?
            int extra_spaces = total_spaces % num_gaps;

            for (int w = i; w < j; w++) {
                line += words[w];
                
                // Si no es la última palabra de la línea, le agregamos espacios
                if (w < j - 1) {
                    // Si este hueco es uno de los primeros 'extra_spaces', lleva +1
                    int spaces_to_add = base_spaces + (w - i < extra_spaces ? 1 : 0);
                    line.append(spaces_to_add, ' '); // Añade 'spaces_to_add' espacios
                }
            }
        }

        // Guardamos la línea formateada y avanzamos 'i' a la siguiente palabra
        result.push_back(line);
        i = j; 
    }

    return result;
}

int main() {
    // Optimización de I/O para programación competitiva
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    // Leemos N (cantidad de palabras) y K (límite de línea)
    if (cin >> n >> k) {
        vector<string> words(n);
        
        // Leemos cada palabra
        for (int i = 0; i < n; i++) {
            cin >> words[i];
        }

        // Ejecutamos la función de justificación
        vector<string> justified_text = justifyFormatting(k, words);
        
        // Imprimimos el resultado línea por línea
        for (const string& line : justified_text) {
            cout << line << "\n";
        }
    }

    return 0;
}