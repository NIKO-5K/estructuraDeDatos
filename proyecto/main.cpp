#include <iostream>
#include <string>
#include "biginteger.h"  // Incluir el archivo de encabezado de BigInteger

// Función para comparar dos números de punto flotante utilizando la clase BigInteger
std::string compareFloats(const std::string& float1, const std::string& float2) {
    BigInteger num1(float1);
    BigInteger num2(float2);
    bool jum = !(num1 <= num2);

    if (num1 < num2) {
        return "Smaller";
    } else if (jum) {
        return "Bigger";
    } else {
        return "Same";
    }
}

int main() {
    int numCases;
    std::cin >> numCases;

    std::string float1, float2;

    for (int i = 1; i <= numCases; i++) {
        std::cin >> float1 >> float2;
        std::string result = compareFloats(float1, float2);
        std::cout << "Case " << i << ": " << result << std::endl;
    }

    return 0;
}
