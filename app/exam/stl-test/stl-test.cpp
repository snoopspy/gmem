#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "gmem.h"

using namespace std;

void malloc_test() {
	malloc(100);
}

void new_test() {
	new char[200];
}

void vector_test() {
	vector<uint64_t> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	v.push_back(9);
	v.push_back(10);

	for (vector<uint64_t>::iterator it = v.begin(); it != v.end(); it++)
		printf("%ld\n", *it);
}

void list_test() {
	list<uint64_t> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);
	l.push_back(6);
	l.push_back(7);
	l.push_back(8);
	l.push_back(9);
	l.push_back(10);

	for (list<uint64_t>::iterator it = l.begin(); it != l.end(); it++)
		printf("%ld\n", *it);
}

void set_test() {
	set<uint64_t> s;
	s.insert(1);
	s.insert(2);
	s.insert(3);
	s.insert(4);

	for (set<uint64_t>::iterator it = s.begin(); it != s.end(); it++)
		printf("%ld\n", *it);
}

void map_test() {
	map<uint64_t, uint64_t> m;
	m.insert({1, 100});
	m.insert({2, 200});
	m.insert({3, 300});
	m.insert({4, 400});

	for (map<uint64_t, uint64_t>::iterator it = m.begin(); it != m.end(); it++)
		printf("%ld %ld\n", it->first, it->second);
}

void unordered_set_test() {
	unordered_set<uint64_t> us;
	us.insert(1);
	us.insert(2);
	us.insert(3);
	us.insert(4);
	us.insert(5);
	us.insert(6);
	us.insert(7);
	us.insert(8);
	us.insert(9);
	us.insert(10);
	us.insert(11);
	us.insert(12);
	us.insert(13);
	us.insert(14);
	us.insert(15);
	us.insert(16);
	us.insert(17);
	us.insert(18);
	us.insert(19);
	us.insert(20);

	for (unordered_set<uint64_t>::iterator it = us.begin(); it != us.end(); it++)
		printf("%ld\n", *it);
}

void unordered_map_test() {
	unordered_map<uint64_t, uint64_t> um;
	um.insert({1, 100});
	um.insert({2, 200});
	um.insert({3, 300});
	um.insert({4, 400});
	um.insert({5, 500});
	um.insert({6, 600});
	um.insert({7, 700});
	um.insert({8, 800});
	um.insert({9, 900});
	um.insert({10, 1000});
	um.insert({11, 1100});
	um.insert({12, 1200});
	um.insert({13, 1300});
	um.insert({14, 1400});
	um.insert({15, 1500});
	um.insert({16, 1600});
	um.insert({17, 1700});
	um.insert({18, 1800});
	um.insert({19, 1900});
	um.insert({20, 2000});

	for (unordered_map<uint64_t, uint64_t>::iterator it = um.begin(); it != um.end(); it++)
		printf("%ld %ld\n", it->first, it->second);
}

int main() {
	gmem_set_verbose(true);

	// malloc_test();
	// new_test();

	// vector_test();
	// list_test();
	// set_test();
	// map_test();
	// unordered_set_test();
	// unordered_map_test();
}
