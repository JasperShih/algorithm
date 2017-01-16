/*
A zero-indexed array A consisting of N different integers is given. The array contains integers in the range [1..(N + 1)], which means that exactly one element is missing.

Your goal is to find that missing element.

Write a function:

int solution(vector<int> &A);
that, given a zero-indexed array A, returns the value of the missing element.

For example, given array A such that:

  A[0] = 2
  A[1] = 3
  A[2] = 1
  A[3] = 5
the function should return 4, as it is the missing element.

Assume that:

N is an integer within the range [0..100,000];
the elements of A are all distinct;
each element of array A is an integer within the range [1..(N + 1)].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.
*/
int solution(vector<int> &vec) {
    std::unordered_map<int, bool> exist_hash;
    for (int idx_vec = 0; idx_vec < vec.size(); ++idx_vec) {
        exist_hash[vec[idx_vec]] = true;
    }
    for (int num = 1; num <= vec.size()+1; ++num) {
        if(exist_hash.find(num) == exist_hash.end() ){
            return num;
        }
    }
    return 0;
}
