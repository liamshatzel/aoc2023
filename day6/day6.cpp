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
    }else if(!isdigit(word[word.length()])){
    }
    return word;
}

int main() {
    string line;

    vector <string> tokens;
    int total_sum = 0;
    string time;
    string distance;
    for(int i = 0; i < 2; i++){
        if(i == 0)
            getline(cin, time);
        if(i == 1)
            getline(cin, distance);
    }

    stringstream times(time);
    stringstream dists(distance);
    vector<int> cur_times; 
    vector<int> cur_dists;
    string cur_time;
    string cur_dist;
    string new_cur_time;
    string new_cur_dist;

    while(getline(times, cur_time, ' ')){
        if(cur_time != "" && cur_time != "\n" && isdigit(cur_time[0])){
            new_cur_time += cur_time;
            cur_times.push_back(stoi(cur_time));
        }

    }
    while(getline(dists, cur_dist, ' ')){
        if(cur_dist != "" && cur_dist != "\n" && isdigit(cur_dist[0])){
            cur_dists.push_back(stoi(cur_dist));
            new_cur_dist += cur_dist;
        }
    }

    cout << new_cur_time << endl;
    cout << new_cur_dist << endl;

    vector<int> tot_wins; 
    for(int i = 0; i < cur_times.size(); i++){
        int tot_time = cur_times[i];
        int win_ways = 0;
        //cout << tot_time << endl;
        for(int j = 0; j < tot_time; j++){
            int does_win = (tot_time - j) * j;
            if(does_win > cur_dists[i]){
                win_ways++;
            }
        }
        tot_wins.push_back(win_ways);
    }
    
    int total_score = 1;
    for(int win : tot_wins){
        //cout << win << endl;
        if(win != 0)
            total_score *= win;
    }

    cout << total_score << endl;

    



    //while(getline(cin, line)){
    //    stringstream ss(line);
    //    for()
    //    getline(ss, time, ':');
    //    getline(ss, distance, ':');
    //    stringstream number_line(game_num);

    //    int j = 0;

    //    //get game line and number
    //    while(getline(number_line, number, ' ')){
    //        if(j > 0){
    //            game_num = number;
    //        }
    //        j++;
    //    }
    //}
}
