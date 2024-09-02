#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class BigInt {

    std::string value;

private:

    int now, max;

public:

    BigInt();
    BigInt(const BigInt&);
    BigInt(const long long&);
    BigInt(const std::string&);

    BigInt& operator=(const BigInt&);
    BigInt& operator=(const long long&);
    BigInt& operator=(const std::string&);

    BigInt operator*(const BigInt&) const;
    BigInt operator/(const BigInt&) const;

    bool operator<(const BigInt&) const;
    bool operator>(const BigInt&) const;

    BigInt operator++(int);
    BigInt operator--(int);

    int GetLen(const BigInt);
    int GetEnd(const BigInt);
    BigInt Div_2(const BigInt);

    friend std::istream& operator>>(std::istream&, BigInt&);
    friend std::ostream& operator<<(std::ostream&, const BigInt&);
};

BigInt::BigInt() {
    value = "0";
}

BigInt::BigInt(const BigInt& num) {
    value = num.value;
}

BigInt::BigInt(const long long& num) {
    value = std::to_string(std::abs(num));
}

BigInt::BigInt(const std::string& num) {
    value = num;
}

BigInt& BigInt::operator=(const BigInt& num) {
    value = num.value;
    return *this;
}

BigInt& BigInt::operator=(const long long& num) {
    BigInt temp(num);
    value = temp.value;
    return *this;
}

BigInt& BigInt::operator=(const std::string& num) {
    value = num;
    return *this;
}

bool BigInt::operator<(const BigInt& num) const {
    int num1 = value.length();
    int num2 = num.value.length();

    if(num1 < num2){
        return 1;
    }
    else if(num2 < num1){
        return 0;
    }
    else if(num1 == num2){
        for(int i = 0; i < num1; i++){
            if(value[i] < num.value[i]){
                return 1;
            }
            else if(num.value[i] < value[i]){
                return 0;
            }
        }
    }
    return 0;
}

bool BigInt::operator>(const BigInt& num) const {
    return !(*this < num);
}

BigInt BigInt::operator*(const BigInt& num) const {
    int len1 = value.length();
    int len2 = num.value.length();

    int *result = new int[len1 + len2];
    for(int i = 0; i < len1 + len2; i++){
        result[i] = 0;
    }

    int i_n1 = 0;
    int i_n2 = 0;

    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = value[i] - '0';
        i_n2 = 0;
        for (int j = len2 - 1; j >= 0; j--) {
            int n2 = num.value[j] - '0';
            int sum = n1 * n2 + result[i_n1 + i_n2] + carry;
            carry = sum / 10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
        i_n1++;
    }
    int i = len1 + len2 - 1;
    while (i >= 0 && result[i] == 0) i--;

    BigInt res;
    res.value = "";
    while (i >= 0)
        res.value += std::to_string(result[i--]);
    return res;
}

BigInt BigInt::Div_2(const BigInt num){

    BigInt result;
    int carry = 0;

    for (char digit : num.value) {
        int currentDigit = digit - '0';
        int currentResult = (carry * 10 + currentDigit) / 2;
        carry = (carry * 10 + currentDigit) % 2;
        result.value += std::to_string(currentResult);
    }

    size_t leadingZeros = result.value.find_first_not_of('0');
    if (leadingZeros != std::string::npos) {
        result = result.value.substr(leadingZeros);
    } else {
        result = "0";
    }
    return result;
}

BigInt BigInt::operator++(int) {

    BigInt result = *this;
    int len = value.length();
    for (int i = len - 1; i >= 0; i--) {
        if (value[i] == '9') {
            value[i] = '0';
        } else {
            value[i]++;
            break;
        }
    }
    if (value[0] == '0') {
        value = '1' + value;
    }
    return result;
}

BigInt BigInt::operator--(int) {
    BigInt result = value;

       int carry = -1;

       for (int i = value.size() - 1; i >= 0; i--) {
           int currentDigit = value[i] - '0' + carry;
           carry = 0;

           if (currentDigit < 0) {
               currentDigit += 10;
               carry = -1;
           }

           value[i] = currentDigit + '0';
       }

       size_t leadingZeros = value.find_first_not_of('0');
       if (leadingZeros != std::string::npos) {
           value = value.substr(leadingZeros);
       } else {
           value = "0";
       }

       return result;
}

int BigInt::GetLen(const BigInt num){
    return num.value.length();
}

int BigInt::GetEnd(const BigInt num){
    return num.value[GetLen(num) - 1];
}



std::istream& operator>>(std::istream& in, BigInt& num) {
    std::string input;
    in >> input;
    num = BigInt(input);
    return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
    out << num.value;
    return out;
}
