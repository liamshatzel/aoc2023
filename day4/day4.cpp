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

        cout << "stripping" << endl;
        return new_word;
    }
    return word;
}


int main() {
    string line;

    vector<int> cards;

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
                    if(cur_sum == 0){
                        cur_sum += 1;
                    }else{
                        cur_sum *= 2;
                    }
                }
            }


        }
        cards.push_back(cur_sum);

        total_sum += cur_sum;
    }

    cout << total_sum << endl;
}
