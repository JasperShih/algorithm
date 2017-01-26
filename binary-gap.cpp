/*
A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.

For example, number 9 has binary representation 1001 and contains a binary gap of length 2. The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3. The number 20 has binary representation 10100 and contains one binary gap of length 1. The number 15 has binary representation 1111 and has no binary gaps.

Write a function:

int solution(int N);
that, given a positive integer N, returns the length of its longest binary gap. The function should return 0 if N doesn't contain a binary gap.

For example, given N = 1041 the function should return 5, because N has binary representation 10000010001 and so its longest binary gap is of length 5.

Assume that:

N is an integer within the range [1..2,147,483,647].
Complexity:

expected worst-case time complexity is O(log(N));
expected worst-case space complexity is O(1).
*/

int solution(int N) {
    int new_num = N, head = 0, max_len = 0, len = 0;

    for(int i=0; i<32; i++){
        int now = new_num & 0x1;
        new_num = new_num>>1;

        if ((head == 0) && (now == 1)){
            head = 1;
        }
        else if ((head == 1) && (now == 0)){
            len += 1;
        }
        else if ((head == 1) && (now == 1)){
            if (len > max_len){
                max_len = len;
            }
            len = 0;
        }
    }
    return max_len;
}

/*
int solution(int num) {
    bool met_set = false;
    int len = 0;
    int max_len = 0;
    for (int bit = 0; bit < 32; ++bit, num = num>>1) {
        if ((num & 0x1) == 1){
            met_set = true;
            if (len > max_len){
                max_len = len;
            }
            len = 0;
        } else if ((num & 0x1) == 0){
            if (met_set){
                len++;
            }
        }
    }
    return max_len;
}
 */