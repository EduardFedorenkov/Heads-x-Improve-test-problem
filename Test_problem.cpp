//============================================================================
// Name        : Test_problem.cpp
// Author      : Fedorenkov Eduard
// Description : Heads x Improve test problem in C++
//============================================================================

#include "test_runner.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <random>
#include <ctime>
using namespace std;

template<typename T, typename Distr, typename RandGen>
vector<T> VectorRandomFilling(size_t n, Distr& distribution, RandGen& random_gen, bool IsUniq){

	vector<T> result;
	if(IsUniq){       // Unique filling of the vector
		set<T> uniq_set;

		while(uniq_set.size() != n){                                // Checking if set of sizes is enough
			T random_element = distribution(random_gen);
			if(uniq_set.insert(random_element).second == true){     // Checking if new size is unique
				result.push_back(random_element);
			}
		}
	}else{           // Not unique filling of the vector
		for(size_t i = 0; i < n; ++i){
			result.push_back(distribution(random_gen));
		}
	}

	return result;
}


template<typename T, typename Distr>
vector<vector<T>> GetSortedVectors(size_t n, const T& min_rand_num, const T& max_rand_num,
		const size_t& min_rand_size, const size_t& max_rand_size){

	if(max_rand_size - min_rand_size + 1 < n){                   // Checking the validity of parameters "min_rand_size" and "max_rand_size"
		throw invalid_argument("The range of vector sizes is not large enough for the consciousness of vectors of unique sizes");
	}
	vector<vector<T>> result;

	mt19937 random_gen(time(0));
	Distr distribution_for_numbers(min_rand_num, max_rand_num);
	uniform_int_distribution<size_t> distribution_for_sizes(min_rand_size, max_rand_size);

	vector<size_t> sizes = VectorRandomFilling<size_t>(n, distribution_for_sizes, random_gen, true); // true -> unique filling of the sizes vector

	bool flag = true;     /* flag for sort
	                       * true -> Ascending sort
	                       * false -> Descending sort
	                       */
	for(size_t size : sizes){
		vector<T> tmp = VectorRandomFilling<T>(size, distribution_for_numbers, random_gen, false);// false -> not unique filling of the numbers vector
		if(flag){
			sort(begin(tmp),end(tmp));
			flag = false;
		}else{
			sort(rbegin(tmp),rend(tmp));
			flag = true;
		}
		result.push_back(tmp);
	}

	return result;
}

template<typename T>
ostream& operator<< (ostream& out, const vector<vector<T>>& x){
	for(auto& vec : x){
		for(auto& num : vec){
			out << num << ' ';
		}
		cout << "\n";
	}
	return out;
}

void TsetVectorUniqRandomFilling(){
	mt19937 random_gen(time(0));
	uniform_int_distribution<int> distribution(-5,4);
	vector<int> vec = VectorRandomFilling<int>(10, distribution, random_gen, true);
	set<int> vec_copy(begin(vec), end(vec));
	ASSERT_EQUAL(vec.size(), vec_copy.size());
}

void TestIsSorted(){
	size_t vectors_number = 4;
	int min_number = -5;
	int max_number = 4;
	size_t min_vector_size = 5;
	size_t max_vector_size = 15;
	vector<vector<int>> vec = GetSortedVectors<int, uniform_int_distribution<int>>
			(vectors_number,min_number,max_number,min_vector_size,max_vector_size);
	ASSERT(is_sorted(vec[0].begin(), vec[0].end()));
	ASSERT(is_sorted(vec[2].begin(), vec[2].end()));
	ASSERT(is_sorted(vec[1].begin(), vec[1].end(), [](int lhs, int rhs){return lhs > rhs;}));
	ASSERT(is_sorted(vec[3].begin(), vec[3].end(), [](int lhs, int rhs){return lhs > rhs;}));
}


int main() {
	TestRunner tr;
	RUN_TEST(tr, TsetVectorUniqRandomFilling);
	RUN_TEST(tr, TestIsSorted);

	try{
		size_t vectors_number = 10;
		int min_number = 0;
		int max_number = 100;
		size_t min_vector_size = 1;
		size_t max_vector_size = 10;

		// GetSortedVectors<"type of numbers", "distribution for numbers">(arguments)

		auto vv = GetSortedVectors<size_t, uniform_int_distribution<size_t>>
				(vectors_number,min_number,max_number,min_vector_size,max_vector_size);
		cout << vv;
	}catch(invalid_argument& ia){
		cerr << "Invalid argument : " << ia.what() << "\n";
	}
	return 0;
}
