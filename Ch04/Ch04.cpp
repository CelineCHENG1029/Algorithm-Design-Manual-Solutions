#include "stdafx.h"
#include "Ch04.h"

using namespace std;

void Stack::push(int x) {
	if (count == N) {
		throw std::out_of_range("Stack::push(): stack is full");
	}
	else {
		if (x < minElem) {
			arr[count] = x - minElem;
			minElem = x;			
		}
		else {
			arr[count] = x;			
		}
		++count;
	}
}

void Stack::pop() {
	if (count == 0) {
		throw std::out_of_range("Stack::pop(): stack is empty");
	}
	else {
		--count;
		if (arr[count] < minElem) {
			minElem -= arr[count];
		}
	}
}

int Stack::minElement() {
	if (count == 0) {
		throw std::out_of_range("Stack::pop(): stack is empty");
	}
	else {
		return minElem;
	}
}

vector<int> Ch04::smallestSnippet45(vector<vector<int>>& indices) {
	int n = indices.size();
	set<int> s;
	map<int, char> m;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < indices[i].size(); ++j) {
			m[indices[i][j]] = 'A' + i;
		}
		s.insert(indices[i][0]);
	}
	vector<int> col(n, 1);
	int dist = INT_MAX;
	vector<int> result;
	while (1) {

		if ((*s.rbegin()) - (*s.begin()) < dist) {
			dist = (*s.rbegin()) - (*s.begin());
			result = { (*s.begin()), (*s.rbegin()) };
		}

		int row = m[(*s.begin())] - 'A';
		if (col[row] == (int)indices[row].size()) {
			break;
		}
		s.erase(s.begin());
		++col[row];
		s.insert(indices[row][col[row]-1]);
	}

	return result;
}
