/*
A non-empty zero-indexed array A consisting of N integers is given. A pair of integers (P, Q), such that 0 ≤ P < Q < N, is called a slice of array A (notice that the slice contains at least two elements). The average of a slice (P, Q) is the sum of A[P] + A[P + 1] + ... + A[Q] divided by the length of the slice. To be precise, the average equals (A[P] + A[P + 1] + ... + A[Q]) / (Q − P + 1).

For example, array A such that:

    A[0] = 4
    A[1] = 2
    A[2] = 2
    A[3] = 5
    A[4] = 1
    A[5] = 5
    A[6] = 8
contains the following example slices:

slice (1, 2), whose average is (2 + 2) / 2 = 2;
slice (3, 4), whose average is (5 + 1) / 2 = 3;
slice (1, 4), whose average is (2 + 2 + 5 + 1) / 4 = 2.5.
The goal is to find the starting position of a slice whose average is minimal.

Write a function:

int solution(vector<int> &A);
that, given a non-empty zero-indexed array A consisting of N integers, returns the starting position of the slice with the minimal average. If there is more than one slice with a minimal average, you should return the smallest starting position of such a slice.

For example, given array A such that:

    A[0] = 4
    A[1] = 2
    A[2] = 2
    A[3] = 5
    A[4] = 1
    A[5] = 5
    A[6] = 8
the function should return 1, as explained above.

Assume that:

N is an integer within the range [2..100,000];
each element of array A is an integer within the range [−10,000..10,000].
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N), beyond input storage (not counting the storage required for input arguments).
Elements of input arrays can be modified.
*/

int solution(vector<int> &vec) {
    double min = (vec[0] + vec[1])/2;
    int idx_min = 0;
    for (int idx_vec = 1; idx_vec < vec.size()-2; ++idx_vec) {
        double now1 = (double) (vec[idx_vec] + vec[idx_vec+1])/2;
        double now2 = (double) (vec[idx_vec] + vec[idx_vec+1] + vec[idx_vec+2])/3;

        if (now1 < min){
            min = now1;
            idx_min = idx_vec;
        }

        if (now2 < min){
            min = now2;
            idx_min = idx_vec;
        }
    }

    int last1 = (vec[vec.size()-2] + vec[vec.size()-1])/2;
    if (last1 < min){
        min = last1;
        idx_min = vec.size()-2;
    }

    return idx_min;
}
