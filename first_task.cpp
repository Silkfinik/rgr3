#include <iostream>
#include <set>
#include <vector>

int main(){
    std::vector<int> nums;
    std::set<int> prime_nums;
    int n;
    std::cout << "Input n: ";
    std::cin  >> n;
    for (int i = 2; i <= n; ++i) {
        nums.push_back(i);
    }
    while (!nums.empty()){
        prime_nums.insert(*nums.begin());
        int temp = *nums.begin();
        for(int i = 0; i < nums.size(); ++i){
            if (nums[i] % temp == 0){
                nums.erase(nums.begin() + i);
            }
        }
    }
    for(auto &i : prime_nums){
        std::cout << i << " ";
    }
}