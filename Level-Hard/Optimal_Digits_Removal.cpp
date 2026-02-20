/**
 * Solución para: Optimal Digits Removal
 * Lenguaje: C++
 *
 * -----------------------------------------------------------------------------
 * EXPLICACIÓN DEL ALGORITMO (ENFOQUE DE 10 PUNTEROS / GREEDY)
 * -----------------------------------------------------------------------------
 *
 * OBJETIVO:
 * Dado un número de N dígitos como cadena, eliminar exactamente K dígitos para
 * maximizar el número resultante, en tiempo O(N), memoria O(1) y sin modificar
 * la cadena original (tratándola como un flujo o "stream" de lectura).
 *
 * ¿POR QUÉ NO USAR UN STACK (PILA)?
 * La solución tradicional utiliza un Stack (o string de resultado dinámico) 
 * donde si el dígito actual es mayor que el tope del stack y aún podemos eliminar 
 * (K > 0), sacamos el elemento del stack. Sin embargo, un stack requiere O(N) 
 * memoria en el peor de los casos, violando la restricción de O(1) memoria.
 *
 * LÓGICA DE LA SOLUCIÓN O(N) TIEMPO Y O(1) MEMORIA:
 * 1. Sabemos que el número final tendrá exactamente (N - K) dígitos.
 * 2. Para maximizar el número resultante, siempre queremos que el primer dígito
 * sea lo más grande posible (idealmente un '9').
 * 3. El primer dígito debe ser elegido de los primeros K + 1 caracteres de la 
 * cadena. ¿Por qué? Porque si elegimos un dígito más allá del índice K, 
 * tendríamos que descartar más de K caracteres antes de él, lo cual no está permitido.
 * 4. Para mantener el tiempo O(N) y memoria O(1), mantenemos un arreglo de 10
 * punteros (uno para cada dígito del 0 al 9). Estos punteros rastrean la 
 * *próxima* aparición de cada dígito.
 * 5. Iteramos de mayor a menor dígito (9 al 0) buscando si su próxima aparición
 * está dentro de nuestra "ventana de descartes permitidos".
 * 6. Si lo encontramos, lo imprimimos directamente a la salida estándar, restamos 
 * del K restante los caracteres que tuvimos que "saltar", y ajustamos nuestro 
 * nuevo punto de partida.
 * * COMPLEJIDAD:
 * - Tiempo: O(N). Aunque hay bucles anidados, cada uno de los 10 punteros avanza
 * hacia adelante y NUNCA retrocede. Por lo tanto, el interior del bucle "while"
 * se ejecuta como máximo N veces por cada dígito a lo largo de TODO el programa. 
 * Total de operaciones: 10 * N = O(N).
 * - Memoria: O(1). Solo almacenamos variables primitivas (n, k, start) y un 
 * arreglo estático de 10 enteros (next_idx). No duplicamos la cadena.
 */

#include <iostream>
#include <string>

using namespace std;

void optimalDigitsRemoval(int n, int k, const string& s) {
    // Calculamos cuántos dígitos tendrá nuestro número final
    int final_length = n - k; 
    
    // Si debemos eliminar todos los dígitos, no hay nada que imprimir
    if (final_length <= 0) return; 
    
    int start = 0; // Índice de inicio desde donde podemos buscar en este paso
    
    // Arreglo de 10 elementos (Memoria O(1)).
    // next_idx[d] guardará la posición más cercana donde aparece el dígito 'd'
    int next_idx[10] = {0}; 
    
    // Necesitamos seleccionar exactamente 'final_length' dígitos
    for (int i = 0; i < final_length; i++) {
        
        // Optimización: Si k llega a 0, ya no se nos permite eliminar nada más.
        // La única opción es imprimir el resto de la cadena tal como está.
        if (k == 0) {
            for (int j = start; j < n; j++) {
                cout << s[j];
            }
            break; // Terminamos, ya que imprimimos todo lo restante
        }
        
        // Buscamos el dígito más grande posible de forma voraz (del 9 bajando al 0)
        for (int d = 9; d >= 0; d--) {
            
            // Actualizamos el puntero para que no busque en índices que ya 
            // quedaron atrás en pasos anteriores
            if (next_idx[d] < start) {
                next_idx[d] = start;
            }
            
            // Avanzamos el puntero hasta encontrar el dígito 'd' o llegar al final
            while (next_idx[d] < n && s[next_idx[d]] - '0' != d) {
                next_idx[d]++;
            }
            
            // Verificamos si encontramos el dígito 'd' DENTRO de nuestra ventana permitida.
            // La ventana permitida es poder saltarnos a lo sumo 'k' caracteres.
            // Los caracteres saltados son (next_idx[d] - start).
            if (next_idx[d] < n && (next_idx[d] - start) <= k) {
                
                // Imprimimos el dígito encontrado (directo al output stream)
                cout << d;
                
                // Restamos del "presupuesto de eliminación" los caracteres que saltamos
                k -= (next_idx[d] - start);
                
                // El nuevo inicio para la siguiente búsqueda es justo después del dígito impreso
                start = next_idx[d] + 1;
                
                // Como ya encontramos el dígito máximo válido para esta posición,
                // rompemos la iteración de dígitos y buscamos la siguiente posición
                break; 
            }
        }
    }
    cout << "\n";
}

int main() {
    // Optimización de I/O para programación competitiva
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    // Leemos N y K
    if (cin >> n >> k) {
        string s;
        // Leemos el gran número como string
        cin >> s;
        
        // Ejecutamos la función
        optimalDigitsRemoval(n, k, s);
    }
    
    return 0;
}