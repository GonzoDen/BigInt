#include "../catch.hpp"
#include "BigInt.h"

using namespace std;

int main() {
	BigInt a = BigInt("11111");
	BigInt b = BigInt("2");
	cout << (a / b);
}


