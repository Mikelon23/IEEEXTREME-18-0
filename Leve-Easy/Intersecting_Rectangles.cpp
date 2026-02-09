/**
 * SOLUCIÓN: Intersecting Rectangles
 * LENGUAJE: C++
 *
 * ======================================================================================
 * ANÁLISIS DEL PROBLEMA Y ESTRATEGIA
 * ======================================================================================
 * 1. El problema pide contar pares de rectángulos que tienen una intersección
 * de área estrictamente mayor a 0.
 * 2. "Estrictamente" significa que si dos rectángulos solo comparten un borde
 * (ej. uno termina en x=5 y el otro empieza en x=5), NO cuenta.
 * 3. Entrada: N rectángulos, cada uno con (x1, y1) esquina inferior izq
 * y (x2, y2) esquina superior der.
 * 4. Restricciones: N permite una solución cuadrática O(N^2).
 *
 * ESTRATEGIA:
 * - Usaremos una estructura (struct) para manejar los datos de cada rectángulo ordenadamente.
 * - Almacenaremos todos los rectángulos en un std::vector.
 * - Usaremos un doble bucle (fuerza bruta) para comparar cada par único.
 * - La condición de intersección se basa en la lógica de AABB (Axis-Aligned Bounding Box).
 */

#include <iostream>
#include <vector>
#include <algorithm> // Para std::max y std::min

// Usamos una estructura para agrupar las 4 coordenadas.
// Esto hace el código más legible que tener 4 arrays separados o un array 2D confuso.
struct Rectangle {
    int x1, y1, x2, y2;
};

/**
 * Función: doIntersect
 * --------------------
 * Determina si dos rectángulos 'a' y 'b' se superponen con área > 0.
 *
 * Lógica Matemática:
 * Para que dos intervalos [minA, maxA] y [minB, maxB] se solapen,
 * el máximo de los inicios debe ser MENOR que el mínimo de los finales.
 *
 * Intervalo intersección en X = [ max(a.x1, b.x1), min(a.x2, b.x2) ]
 * Intervalo intersección en Y = [ max(a.y1, b.y1), min(a.y2, b.y2) ]
 *
 * Si en ambos ejes, el inicio del intervalo de intersección es
 * ESTRICTAMENTE menor que el final, entonces existe un área positiva.
 */
bool doIntersect(const Rectangle& a, const Rectangle& b) {
    // 1. Calculamos los límites de la intersección en el eje X
    int overlapX_start = std::max(a.x1, b.x1);
    int overlapX_end   = std::min(a.x2, b.x2);

    // 2. Calculamos los límites de la intersección en el eje Y
    int overlapY_start = std::max(a.y1, b.y1);
    int overlapY_end   = std::min(a.y2, b.y2);

    // 3. Verificamos si la intersección es válida (distancia positiva)
    // Usamos '<' y no '<=' porque el problema pide intersección estricta.
    // Si overlap_start == overlap_end, el ancho es 0 (solo se tocan los bordes).
    bool overlapX = overlapX_start < overlapX_end;
    bool overlapY = overlapY_start < overlapY_end;

    // Deben solaparse en AMBOS ejes para que exista intersección 2D
    return overlapX && overlapY;
}

int main() {
    // OPTIMIZACIÓN DE I/O:
    // Desactivamos la sincronización con stdio de C y el 'tie' de cin/cout.
    // Esto hace que cin/cout sean mucho más rápidos, algo crucial en C++
    // para problemas competitivos con muchas líneas de entrada.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if (!(std::cin >> N)) return 0;

    // Creamos un vector para almacenar los N rectángulos.
    // Reservamos memoria de antemano para evitar realocaciones innecesarias.
    std::vector<Rectangle> rects(N);

    // LECTURA DE DATOS
    for (int i = 0; i < N; ++i) {
        std::cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;
    }

    long long count = 0; // Usamos long long por seguridad, aunque int bastaría para N < 40,000

    // PROCESAMIENTO O(N^2)
    // Comparamos cada rectángulo con todos los siguientes.
    for (int i = 0; i < N; ++i) {
        // Empezamos j desde i + 1.
        // ESTO ES CLAVE:
        // 1. Evita comparar un rectángulo consigo mismo (i vs i).
        // 2. Evita duplicados (si ya comparé A vs B, no comparo B vs A).
        //    El par (A, B) es el mismo que (B, A).
        for (int j = i + 1; j < N; ++j) {
            if (doIntersect(rects[i], rects[j])) {
                count++;
            }
        }
    }

    // SALIDA
    std::cout << count << "\n";

    return 0;
}