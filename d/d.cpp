#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
using std::cin, std::cout, std::endl, std::vector;

long int med(long int nums[], short len){
    std::sort(&nums[0], &nums[len]);
    return nums[(len - 1) / 2];
}

long int magic5(vector<long int> &nums, int k){
    vector<long int> medians; long int median;
    long int five[5]; short len = 0;
    for(int i = 0; i < (int)nums.size(); i += 5){
        for(int j = 0; j < 5; j++){
            if((i + j) == (int)nums.size()) break;
            len = j; five[j] = nums[i + j];
        }
        medians.push_back(med(five, len + 1));
    }
    if(medians.size() > 5)
        median = magic5(medians, (medians.size() - (int)(medians.size() % 3 == 0)) / 2);
    else{
        long int meds[medians.size()];
        for(int i = 0; i < (int)medians.size(); i++){
            meds[i] = medians[i];
        }
        median = med(meds, medians.size());
    }
    vector<long int> smaller;
    vector<long int> equal;
    vector<long int> bigger;

    for(auto i = nums.begin(); i < nums.end(); i++){
        if(*i < median) smaller.push_back(*i);
        else if(*i == median) equal.push_back(*i);
        else bigger.push_back(*i);
    }
    
    if(k < (long int)smaller.size()) 
        return magic5(smaller, k);
    else if(k <= (long int)(smaller.size() + equal.size()))
        return median;
    else
        return magic5(bigger, k - smaller.size() - equal.size());
}

int main(){
    int n, k;
    vector<long int> numbers;

    cin >> n >> k; long int tmp;
    for(int i = 0; i < n; i++){
        cin >> tmp;
        numbers.push_back(tmp);
    }
    cout << magic5(numbers, k) << endl;
}
