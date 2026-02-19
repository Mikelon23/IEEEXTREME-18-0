/**
 * SOLUCIÓN: Bit Menos Significativo (Least Significant Bit - LSB)
 * -------------------------------------------------------------------------
 * PROBLEMA:
 * Dado un número entero 'x', encontrar el valor de su bit más a la derecha
 * que esté encendido (en 1).
 * * Ejemplo: x = 10
 * En binario: 10 = 0000 1010
 * El bit '1' más a la derecha está en la posición 1 (valor 2^1 = 2).
 * Respuesta esperada: 2.
 *
 * ESTRATEGIA (Operaciones a nivel de bits - O(1)):
 * Existe un truco clásico e increíblemente elegante en programación para
 * aislar el bit menos significativo:  x & -x
 *
 * ¿Por qué funciona 'x & -x'?
 * Las computadoras representan los números negativos usando un sistema
 * llamado "Complemento a 2". 
 * La regla del complemento a 2 dice que:  -x = (~x) + 1
 * (Donde ~x es invertir todos los bits de x: ceros a unos y unos a ceros).
 *
 * Veamos la magia paso a paso con x = 10 (0000 1010):
 * 1) x             = ... 0000 1010
 * 2) Invertir (~x) = ... 1111 0101  (Cambiamos todos los 0s por 1s y viceversa)
 * 3) Sumar 1 (-x)  = ... 1111 0110  (Este es el valor de -10 en la computadora)
 * * Ahora hacemos el AND lógico a nivel de bits (&) entre x y -x:
 * x  = ... 0000 1010
 * -x  = ... 1111 0110
 * -------------------- (AND: solo da 1 si ambos son 1)
 * RES = ... 0000 0010  (¡El resultado es 2!)
 *
 * Al sumar 1 al número invertido, todos los bits a la derecha del LSB original
 * que eran 1s (y se volvieron 0s) vuelven a volverse 0s, arrastrando el acarreo 
 * justo hasta la posición del LSB, volviéndolo 1. 
 * Todos los bits a la izquierda quedan invertidos, así que al hacer el AND con el
 * original, se cancelan a 0. ¡Solo sobrevive el LSB!
 */

#include <iostream>

using namespace std;

// Usamos long long para x por si acaso los números de prueba son muy grandes,
// aunque la lógica aplica igual para int.
long long leastSignificantBit(long long x) {
    // La operación mágica O(1)
    return x & -x;
}

int main() {
    // Optimización de I/O para procesar múltiples casos de prueba muy rápido
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    // Leemos la cantidad de casos de prueba
    if (cin >> T) {
        while (T--) {
            long long x;
            cin >> x;
            
            // Llamamos a nuestra función O(1) e imprimimos
            cout << leastSignificantBit(x) << "\n";
        }
    }

    return 0;
}