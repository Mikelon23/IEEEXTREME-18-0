/**
 * Solución para: Tic-Tac-Toe
 * Lenguaje: C++
 *
 * -----------------------------------------------------------------------------
 * EXPLICACIÓN DEL ALGORITMO (VALIDACIÓN + MINIMAX)
 * -----------------------------------------------------------------------------
 *
 * OBJETIVO:
 * 1. Validar si un tablero de 3x3 es un estado legal que puede alcanzarse en
 * una partida real (Retornar -1 si es inválido).
 * 2. Si es válido, predecir el resultado del juego asumiendo que ambos
 * jugadores juegan de forma óptima (1 = Gana X, 2 = Gana O, 0 = Empate).
 *
 * PARTE 1: VALIDACIÓN DEL ESTADO
 * En el Tic-Tac-Toe estándar, el Jugador 1 ('X' o 1) siempre empieza. 
 * Por lo tanto, un tablero solo es válido si cumple TODAS estas reglas:
 * - Turnos: La cantidad de 1s debe ser igual a la de 2s (es el turno de 1), 
 * o la cantidad de 1s debe ser exactamente la de 2s más uno (es el turno de 2).
 * - No pueden ganar ambos a la vez.
 * - Si el Jugador 1 ya tiene una línea ganadora, obligatoriamente el 
 * tablero debe tener un '1' más que '2' (porque el juego debió terminar 
 * justo en el movimiento del Jugador 1).
 * - Si el Jugador 2 ya tiene una línea ganadora, obligatoriamente el tablero 
 * debe tener la misma cantidad de '1' y '2' (porque el juego terminó en el 
 * turno del Jugador 2).
 *
 * PARTE 2: ALGORITMO MINIMAX
 * Como el tablero es de 3x3, el número total de estados posibles es muy 
 * pequeño (3^9 = 19683, y los válidos son aún menos). Esto nos permite usar
 * el algoritmo "Minimax" sin necesidad de optimizaciones complejas (como Poda 
 * Alfa-Beta), ya que calcular todo el árbol de juego toma una fracción 
 * minúscula de segundo.
 * * - Convertimos el problema a puntajes: Gana 1 = +1, Empate = 0, Gana 2 = -1.
 * - El Jugador 1 busca MAXIMIZAR este puntaje.
 * - El Jugador 2 busca MINIMIZAR este puntaje.
 * - Simulamos todas las jugadas posibles mediante recursión. Si es el turno 
 * del Jugador 1, elige el movimiento que retorne el mayor valor. Si es el 
 * turno del Jugador 2, elige el que retorne el menor valor.
 *
 * COMPLEJIDAD:
 * - Tiempo: O(9!) en el peor de los casos (tablero vacío), lo cual es 
 * ~362,880 operaciones. Ejecución instantánea, cumple O(1) en términos 
 * de escala algorítmica.
 * - Memoria: O(1) de espacio extra, ya que la pila de recursión llega a un 
 * máximo de 9 niveles de profundidad.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Función auxiliar para verificar si un jugador específico tiene 3 en línea
bool checkWin(const vector<vector<int>>& board, int player) {
    // Revisar filas y columnas
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Revisar diagonales
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    
    return false;
}

// Función auxiliar para validar si el estado del tablero es legal
bool isValidState(const vector<vector<int>>& board, int count1, int count2) {
    // La diferencia de fichas debe ser correcta (1 empieza)
    if (count1 != count2 && count1 != count2 + 1) return false;

    bool win1 = checkWin(board, 1);
    bool win2 = checkWin(board, 2);

    // No pueden ganar los dos al mismo tiempo
    if (win1 && win2) return false;

    // Si el Jugador 1 ganó, debe haber puesto la última ficha (count1 == count2 + 1)
    if (win1 && count1 != count2 + 1) return false;

    // Si el Jugador 2 ganó, el Jugador 1 no debió haber jugado después (count1 == count2)
    if (win2 && count1 != count2) return false;

    return true;
}

// Función Minimax pura
// Retorna: 1 (si el Jugador 1 asegura la victoria), -1 (si el Jugador 2 asegura victoria), 0 (empate)
int minimax(vector<vector<int>>& board, int turn) {
    // 1. Revisar si hemos llegado a un estado terminal (alguien ganó en el paso anterior)
    if (checkWin(board, 1)) return 1;
    if (checkWin(board, 2)) return -1;

    // 2. Revisar si hay celdas vacías, si no las hay y nadie ganó, es un empate
    bool isFull = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 0) isFull = false;
        }
    }
    if (isFull) return 0;

    // 3. Simular todos los movimientos posibles
    if (turn == 1) {
        // Turno del Jugador 1 (Maximizador)
        int bestScore = -2; // Peor escenario inicial
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = 1; // Hacemos la jugada
                    int score = minimax(board, 2); // Llamada recursiva cambiando de turno
                    board[i][j] = 0; // Deshacemos la jugada (Backtracking)
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else {
        // Turno del Jugador 2 (Minimizador)
        int bestScore = 2; // Peor escenario inicial
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = 2;
                    int score = minimax(board, 1);
                    board[i][j] = 0;
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}

int solveTicTacToe(vector<vector<int>>& board) {
    int count1 = 0, count2 = 0;
    
    // Contamos las piezas de cada jugador
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 1) count1++;
            else if (board[i][j] == 2) count2++;
        }
    }

    // Paso 1: Si el tablero rompe las reglas, devolvemos -1
    if (!isValidState(board, count1, count2)) {
        return -1;
    }

    // Paso 2: Si es un tablero válido, determinamos de quién es el turno actual.
    // Si tienen igual cantidad, le toca al Jugador 1, si no, al Jugador 2.
    int currentTurn = (count1 == count2) ? 1 : 2;

    // Paso 3: Lanzamos Minimax para predecir el futuro del juego
    int result = minimax(board, currentTurn);

    // Mapeamos el puntaje interno (-1, 0, 1) a las salidas requeridas por el problema
    if (result == 1) return 1;       // Gana el Jugador 1
    else if (result == -1) return 2; // Gana el Jugador 2
    else return 0;                   // Empate
}

int main() {
    // Optimización de I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<int>> board(3, vector<int>(3));
    
    // Validamos que se pueda leer el tablero
    if (cin >> board[0][0]) {
        cin >> board[0][1] >> board[0][2];
        for (int i = 1; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> board[i][j];
            }
        }
        
        // Ejecutamos la solución e imprimimos el resultado
        cout << solveTicTacToe(board) << "\n";
    }

    return 0;
}