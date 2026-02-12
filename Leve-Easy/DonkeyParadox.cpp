/**
 * SOLUCIÓN: Donkey Paradox
 * LENGUAJE: C++
 * * ======================================================================================
 * ANÁLISIS DEL PROBLEMA
 * ======================================================================================
 * 1. El escenario es una cuadrícula de N x M.
 * 2. Hay dos pajares (haystacks) en posiciones fijas: (r1, c1) y (r2, c2).
 * 3. El burro muere de hambre si se encuentra en una celda donde la distancia al
 * pajar 1 es IGUAL a la distancia al pajar 2.
 * 4. Movimiento: El burro solo puede moverse en 4 direcciones (arriba, abajo, izq, der).
 * 5. Distancia: Dado que solo se mueve en estas direcciones, la distancia más corta
 * entre dos puntos (r_a, c_a) y (r_b, c_b) en una cuadrícula es la 
 * DISTANCIA DE MANHATTAN.
 * * Fórmula de Manhattan: d = |r_a - r_b| + |c_a - c_b|
 * * ======================================================================================
 * ESTRATEGIA DE RESOLUCIÓN
 * ======================================================================================
 * - Los límites de N y M son pequeños (hasta 200).
 * - Una solución de fuerza bruta recorriendo todas las celdas de la matriz es O(N * M).
 * - Con N, M = 200, el total de celdas es 40,000, lo cual es muy eficiente para 1000ms.
 * - Para cada celda (i, j):
 * a) Calcular d1 = |i - r1| + |j - c1|
 * b) Calcular d2 = |i - r2| + |j - c2|
 * c) Si d1 == d2, incrementar el contador.
 */

#include <iostream>
#include <cmath> // Para std::abs

using namespace std;

/**
 * Función: calculateManhattan
 * --------------------------
 * Calcula la distancia de Manhattan entre dos celdas (r1, c1) y (r2, c2).
 */
int calculateManhattan(int r1, int c1, int r2, int c2) {
    // La distancia es la suma de las diferencias absolutas de sus coordenadas.
    return abs(r1 - r2) + abs(c1 - c2);
}

int main() {
    // Optimización de flujo de entrada/salida.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    int r1, c1, r2, c2;
    // Leer coordenadas del primer pajar.
    cin >> r1 >> c1;
    // Leer coordenadas del segundo pajar.
    cin >> r2 >> c2;

    int starvingCells = 0;

    /**
     * RECORRIDO DE LA MATRIZ
     * Iteramos sobre cada celda (i, j) de la cuadrícula.
     * Nota: En problemas de matrices, a veces las coordenadas empiezan en 1.
     * Los ejemplos de la imagen muestran coordenadas como (3,1), (4,5), etc.
     * Por lo tanto, usaremos un rango de 1 a N y 1 a M.
     */
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            
            // Calculamos la distancia de la celda actual al primer pajar.
            int d1 = calculateManhattan(i, j, r1, c1);
            
            // Calculamos la distancia de la celda actual al segundo pajar.
            int d2 = calculateManhattan(i, j, r2, c2);

            // CONDICIÓN DE PARADOJA:
            // Si las distancias son exactamente iguales, el burro no puede decidir.
            if (d1 == d2) {
                starvingCells++;
            }
        }
    }

    // Imprimir el resultado final.
    cout << starvingCells << endl;

    return 0;
}