#include <iostream>
#include <set>
#include <map>
#include <string>
#include <fstream>

void fill_multiset(std::multiset<std::string>& words){
    std::ifstream in;
    in.open("C:\\Users\\silkfinik\\CLionProjects\\rgr3\\Input1.txt");
    if(in.is_open()){
        std::string temp;
        while(in >> temp){
            words.insert(temp);
        }
    }
    in.close();
}

void fill_set(std::set<std::string>& unique_words, const std::multiset<std::string>& words){
    for (const auto& i : words){
        unique_words.insert(i);
    }
}

void print_set(const std::set<std::string>& unique_words){
    for (const auto& i : unique_words){
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
    std::cout << "----------------------------------\n";
    std::cout << std::endl;
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

void print_map(const std::map<std::string, int>& word_counter){
    for (const auto& i : word_counter){
        std::cout << i.first << " " << i.second << std::endl;
    }
    std::cout << std::endl;
    std::cout << "----------------------------------\n";
    std::cout << std::endl;
}

int main(){
    std::multiset<std::string> words;
    std::set<std::string> unique_words;
    fill_multiset(words);
    fill_set(unique_words, words);
    print_set(unique_words);
    std::map<std::string, int> word_counter;
    std::map<std::string, int> word_counter_diff;
    count_with_dif(word_counter, words);
    print_map(word_counter);
    count_without_dif(word_counter_diff, words);
    print_map(word_counter_diff);
    std::cout << " ";
}