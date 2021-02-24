# Heads-x-Improve-test-problem
Heads x Improve test problem in C++

The repository contains the solution to the test problem.

Discription of the main functions:
1) template<typename T, typename Distr, typename RandGen> vector<T> VectorRandomFilling(size_t n, Distr& distribution, RandGen& random_gen, bool IsUniq);

  The VectorRandomFilling returns a vector of size n. The vector is filled with random numbers of type T, distributed over the distribution using random generator random_gen. Random numbers are unique if IsUniq == true or not unique if IsUniq == false.
  
2) template<typename T, typename Distr> vector<vector<T>> GetSortedVectors(size_t n, const T& min_rand_num, const T& max_rand_num, const size_t& min_rand_size, const size_t& max_rand_size);

  The GetSortedVectors returns a vector of size n. The vector is filled with vectors of random unique sizes from "min_rand_size" to "max_rand_size". Each vector is filled with random numbers with distribution type of Distr from "min_rand_num" to "max_rand_num".
  The GetSortedVectors throw exception "ivalid_argument" if range [min_rand_size, max_rand_size] is not enough to build "n" unique sizes of vectors.
  Example of using GetSortedVectors: 
  
            // GetSortedVectors<"type of numbers", "distribution for numbers">(arguments)
        		auto vv = GetSortedVectors<size_t, uniform_int_distribution<size_t>>(vectors_number,min_number,max_number,min_vector_size,max_vector_size);
            
		           
