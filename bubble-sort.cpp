#include <vector>

int main(int argc, char **argv) {
    vector<int> vec = {6,7,4,2,6,4,9,12,1};
    for (int times = 0; times < vec.size()-1; ++times) {
        for (int idx_vec = 0; idx_vec < vec.size()-times-1; ++idx_vec) {
            if (vec[idx_vec] > vec[idx_vec+1]){
                int tmp = vec[idx_vec+1];
                vec[idx_vec+1] = vec[idx_vec];
                vec[idx_vec] = tmp;
            }
        }
    }
}
