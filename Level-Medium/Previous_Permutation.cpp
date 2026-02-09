/**
 * SOLUCIÓN: Permutación Previa (Previous Permutation)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Dada una secuencia de números (una permutación), encontrar la permutación
 * que vendría justo antes si las ordenáramos todas alfabéticamente (lexicográficamente).
 *
 * Ejemplo intuitivo:
 * Si tienes [1, 5, 4], el anterior es [1, 4, 5].
 * Si tienes [1, 2, 3], es el más pequeño posible, no hay anterior -> return false.
 *
 * LÓGICA DEL ALGORITMO (O(N)):
 * 1. IDENTIFICAR EL "PUNTO DE QUIEBRE":
 * Recorremos el arreglo de DERECHA a IZQUIERDA. Buscamos el primer par
 * donde el número de la izquierda es MAYOR que el de la derecha (nums[i] > nums[i+1]).
 * Esto indica que el sufijo ya no está en orden ascendente y podemos "reducir" el valor
 * intercambiando nums[i].
 *
 * 2. ENCONTRAR EL SUSTITUTO:
 * Una vez hallado el índice 'i', buscamos a su derecha el número más grande posible
 * que sea MENOR que nums[i]. Queremos reducir nums[i] lo menos posible para
 * estar justo en el paso anterior.
 *
 * 3. INTERCAMBIAR (SWAP):
 * Cambiamos nums[i] con ese sustituto.
 *
 * 4. INVERTIR EL SUFIJO:
 * Después del intercambio, la parte derecha quedó en orden ascendente (el "menor" orden posible).
 * Para que sea la permutación INMEDIATAMENTE ANTERIOR, necesitamos que esa parte
 * esté en su configuración "máxima" (orden descendente). Por eso invertimos el sufijo.
 */

#include <iostream>
#include <vector>
#include <algorithm> // Para std::swap y std::reverse

using namespace std;

// Función que modifica el vector 'p' en su permutación anterior.
// Retorna false si no existe (ya es la menor permutación), true si tuvo éxito.
bool previousPermutation(vector<int>& p) {
    int n = p.size();
    if (n <= 1) return false;

    // PASO 1: Encontrar el primer elemento que rompe el orden ascendente (visto desde la derecha).
    // Buscamos un índice 'i' tal que p[i] > p[i+1].
    // Ejemplo: 2 1 5 3 4 6 7
    // Desde el final: 7>6 (no), 6>4 (no), 4>3 (no), 3<5 (¡SÍ!).
    // El 5 está en la posición 'i', y es mayor que el 3. Ese es nuestro pivote.
    int i = n - 2;
    while (i >= 0 && p[i] <= p[i + 1]) {
        i--;
    }

    // Si i < 0, significa que todo el arreglo es ascendente (ej: 1 2 3 4).
    // Esta es la permutación más pequeña posible, no hay anterior.
    if (i < 0) return false;

    // PASO 2: Encontrar el elemento a la derecha de 'i' para hacer el intercambio.
    // Buscamos el elemento más a la derecha que sea MENOR que p[i].
    // ¿Por qué? Porque queremos bajar el valor de p[i], pero maximizando el resultado.
    int j = n - 1;
    while (p[j] >= p[i]) {
        j--;
    }

    // PASO 3: Intercambiar el pivote con el candidato encontrado.
    // Siguiendo el ejemplo anterior (p[i]=5), encontramos que p[j]=4 es el candidato.
    // Swap(5, 4) -> El arreglo cambia de ...5 3 4... a ...4 3 5...
    swap(p[i], p[j]);

    // PASO 4: Invertir el sufijo.
    // El sufijo (todo lo que está a la derecha de i) actualmente está en orden ascendente
    // (porque así lo recorrimos en el paso 1).
    // Para obtener la permutación PREVIA (la más alta por debajo de la actual),
    // necesitamos que ese sufijo sea lo más grande posible -> Orden Descendente.
    // Simplemente lo invertimos.
    reverse(p.begin() + i + 1, p.end());

    return true;
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<int> p(N);
    for (int i = 0; i < N; ++i) {
        cin >> p[i];
    }

    // Llamamos a nuestra función con la lógica explicada
    if (previousPermutation(p)) {
        // Si retornó true, imprimimos el arreglo modificado
        for (int i = 0; i < N; ++i) {
            cout << p[i] << (i == N - 1 ? "" : " ");
        }
        cout << endl;
    } else {
        // Si retornó false, imprimimos -1
        cout << "-1" << endl;
    }

    return 0;
}