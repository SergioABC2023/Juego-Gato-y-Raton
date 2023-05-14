#include <iostream>
#include <vector>

using namespace std;

const int tamano = 3;


char board[tamano][tamano];

// Función para imprimir el tablero
void imprimirTablero() {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Función para verificar quien gano
bool verificarGanador(char simbolo) {
    // Verificar filas
    for (int i = 0; i < tamano; i++) {
        if (board[i][0] == simbolo && board[i][1] == simbolo && board[i][2] == simbolo) {
            return true;
        }
    }

    // Verificar columnas
    for (int j = 0; j < tamano; j++) {
        if (board[0][j] == simbolo && board[1][j] == simbolo && board[2][j] == simbolo) {
            return true;
        }
    }

    // Verificar diagonales
    if (board[0][0] == simbolo && board[1][1] == simbolo && board[2][2] == simbolo) {
        return true;
    }
    if (board[0][2] == simbolo && board[1][1] == simbolo && board[2][0] == simbolo) {
        return true;
    }

    return false;
}

// Función para verificar si el tablero está lleno
bool tableroLleno() {
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (board[i][j] == '-') {
                return false;
            }
        }
    }
    return true;
}

// Función que imprime las posiciones vacías
vector<pair<int, int>> get_empty_cells() {
    vector<pair<int, int>> empty_cells;
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (board[i][j] == '-') {
                empty_cells.push_back(make_pair(i, j));
            }
        }
    }
    return empty_cells;
}

// Función que evalúa la posición actual de la IA
int evaluarposicion(char simbolo) {
    if (verificarGanador(simbolo)) {
        return 1;
    } else if (verificarGanador((simbolo == 'x') ? 'o' : 'x')) {
        return -1;
    } else {
        return 0;
    }
}

// Función para minimax
int minimax(char simbolo, int depth, int alpha, int beta) {
    if (verificarGanador('x')) {
        return 1;
    }
    if (verificarGanador('o')) {
        return -1;
    }
    if (tableroLleno()) {
        return 0;
    }

    vector<pair<int, int>> empty_cells = get_empty_cells();

    if (simbolo == 'x') {
        int best_score = -1000;
        for (int i = 0; i < empty_cells.size(); i++) {
        int row = empty_cells[i].first;
        int col = empty_cells[i].second;
        board[row][col] = simbolo;

        int score = minimax('o', depth+1, alpha, beta);
        best_score = max(best_score, score);
        alpha = max(alpha, score);

        board[row][col] = '-';
        if (beta <= alpha) {
            break;
        }
    }
    return best_score;
} else {
    int best_score = 1000;
    for (int i = 0; i < empty_cells.size(); i++) {
        int row = empty_cells[i].first;
        int col = empty_cells[i].second;
        board[row][col] = simbolo;

        int score = minimax('x', depth+1, alpha, beta);
        best_score = min(best_score, score);
        beta = min(beta, score);

        board[row][col] = '-';
        if (beta <= alpha) {
            break;
        }
    }
    return best_score;
}
}

// Función para que la IA haga su turno
void computer_move() {
vector<pair<int, int>> empty_cells = get_empty_cells();
int best_score = -1000;
pair<int, int> best_move;
for (int i = 0; i < empty_cells.size(); i++) {
    int row = empty_cells[i].first;
    int col = empty_cells[i].second;
    board[row][col] = 'x';
    int score = minimax('o', 0, -1000, 1000);
    board[row][col] = '-';

    if (score > best_score) {
        best_score = score;
        best_move = make_pair(row, col);
    }
}

board[best_move.first][best_move.second] = 'x';
cout << "Posicion de turno de la IA [X](" << best_move.first << ", " << best_move.second << ")" << endl;
}

// Función para que el jugador haga su turno
void player_move() {
int row, col;
cout << "Ingresa la posicion de tu turno [O](fila, columna) EJEMPLO:(0 0): ";
cin >> row >> col;
while (row < 0 || row >= tamano || col < 0 || col >= tamano || board[row][col] != '-') {
    cout << "Posicion invalida o ocupada. Ingresa la posición de tu turno [O](fila, columna) EJEMPLO:(0 0): ";
    cin >> row >> col;
}

board[row][col] = 'o';
}

int main() {

for (int i = 0; i < tamano; i++) {
for (int j = 0; j < tamano; j++) {
board[i][j] = '-';
}
}


while (!verificarGanador('x') && !verificarGanador('o') && !tableroLleno()) {
    imprimirTablero();
    player_move();
    if (!verificarGanador('o') && !tableroLleno()) {
        computer_move();
    }
}

imprimirTablero();

if (verificarGanador('x')) {
    cout << "Gana la IA" << endl;
} else if (verificarGanador('o')) {
    cout << "Ganaste" << endl;
} else {
    cout << "Empate" << endl;
}

return 0;
}
