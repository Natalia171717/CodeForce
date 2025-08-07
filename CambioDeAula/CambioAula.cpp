#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

//Como tengo sólo 1 y -1 y además mi camino es par, puedo estar segura de que si me da 0 dentro del rango, existe alguna suma de celdas que da cero:
//igual cant de -1 y 1 entonces siempre tengo el cero. Si es distinta, se que igual tendré ambas cantidades pares o impares a la vez,
//y la suma siempre será par (ademas varía de 2 en 2 cada dos celdas). Entonces, si el cero está en rango, existe.
//Esto ya que hay una combinacion que los junta de tal forma que da cero la suma (está dentro de la progresión de (min,min+2,...,max-2,max)). 
//Tambien se puede ver que en la misma diagonal, todas las sumas tienen la misma paridad (resto -2, sumo +2 o me queda igual),
//lo que confirma que tengo toda la progresión posible de 2 en 2 desde min a max (sólo si el camino es par).

void ca(vector<vector<int>> aulas, int fil, int col) {
    vector<vector<tuple<int, int>>> sumas(fil, vector<tuple<int, int>>(col, make_tuple(0, 0)));    //primer componente es minimo y segundo es maximo
    int minimo = fil + col - 1;   //longitud de un camino minimo
    if (minimo % 2 != 0) {
        cout << "NO" << endl;
        return;
    }
    get<0>(sumas[0][0]) = aulas[0][0];
    get<1>(sumas[0][0]) = aulas[0][0];

    for (int j = 1; j < col; j++) { //inicializo primera fila
        int nu = get<0>(sumas[0][j - 1]) + aulas[0][j];
        get<0>(sumas[0][j]) = nu;
        get<1>(sumas[0][j]) = nu;
    }

    for (int i = 1; i < fil; i++) { //inicializo primera columna
        int nu = get<0>(sumas[i-1][0]) + aulas[i][0];
        get<0>(sumas[i][0]) = nu;
        get<1>(sumas[i][0]) = nu;
    }

    for (int i = 1; i < fil; i++) {
        for (int j = 1; j < col; j++) {
            get<0>(sumas[i][j]) = ((get<0>(sumas[i - 1][j]) < get<0>(sumas[i][j - 1])) ? get<0>(sumas[i - 1][j]) : get<0>(sumas[i][j - 1])) + aulas[i][j]; //tomo el minimo
            get<1>(sumas[i][j]) = ((get<1>(sumas[i - 1][j]) > get<1>(sumas[i][j - 1])) ? get<1>(sumas[i - 1][j]) : get<1>(sumas[i][j - 1])) + aulas[i][j]; //tomo el maximo
        }
    }
    int min = get<0>(sumas[fil - 1][col - 1]);
    int max = get<1>(sumas[fil - 1][col - 1]);

    cout << ((min <= 0 and max >= 0) ? "YES" : "NO") << endl;   //en algun camino sumo cero?
}

int main()
{
    int test, n, m;

    cin >> test;
    while (test--) {   //test iteraciones
        cin >> n;   //filas
        cin >> m;   //columnas
        vector<vector<int>> aulas(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> aulas[i][j];
            }
        }
        ca(aulas, n, m);
    }
}
