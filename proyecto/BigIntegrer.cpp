//
// Created by Nikolas Jimenez on 7/05/2023.
//
#include "BigInteger.h"

BigInteger BigInteger::operator+(const BigInteger& other) {
    BigInteger result(""); // Resultado de la suma
    BigInteger num1(*this); // Primer sumando (BigInteger actual)
    BigInteger num2(other); // Segundo sumando (BigInteger pasado como parámetro)
    int carry = 0; // Acarreo inicializado en 0

    // Realizar la suma de los dígitos en cada posición
    while (!num1.lista.empty() || !num2.lista.empty() || carry != 0) {
        int digitSum = carry; // Suma de los dígitos en la posición actual

        // Si hay dígitos en num1, sumar el dígito correspondiente
        if (!num1.lista.empty()) {
            digitSum += num1.lista.back();
            num1.lista.pop_back();
        }

        // Si hay dígitos en num2, sumar el dígito correspondiente
        if (!num2.lista.empty()) {
            digitSum += num2.lista.back();
            num2.lista.pop_back();
        }

        // Calcular el dígito actual y el acarreo
        int currentDigit = digitSum % 10;
        carry = digitSum / 10;

        // Agregar el dígito al resultado
        result.lista.push_front(currentDigit);
    }

    return result;
}


BigInteger BigInteger::operator-(const BigInteger& other) {
    BigInteger result(""); // Resultado de la resta
    BigInteger num1(*this); // Minuendo (BigInteger actual)
    BigInteger num2(other); // Sustraendo (BigInteger pasado como parámetro)
    int borrow = 0; // Préstamo inicializado en 0

    // Realizar la resta de los dígitos en cada posición
    while (!num1.lista.empty() || !num2.lista.empty()) {
        int digitDiff = borrow; // Diferencia de los dígitos en la posición actual

        // Si hay dígitos en num1, restar el dígito correspondiente
        if (!num1.lista.empty()) {
            digitDiff += num1.lista.back();
            num1.lista.pop_back();
        }

        // Si hay dígitos en num2, restar el dígito correspondiente
        if (!num2.lista.empty()) {
            digitDiff -= num2.lista.back();
            num2.lista.pop_back();
        }

        // Verificar si se requiere un préstamo
        if (digitDiff < 0) {
            digitDiff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        // Agregar el dígito al resultado
        result.lista.push_front(digitDiff);
    }

    // Eliminar los ceros no significativos en el resultado
    while (result.lista.size() > 1 && result.lista.front() == 0) {
        result.lista.pop_front();
    }

    return result;
}

BigInteger BigInteger::operator/(const BigInteger& other) {
    BigInteger quotient(""); // Cociente de la división
    BigInteger dividend(*this); // Dividendo (BigInteger actual)
    BigInteger divisor(other); // Divisor (BigInteger pasado como parámetro)
    bool a = !(dividend < divisor);

    // Verificar si el dividendo es menor que el divisor
    if (dividend < divisor) {
        return quotient; // El cociente es 0 en este caso
    }

    // Realizar la división utilizando el algoritmo de la división larga
    while (a) {
        int numZeros = dividend.lista.size() - divisor.lista.size(); // Cantidad de ceros para el desplazamiento

        // Desplazar el divisor a la izquierda según el número de ceros
        BigInteger shiftedDivisor(divisor);
        for (int i = 0; i < numZeros; ++i) {
            shiftedDivisor.lista.push_front(0);
        }

        // Realizar una resta entre el dividendo y el divisor desplazado
        dividend = dividend - shiftedDivisor;

        // Agregar el dígito al cociente (resultado de la división)
        quotient.lista.push_front(1);

        // Eliminar los ceros no significativos en el dividendo
        while (dividend.lista.size() > 1 && dividend.lista.front() == 0) {
            dividend.lista.pop_front();
        }
        a = !(dividend < divisor);
    }

    return quotient;
}


BigInteger BigInteger::operator*(const BigInteger& other) {
    BigInteger product(""); // Producto de la multiplicación
    BigInteger num1(*this); // Primer factor (BigInteger actual)
    BigInteger num2(other); // Segundo factor (BigInteger pasado como parámetro)

    // Verificar si alguno de los factores es cero
    if (num1 == BigInteger("0") || num2 == BigInteger("0")) {
        return product; // El producto es 0 en este caso
    }

    // Realizar la multiplicación utilizando el algoritmo de la multiplicación en columna
    int numZeros = 0; // Cantidad de ceros para el desplazamiento

    // Multiplicar cada dígito de num2 por num1 y sumar los productos parciales
    for (int digit2 : num2.lista) {
        BigInteger partialProduct(""); // Producto parcial de un dígito de num2 por num1

        // Realizar la multiplicación de un dígito de num2 por num1
        int carry = 0; // Acarreo inicializado en 0
        for (int digit1 : num1.lista) {
            int digitProduct = digit1 * digit2 + carry; // Producto parcial de los dígitos
            carry = digitProduct / 10; // Nuevo acarreo
            digitProduct %= 10; // Dígito del producto parcial

            // Agregar el dígito al producto parcial
            partialProduct.lista.push_back(digitProduct);
        }

        // Si hay acarreo al finalizar la multiplicación, agregarlo como dígito adicional
        if (carry > 0) {
            partialProduct.lista.push_back(carry);
        }

        // Desplazar el producto parcial según el número de ceros
        for (int i = 0; i < numZeros; ++i) {
            partialProduct.lista.push_front(0);
        }

        // Sumar el producto parcial al producto total
        product = product + partialProduct;

        // Incrementar la cantidad de ceros para el siguiente producto parcial
        ++numZeros;
    }

    return product;
}


BigInteger BigInteger::operator%(const BigInteger& other) {
    BigInteger remainder(""); // Residuo de la división
    BigInteger dividend(*this); // Dividendo (BigInteger actual)
    BigInteger divisor(other); // Divisor (BigInteger pasado como parámetro)
    bool a = !(dividend < divisor);
    // Verificar si el dividendo es menor que el divisor
    if (dividend < divisor) {
        return dividend; // El residuo es igual al dividendo en este caso
    }

    // Realizar la división utilizando el algoritmo de la división larga
    while (a) {
        int numZeros = dividend.lista.size() - divisor.lista.size(); // Cantidad de ceros para el desplazamiento

        // Desplazar el divisor a la izquierda según el número de ceros
        BigInteger shiftedDivisor(divisor);
        for (int i = 0; i < numZeros; ++i) {
            shiftedDivisor.lista.push_front(0);
        }

        // Realizar una resta entre el dividendo y el divisor desplazado
        dividend = dividend - shiftedDivisor;

        // Eliminar los ceros no significativos en el dividendo
        while (dividend.lista.size() > 1 && dividend.lista.front() == 0) {
            dividend.lista.pop_front();
        }
        a = !(dividend < divisor);
    }

    return dividend;
}


bool BigInteger::operator==(const BigInteger& other) {
    // Verificar si las listas de dígitos son iguales
    return lista == other.lista;
}


bool BigInteger::operator<(const BigInteger& other) {
    // Comparar la longitud de las listas de dígitos
    if (lista.size() < other.lista.size()) {
        return true; // La lista del BigInteger actual es más corta, por lo tanto es menor
    }
    else if (lista.size() > other.lista.size()) {
        return false; // La lista del BigInteger actual es más larga, por lo tanto es mayor
    }

    // Si las listas tienen la misma longitud, comparar dígito por dígito
    auto it1 = lista.rbegin();
    auto it2 = other.lista.rbegin();

    while (it1 != lista.rend() && it2 != other.lista.rend()) {
        if (*it1 < *it2) {
            return true; // El dígito del BigInteger actual es menor
        }
        else if (*it1 > *it2) {
            return false; // El dígito del BigInteger actual es mayor
        }

        ++it1;
        ++it2;
    }

    return false; // Los BigInteger son iguales
}


bool BigInteger::operator<=(const BigInteger& other) {
    return (*this < other) || (*this == other);
}

BigInteger::BigInteger(std::string number) {
    // Iterar sobre la cadena de dígitos en orden inverso
    for (int i = number.length() - 1; i >= 0; i--) {
        // Obtener el dígito en la posición i
        char digitChar = number[i];
        int digit = digitChar - '0'; // Convertir el carácter a entero

        // Agregar el dígito a la lista (al frente para mantener el orden correcto)
        lista.push_front(digit);
    }
}

BigInteger::BigInteger(const BigInteger& other) : lista(other.lista) {
    // No se requiere ninguna implementación adicional, ya que la lista se copia automáticamente
}

BigInteger BigInteger::sumarListaValores(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result(""); // Crear un objeto BigInteger para almacenar el resultado

    int carry = 0; // Variable para almacenar el acarreo durante la suma

    // Recorrer las listas de dígitos de los números, desde el dígito menos significativo hacia el más significativo
    auto it1 = num1.lista.begin();
    auto it2 = num2.lista.begin();

    while (it1 != num1.lista.end() || it2 != num2.lista.end() || carry != 0) {
        int sum = carry; // Inicializar la suma con el valor del acarreo

        // Sumar los dígitos de los números, si existen
        if (it1 != num1.lista.end()) {
            sum += *it1;
            ++it1;
        }
        if (it2 != num2.lista.end()) {
            sum += *it2;
            ++it2;
        }

        carry = sum / 10; // Calcular el acarreo para la siguiente posición
        int digit = sum % 10; // Calcular el dígito en la posición actual

        // Agregar el dígito al resultado (al frente para mantener el orden correcto)
        result.lista.push_front(digit);
    }

    return result;
}


BigInteger BigInteger::multiplicarListaValores(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result("0"); // Inicializar el resultado como "0"

    // Multiplicar cada dígito de num1 por num2 y sumar los resultados parciales
    int shift = 0; // Variable para manejar el desplazamiento de posición en cada iteración

    for (auto it1 = num1.lista.rbegin(); it1 != num1.lista.rend(); ++it1) {
        int carry = 0; // Variable para almacenar el acarreo durante la multiplicación
        BigInteger partialResult(""); // Resultado parcial de la multiplicación

        // Agregar ceros al final de la representación en cada iteración para el desplazamiento
        for (int i = 0; i < shift; ++i) {
            partialResult.lista.push_back(0);
        }

        // Multiplicar el dígito actual de num1 por todos los dígitos de num2
        for (auto it2 = num2.lista.rbegin(); it2 != num2.lista.rend(); ++it2) {
            int prod = (*it1) * (*it2) + carry; // Producto del dígito actual por el dígito de num2

            carry = prod / 10; // Calcular el acarreo para la siguiente posición
            int digit = prod % 10; // Calcular el dígito en la posición actual

            // Agregar el dígito al resultado parcial
            partialResult.lista.push_front(digit);
        }

        // Si hay un acarreo al final de la multiplicación, agregarlo al resultado parcial
        if (carry != 0) {
            partialResult.lista.push_front(carry);
        }

        // Sumar el resultado parcial al resultado acumulado
        result = sumarListaValores(result, partialResult);

        shift++; // Incrementar el desplazamiento para la siguiente iteración
    }

    return result;
}


void BigInteger::add(const BigInteger& other) {
    auto it1 = lista.rbegin(); // Iterador para recorrer los dígitos del BigInteger actual (de derecha a izquierda)
    auto it2 = other.lista.rbegin(); // Iterador para recorrer los dígitos del otro BigInteger (de derecha a izquierda)
    int carry = 0; // Variable para almacenar el acarreo durante la suma

    while (it1 != lista.rend() || it2 != other.lista.rend() || carry != 0) {
        int sum = carry; // Inicializar la suma con el valor del acarreo

        // Sumar los dígitos de los BigInteger, si existen
        if (it1 != lista.rend()) {
            sum += *it1;
            ++it1;
        }
        if (it2 != other.lista.rend()) {
            sum += *it2;
            ++it2;
        }

        carry = sum / 10; // Calcular el acarreo para la siguiente posición
        int digit = sum % 10; // Calcular el dígito en la posición actual

        // Actualizar el dígito en la lista del BigInteger actual
        if (it1 != lista.rend()) {
            *it1 = digit;
        } else {
            lista.push_front(digit);
        }
    }
}


void BigInteger::subtrac(const BigInteger& other) {
    auto it1 = lista.rbegin(); // Iterador para recorrer los dígitos del BigInteger actual (de derecha a izquierda)
    auto it2 = other.lista.rbegin(); // Iterador para recorrer los dígitos del otro BigInteger (de derecha a izquierda)
    int borrow = 0; // Variable para almacenar el préstamo durante la resta

    while (it1 != lista.rend() || it2 != other.lista.rend() || borrow != 0) {
        int digit = borrow; // Inicializar el dígito con el valor del préstamo

        // Restar los dígitos de los BigInteger, si existen
        if (it1 != lista.rend()) {
            digit += *it1;
            ++it1;
        }
        if (it2 != other.lista.rend()) {
            digit -= *it2;
            ++it2;
        }

        if (digit < 0) {
            digit += 10; // Si el resultado es negativo, agregar 10 para compensar el préstamo
            borrow = -1; // Establecer el préstamo como -1
        } else {
            borrow = 0; // Establecer el préstamo como 0
        }

        // Actualizar el dígito en la lista del BigInteger actual
        if (it1 != lista.rend()) {
            *it1 = digit;
        } else {
            lista.push_front(digit);
        }
    }

    // Eliminar los ceros no significativos en la parte izquierda del BigInteger actual
    while (lista.size() > 1 && lista.front() == 0) {
        lista.pop_front();
    }
}


void BigInteger::produc(const BigInteger& other) {
    BigInteger result("0"); // Inicializar el resultado como "0"

    int shift = 0; // Variable para manejar el desplazamiento de posición en cada iteración

    // Multiplicar cada dígito del BigInteger actual por otros dígitos del otro BigInteger
    for (auto it1 = lista.rbegin(); it1 != lista.rend(); ++it1) {
        int carry = 0; // Variable para almacenar el acarreo durante la multiplicación
        BigInteger partialResult(""); // Resultado parcial de la multiplicación

        // Agregar ceros al final de la representación en cada iteración para el desplazamiento
        for (int i = 0; i < shift; ++i) {
            partialResult.lista.push_back(0);
        }

        // Multiplicar el dígito actual del BigInteger actual por todos los dígitos del otro BigInteger
        for (auto it2 = other.lista.rbegin(); it2 != other.lista.rend(); ++it2) {
            int prod = (*it1) * (*it2) + carry; // Producto del dígito actual por el dígito del otro BigInteger

            carry = prod / 10; // Calcular el acarreo para la siguiente posición
            int digit = prod % 10; // Calcular el dígito en la posición actual

            // Agregar el dígito al resultado parcial
            partialResult.lista.push_front(digit);
        }

        // Si hay un acarreo al final de la multiplicación, agregarlo al resultado parcial
        if (carry != 0) {
            partialResult.lista.push_front(carry);
        }

        // Sumar el resultado parcial al resultado acumulado
        result.add(partialResult);

        shift++; // Incrementar el desplazamiento para la siguiente iteración
    }

    // Asignar el resultado final al objeto BigInteger actual
    lista = result.lista;
}


void BigInteger::remainder(const BigInteger& other) {
    BigInteger quotient(""); // Resultado de la división (cociente)
    BigInteger remainder(""); // Resultado de la división (residuo)
    BigInteger dividend(*this); // Dividendo (objeto BigInteger actual)
    BigInteger divisor(other); // Divisor (objeto BigInteger pasado como parámetro)
    bool a = !(dividend < divisor);

    // Verificar si el dividendo es menor que el divisor
    if (dividend < divisor) {
        // El residuo es igual al dividendo en este caso
        lista = dividend.lista;
        return;
    }

    // Realizar la división utilizando el algoritmo de la división larga
    while (a) {
        int numZeros = dividend.lista.size() - divisor.lista.size(); // Cantidad de ceros para el desplazamiento

        // Desplazar el divisor a la izquierda según el número de ceros
        BigInteger shiftedDivisor(divisor);
        for (int i = 0; i < numZeros; ++i) {
            shiftedDivisor.lista.push_front(0);
        }

        // Realizar una resta entre el dividendo y el divisor desplazado
        dividend.subtrac(shiftedDivisor);

        // Agregar el dígito al cociente (resultado de la división)
        quotient.lista.push_front(1);

        // Eliminar los ceros no significativos en el dividendo
        while (dividend.lista.size() > 1 && dividend.lista.front() == 0) {
            dividend.lista.pop_front();
        }
        a = !(dividend < divisor);
    }

    // Asignar el residuo (dividendo) al objeto BigInteger actual
    lista = dividend.lista;
}


void BigInteger::pow(const BigInteger& other) {
    BigInteger base(*this); // Base (objeto BigInteger actual)
    BigInteger exponent(other); // Exponente (objeto BigInteger pasado como parámetro)
    BigInteger result("1"); // Resultado inicializado como "1"
    bool a = !(exponent <= BigInteger("0"));

    // Verificar si el exponente es cero
    if (exponent == BigInteger("0")) {
        lista = result.lista; // El resultado es 1
        return;
    }

    // Verificar si el exponente es negativo
    if (exponent < BigInteger("0")) {
        // El resultado es 0, ya que no se puede calcular una potencia con exponente negativo
        lista = BigInteger("0").lista;
        return;
    }

    // Realizar la potencia utilizando multiplicaciones repetidas
    while (a) {
        // Multiplicar el resultado parcial por la base en cada iteración
        result.produc(base);

        // Decrementar el exponente en 1
        exponent.subtrac(BigInteger("1"));
        a = !(exponent <= BigInteger("0"));
    }

    // Asignar el resultado final al objeto BigInteger actual
    lista = result.lista;
}


void BigInteger::quotient(const BigInteger& other) {
    BigInteger quotient(""); // Resultado de la división (cociente)
    BigInteger remainder(""); // Resultado de la división (residuo)
    BigInteger dividend(*this); // Dividendo (objeto BigInteger actual)
    BigInteger divisor(other); // Divisor (objeto BigInteger pasado como parámetro)
    bool a = !(dividend < divisor);

    // Verificar si el dividendo es menor que el divisor
    if (dividend < divisor) {
        // El cociente es 0 en este caso
        lista = BigInteger("0").lista;
        return;
    }

    // Realizar la división utilizando el algoritmo de la división larga
    while (a) {
        int numZeros = dividend.lista.size() - divisor.lista.size(); // Cantidad de ceros para el desplazamiento

        // Desplazar el divisor a la izquierda según el número de ceros
        BigInteger shiftedDivisor(divisor);
        for (int i = 0; i < numZeros; ++i) {
            shiftedDivisor.lista.push_front(0);
        }

        // Realizar una resta entre el dividendo y el divisor desplazado
        dividend.subtrac(shiftedDivisor);

        // Agregar el dígito al cociente (resultado de la división)
        quotient.lista.push_front(1);

        // Eliminar los ceros no significativos en el dividendo
        while (dividend.lista.size() > 1 && dividend.lista.front() == 0) {
            dividend.lista.pop_front();
        }
        a = !(dividend < divisor);
    }

    // Asignar el cociente al objeto BigInteger actual
    lista = quotient.lista;
}


std::string BigInteger::toString() {
    std::string result; // Cadena de caracteres resultado

    // Verificar si el BigInteger es 0
    if (lista.size() == 1 && lista.front() == 0) {
        result = "0";
    } else {
        // Convertir cada dígito en el BigInteger a un carácter y concatenarlos en la cadena resultado
        for (int digit : lista) {
            result += std::to_string(digit);
        }
    }

    return result;
}