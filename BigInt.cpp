#include "BigInt.h"
#include <string>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <limits>

using namespace std;

const size_t MaxSizeT = std::numeric_limits<size_t>::max();

BigInt::BigInt(string s)
	: isNegative(false)
{
	size_t i = 0;
	if (s.length() == 0){
			throw runtime_error("empty string");	
	}
	while (s[i] == ' '){
		i++;
		if (i == s.length()){
			throw runtime_error("empty string");
		}
	}
	if (s[i] == '+' || s[i] == '-'){
		if (s[i] == '-')
			isNegative = true;
		i++;
	}
	if (s[i] == '0'){
		while(s[i] == '0'){
			i++;
		}
	}
	while (true){
		if (i == s.length()){
			break;
		}
		if (isdigit(s[i])){
			mDigits.push_back(s[i]-'0');
			i++;
		}
		else
			break;			
	}
	
	if (i != s.length() && s[i] == ' '){
		while(s[i] == ' ')
			i++;
	}
	if (i != s.length())
			throw runtime_error("wrong string");
	else if (i == s.length() && mDigits.size() == 0){
			isNegative = false;
			mDigits.push_back(0);
	} 
}

string BigInt::toString() const
{
	string r;

	r += isNegative ? "-" : "";

	for (auto i : mDigits){
		r += char (i + '0');
	}
	return r;
}

void operator+=(BigInt& x, const BigInt& y){
	x = x + y;
}

void operator-=(BigInt& x, const BigInt& y){
	x = x - y;
}

void operator*=(BigInt& x, const BigInt& y){
	x = x * y;
}

void operator/=(BigInt& x, const BigInt& y){
	x = x / y;
}

BigInt operator++(BigInt& x, int y){ //prefix
 	BigInt a = x;
    x = x + 1;
 	return a;
}

BigInt operator++(BigInt& x){ //postfix
 	x = x + 1;
 	return x;
 }

BigInt operator--(BigInt& x, int y){
 	BigInt a = x;
    x = x - 1;
 	return a;
}

BigInt operator--(BigInt& x){ 			
 	x = x - 1;
 	return x;
 }



BigInt BigInt::slozhenie(const BigInt& x, const BigInt& y){
	
	
	BigInt r;
	
	r.mDigits.resize(max(x.mDigits.size(), y.mDigits.size())+1);
	
	size_t i = x.mDigits.size()-1;
	size_t j = y.mDigits.size()-1;
	size_t k = r.mDigits.size()-1;
	
	int carry = 0;
	while(i != MaxSizeT || j != MaxSizeT){
		int c = carry;
		
		if (i != MaxSizeT){
			c+= x.mDigits[i];
			i--;
		}
		
		if (j != MaxSizeT){
			c+= y.mDigits[j];
			j--;
		}
		
		carry = c/10;
		c = c%10;
		r.mDigits[k] = c;
		k--;
		
	}
	
	if (carry){
		r.mDigits[k] = 1;
	}
	else{
		r.mDigits.erase(r.mDigits.begin());
	}
	
	return r;
}

BigInt operator+(const BigInt& x, const BigInt& y){
	BigInt r;
	
	if (x.isNegative == y.isNegative){
		r = BigInt::slozhenie(x,y);
		r.isNegative = x.isNegative;
	}
	else{
		if (y.isNegative){
			 r = BigInt::vychitanie(x,y);
		}
		else {
			 r = BigInt::vychitanie(y,x);
		}
	}
	
	return r;
}

BigInt BigInt::vychitanie(const BigInt& x, const BigInt& y){
	
	BigInt r;
	BigInt a = x;
	BigInt b = y;
	b.isNegative = false;
	
	if (y == 0){
		r.mDigits = a.mDigits;
		return r;
	}
	
	if (a < b){ 				//ili vse-taki override?
		r.isNegative = true;
		
		BigInt c;
		c = a;
		a = b;
		b = c;
		
	}
	
	r.mDigits.resize(a.mDigits.size());
	
	size_t i = a.mDigits.size()-1;
	size_t j = b.mDigits.size()-1;
	size_t k = r.mDigits.size()-1;
	
	int carry = 0;
	while (i != MaxSizeT){
		int c = a.mDigits[i] - carry;
		carry = 0;
		if (j != MaxSizeT){
			if (b.mDigits[j] > c){
				c+= 10;
				carry = 1;
			}
			c -= b.mDigits[j];
			j--;
		}
		if (c < 0){
			c = 9;
			carry = 1;
		}
		r.mDigits[k] = c;
		k--;
		i--;
	}
	
	while (r.mDigits[0] == 0){
		if (r.mDigits.size() == 0){
			r.mDigits.push_back(0);
			break;
		}
		r.mDigits.erase(r.mDigits.begin());
	}
	
	return r;
}

BigInt operator-(const BigInt& x, const BigInt& y){
	if (!x.isNegative && !y.isNegative){
		return BigInt::vychitanie(x,y);
	}
	else if (!x.isNegative && y.isNegative){
		return BigInt::slozhenie(x,y);
	}
	else if (x.isNegative && !y.isNegative){
		BigInt r = BigInt::slozhenie(x,y);
		r.isNegative = true;
		return r;
	}
	else {
		BigInt a = y;
		a.isNegative = false;
		return BigInt::vychitanie(a,x);
	}
}

BigInt BigInt::umnozhenie(const BigInt& x, const BigInt& y){ // TODO: recheck algorithm
	
	BigInt r;
	
	r.mDigits.resize(x.mDigits.size()+y.mDigits.size());
	
	BigInt verh;						
	BigInt niz;
	
	size_t j;
	
	if (x.mDigits.size() > y.mDigits.size()){
		verh = x;
		niz = y;
		j = y.mDigits.size()-1;
	}
	else {
		verh = y;
		niz = x;
		j = x.mDigits.size()-1;
	}
	
	verh.isNegative = false;
	niz.isNegative = false;
	
	r = BigInt::umnozhenieRazByRaz(verh, niz.mDigits[j]);
	j--;
	
	while (j != MaxSizeT) {
		BigInt b = BigInt::umnozhenieRazByRaz(verh, niz.mDigits[j]);
		b.mDigits.resize(b.mDigits.size()+ (niz.mDigits.size()-j-1));
		if (b.mDigits[0] == 0){

		}
		r += b;
		j--; 	
	}
	return r;
}

BigInt BigInt::umnozhenieRazByRaz(const BigInt& x, int64_t y){
	
	if (y == 1){
		return x;
	}
	
	if (x == 1){ 		
		return y;
	}
	
	if (y == 0){
		return 0;
	}
	
	if (x == 0){		
		return 0;
	}
	
	
	BigInt r;
	
	r.mDigits.resize(x.mDigits.size()+1);
	
	size_t i = x.mDigits.size()-1;
	size_t j = r.mDigits.size()-1;

	int carry = 0;
	
	while (i != MaxSizeT){
		int c = x.mDigits[i] * y + carry;
		carry = c/10;
		c %= 10;
		r.mDigits[j] = c;
		j--;
		i--;
	}
	
	if (carry > 0){
		r.mDigits[0] = carry;
	}
	else{
		r.mDigits.erase(r.mDigits.begin());
	}
	
	return r;
}

BigInt operator*(const BigInt& x, const BigInt& y){
	if (x == 0 || y == 0){
		return 0;
	}
	if (x.isNegative == y.isNegative){
		BigInt r = BigInt::umnozhenie(x,y);
		r.isNegative = false; 
		return r;
	}
	else{
		BigInt r = BigInt::umnozhenie(x,y);
		r.isNegative = true;
		return r; 
	}
}

BigInt BigInt::delenie(const BigInt& a, const BigInt& b)
{
	BigInt verh = abs(a);
	BigInt niz = abs(b);
	if(niz == 1){
		return verh;
	}
		
	BigInt i(1);
	while(i * niz < verh){
		i++;
		if(i * i * i * niz < verh){
			i = i * i * i;
		} 
	}
	return i;
}

BigInt operator/(const BigInt& a, const BigInt& b)
{
	BigInt r = BigInt::delenie(a,b);
	if(a.isNegative == b.isNegative){
		return r;
	}else{
		r.isNegative = true;
		return r;
	}	
}

BigInt operator-(const BigInt& a)
{
	BigInt r = a;
	r.isNegative = !r.isNegative;
	return r;
		
}

BigInt operator+(const BigInt& a)
{
	BigInt r = a;
	return r;
		
}

int BigInt::sravnenie(const BigInt& x, const BigInt& y){
	if (!x.isNegative && y.isNegative){
		return 1;
	}
	if (x.isNegative && !y.isNegative){
		return -1;
	}
	else{
		if (x.mDigits.size() > y.mDigits.size()){
			return x.isNegative ? -1 : 1;
		}
		else if (x.mDigits.size() < y.mDigits.size()){
			return x.isNegative ? 1 : -1;
		}
		else{
			for (int i =0; i < x.mDigits.size(); i++){
				if (x.mDigits[i] > y.mDigits[i]){
					return x.isNegative ? -1 : 1;
				}
				else if (x.mDigits[i] < y.mDigits[i]){
					return x.isNegative ? 1 : -1;
				}
			}
			return 0;
		}
	}
}

BigInt abs(const BigInt& x) {
	BigInt a = x;
	if (a < 0)
		a = -a;
	return a;
}

bool operator==(const BigInt& x, const BigInt& y){ 
	if (BigInt::sravnenie(x,y) == 0)
		return true;
	return false;	 
}

bool operator!=(const BigInt& x, const BigInt& y){ 
	if (BigInt::sravnenie(x,y) != 0)
		return true;
	return false;	 
}



bool operator>(const BigInt& x, const BigInt& y){
	if (BigInt::sravnenie(x,y) == 1)
		return true;
	return false;
}

bool operator<(const BigInt& x, const BigInt& y){
	if (BigInt::sravnenie(x,y) == -1)
		return true;
	return false;
}



bool operator<=(const BigInt& x, const BigInt& y){
	int a = BigInt::sravnenie(x,y);
	if (a == -1 || a == 0)
		return true;
	return false;
}

bool operator>=(const BigInt& x, const BigInt& y){
	int a = BigInt::sravnenie(x,y);
	if (a == 1 || a == 0)
		return true;
	return false;
}

istream& operator>> (istream& is, BigInt& a) {
		a = BigInt();
		a.mDigits.pop_back();
		a.isNegative = false;
		char ch;
		if (!(is.get(ch)))
			return is;
		while (isspace(ch)){
			is.get(ch);
		}
		if (ch == '-' || ch == '+'){
			if (ch == '-'){
				a.isNegative = true;
				is.get(ch);
			}
		}
		
		if (isdigit(ch)){
			a.mDigits.push_back(ch-'0');
		
			while(is.get(ch)){
				if (isdigit(ch))
					a.mDigits.push_back(ch-'0');
				else {
					is.unget();
					return is;
				}
			}      
		}
		else{
			is.setstate(ios_base::failbit);
			return is;
		}
	
	return is;
}








