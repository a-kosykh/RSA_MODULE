#include <rsa.h>
#include <catch.hpp>
#include <ttmath.h>
#include <vector>

SCENARIO("check every uniCODE")
{
	MyInt bignum = "666666666666666666666";
	MyInt message, result;

	Rsa rsa;
	Key keys;
	do {
		keys = rsa.produce_keys();
	} while (keys.dkey > bignum);

	std::cout 
		<< "(private) d: " << keys.dkey << "\n" 
		<< "(public) exp: " << keys.ekey << "\n" 
		<< "(public) p: " << keys.pkey << "\n";

	std::vector<MyInt> char_codes;
	for (unsigned int i = 0; i < 1000; ++i) {
		char_codes.push_back(i);
	}
	
	std::vector<MyInt> crypted_codes;
	for (unsigned int i = 0; i < char_codes.size(); ++i)
	{
		message = char_codes.at(i);
		result = 0;
		int carry = powm(message, keys.ekey, keys.pkey, result);
		crypted_codes.push_back(result);
	}

	std::vector<MyInt> decrypted_codes;
	for (unsigned int i = 0; i < crypted_codes.size(); ++i) {
		message = crypted_codes.at(i);
		result = 0;
		int carry = powm(message, keys.dkey, keys.pkey, result);
		decrypted_codes.push_back(result);
	}
	
	bool check = false;
	if (char_codes == decrypted_codes)
		check = true;
	
	REQUIRE (check == true);
}