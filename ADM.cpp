// ADM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Ch04.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	// stack
	/*Stack stack;
	vector<int> vec = { 1, 2 ,3, 0 };
	for (int v : vec) {
		stack.push(v);
		cout << stack.minElement() << ' ';
	}
	cout << endl;*/

	// ch04
	Ch04 ch04;
	vector<vector<int>> indices;
	vector<int> vec = { 1,4,5 };
	indices.push_back(vec);
	vec = { 3,9,10 }; indices.push_back(vec);
	vec = { 2,6,15 }; indices.push_back(vec);

	vector<int> rst = ch04.smallestSnippet45(indices);
	system("pause");
    return 0;
}

