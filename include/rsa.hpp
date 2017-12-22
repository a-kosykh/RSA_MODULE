#pragma once
#include <cstdlib>
#include <ctime>
typedef struct key
{
	long pkey;
	long ekey;
	long dkey;
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
	long produce_pkey(const long prime1, const long prime2);
	long produce_ekey(const long orla);
	long produce_dkey(const long ekey, const long orla);
	long produce_prime();
	long produce_orla(const long prime1, const long prime2);
	long produce_gcd(const long a, const long b);
	bool is_prime(const long digit);
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