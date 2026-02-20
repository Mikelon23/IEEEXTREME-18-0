/**
 * Solución para: All BST Preorders
 * Lenguaje: C++
 *
 * -----------------------------------------------------------------------------
 * EXPLICACIÓN DEL ALGORITMO (BACKTRACKING CON PODA PERFECTA)
 * -----------------------------------------------------------------------------
 *
 * OBJETIVO:
 * Generar todos los recorridos en preorden válidos de un Árbol Binario de
 * Búsqueda (BST) que contiene llaves del 1 al N, en orden lexicográfico.
 *
 * RESTRICCIONES:
 * - Memoria O(N): No podemos guardar todos los recorridos, ni crear 
 * múltiples arreglos en cada paso de la recursión.
 * - Tiempo O(output): Significa que el tiempo total de ejecución debe ser 
 * proporcional a la cantidad de secuencias válidas. Por lo tanto, ¡NO PODEMOS 
 * explorar combinaciones inválidas (caminos sin salida o "dead ends")!
 *
 * PROPIEDAD CLAVE DEL PREORDEN DE UN BST:
 * Un arreglo es un preorden válido de un BST si y solo si podemos simular 
 * su construcción usando una pila (stack). Si al procesar un número 'x' 
 * este es mayor que el tope de la pila, significa que 'x' es hijo derecho 
 * de algún ancestro. Retiramos elementos de la pila, y el último elemento 
 * retirado se convierte en el "límite inferior" (lower_bound) estricto para 
 * TODOS los futuros elementos. Si en el futuro aparece un elemento menor 
 * a este límite, la secuencia es inválida.
 *
 * LÓGICA DE LA PODA:
 * Queremos añadir un número 'x' a nuestra secuencia parcial. 
 * 1. Mantenemos el conjunto de números que aún no hemos usado. Sea 
 * 'min_unused' el número más pequeño disponible.
 * 2. Si probamos agregar 'x', simulamos qué pasaría con nuestra pila y 
 * cuál sería el nuevo 'lower_bound'.
 * 3. Si el nuevo 'lower_bound' es MAYOR O IGUAL al número más pequeño que 
 * todavía falta por colocar (el próximo min_unused), entonces es IMPOSIBLE
 * completar la secuencia, porque ese número restante romperá el límite.
 * 4. Por lo tanto, podamos (break) la búsqueda. Como iteramos 'x' en orden 
 * ascendente (del 1 al N), si un 'x' rompe este límite, cualquier número 
 * mayor también lo hará. Esto nos permite un 'break' directo sin 
 * desperdiciar operaciones.
 *
 * COMPLEJIDAD:
 * - Tiempo: O(output). Gracias a la poda perfecta, cada llamada recursiva
 * conduce directamente a una solución válida. El tiempo amortizado es óptimo.
 * - Memoria: O(N). Usamos un vector global como pila y sobreescribimos /
 * restauramos sus elementos en cada paso. No creamos nuevas estructuras de
 * datos durante la recursión.
 */

#include <iostream>
#include <vector>

using namespace std;

int n;
vector<int> seq;      // Almacena la secuencia en preorden actual
vector<bool> used;    // Marca qué números del 1 al N ya están en la secuencia
vector<int> s;        // Funciona como nuestra pila (stack) de memoria O(N)

// Función recursiva de Backtracking
// top_idx: índice del tope actual de nuestra pila 's'
// lower_bound: el límite inferior estricto actual
void generatePreorders(int top_idx, int lower_bound) {
    // Caso Base: Hemos colocado N elementos con éxito
    if (seq.size() == n) {
        // Imprimimos el resultado (garantizado que es válido)
        for (int i = 0; i < n; i++) {
            cout << seq[i] << (i == n - 1 ? "" : " ");
        }
        cout << "\n";
        return;
    }

    // Buscamos el elemento más pequeño que aún no hemos usado
    int min_unused = 1;
    while (min_unused <= n && used[min_unused]) {
        min_unused++;
    }

    // Variables temporales para simular qué pasa en la pila a medida que
    // incrementamos nuestra elección de 'x'
    int current_lower = lower_bound;
    int current_top = top_idx;

    // Iteramos intentando colocar el siguiente número del 1 al N.
    // Iterar en orden ascendente garantiza la salida lexicográfica natural.
    for (int x = 1; x <= n; x++) {
        
        // Simulamos la inserción en el BST. Si 'x' es mayor que el tope,
        // retrocedemos en el árbol (sacamos de la pila) y actualizamos el límite.
        // NOTA: No reiniciamos current_top ni current_lower en cada iteración de 'x'.
        // Como 'x' siempre aumenta, los elementos que debe sacar de la pila 
        // son los mismos y más, lo que amortiza el costo a O(1).
        while (current_top >= 0 && x > s[current_top]) {
            current_lower = s[current_top];
            current_top--;
        }

        if (used[x]) continue;

        // Calculamos cuál será el número mínimo disponible si decidimos usar 'x'
        int next_min_unused = min_unused;
        if (x == min_unused) {
            next_min_unused = x + 1;
            while (next_min_unused <= n && used[next_min_unused]) {
                next_min_unused++;
            }
        }

        // PODA MAESTRA: Si el límite inferior requerido por colocar 'x' es mayor
        // o igual al elemento más pequeño que aún tenemos pendiente por usar,
        // es IMPOSIBLE terminar este BST. 
        // Además, cualquier número mayor que 'x' también exigirá un límite igual
        // o peor. ¡Podemos cancelar todo el resto de este bucle!
        if (current_lower >= next_min_unused) {
            break; 
        }

        // --- Aplicar cambios (Hacer la elección) ---
        seq.push_back(x);
        used[x] = true;
        
        // Guardamos el elemento de la pila que vamos a sobreescribir para
        // mantener la restricción de Memoria O(N) sin clonar vectores.
        int overwritten = s[current_top + 1];
        s[current_top + 1] = x;

        // Llamada recursiva con el nuevo estado
        generatePreorders(current_top + 1, current_lower);

        // --- Revertir cambios (Backtracking puro) ---
        s[current_top + 1] = overwritten;
        used[x] = false;
        seq.pop_back();
    }
}

int main() {
    // Optimización crítica de I/O, sin esto el problema puede exceder el límite 
    // de 1000ms al imprimir grandes cantidades de datos.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (cin >> n) {
        // Pre-alojar memoria para garantizar espacio estricto de O(N)
        seq.reserve(n);
        used.assign(n + 1, false);
        s.assign(n, 0);
        
        // Disparador inicial
        generatePreorders(-1, 0);
    }
    return 0;
}