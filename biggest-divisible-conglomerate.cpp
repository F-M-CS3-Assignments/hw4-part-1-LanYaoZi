#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

#include "bdc.h"

// to_string function
string vec_to_string(vector<int> v){
    string outcome="{";
    for(int i:v){
        outcome+=to_string(i);
        outcome+=",";
    }
    if(v.size()>=1){  
        outcome.pop_back();
    }
    outcome+="}";
    return outcome;
}

//check if a vector divisible
bool is_divisible(const vector<int> subset) {
    for (long long unsigned int i = 0; i < subset.size(); ++i) {
        for (long long unsigned int j = i + 1; j < subset.size(); ++j) {
            int larger = max(subset[i], subset[j]);
            int smaller = min(subset[i], subset[j]);
            if (larger % smaller != 0) {
                return false;
            }
        }
    }
    return true;
}

//recursion to finding best_vec by Pass by reference. Some ideas from https://stackoverflow.com/questions/42424291/reference-parameters-and-recursion
//and https://stackoverflow.com/questions/40102450/passing-a-vector-as-a-reference-to-a-recursive-function
void finding_recursion(const vector<int>& input, vector<int> current_vec, vector<int>& best_vec, long long unsigned int index) {
    //base case
    if (index == input.size()) {
        //check if current_vec is better than the best_vec
        if (current_vec.size() > best_vec.size()) {
            //for test
            //cout<<"current_vec/best_vec"<<vec_to_string(current_vec)<<vec_to_string(best_vec)<<endl;
            best_vec = current_vec;
        }
        return;
    }

    //two ways of recursion:
    //Use it
    current_vec.push_back(input[index]);
    if(is_divisible(current_vec)){
        finding_recursion(input, current_vec, best_vec, index+1);
    }
    current_vec.pop_back();

    //throw it
    finding_recursion(input, current_vec, best_vec, index+1);

}

vector<int> biggest_divisible_conglomerate(vector<int> input){
    // in case exception
    if (input.empty()) return {};
    if (input.size() == 1) return input;

    //make sure the smallest element always is the first one 
    sort(input.begin(), input.end());
    vector<int> best_vec;
    vector<int> current_vec;
    finding_recursion(input, current_vec, best_vec, 0);
    return best_vec;

}