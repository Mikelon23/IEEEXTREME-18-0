/**
 * Solución para: Palindrome Creation
 * Lenguaje: C++
 *
 * -----------------------------------------------------------------------------
 * EXPLICACIÓN DEL ALGORITMO (KMP Y ARREGLO LPS)
 * -----------------------------------------------------------------------------
 *
 * OBJETIVO:
 * Encontrar el número mínimo de caracteres que debemos agregar al principio o
 * al final de una cadena S para convertirla en un palíndromo en tiempo O(N).
 *
 * LÓGICA DE LA SOLUCIÓN O(N):
 * 1. Si agregamos caracteres al PRINCIPIO de S para hacerla palíndromo,
 * la cantidad mínima de caracteres a agregar será:
 * Longitud(S) - Longitud_del_Prefijo_Palindrómico_Más_Largo(S).
 * Ejemplo: S = "abac". El prefijo palindrómico más largo es "aba" (long. 3).
 * Los caracteres no balanceados son "c" (longitud 1). Agregando "c" al inicio
 * obtenemos "cabac" (1 caracter agregado).
 *
 * 2. Si agregamos caracteres al FINAL de S, la cantidad mínima a agregar es:
 * Longitud(S) - Longitud_del_Sufijo_Palindrómico_Más_Largo(S).
 * Ejemplo: S = "xzz". El sufijo palindrómico más largo es "zz" (long. 2).
 * Los caracteres no balanceados son "x" (longitud 1). Agregando "x" al final
 * obtenemos "xzzx" (1 caracter agregado).
 *
 * 3. Por lo tanto, el problema se reduce a encontrar el máximo entre el
 * prefijo palindrómico más largo y el sufijo palindrómico más largo.
 * La respuesta final será: Longitud(S) - max(prefijo_max, sufijo_max).
 *
 * 4. ¿Cómo hallar estos prefijos y sufijos en tiempo lineal O(N)?
 * Utilizamos la función de prefijos (Arreglo LPS - Longest Prefix Suffix)
 * del algoritmo KMP.
 *
 * - Para el PREFIJO palindrómico más largo:
 * Creamos una cadena: temp = S + "#" + Reverso(S)
 * Calculamos el arreglo LPS. El último valor del arreglo nos dirá la 
 * longitud del mayor prefijo de S que coincide con el inicio de Reverso(S), 
 * lo cual es exactamente el prefijo palindrómico más largo.
 *
 * - Para el SUFIJO palindrómico más largo:
 * Creamos una cadena: temp = Reverso(S) + "#" + S
 * Calculamos su arreglo LPS. El último valor nos dará el sufijo
 * palindrómico más largo.
 *
 * COMPLEJIDAD:
 * - Tiempo: O(N), ya que invertir la cadena, concatenar y calcular el arreglo
 * LPS toman tiempo estrictamente lineal respecto al tamaño de S.
 * - Memoria: O(N) para almacenar las cadenas temporales y el arreglo LPS, lo
 * cual es óptimo y respeta holgadamente el límite de 128 MB.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Función auxiliar para calcular el arreglo LPS (Longest Prefix Suffix) de KMP
vector<int> computeLPS(const string& s) {
    int n = s.length();
    vector<int> lps(n, 0);
    int len = 0; // Longitud del prefijo-sufijo más largo anterior
    int i = 1;

    // Calculamos el LPS en O(N)
    while (i < n) {
        if (s[i] == s[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1]; // Retrocedemos usando los cálculos previos
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int minCharsToPalindrome(string s) {
    int n = s.length();
    if (n <= 1) return 0;

    // Obtenemos la cadena invertida en O(N)
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());

    // 1. Encontrar el PREFIJO palindrómico más largo
    // El '#' actúa como separador para asegurar que un prefijo no se expanda
    // más allá de la longitud original de 's'.
    string temp_prefix = s + "#" + rev_s;
    vector<int> lps_prefix = computeLPS(temp_prefix);
    int longest_palindromic_prefix = lps_prefix.back();

    // 2. Encontrar el SUFIJO palindrómico más largo
    string temp_suffix = rev_s + "#" + s;
    vector<int> lps_suffix = computeLPS(temp_suffix);
    int longest_palindromic_suffix = lps_suffix.back();

    // 3. Tomar el mejor escenario (el que nos obligue a agregar menos letras)
    int max_palindromic_part = max(longest_palindromic_prefix, longest_palindromic_suffix);

    // La respuesta es la cantidad de letras que no forman parte de ese palíndromo base
    return n - max_palindromic_part;
}

int main() {
    // Optimización de I/O para programación competitiva
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    // Leemos la cadena S
    if (cin >> s) {
        // Ejecutamos la función e imprimimos el resultado
        cout << minCharsToPalindrome(s) << "\n";
    }

    return 0;
}