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
        //cout << i % 6 << ':' << list[i] << ' ';
        cout << list[i] << ' ';
    }
    cout << endl;
}

vector<vector<int>> make_scratchers(vector<int> cur_list){
    vector<vector<int>> ret_val;
    for(int i = 0; i < cur_list.size(); i++){
        int num_copy = cur_list[i];
        vector<int> new_list;
        for(int j = i + 1; j < num_copy + i + 1; j++){
            if(j <= cur_list.size()){
              new_list.push_back(cur_list[j]);
            }
        }
        ret_val.push_back(new_list);
    }
    return ret_val;
}

vector<int> make_scratchers_flat(vector<int> cur_list, int start_pos){
    vector<int> ret_val;
        int num_copy = cur_list[start_pos];
        for(int j = start_pos + 1; j < num_copy + start_pos + 1; ++j){
            if(j < cur_list.size()){
              ret_val.push_back(cur_list[j]);
            }
        }
    return ret_val;
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
    //cards.push_back(-1);

    //make_scratchers(cards);

    //c_big.push_back(cards);
    int part_2_sum = 0;

    int i = 0;

    int more_cards = 1;
    //while(i < c_big.size()){
    //    vector<vector<int>> more_lists = make_scratchers(c_big[i]);
    //    for(vector<int> vec : more_lists){
    //        c_big.push_back(vec);
    //    }

    //    if(more_lists.size() == 0){
    //        more_cards = 0;
    //    }
    //    i++;
    //}

    int m = 0;
    while(m < cards.size()){
        //vector<int> to_add = make_scratchers_flat(cards, m);
        int num_copy = cards[m];
        for(int j = m + 1; j <= num_copy + m; j++){
            //if(cards[j] == -1){
            //        break;
            //}else{
                cards.push_back(cards[(j % 6)]);
            }
            //if(j == num_copy + m){
            //    cards.push_back(-1);
            //}
        //for(int k= 0; k < to_add.size(); k++){
        //    cards.push_back(to_add[k]);
        //}
        print_list(cards);
        m++;
    }

    //erase(cards, -1);
    print_list(cards);

    //for(vector<int> card : c_big){
    //    part_2_sum += card.size();
    //    print_list(card);
    //}
    cout << cards.size() << endl;
    cout << total_sum << endl;
}


