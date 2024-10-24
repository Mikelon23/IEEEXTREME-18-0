from itertools import combinations

def minimum_reading_time(books):
    # Set de todos los temas que Alice necesita cubrir
    all_topics = set()
    for book in books:
        all_topics.update(book[1])
    
    # Número de libros
    n = len(books)
    min_time = float('inf')  # Iniciamos con infinito
    
    # Probar todas las combinaciones de libros
    for r in range(1, n + 1):
        for comb in combinations(books, r):
            covered_topics = set()
            total_time = 0
            for book in comb:
                total_time += book[0]  # Sumamos el tiempo de lectura de cada libro
                covered_topics.update(book[1])  # Añadimos los temas que cubre el libro
            
            # Verificamos si cubrimos todos los temas
            if covered_topics == all_topics:
                min_time = min(min_time, total_time)  # Actualizamos el mínimo tiempo
    
    return min_time

# Entrada
books = [
    (300, {"Backtracking", "Dynamic_Programming", "Greedy"}),
    (125, {"Dynamic_Programming"}),
    (35, {"Backtracking"}),
    (85, {"Greedy"}),
    (120, {"Backtracking", "Dynamic_Programming"}),
    (80, {"Greedy", "Backtracking"})
]

# Salida
print(minimum_reading_time(books))
