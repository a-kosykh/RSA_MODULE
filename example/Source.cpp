#include "testclass.hpp"
int main() {
	BinarySearchTree<int> obj;
	try {
		if (obj.fileIn("testin.txt") == 1)
			throw "Can't open the file";
	}
	catch (const char* msg) {
		cout << msg << endl;
	}
	obj.remove(16);
	obj.paintTree();
	obj.Out("testout.txt");
	system("pause");
	return 0;
}