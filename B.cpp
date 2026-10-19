#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// AVL con los numeros de camiseta que actualmente estan libres.
// Se usa la misma estructura y las rotaciones de la plantilla AVL.
struct Nodo {
    int clave;
    int altura;
    Nodo* izq;
    Nodo* der;

    Nodo(int k) : clave(k), altura(0), izq(nullptr), der(nullptr) {}
};

class AVLTree {
private:
    Nodo* raiz;

    int h(Nodo* v) {
        if (v == nullptr) return -1;
        return v->altura;
    }

    void actualizar(Nodo* v) {
        if (v != nullptr) {
            v->altura = 1 + max(h(v->izq), h(v->der));
        }
    }

    int FB(Nodo* v) {
        if (v == nullptr) return 0;
        return h(v->izq) - h(v->der);
    }

    Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izq;
        y->izq = x->der;
        x->der = y;

        actualizar(y);
        actualizar(x);
        return x;
    }

    Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->der;
        x->der = y->izq;
        y->izq = x;

        actualizar(x);
        actualizar(y);
        return y;
    }

    Nodo* rebalancear(Nodo* v) {
        if (v == nullptr) return nullptr;
        actualizar(v);

        if (FB(v) > 1) {
            if (FB(v->izq) < 0) {
                v->izq = rotarIzquierda(v->izq);
            }
            return rotarDerecha(v);
        }

        if (FB(v) < -1) {
            if (FB(v->der) > 0) {
                v->der = rotarDerecha(v->der);
            }
            return rotarIzquierda(v);
        }

        return v;
    }

    Nodo* insertar(Nodo* v, int k) {
        if (v == nullptr) return new Nodo(k);

        if (k < v->clave) {
            v->izq = insertar(v->izq, k);
        } else if (k > v->clave) {
            v->der = insertar(v->der, k);
        } else {
            return v;
        }

        return rebalancear(v);
    }

    Nodo* minimo(Nodo* v) {
        while (v != nullptr && v->izq != nullptr) {
            v = v->izq;
        }
        return v;
    }

    Nodo* eliminar(Nodo* v, int k) {
        if (v == nullptr) return nullptr;

        if (k < v->clave) {
            v->izq = eliminar(v->izq, k);
        } else if (k > v->clave) {
            v->der = eliminar(v->der, k);
        } else {
            if (v->izq == nullptr) {
                Nodo* temp = v->der;
                delete v;
                return temp;
            } else if (v->der == nullptr) {
                Nodo* temp = v->izq;
                delete v;
                return temp;
            }

            Nodo* s = minimo(v->der);
            v->clave = s->clave;
            v->der = eliminar(v->der, s->clave);
        }

        return rebalancear(v);
    }

    void liberar(Nodo* v) {
        if (v == nullptr) return;
        liberar(v->izq);
        liberar(v->der);
        delete v;
    }

public:
    AVLTree() : raiz(nullptr) {}

    ~AVLTree() {
        liberar(raiz);
    }

    void insertar(int k) {
        raiz = insertar(raiz, k);
    }

    void eliminar(int k) {
        raiz = eliminar(raiz, k);
    }

    int menor() {
        return minimo(raiz)->clave;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    // En q operaciones, como maximo q numeros distintos pueden estar
    // ocupados. Por eso siempre hay algun numero libre entre 0 y q.
    AVLTree libres;
    for (int i = 0; i <= q; i++) {
        libres.insertar(i);
    }

    // Hay que contar jugadores repetidos con la misma camiseta.
    vector<int> frecuencia(200001, 0);

    for (int i = 0; i < q; i++) {
        int tipo;
        cin >> tipo;

        if (tipo == 1) {
            int x;
            cin >> x;
            if (frecuencia[x] == 0 && x <= q) {
                libres.eliminar(x);
            }
            frecuencia[x]++;
        } else if (tipo == 2) {
            int x;
            cin >> x;
            frecuencia[x]--;
            if (frecuencia[x] == 0 && x <= q) {
                libres.insertar(x);
            }
        } else {
            cout << libres.menor() << "\n";
        }
    }

    return 0;
}
