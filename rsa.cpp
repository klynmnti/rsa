#include <sstream>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

/* CS111 HW2 RSA CODE */

int e, c, n, m, p, q, euler = 0;
long long d;
int cipherint;
vector <int> ciphertext;
long long decodedint;
char eng;

int cipherword;
string message = "";

// returns the gcd of two integers
int gcd(int a, int b) {
    int remainder;
    
    while (a % b > 0) {
        remainder = a % b;
        a = b;
        b = remainder;
    
    }
    return b;
}

// determines if two integers are coprime
bool isCoprime(int a, int b) {
    if (gcd(a, b) == 1) { return true; }

    return false;
}

// determines if public key is valid
bool isValid(int e, int n, int euler) {
    if ((e > n)) { return false; }
    if ((e > euler) || (!isCoprime(e, euler))) { return false; }

    return true;
}

// returns one factor of an integer a
int factor(int a) {
    for (int i = 2; i <= sqrt(a); i++) {
        if (a % i == 0) { return i; }
    }

    return -1;
}

// converts decoded integer to english
char convertToEng(int a) {

    vector<char> alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    
    if (a == 33) { return ' '; }
    if (a == 34) { return '\"'; }
    if (a == 35) { return ','; }
    if (a == 36) { return '.'; }
    if (a == 37) { return '\''; }

    return alphabet.at(a - 7);
}

// used to determine the decoded integer
// considering a as the exponent base
// b as the power raised to
// and n as the modulo
int modulo(int a, int b, int n) {
    if (a == 0) { a = 2; }

    int x = 1;
    int y = a;

    while (b > 0) {
        if (b % 2 == 1) { x = (x * y) % n; }
        y = (y * y) % n;
        b /= 2;
    }

    return x % n;
}

// using euclid's extended algorithm to determine d
// considering a as e and m as euler's totient
int euclidExtended(int a, int m) {
    int x = m;
    int y = m;
    int quotient = m;
    int temp1 = 0;
    int temp2 = 1;
    
    if (m == 1) { return 0; }

    while (a > 1) {
        quotient = a / m;
        y = m;
        m = a % m;
        a = y;
        y = temp1;
        temp1 = temp2 - quotient * temp1;
        temp2 = y;
    }

    if (temp2 < 0) { temp2 += x; }
    return temp2;
}

int main() {

    cin >> e;
    cin >> n;
    cin >> m;
    
    for (int i = 0; i < m; i++) {
        cin >> cipherint;
        ciphertext.push_back(cipherint);
    }

    p = factor(n);
    q = n / p;
    euler = (p - 1) * (q - 1);

    if (!isValid(e, n, euler)) {
        cout << "Public key is not valid!";
        return -1;
    }

    d = euclidExtended(e, euler);

    cout << p << " " << q << " " << euler << " " << d << endl;

    for (int i = 0; i < ciphertext.size(); i++) {
        decodedint = modulo(ciphertext.at(i), d, n);
        cout << decodedint << " ";
        eng = convertToEng(decodedint);
        message += eng;
    }

    cout << endl << message;

    return 0;
}