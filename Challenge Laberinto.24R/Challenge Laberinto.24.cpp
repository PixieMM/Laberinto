// Directivas #include permiten que el programa utilice funcionalidades específicas de estas bibliotecas estándar de C++

#include <iostream> //  Incluir la biblioteca estándar de entrada y salida para mostrar información en la consola y obtener entrada del usuario
#include <vector> // Proporciona soporte para contenedores de datos dinámicos llamados vectores. Los vectores son similares a los arreglos, pero su tamaño puede cambiar dinámicamente.
#include <cstdlib> // Generacion de numeros aleatorios
#include <ctime> // Libreria para obtener la hora actual del sistema
#include <algorithm> // Para usar std::shuffle // proporciona una colección de funciones genéricas para operaciones en rangos de elementos. Esto incluye algoritmos para ordenar, buscar y manipular elementos en contenedores como vectores.
#include <random>    // Para usar std::default_random_engine Porque no me reconocia estas librerias el compilador. Para crear numeros de forma aleatoria

using namespace std; // Utilizamos para llamar especificamente a una variable

// Estructura para representar direcciones (arriba, abajo, izquierda, derecha)
struct Direccion {
    int fila, columna;
};

// Función para imprimir el laberinto en la consola
void imprimirLaberinto(const vector<vector<char>>& laberinto) {
    for (size_t i = 0; i < laberinto.size(); ++i) {
        for (size_t j = 0; j < laberinto[i].size(); ++j) {
            cout << laberinto[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para generar el laberinto utilizando Backtracking (recursividad), en este caso, significa que si recorre un camino y encuentra un muro, retrocede para elegir otro camino
void generarLaberinto(vector<vector<char>>& laberinto, int fila, int columna) {
    int filas = laberinto.size();
    int columnas = laberinto[0].size();

    // Direcciones posibles: arriba, abajo, izquierda, derecha
    vector<Direccion> direcciones = {
        {-2, 0},  // arriba
        {2, 0},   // abajo
        {0, -2},  // izquierda
        {0, 2}    // derecha
    };

    // Barajamos aleatoriamente las direcciones
    shuffle(direcciones.begin(), direcciones.end(), std::default_random_engine(time(nullptr)));

    // Visitamos cada dirección
    for (auto& direccion : direcciones) {
        int nuevaFila = fila + direccion.fila;
        int nuevaColumna = columna + direccion.columna;

        // Verificamos si la nueva posición es válida
        if (nuevaFila >= 0 && nuevaFila < filas && nuevaColumna >= 0 && nuevaColumna < columnas) {
            if (laberinto[nuevaFila][nuevaColumna] == '#') {
                // Rompemos la pared entre la celda actual y la nueva celda
                laberinto[nuevaFila][nuevaColumna] = ' ';

                // Rompemos la pared intermedia
                int paredFila = fila + direccion.fila / 2;
                int paredColumna = columna + direccion.columna / 2;
                laberinto[paredFila][paredColumna] = ' ';

                // Llamamos recursivamente a la función desde la nueva celda
                generarLaberinto(laberinto, nuevaFila, nuevaColumna);
            }
        }
    }
}

// Función para encontrar una solución en el laberinto utilizando DFS, (recorridos en grafos  por profundidad)
bool encontrarSolucion(vector<vector<char>>& laberinto, int fila, int columna) {
    int filas = laberinto.size();
    int columnas = laberinto[0].size();

    // Caso base: si estamos fuera de los límites del laberinto
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        return false; //no se realiza
    }

    // Caso base: si encontramos la salida
    if (fila == filas - 1 && columna == columnas - 1) {
        laberinto[fila][columna] = 'X'; // Marcamos la salida con 'X'
        return true;
    }

    // Si estamos en un camino válido
    if (laberinto[fila][columna] == ' ') {
        // Marcamos el camino como visitado ('.')
        laberinto[fila][columna] = '.';

        // Direcciones posibles: arriba, abajo, izquierda, derecha
        vector<Direccion> direcciones = {
            {-1, 0},  // arriba
            {1, 0},   // abajo
            {0, -1},  // izquierda
            {0, 1}    // derecha
        };

        // Exploramos cada dirección
        for (auto& direccion : direcciones) {
            int nuevaFila = fila + direccion.fila;
            int nuevaColumna = columna + direccion.columna;

            // Intentamos encontrar una solución recursivamente
            if (encontrarSolucion(laberinto, nuevaFila, nuevaColumna)) {
                return true;
            }
        }

        // Si no encontramos solución, marcamos la celda como no visitada
        laberinto[fila][columna] = ' ';
    }

    return false;
}

int main() {
    // Inicializar la semilla para los números aleatorios
    srand(static_cast<unsigned int>(time(nullptr)));

    // Definir las dimensiones del laberinto
    int filas, columnas;
    cout << "Ingrese el número de filas del laberinto: ";
    cin >> filas;
    cout << "Ingrese el número de columnas del laberinto: ";
    cin >> columnas;
    cout << endl;

    // Crear el laberinto inicialmente con todos los muros
    vector<vector<char>> laberinto(filas, vector<char>(columnas, '#'));

    // Empezamos en una celda impar para asegurar que la generación comienza correctamente
    int filaInicial = 1;
    int columnaInicial = 1;

    // Generar el laberinto desde la celda inicial
    generarLaberinto(laberinto, filaInicial, columnaInicial);

    // Establecer la entrada y la salida en los extremos opuestos del laberinto
    laberinto[filaInicial][0] = ' ';              // Entrada
    laberinto[filas - 2][columnas - 1] = ' ';     // Salida

    // Imprimir el laberinto generado
    cout << "Laberinto generado:" << endl;
    imprimirLaberinto(laberinto);
    cout << endl;

    // Encontrar una solución en el laberinto utilizando DFS
    bool solucionEncontrada = encontrarSolucion(laberinto, filaInicial, 0);

    // Imprimir el laberinto con la solución encontrada (si existe)
    if (solucionEncontrada) {
        cout << "Laberinto con solución:" << endl;
        imprimirLaberinto(laberinto);
    }

    return 0;
}
