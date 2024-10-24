#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

// Función para calcular el tiempo mínimo de lectura que cubra todos los temas
int minimum_reading_time(vector<pair<int, set<string>>>& books) {
    // Set de todos los temas que Alice necesita cubrir
    set<string> all_topics;
    for (auto& book : books) {
        all_topics.insert(book.second.begin(), book.second.end());
    }

    int n = books.size();
    int min_time = INT_MAX; // Inicializamos el tiempo mínimo con un valor muy alto

    // Probar todas las combinaciones de libros
    for (int mask = 1; mask < (1 << n); ++mask) {
        set<string> covered_topics;
        int total_time = 0;
        
        // Revisamos cada libro en la combinación actual (definida por el bitmask)
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) { // Si el libro i está en la combinación
                total_time += books[i].first; // Sumar el tiempo del libro
                covered_topics.insert(books[i].second.begin(), books[i].second.end()); // Añadir los temas cubiertos
            }
        }

        // Verificamos si cubrimos todos los temas
        if (covered_topics == all_topics) {
            min_time = min(min_time, total_time); // Actualizamos el tiempo mínimo
        }
    }

    return min_time;
}

int main() {
    // Vector de libros, cada uno con su tiempo y conjunto de temas cubiertos
    vector<pair<int, set<string>>> books = {
        {300, {"Backtracking", "Dynamic_Programming", "Greedy"}},
        {125, {"Dynamic_Programming"}},
        {35,  {"Backtracking"}},
        {85,  {"Greedy"}},
        {120, {"Backtracking", "Dynamic_Programming"}},
        {80,  {"Greedy", "Backtracking"}}
    };

    // Calculamos el tiempo mínimo de lectura
    int result = minimum_reading_time(books);
    
    // Imprimimos el resultado
    cout << result << endl;

    return 0;
}
