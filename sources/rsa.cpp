#include "rsa.h"
#include "ttmath.h"

typedef ttmath::UInt<64> MyInt;

using namespace std;

Rsa::Rsa()
{
}

Rsa::~Rsa()
{
}


unsigned long long llrand() {
	unsigned long long r = 0;

	for (int i = 0; i < 5; ++i) {
		r = (r << 15) | (rand() & 0x7FFF);
	}

	return r & 0xFFFFFFFFFFFFFFFFULL;
}

long lrand()
{
	if (sizeof(int) < sizeof(long))
		return (static_cast<long>(rand()) << (sizeof(int) * 8)) |
		rand();

	return rand();
}

MyInt gcdExtended(MyInt a, MyInt b, MyInt *x, MyInt *y);

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
	MyInt prime1 = produce_prime();
	MyInt prime2 = produce_prime();
	while (prime2 == prime1)
		prime2 = produce_prime();
	
	std::cout << "Prime1: " << prime1 << "\n";
	std::cout << "Prime2: " << prime2 << "\n";

	Key key;
	MyInt orla = produce_orla(prime1, prime2);
	std::cout << "orla: " << orla << "\n";
	
	key.pkey = produce_pkey(prime1, prime2);
	key.ekey = produce_ekey(orla);
	key.dkey = produce_dkey(key.ekey, orla);
	return key;
}

MyInt Rsa::produce_pkey(const MyInt prime1, const MyInt prime2)
{
	return prime1 * prime2;
}


MyInt Rsa::produce_orla(const MyInt prime1, const MyInt prime2)
{
	return (prime1 - 1) * (prime2 - 1);
}

MyInt Rsa::produce_ekey(const MyInt orla)
{
	MyInt ekey;
	while (true)
	{
		MyInt rand_big = llrand();
		ekey = rand_big % orla;
		if (ekey >= 2 && produce_gcd(ekey, orla) == 1)
			break;
	}
	if (ekey > orla) {
		produce_ekey(orla);
	}
	else
		return ekey;
}


//MyInt Rsa::produce_dkey(const MyInt ekey, const MyInt orla) {
//	MyInt b = orla;
//	MyInt a = ekey;
//	MyInt b0 = b, t, q;
//	MyInt x0 = 0, x1 = 1;
//	if (b == 1) return 1;
//	while (a > 1) {
//		q = a / b;
//		t = b, b = a % b, a = t;
//		t = x0, x0 = x1 - q * x0, x1 = t;
//	}
//	if (x1 < 0) x1 += b0;
//	return x1;
//}


//MyInt Rsa::produce_dkey(const MyInt ekey, const MyInt orla) {
//	MyInt x, y;
//	MyInt g = gcdExtended(ekey, orla, &x, &y);
//	if (g != 1)
//		cout << "Inverse doesn't exist";
//	else
//	{
//		// m is added to handle negative x
//		MyInt res = (x % orla + orla) % orla;
//		return res;
//	}
//}

MyInt Rsa::produce_dkey(const MyInt ekey, const MyInt orla) {
	MyInt inv, u1, u3, v1, v3, t1, t3, q;
	int iter;
	/* Step X1. Initialise */
	u1 = 1;
	u3 = ekey;
	v1 = 0;
	v3 = orla;
	/* Remember odd/even iterations */
	iter = 1;
	/* Step X2. Loop while v3 != 0 */
	while (v3 != 0)
	{
		/* Step X3. Divide and "Subtract" */
		q = u3 / v3;
		t3 = u3 % v3;
		t1 = u1 + q * v1;
		/* Swap */
		u1 = v1; v1 = t1; u3 = v3; v3 = t3;
		iter = -iter;
	}
	/* Make sure u3 = gcd(u,v) == 1 */
	if (u3 != 1)
		return 0;   /* Error: No inverse exists */
					/* Ensure a positive result */
	if (iter < 0)
		inv = orla - u1;
	else
		inv = u1;
	return inv;
}

MyInt gcdExtended(MyInt a, MyInt b, MyInt *x, MyInt *y) {
	// ќбычный случай
	if (a == 0)
	{
		*x = 0, *y = 1;
		return b;
	}

	MyInt x1, y1; // ƒл€ хранени€ результатов рекурсивного вызова
	MyInt gcd = gcdExtended(b%a, a, &x1, &y1);

	// ќбновл€ес результаты, использу€ результаты рекурсии
	// вызов
	*x = y1 - (b / a) * x1;
	*y = x1;

	return gcd;
}

MyInt Rsa::produce_prime()
{
	long prime = 0;
	srand(time(0));
	while (true)
	{
		prime = llrand() % 1000000;
		if (is_prime(prime))
			break;
	}
	MyInt big_rand = prime;
	return big_rand;
}


MyInt Rsa::produce_gcd(const MyInt a, const MyInt b)
{
	MyInt dividend = a;
	MyInt divisor = b;
	MyInt residual = dividend % divisor;
	while (residual != 0)
	{
		dividend = divisor;
		divisor = residual;
		residual = dividend % divisor;
	}
	return divisor;
}


bool Rsa::is_prime(const MyInt digit)
{
	MyInt tmp = 2;
	while (tmp < digit) {

		if (digit % tmp++ == 0)
			break;
	}
	if (tmp == digit)
		return true;
	return false;
}

