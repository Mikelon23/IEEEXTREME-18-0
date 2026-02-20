/**
 * Solución para: Binary Stable Sort
 * Lenguaje: C++
 *
 * -----------------------------------------------------------------------------
 * EXPLICACIÓN DEL ALGORITMO (DIVIDE AND CONQUER + IN-PLACE ROTATE)
 * -----------------------------------------------------------------------------
 *
 * OBJETIVO:
 * Ordenar a los niños de modo que todos los del equipo 'B' (Blue) estén antes
 * que los del equipo 'R' (Red), conservando el orden original (estabilidad).
 * Todo esto en tiempo O(N log N) y memoria adicional O(1).
 *
 * ¿POR QUÉ NO UN SORT TRADICIONAL O ARREGLOS AUXILIARES?
 * - std::stable_sort toma O(N log^2 N) si no tiene memoria extra, o O(N) memoria.
 * - Usar dos vectores extra (uno para 'B' y otro para 'R') es la solución
 * trivial, pero viola la regla de memoria extra O(1) requerida.
 *
 * LÓGICA DE LA SOLUCIÓN O(N log N) TIEMPO / O(1) MEMORIA:
 * Utilizamos un enfoque de "Divide y Vencerás" combinado con rotaciones:
 * * 1. DIVIDIR:
 * Partimos el arreglo a la mitad de forma recursiva hasta llegar a 
 * sub-arreglos de tamaño 1.
 * * 2. VENCER (Caso Base):
 * Si el sub-arreglo tiene tamaño 1, ya está "ordenado". Retornamos el índice
 * donde empiezan los niños del equipo 'R'.
 * * 3. COMBINAR (El truco principal):
 * Supongamos que ya procesamos la mitad izquierda y la mitad derecha.
 * - Mitad Izquierda quedó:  [ B_izq1, B_izq2 ] y [ R_izq1, R_izq2 ]
 * - Mitad Derecha quedó:    [ B_der1, B_der2 ] y [ R_der1, R_der2 ]
 * * Al unirlas, el arreglo se ve así:
 * [ B_izq1, B_izq2,  R_izq1, R_izq2,  B_der1, B_der2,  R_der1, R_der2 ]
 * |-------------|  |-------------|
 * BLOQUE 1        BLOQUE 2
 * * Para que todos los 'B' queden al principio y todos los 'R' al final sin 
 * perder el orden, solo necesitamos intercambiar el BLOQUE 1 (los 'R' de 
 * la izquierda) con el BLOQUE 2 (los 'B' de la derecha).
 * * Como los bloques pueden tener tamaños diferentes, usamos la función 
 * std::rotate, la cual mueve elementos en un rango usando O(1) memoria 
 * adicional y tiempo lineal proporcional al tamaño de los bloques.
 *
 * COMPLEJIDAD:
 * - Tiempo: En cada nivel de la recursión hacemos rotaciones que suman O(N).
 * Como dividimos a la mitad, hay O(log N) niveles. Total: O(N log N).
 * - Memoria: O(1) de espacio extra, excluyendo la pila de llamadas del sistema 
 * para la recursión (que es O(log N) y permitida en este tipo de restricciones).
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Para std::rotate

using namespace std;

// Estructura para almacenar los datos de cada niño
struct Child {
    string name;
    char team;
};

// Función recursiva que realiza la partición estable
// Recibe el arreglo y los límites [left, right)
// Retorna el índice exacto donde comienza el bloque del equipo 'R'
int stablePartitionInPlace(vector<Child>& arr, int left, int right) {
    // 1. Caso Base: Si el rango tiene 1 o 0 elementos
    if (right - left <= 1) {
        if (left < right && arr[left].team == 'R') {
            return left; // El equipo 'R' empieza aquí mismo
        }
        return right; // No hay equipo 'R', devolvemos el límite superior
    }

    // 2. Dividir: Calculamos el punto medio
    int mid = left + (right - left) / 2;

    // 3. Llamadas recursivas para procesar ambas mitades
    // bound1 será donde empiezan los 'R' en la mitad izquierda
    int bound1 = stablePartitionInPlace(arr, left, mid);
    
    // bound2 será donde empiezan los 'R' en la mitad derecha
    int bound2 = stablePartitionInPlace(arr, mid, right);

    // 4. Combinar:
    // Actualmente el rango [bound1, mid) contiene los 'R' de la izquierda.
    // El rango [mid, bound2) contiene los 'B' de la derecha.
    // Queremos que los 'B' de la derecha pasen antes que los 'R' de la izquierda.
    // std::rotate(inicio, nuevo_inicio, fin) hace exactamente esto en O(N) in-place.
    std::rotate(arr.begin() + bound1, arr.begin() + mid, arr.begin() + bound2);

    // Calculamos el nuevo punto de inicio de los 'R' en este segmento.
    // El bloque 'R' se desplazó a la derecha por la cantidad de 'B' que saltaron.
    // La cantidad de 'B' que saltaron es (bound2 - mid).
    return bound1 + (bound2 - mid);
}

int main() {
    // Optimización de I/O para programación competitiva
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    // Leemos la cantidad de niños
    if (cin >> n) {
        vector<Child> children(n);
        
        // Leemos los N niños (Nombre y Equipo)
        for (int i = 0; i < n; i++) {
            cin >> children[i].name >> children[i].team;
        }

        // Ejecutamos la función. Pasamos el rango [0, n)
        stablePartitionInPlace(children, 0, n);

        // Imprimimos el resultado final
        for (int i = 0; i < n; i++) {
            cout << children[i].name << "\n";
        }
    }

    return 0;
}