#include <rsa.h>
#include <catch.hpp>
#include <ttmath.h>
#include <vector>

SCENARIO("check every uniCODE")
{
	std::vector<int> char_codes;
	for (unsigned int i = 0; i < 109384; ++i)
	{
		char_codes.push_back(i);
	}
	
	typedef ttmath::UInt<64> MyInt;

	MyInt mess, e, p, d, res;
	
	Rsa rsa;
	Key keys = rsa.produce_keys();
	
	
	e = keys.ekey;
	p = keys.pkey;
	d = keys.dkey;
	
	std::vector<int> crypted_codes;
	for (unsigned int i = 0; i < char_codes.size(); ++i)
	{
		mess = char_codes.at(i);
		res = 0;
		int carry = powm(mess, e, p, res);
		int res_int = res.ToUInt();
		crypted_codes.push_back(res_int);
	}
	
	std::vector<int> decrypted_codes;
	for (unsigned int i = 0; i < crypted_codes.size(); ++i)
	{
		mess = crypted_codes.at(i);
		res = 0;
		int carry = powm(mess, d, p, res);
		int res_int = res.ToUInt();
		decrypted_codes.push_back(res_int);
	}
	
	REQUIRE (char_codes == decrypted_codes);
}