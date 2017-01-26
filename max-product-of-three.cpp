/*

  A[5] = 6
the function should return 60, as the product of triplet (2, 4, 5) is maximal.

Assume that:

N is an integer within the range [3..100,000];
each element of array A is an integer within the range [−1,000..1,000].
Complexity:

expected worst-case time complexity is O(N*log(N));
expected worst-case space complexity is O(1), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.
*/
#include <algorithm>

int solution(vector<int> &vec) {
    std::sort(vec.begin(), vec.end());
    if((vec[0]*vec[1]*vec.back()) >
       (vec[vec.size()-1]*vec[vec.size()-2]*vec[vec.size()-3])){
        return (vec[0]*vec[1]*vec.back());
    } else{
        return (vec[vec.size()-1]*vec[vec.size()-2]*vec[vec.size()-3]);
    }
}
