/**
 * SOLUCIÓN: El Número Concatenado Más Grande (Largest Concat Number)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Dada una lista de números (como cadenas de texto), concatenarlos en el
 * orden que forme el número total más grande posible.
 *
 * LA TRAMPA DEL ORDENAMIENTO NORMAL:
 * Si simplemente ordenamos alfabéticamente de mayor a menor, fallaremos.
 * Ejemplo: "3" y "32".
 * Orden normal descendente: "32", "3" -> Concatenado: "323".
 * ¡Pero "332" (3 seguido de 32) es mayor que "323"!
 * El '3' debe ir antes que el '32'.
 *
 * ESTRATEGIA (Ordenamiento Personalizado con Concatenación):
 * En lugar de preguntarnos "¿Es 'a' mayor que 'b'?", nos preguntamos:
 * "¿Es mejor poner 'a' primero o 'b' primero?"
 * * Para saberlo, simulamos ambas opciones:
 * Opcion 1: a + b (concatenación de a y b)
 * Opcion 2: b + a (concatenación de b y a)
 * * Regla de ordenamiento: 'a' debe ir antes que 'b' si (a + b) > (b + a).
 * * Ejemplo con "3" y "32":
 * a = "3", b = "32"
 * a + b = "332"
 * b + a = "323"
 * Como "332" > "323", entonces "3" debe ir ANTES que "32".
 *
 * CASO BORDE IMPORTANTE:
 * ¿Qué pasa si el arreglo es ["0", "0", "0"]?
 * Nuestro algoritmo lo ordenará y concatenará como "000".
 * Pero el número "000" matemáticamente es solo "0". Debemos manejar este caso.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Función comparadora personalizada para std::sort
bool compareConcat(const string& a, const string& b) {
    // Retorna true si concatenar 'a' antes que 'b' forma un string mayor.
    // Como ambas concatenaciones (a+b y b+a) tienen exactamente la misma longitud,
    // el operador '>' de strings (que compara lexicográficamente) funciona perfecto
    // para comparar sus valores numéricos reales.
    return a + b > b + a;
}

int main() {
    // Optimización de entrada/salida para manejar N grande rápidamente
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<string> nums(N);
    for (int i = 0; i < N; ++i) {
        cin >> nums[i];
    }

    // Ordenamos el arreglo usando nuestra regla mágica
    sort(nums.begin(), nums.end(), compareConcat);

    // Manejo del caso borde: Múltiples Ceros
    // Después de ordenar, si el número "más grande" (el primero en el arreglo)
    // es un "0", significa que TODOS los demás números también son "0" o menores.
    // La concatenación de puros ceros debe ser un solo "0".
    if (nums[0] == "0") {
        cout << "0\n";
        return 0;
    }

    // Construimos la respuesta concatenando en el orden ya establecido
    string largestNumber = "";
    for (int i = 0; i < N; ++i) {
        largestNumber += nums[i];
    }

    // Imprimimos el resultado final
    cout << largestNumber << "\n";

    return 0;
}