#pragma once

#include <stdexcept>
#include <climits>
#include <vector>
#include <set>
#include <map>
// #include <cstddef> // for size_t

using namespace std;

class Stack {
private:
	static const int N = 10000;
	int arr[N];
	int count = 0;
	int minElem = INT_MAX;
public:
	void push(int x);
	void pop();
	int minElement();
};

class Ch04 {
public:
	vector<int> smallestSnippet45(vector<vector<int>>& indices);
};
