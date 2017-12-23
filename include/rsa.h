#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "ttmath.h"

typedef ttmath::UInt<64> MyInt;

typedef struct key
{
	MyInt pkey;
	MyInt ekey;
	MyInt dkey;
} Key;

class Rsa
{
public:
	Rsa();
	virtual ~Rsa();

public:
	Key produce_keys();
	long endecrypt(const long msg, const long key, const long pkey);

private:
	MyInt produce_pkey(const MyInt prime1, const MyInt prime2);
	MyInt produce_ekey(const MyInt orla);
	MyInt produce_dkey(const MyInt ekey, const MyInt orla);
	MyInt produce_prime();
	MyInt produce_orla(const MyInt prime1, const MyInt prime2);
	MyInt produce_gcd(const MyInt a, const MyInt b);
	bool is_prime(const MyInt digit);
};

template<typename Integer>
int powm(const Integer & base, const Integer & exponent,
	const Integer & modulus, Integer & result)
{
	int c = 0;
	Integer rem, b, e;

	if ((base == 0 && exponent == 0) || modulus == 0)
		return 1;

	result = 1;
	b = base;
	e = exponent;

	while (e > 0)
	{
		if (e.IsTheLowestBitSet())
		{
			c += result.Mul(b);
			c += result.Div(modulus, &rem);
			result = rem;
		}

		e.Rcr(1);

		c += b.Mul(b);
		c += b.Div(modulus, &rem);
		b = rem;
	}

	return (c > 0) ? 1 : 0;
}