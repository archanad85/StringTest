#include "MegaString.h"
#include <string.h>
#include <iostream>

int main()
{
	MegaString(testStr);

	testStr = "Hello";

	//Test GetString
	std::cout << testStr.data() << '\n';

	//Test GetLength
	std::cout << testStr.length() << '\n';

	//Test empty
	std::cout << testStr.empty() << '\n';

	//Test String assignment
	testStr.operator=("Is this fine ?");
	std::cout << testStr.data() << '\n';

	//Test ClearString
	testStr.clear();
	std::cout << "Test data" << testStr.data() << '\n';

	//Test replace
	MegaString(replaceStr);
	testStr = "Hi are you doing ?";
	replaceStr = "How ";
	testStr.replace(3, 0, replaceStr);
	std::cout << "Replace string:" << testStr.data() << '\n';

	//Test append
	replaceStr = "?? Is all good?";
	testStr.append(replaceStr);
	std::cout << "Appended string:" << testStr.data() << '\n';

	//Test pop back
	testStr.pop_back();
	std::cout << "After pop back string:" << testStr.data() << '\n';

	//Test push back
	testStr.push_back('c');
	std::cout << "After push back string:" << testStr.data() << '\n';

	return 0;

}

