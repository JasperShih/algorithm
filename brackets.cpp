/*
A string S consisting of N characters is considered to be properly nested if any of the following conditions is true:

S is empty;
S has the form "(U)" or "[U]" or "{U}" where U is a properly nested string;
S has the form "VW" where V and W are properly nested strings.
For example, the string "{[()()]}" is properly nested but "([)()]" is not.

Write a function:

int solution(string &S);

that, given a string S consisting of N characters, returns 1 if S is properly nested and 0 otherwise.

For example, given S = "{[()()]}", the function should return 1 and given S = "([)()]", the function should return 0, as explained above.

Assume that:

N is an integer within the range [0..200,000];
string S consists only of the following characters: "(", "{", "[", "]", "}" and/or ")".
Complexity:

expected worst-case time complexity is O(N);
expected worst-case space complexity is O(N) (not counting the storage required for input arguments).
*/

int solution(string &str) {
    vector<char> stack;
    auto iter = str.begin();

    while (true) {
        switch (*iter) {
            case '\0':
                if (stack.empty()) {
                    return 1;
                } else {
                    return 0;
                }
                break;
            case '{':
            case '[':
            case '(':
                stack.push_back(*iter);
                break;
            case '}':
                if ((!stack.empty()) && (stack.back() == '{')) {
                    stack.pop_back();
                } else {
                    return 0;
                }
                break;
            case ']':
                if ((!stack.empty()) && (stack.back() == '[')) {
                    stack.pop_back();
                } else {
                    return 0;
                }
                break;
            case ')':
                if ((!stack.empty()) && (stack.back() == '(')) {
                    stack.pop_back();
                } else {
                    return 0;
                }
                break;
            default:break;
        }
        iter = iter + 1;
    }
}
