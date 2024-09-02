#include "bigint.h"

BigInt my_pow(BigInt a, BigInt b){

    if(b.GetLen(b) == 1 && b.GetEnd(b) == 49) return a;
    if (b.GetEnd(b) % 2 == 0){
        return my_pow(a * a, b.Div_2(b));
    }
    b--;

    return a * my_pow(a, b);
}

int main()
{
    BigInt a(3);
    BigInt b, c;

    std::cin >> b;

    c = my_pow(a, b);

    std::cout << c;

    return 0;
}
