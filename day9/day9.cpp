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
    int num_lines = 0;
    //vector<int> line_1;
    int total_sum = 0;
    while(getline(cin, line)){
        stringstream ss(line);
        string cur_num;
        vector<int> cur_line;

        while(getline(ss, cur_num, ' ')){
            cur_line.push_back(stoi(cur_num));
        }

        vector<vector<int>> history;
        int cont = 1;
        int diff_line = 0;
        history.push_back(cur_line);
        while(cont){
            vector<int> cur_li = history[diff_line];
            vector<int> diffs;
            for(int i = 1; i < cur_li.size(); i++){
                int cur_diff = cur_li[i] - cur_li[i-1];
                diffs.push_back(cur_diff);
            }
        
            int no_zeros = 1;

            int zero_count = 0;
            for(int diff : diffs){
                if(diff == 0){
                    zero_count++;
                }
            }

            if(zero_count == cur_li.size() - 1){
                cont = 0;
            }

            diff_line++;
            history.push_back(diffs);
        }


        for(vector<int> vec : history){
            for(int el : vec){
                cout << el << ' ';
            }
            cout << endl;
        }
        int running_sum = 0;
        int extrap = 0;
        for(int k = history.size()-1; k > 0; k--){
            vector<int> cur_list = history[k];
            vector<int> next_list = history[k-1];
            extrap = next_list[0] - extrap;
            cout << extrap << endl;
            //cout << running_sum << endl;
        }

        total_sum += extrap;
        //cout << running_sum << endl;

        num_lines++;
    }
    cout << total_sum <<endl;
}
