#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

//Wasnt sure whether to count eightwo as 82 or 8wo, turns out its 82
//Also note: substr(start idx, length of substring not end idx)


int parse_line(string line){
    string num_1;
    string num_2;

    int len = line.length();
    int i = 0; 
    int j = len;

    while(!isdigit(line[i]) && i <= len){
        i++;
    }
    while(!isdigit(line[j]) && j >= 0){
        j--;
    }

    num_1 = line[i];
    num_2 = line[j];


    return stoi(num_1 + num_2);

}

int is_number_word(string word){
    map<string, int> wm; 

    wm["one"] = 1;
    wm["two"] = 2;
    wm["three"] = 3;
    wm["four"] = 4;
    wm["five"] = 5;
    wm["six"] = 6;
    wm["seven"] = 7;
    wm["eight"] = 8;
    wm["nine"] = 9;
    
    if(wm.count(word) > 0){
        return wm[word];
    }else{
        return -1;
    }
}

string fix_line(string line){
    string fixed = "";
    int i = 0;
    int j = 0;
    for(int i = 0; i < line.length(); i++){
        for(int j = 0; j < line.length(); j++){
            string word = line.substr(i, j);
            if(is_number_word(word) != -1){
                fixed += to_string(is_number_word(word));
                break;
            }
        }
        if(isdigit(line[i])){
            fixed += line[i];
        }
    }
    return fixed;
}


int main() {
    string line;
    ifstream input_file("day1.txt");
    int total_sum = 0;

    if(input_file.is_open()){
        while(getline(input_file, line)){
            total_sum += parse_line(fix_line(line));
        }
        input_file.close();
    }
    cout << total_sum;
    return 0;
}

