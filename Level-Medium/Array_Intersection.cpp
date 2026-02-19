/**
 * SOLUCIÓN: Intersección de Arreglos (Array Intersection)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Dados dos arreglos, encontrar sus elementos comunes.
 * Si un número aparece 'x' veces en el primer arreglo y 'y' veces en el segundo,
 * debe aparecer exactamente min(x, y) veces en el resultado.
 *
 * ESTRATEGIA (Hash Map - O(N1 + N2)):
 * Como se nos exige una solución en tiempo lineal, usaremos un diccionario
 * (unordered_map en C++) para contar las frecuencias de los elementos.
 *
 * ALGORITMO:
 * 1. CONSTRUIR EL MAPA DE FRECUENCIAS:
 * Recorremos el PRIMER arreglo y guardamos cuántas veces aparece cada número.
 * - Clave (Key): El número.
 * - Valor (Value): Su frecuencia (conteo).
 * * Complejidad: O(N1).
 *
 * 2. BUSCAR INTERSECCIONES:
 * Recorremos el SEGUNDO arreglo número por número.
 * - Si el número actual existe en nuestro mapa Y su conteo es mayor a 0:
 * a) Lo agregamos a nuestro arreglo de resultados (es una intersección válida).
 * b) RESTAMOS 1 a su conteo en el mapa. Esto es crucial para cumplir
 * con la regla de min(x, y). Si ya "gastamos" una coincidencia, 
 * no podemos volver a usarla a menos que el primer arreglo tuviera más copias.
 * * Complejidad: O(N2).
 *
 * COMPLEJIDAD FINAL:
 * Tiempo: O(N1 + N2) - Porque recorrer arreglos y consultar un unordered_map toma O(1) en promedio.
 * Espacio: O(N1) - Para almacenar las frecuencias del primer arreglo en el mapa.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Función que calcula y retorna la intersección de dos arreglos
vector<int> arrayIntersection(const vector<int>& a, const vector<int>& b) {
    // Mapa para guardar las frecuencias de los elementos del arreglo 'a'
    unordered_map<int, int> conteo_a;
    
    // 1. Llenar el mapa con el primer arreglo
    for (int num : a) {
        conteo_a[num]++;
    }

    vector<int> interseccion;

    // 2. Buscar coincidencias con el segundo arreglo
    for (int num : b) {
        // Buscamos si el número está en el mapa y si aún tenemos "copias disponibles"
        if (conteo_a[num] > 0) {
            // ¡Es una coincidencia! Lo agregamos al resultado
            interseccion.push_back(num);
            
            // Consumimos una copia restando 1 a su frecuencia
            conteo_a[num]--;
        }
    }

    return interseccion;
}

int main() {
    // Optimización estándar para acelerar la entrada/salida en C++
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N1, N2;
    // Leer los tamaños de ambos arreglos
    if (!(cin >> N1 >> N2)) return 0;

    vector<int> array1(N1);
    for (int i = 0; i < N1; ++i) {
        cin >> array1[i];
    }

    vector<int> array2(N2);
    for (int i = 0; i < N2; ++i) {
        cin >> array2[i];
    }

    // Llamamos a nuestra función principal
    vector<int> resultado = arrayIntersection(array1, array2);

    // Formato de salida requerido por el problema:
    // Primera línea: Tamaño del arreglo resultante
    cout << resultado.size() << "\n";
    
    // Segunda línea: Los elementos del arreglo resultante separados por espacio
    for (int i = 0; i < resultado.size(); ++i) {
        cout << resultado[i] << (i == resultado.size() - 1 ? "" : " ");
    }
    cout << "\n";

    return 0;
}