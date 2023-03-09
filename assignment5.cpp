// 40195538_Fung Sim LEUNG

#include "assignment5.h"

// Task 1
/* This function extracts the English words in a text file and generates a string vector.*/
WordsVector read_words_into_vector(const std::string& inFileName) {

	std::ifstream ifs(inFileName); // Create an input file stream
	if (!ifs.is_open()) { // Check that the file is open
		cout << "Could not open file " + inFileName << endl;
		throw std::runtime_error("Could not open file " + inFileName);	
	}
	WordsVector words_vector; // an empty vector

	std::istream_iterator<std::string> first(ifs);
	std::istream_iterator<std::string> last;

	std::copy(first, last, std::back_inserter(words_vector)); // start of input stream, end of input stream, destination
	return words_vector;
}

// Task 2
/* This function counts the frequency of each word in the vector using a lambda expression and generates a map container.*/
WordsMap map_and_count_words_using_lambda(const WordsVector& wvec)
{
	WordsMap wmap;		//Tthe keys are the words and the values are the frequency of the words.	
	auto f = [&](std::string word) {
		++wmap[word]; 
	};		// Declare a lamba expression to increment the frequency of a key.

	std::for_each(wvec.begin(), wvec.end(), f); // start of source, end of source,  lambda expression)	
	return wmap;	
}

// Task 3
/* This function counts the frequency of each word in the vector using a functor and generates a map container.
	 The class WordCountFunctor is declared in assignment5.h.
*/
void WordCountFunctor::operator()(string word) {		// Create a functor
	wmap[word]++;
}
// A method needed in the map_and_count_words_using_functor method. It returns a map.
WordsMap WordCountFunctor::getmap() {
	return wmap;
}
WordsMap map_and_count_words_using_functor(const WordsVector& wvec) {
	WordCountFunctor wcf{};
	wcf = std::for_each(wvec.begin(), wvec.end(), wcf);// start of source, end of source, a functor keeping trac of the frequencies

	return wcf.getmap();
}

//Task 4

/*A function to remove the duplicated words in the supplied words vector.
The SmallerThan function template is defined in the header file.
I need to to sort() to sort words_vec alphabetically, use unique() to rearrange the words in the
sorted words_vec, and use erase to remove  the range of non-unique	words*/

WordsVector remove_duplicates(const WordsVector& words_vector)
{
	WordsVector words_vec{ words_vector }; // make a copy of the supplied words_vector

	std::sort(words_vec.begin(), words_vec.end(), SmallerThan<string>());
	auto last = std::unique(words_vec.begin(), words_vec.end());

	words_vec.erase(last, words_vec.end());
	return words_vec;
}


// Task 5

/* A palindrome is a word or phrase that reads the same backward and forward,
	 This function determines whether a string is a palindrome.
	 I need a helper function is_not_alphabetic to check if a character in the phraes is non-alphabetical letter.
*/
bool is_not_alphabetic(char ch) {
	return (isalpha(ch) == 0);
}
bool is_palindrome(const std::string& phrase) {
	string temp;
	auto temp_it{ temp.begin() };		//	An iterator of the temp string
	// I need to use std::inserter because I don't know the length of the resultant string in advance.
	std::remove_copy_if(phrase.begin(), phrase.end(), std::inserter<std::string>(temp, temp_it), is_not_alphabetic);
	// I use a lambda express to convert an uppercase letter into lowercase letters. the transform() will shorten the length of phrase_to_check.
	auto lower = [=](char ch) { return (char)(tolower(ch)); };
	std::transform(temp.begin(), temp.end(), temp.begin(), lower);
	// I use equal() to compare the string with its reversed version.
	bool result = std::equal(temp.begin(), temp.end(), temp.rbegin(), temp.rend());

	return result;
}

//Task 6

/*  Write three functions that have the same return type and parameter lists of the form.
Using the count if algorithm, each function must count and return the number of elements in vec that are of
length n. */
size_t count_using_lambda(const std::vector<std::string>& vec, int n) {
	using namespace std::placeholders;

	// a lambda
	auto count_lambda = [=](string word, int n) {return (word.length() == n);  };
	auto f = std::bind(count_lambda, _1, n);
	size_t result = std::count_if(vec.begin(), vec.end(), f);
	return result;
}

// A free function
bool freeFunc(string word, int n) {
	return (word.length() == n);
}
size_t count_using_Free_Func(const std::vector<std::string>& vec, int n) {
	using namespace std::placeholders;
	auto unaryFreeFunc = std::bind(freeFunc, _1, n);
	size_t result = std::count_if(vec.begin(), vec.end(), unaryFreeFunc);
	return result;
}

// A functor
bool WordLengthChecker::operator()(string word, int n) {
	return (word.length() == n);
}
size_t count_using_Functor(const std::vector<std::string>& vec, int n) {
	WordLengthChecker wlc;
	using namespace std::placeholders;
	auto f = std::bind(wlc, _1, n);
	size_t result = std::count_if(vec.begin(), vec.end(), f);
	return result;
}

// Task 7
/* The function multisetUsingDefaultComparator has a multiset container 
	to store and sort the content of a vector of string using the default comparator std::less<T>. 
	The function then prints the sorted multiset.*/
void multisetUsingDefaultComparator(const std::vector<std::string>& vec)
{
	std::multiset<std::string> strSet; // an empty set
	//  source start and finish, destination start using a general inserter
	std::copy(vec.begin(), vec.end(), std::inserter(strSet, strSet.begin())); 
	// create an ostream_iterator attached to cout, using a space " " as a separator
	std::ostream_iterator<std::string> out(cout, " ");
	// output the set elements to the cout
	std::copy(strSet.begin(), strSet.end(), out);
}

/* The function multisetUsingMyComparator has a multiset container
	to store and sort the content of a vector of string using the user-defined comparator ShorterAndSmallerThan.
	The function then prints the sorted multiset.
	The ShorterAndSmallerThan is declared in assignment 5.h.*/
bool ShorterAndSmallerThan::operator() (const std::string& left, const std::string& right) const
{
	bool result = true;
	if ( (left.length() < right.length() ) && (left < right) ) {
		result = true;
	}
	else if ((left.length() == right.length()) && (left < right)) {
		result = true;
	}
	else if ((left.length() < right.length() ) && (left > right)) {
		result = true;
	}
	else {
		result = false;
	}
	return result;
}
// The version sorts the strings lexicographically.
void multisetUsingMyComparator(const std::vector<std::string>& vec)
{
	// I can only modify this line to use a user-defined comparator. So I created 
	std::multiset<std::string, ShorterAndSmallerThan> strSet; // an empty set
	std::copy(vec.begin(), vec.end(), std::inserter(strSet, strSet.begin())); 
	std::ostream_iterator<std::string> out(cout, " ");
	std::copy(strSet.begin(), strSet.end(), out);
}


// Task 8
/* This function generates the first N Fibonacci numbers using the std::generate n algorithm. */
std::vector<int> getnerate_Fibonacci(int n) {
	std::vector<int> vec(n);
	if (n >= 0) {
		vec[0] = 0;
	}
	if (n >= 1) {
		vec[1] = 1;
	}
	if (n >= 2) {
		auto vec_it{ vec.begin() };
		std::advance(vec_it, 2);
		std::generate_n(vec_it, n-2, Fibonacci());
	}
	return vec;
}