#include "rsa.hpp"
int main() {
	Rsa rsa; // объявление переменной класса RSA (делают оба человека)

// генерация ключей и шифрование сообщения
	Key keys = rsa.produce_keys(); // генерация ключей (делает только тот, кто принимает)

// ......отправка ключей.........

	long crypt = 9635; // сообщение 
	crypt = rsa.endecrypt(crypt,keys.ekey,keys.pkey); // шифрование 
// 						    (сообщение, экспонента, публичный ключ) 

	crypt = rsa.endecrypt(crypt,keys.dkey,keys.pkey); // расшифровка 
//                    (зашифр. сообщение, приватный, публичный)

	return 0;
}