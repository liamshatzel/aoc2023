//Parse three lines at a time
//Make 2d array around number runs
//
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;

class gearloc{
    public:
        int x;
        int y;
};

class num_obj{
    public:
        int start_idx;
        int end_idx;
        int height;
        int val;
        vector<gearloc>;
};

vector<num_obj> find_num_runs(string line, int text_height){
    int start = 0;
        int end = 0;

    string cur_num = "";
    vector<num_obj> num_list;

    for(int i = 1; i <= line.length(); i++){

        int been_added = 0;

        char prev = line[i - 1];
        char cur = line[i];

        if(isdigit(prev) && i == 1){
            cur_num += prev;
        }

        //start of run
        if(isdigit(cur) && !isdigit(prev)){
            start = i;
            cur_num += cur;
            been_added = 1;
        }else if(isdigit(prev) && !isdigit(cur)){
            end = i;

            num_obj num_info;
            num_info.start_idx = start;
            num_info.end_idx = end;
            num_info.height = text_height;
            num_info.val = stoi(cur_num);
            
            num_list.push_back(num_info);

            //reset
            start = 0;
            end = 0;
            cur_num = "";
        } else if(isdigit(prev) && isdigit(cur)){
            cur_num += cur;
        }
    }
    return num_list;
}

int is_part(string line, int index){
    if(line.length() > 0){
        if(!isdigit(line[index]) && (line[index] != '.')){
            return 1;
        }
    }
    return 0;
}

int parse_nums(vector<num_obj> nums, vector<string> lines){
    vector<num_obj> result;
    int total_sum = 0;
    for(num_obj num : nums){
        int y = num.height;
        int start = num.start_idx;
        int end = num.end_idx;
        string cur_line = lines[y];
        string top_line;
        string bot_line;

        int to_add = 0;

        //...
        //.x.
        //...
        
        //make bounds 
        if(y-1 >= 0){
            top_line = lines[y - 1];
        }
        if(y+1 <= lines.size()){
            bot_line = lines[y+1];
        }

        if(start-1 >= 0){
            start -= 1;
        }
        if(end+1 <= cur_line.length()){
            end+=1;
        }

        for(int i = start; i < end; i++){
            if(is_part(cur_line, i) || is_part(top_line, i) || is_part(bot_line, i)){
                to_add = 1;
            }
        }

        if(to_add){
            result.push_back(num);
            total_sum += num.val;
        }
    }
    return total_sum;
}

int main() {
    string line;
    vector<string> m;
    int line_count= 0;

    while(getline(cin, line)){
        m.push_back(line);
        line_count++;
    }

    vector<num_obj> num_runs;

    
    for(int i = 0; i < m.size(); i++){
        vector<num_obj> line_runs;
        line_runs = find_num_runs(m[i], i);
        for(num_obj run : line_runs){
            num_runs.push_back(run);
        }
    }

    int res = parse_nums(num_runs, m);
    cout << res << endl;
}
