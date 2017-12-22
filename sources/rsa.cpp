#include "rsa.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Rsa::Rsa()
{
}

Rsa::~Rsa()
{
}

long Rsa::endecrypt(const long msg, const long key, const long pkey)
{
	long msg_des = 1;
	long root = msg;
	long index = key;
	while (index)
	{
		if (index & 1)
			msg_des = (msg_des * root) % pkey;
		index >>= 1;
		root = (root * root) % pkey;
	}
	return msg_des;
}

Key Rsa::produce_keys()
{
	long prime1 = produce_prime();
	long prime2 = produce_prime();
	while (prime2 == prime1)
		prime2 = produce_prime();

	Key key;
	long orla = produce_orla(prime1, prime2);
	key.pkey = produce_pkey(prime1, prime2);
	key.ekey = produce_ekey(orla);
	key.dkey = produce_dkey(key.ekey, orla);
	return key;
}

long Rsa::produce_pkey(const long prime1, const long prime2)
{
	return prime1 * prime2;
}


long Rsa::produce_orla(const long prime1, const long prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}

long Rsa::produce_ekey(const long orla)
{
	long ekey;
	while (true)
	{
		ekey = rand() % orla;
		if (ekey >= 2 && produce_gcd(ekey, orla) == 1)
			break;
	}
	return ekey;
}

//long Rsa::produce_dkey(const long ekey, const long orla)
//{
//	long dkey = orla / ekey;
//	while (true)
//	{
//		if (((dkey * ekey) % orla) == 1)
//			break;
//		else
//			++dkey;
//	}
//	return dkey;
//}
long Rsa::produce_dkey(const long ekey, const long orla) {
	int b = orla;
	int a = ekey;
	long b0 = b, t, q;
	long x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}


long Rsa::produce_prime()
{
	long prime = 0;
	srand(time(0));
	while (true)
	{
		prime = rand() % (2000 + 1 - 1000) + 1000;
		if (is_prime(prime))
			break;
	}
	return prime;
}


long Rsa::produce_gcd(const long a, const long b)
{
	long dividend = a;
	long divisor = b;
	long residual = dividend % divisor;
	while (residual)
	{
		dividend = divisor;
		divisor = residual;
		residual = dividend % divisor;
	}
	return divisor;
}


bool Rsa::is_prime(const long digit)
{
	int tmp = 2;
	while (tmp < digit)
		if (!(digit % tmp++))
			break;

	if (tmp == digit)
		return true;
	return false;
}

