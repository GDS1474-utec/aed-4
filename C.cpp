#include <iostream>
#include <vector>

using namespace std;

const int N = 3;
vector<vector<int>> tablero(N, vector<int>(N, 0));
vector<bool> usado(10, false);
int respuestas = 0;

// Si la linea ya esta completa, debe sumar 15.
// Si todavia tiene ceros, no puede superar 15.
bool suma_valida(int a, int b, int c) {
    int suma = a + b + c;
    if (suma > 15) return false;
    if (a != 0 && b != 0 && c != 0 && suma != 15) return false;
    return true;
}

bool verificar() {
    for (int i = 0; i < N; i++) {
        // Revisar fila y columna.
        if (!suma_valida(tablero[i][0], tablero[i][1], tablero[i][2])) {
            return false;
        }
        if (!suma_valida(tablero[0][i], tablero[1][i], tablero[2][i])) {
            return false;
        }
    }

    // Revisar las dos diagonales.
    if (!suma_valida(tablero[0][0], tablero[1][1], tablero[2][2])) {
        return false;
    }
    if (!suma_valida(tablero[0][2], tablero[1][1], tablero[2][0])) {
        return false;
    }
    return true;
}

void back_tracking(int pos) {
    // Verificar si la construccion actual aun puede ser valida.
    if (!verificar()) return;

    // Caso base: se llenaron las 9 casillas.
    if (pos == N * N) {
        respuestas++;
        return;
    }

    int i = pos / N;
    int j = pos % N;

    // Las casillas dadas no se pueden cambiar.
    if (tablero[i][j] != 0) {
        back_tracking(pos + 1);
        return;
    }

    // Construir, continuar y retroceder.
    for (int numero = 1; numero <= 9; numero++) {
        if (!usado[numero]) {
            tablero[i][j] = numero;
            usado[numero] = true;

            back_tracking(pos + 1);

            usado[numero] = false;
            tablero[i][j] = 0;
        }
    }
}

int main() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> tablero[i][j];
            if (tablero[i][j] != 0) {
                usado[tablero[i][j]] = true;
            }
        }
    }

    back_tracking(0);
    cout << respuestas << "\n";

    return 0;
}
