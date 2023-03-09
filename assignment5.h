// 40195538_Fung Sim LEUNG

#pragma once

#ifndef ASSIGNMENT5_H_
#define ASSIGNMENT5_H_

#include <cassert>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <set>
#include <map>

using std::string;
using std::cin;
using std::cout;
using std::endl;
// Type aliases
class assignment5
{
};

#endif

using WordsVector = std::vector<std::string>;
using WordsMap = std::map<std::string, size_t>;


// This class is used to create a functor of WordCountFunctor.
class WordCountFunctor {
private:
	WordsMap wmap;
public:
	void operator()(string word);		// Create a functor
	WordsMap getmap();
};

// We use this helper function to compare words alphabetically.
template<class T> class SmallerThan
{
public:
	bool operator()(const T& obj1, const T& obj2)
	{
		return (obj1 < obj2);
	}
};

// This class is used to create a functor of WordCountFunctor.
class WordLengthChecker {
public:
	bool operator()(string word, int n);		// Create a functor
};

class ShorterAndSmallerThan
{
public:
	bool operator() (const std::string& left, const std::string& right) const;
};

class Fibonacci
{
	int num1{ 0 };
	int num2{ 1 };
public:
	Fibonacci() = default;
	int operator() () {
		int result = num1 + num2;
		num1 = num2;
		num2 = result;
		return result;
	}
};
WordsVector read_words_into_vector(const std::string& inFileName);
WordsMap map_and_count_words_using_lambda(const WordsVector& wvec);
WordsMap map_and_count_words_using_functor(const WordsVector& wvec);
WordsVector remove_duplicates(const WordsVector& words_vector);
bool is_palindrome(const std::string& phrase);
size_t count_using_lambda(const std::vector<std::string>& vec, int n);
size_t count_using_Free_Func(const std::vector<std::string>& vec, int n);
size_t count_using_Functor(const std::vector<std::string>& vec, int n);
void multisetUsingMyComparator(const std::vector<std::string>& vec);
void multisetUsingDefaultComparator(const std::vector<std::string>& vec);
std::vector<int> getnerate_Fibonacci(int n);


