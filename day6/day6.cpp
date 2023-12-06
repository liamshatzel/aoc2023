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
            cur_times.push_back(stoll(cur_time));
        }

    }
    while(getline(dists, cur_dist, ' ')){
        if(cur_dist != "" && cur_dist != "\n" && isdigit(cur_dist[0])){
            cur_dists.push_back(stoll(cur_dist));
            new_cur_dist += cur_dist;
        }
    }
    unsigned long long new_tot_time = stoll(new_cur_time);
    unsigned long long new_tot_dist = stoll(new_cur_dist);

    vector<int> tot_wins; 
        int tot_time = new_tot_time;
        int win_ways = 0;

        for(unsigned long long j = 0; j < tot_time; j++){
            unsigned long long does_win = (tot_time - j) * j;
            if(does_win > new_tot_dist){
                win_ways++;
            }
        }
        tot_wins.push_back(win_ways);
    
    int total_score = 1;
    for(int win : tot_wins){
        if(win != 0)
            total_score *= win;
    }

    cout << total_score << endl;

}
