#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;

string strip(string word){
    string new_word = "";
    if(word[0] == ' '){
        for(int i = 1; i < word.length(); i++){
            new_word[i] = word[i];
        }
        return new_word;
    }
    return word;
}

void print_list(vector<int> list){
    for(int i = 0; i < list.size(); i++){
        cout << list[i] << ' ';
    }
    cout << endl;
}

int find_matches(const vector<int>& list, int index){
    int count = 1;
    for(int i = 0; i < list[index]; i++){
        count += find_matches(list, index + i + 1);
    }
    return count;
}

int test_find_match(vector<int> vec){
    int total_matches = 0;
    for(int i = 0; i < vec.size(); i++){
        total_matches += find_matches(vec, i);
    }
    return total_matches;
}

int main() {
    string line;

    vector<int> cards;

    vector<vector<int>> c_big;

    int total_sum = 0;

    while(getline(cin, line)){
        map<string, int> num_map;
        int num_type = 0;
        string game_num;
        string cut_off;

        stringstream ss(line);
        for(int i = 0; i < 2; i++){
            if(i > 0){
                getline(ss, cut_off, ':');
            }else{
                getline(ss, game_num, ':');
            }
        }

        stringstream number_line(cut_off);
        string number; 

        int cur_sum = 0;

        while(getline(number_line, number, ' ')){
            if(number == "|"){
                num_type = 1;
                continue;
            }

            number = strip(number);

            if(number == ""|| number == "\n" || number == "\b"){
                continue;
            }

            //hash all nums before pipe
            if(!num_type){
                num_map[number] = 0;
            }

            //after pipe
            if(num_type){
                if(num_map.count(number) > 0){
                    num_map[number] = 1;
                    cur_sum += 1;
                }
            }
        }
        cards.push_back(cur_sum);
        total_sum += cur_sum;
    }
    int sum = test_find_match(cards);

    cout << sum << endl;
    cout << total_sum << endl;
}


