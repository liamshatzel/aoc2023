#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;

int main() {
    string line;

    vector <string> tokens;
    stringstream check1;
    int total_sum = 0;

    while(getline(cin, line)){
        stringstream ss(line);
        string tmp_string;
        string cur_game_id = "";
        map<string, int> color_val;
        string game_num = "";
        string number = "";
        int works = 1;

        getline(ss, game_num, ':');
        stringstream number_line(game_num);

        int j = 0;

        //get game line and number
        while(getline(number_line, number, ' ')){
            if(j > 0){
                game_num = number;
            }
            j++;
        }

        //get hand from each draw 
        while(getline(ss, tmp_string, ';')){
            stringstream s2(tmp_string);
            string cur_word;

            while(getline(s2, cur_word, ',')){
                stringstream s3(cur_word);
                string cur_num;
                int i = 0; 

                string num;
                string color;
                while(getline(s3, cur_num, ' ')){
                    if(i == 0){
                        color = cur_num;
                        i++;
                    }else{
                        num = cur_num;
                        i = 0;
                    }
                }

                if(color_val.count(color) > 0){
                    if(color_val[color] < stoi(num)){
                        color_val[color] = stoi(num);
                    }
                }else{
                    color_val[color] = stoi(num);
                }

                if(color_val.count("red") > 0){
                    if(color_val["red"] > 12){
                        works = 0;
                    }
                }

                if(color_val.count("green") > 0){
                    if(color_val["green"] > 13){
                        works = 0;
                    }
                }

                if(color_val.count("blue") > 0){
                    if(color_val["blue"] > 14){
                        works = 0;
                    }
                }
            }
        }
        int power = 1; 
        for(auto it = color_val.cbegin(); it != color_val.cend(); ++it)
        {
            power *= it->second;
        } 
        total_sum += power;
    }

    cout << total_sum << '\n';
    return 0;
}
