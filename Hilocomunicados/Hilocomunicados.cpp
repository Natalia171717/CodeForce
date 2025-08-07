#include <iostream>
#include <string>
#include <iomanip>  // para setprecision
using namespace std;

int potencia(int base, int exponente) {
    if (exponente == 0) { return 1; }
    int b = base;
    for (exponente; exponente > 1; exponente--) {
        base *= b;
    }
    return base;
}


void HC(long long& totales, long long& validos, int n, int m, int nE, int mE, int q) {
    if (q == 0) {
        if (n == nE && m == mE) {
            validos++;
            totales++;
        }
        else { totales++; }
    }
    else if (mE > m || nE > n) { totales=totales+potencia(2,q); }
    else {
        HC(totales, validos, n, m, (nE + 1), mE, (q - 1)); 
        HC(totales, validos, n, m, nE, (mE + 1), (q - 1));
    }
}

int main()
{
    string original, escuchado;
    long double p;
    int m=0, n=0, q=0, mE=0, nE=0;  //contadores de caracteres

    getline(cin, original);
    getline(cin, escuchado);

    for (int i = 0; i < original.length(); i++) {
        (original[i] == '+') ? m++ : n++;
        if (escuchado[i] == '+') { mE++; }
        else if (escuchado[i] == '-') { nE++; }
        else { q++; }
    }

    if (mE > m || nE > n) { p = 0; }
    else if (mE == m && nE == n) { p = 1; }
    else {
        //int pos = m - n;
        //int res = mE - nE;
        long long totales=0, validos=0;
        HC(totales, validos, n, m, nE, mE, q);

        p = static_cast<long double>(validos) / totales;    //para que mi división mantenga la presición que quiero
    }

    cout << fixed << setprecision(12) << p << endl; //12 decimales de presición
}
