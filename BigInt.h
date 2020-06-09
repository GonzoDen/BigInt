#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

class BigInt
{
	std::vector<int> mDigits;
	bool isNegative;
	
	static BigInt slozhenie(const BigInt& a, const BigInt& b);
	static BigInt vychitanie(const BigInt& a, const BigInt& b);
	static BigInt umnozhenie(const BigInt& a, const BigInt& b);
	static BigInt umnozhenieRazByRaz(const BigInt& x, int64_t y);
	static BigInt delenie(const BigInt& a, const BigInt& b);
	static int sravnenie(const BigInt& a, const BigInt& b);

	
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator-(const BigInt& a, const BigInt& b);

	friend BigInt operator*(const BigInt& a, const BigInt& b);
	friend BigInt operator/(const BigInt& a, const BigInt& b);
	
	friend BigInt operator+(const BigInt& a);
	friend BigInt operator-(const BigInt& a);
	
	friend BigInt operator++(BigInt& x, int y);
	friend BigInt operator++(BigInt& x);
	friend BigInt operator--(BigInt& x, int y);
	friend BigInt operator--(BigInt& x);
	

	friend bool operator>(const BigInt& a, const BigInt& b);
	friend bool operator<(const BigInt& a, const BigInt& b);
	friend bool operator==(const BigInt& a, const BigInt& b);
	friend bool operator!=(const BigInt& a, const BigInt& b);
	friend bool operator<=(const BigInt& x, const BigInt& y);
	friend bool operator>=(const BigInt& x, const BigInt& y);
	friend std::istream& operator>> (std::istream& is, BigInt& a);
	
public:

	BigInt()
	: isNegative(false)
	{
		mDigits.push_back(0);
	}
	BigInt(std::string s);
	BigInt(std::uint64_t a) : BigInt(std::to_string(a)){}

	std::string toString() const;
};	

inline std::ostream& operator<<(std::ostream& out, const BigInt& x){
	return out << x.toString();
}

BigInt abs(const BigInt& x);	