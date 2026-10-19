#include <iostream>
#include <string>

using namespace std;

string digitos;
string palabra;
string teclas[10] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

void back_tracking(int pos) {
    // Caso base: la palabra ya tiene una letra por cada tecla.
    if (pos == (int)digitos.size()) {
        cout << palabra << "\n";
        return;
    }

    // Construir una letra, continuar y retroceder.
    int tecla = digitos[pos] - '0';
    for (char letra : teclas[tecla]) {
        palabra.push_back(letra);
        back_tracking(pos + 1);
        palabra.pop_back();
    }
}

int main() {
    cin >> digitos;

    int cantidad = 1;
    for (char digito : digitos) {
        cantidad *= (int)teclas[digito - '0'].size();
    }

    cout << cantidad << "\n";
    back_tracking(0);

    return 0;
}
