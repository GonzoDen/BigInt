#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "BigInt.h"

using namespace std;

TEST_CASE("Constructors", "[constr]") {
		REQUIRE( BigInt().toString() == "0");

		
		REQUIRE_THROWS_AS( BigInt("5  0 "), runtime_error);

}

TEST_CASE("operator<<") {
	ostringstream out;
	out << BigInt();
}


