#include <iostream>
#include <set>
#include <map>
#include <string>
#include <fstream>

void fill_set(std::multiset<std::string>& words){
    std::ifstream in;
    in.open("C:\\Users\\silkfinik\\CLionProjects\\rgr3\\Input1.txt");
    if(in.is_open()){
        std::string str;
        while(std::getline(in, str)){
            words.insert(str);
        }
    }
    in.close();
}

void print_set(const std::multiset<std::string>& words){
    for (const auto& i : words){
        std::cout << i << std::endl;
    }
}

void count_with_dif(std::map<std::string, int>& word_counter, const std::multiset<std::string>& words){
    for (const auto& i : words){
        word_counter[i]++;
    }
}

void count_without_dif(std::map<std::string, int>& word_counter_diff, const std::multiset<std::string>& words){
    for (const auto& i : words){
        std::string temp = i;
        for (auto& j : temp){
            j = std::tolower(j);
        }
        word_counter_diff[temp]++;
    }
}

int main(){
    std::multiset<std::string> words;
    fill_set(words);
    print_set(words);
    std::map<std::string, int> word_counter;
    std::map<std::string, int> word_counter_diff;
    count_with_dif(word_counter, words);
    count_without_dif(word_counter_diff, words);
    std::cout << " ";
}