#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;



class range_block {
    public:
        unsigned long long dest;
        unsigned long long source;
        unsigned long long range;
};

unsigned long long find_min(vector<unsigned long long> seeds){
    unsigned long long min = seeds[0];
    for(int i = 1; i < seeds.size(); i++){
        if(seeds[i] <= min){
            min = seeds[i];
        }
    }
    return min;
}

//for each interval object:
//Starting at interval objects for seeds, make more interval objects as needed
//Cases: start/end not in interval, start out end in, start in end out, both in (dont split)
////Do this for each map
///
class interval {
    public:
        unsigned long long start;
        unsigned long long end;
        unsigned long long range;
};

unsigned long long find_min_intervals(vector<interval> seed_intervals){
    unsigned long long min = seed_intervals[0].start;
    for(int i = 1; i < seed_intervals.size(); i++){
        if(seed_intervals[i].start <= min){
            min = seed_intervals[i].start;
        }
    }
    return min;
}


int main() {
    string line;

    vector<string> tokens;
    int total_sum = 0;

    //dest(start, end), source(start, end)
    vector<unsigned long long> seeds;
    vector<unsigned long long> short_seeds;
    vector<interval> seed_intervals;
    vector<range_block> range_map;
     
    //get seeds before
    //TODO: Non seed intervals shouldnt be passed down
    int line_count = 0;
    int num_blocks = 0;
    while(getline(cin, line)){
        stringstream ss(line);
        string title = "";
        string numbers = "";

        if(line == ""){
            int k = seed_intervals.size();
            cout << k << endl;
            for(int i = 0; i < k; i++){
                for(int j = 0; j < range_map.size(); j++){
                    range_block cur_map = range_map[j];

                    unsigned long long r_start = range_map[j].source;
                    unsigned long long r_end = range_map[j].source + range_map[j].range;
                    unsigned long long s_start = seed_intervals[i].start;
                    unsigned long long s_end = seed_intervals[i].end;

                    //  seed; | --- |
                    //  range     | --- |
                    if(s_start < r_start && s_end <= r_end){
                        //starts out range ends in range
                        interval i_1;
                        i_1.start = r_start - s_start;
                        i_1.end = r_start - 1;
                        seed_intervals[i] = i_1;

                        interval i_2;
                        unsigned long long start_offset = r_start - r_start;
                        unsigned long long end_offset = s_end - r_start;
                        unsigned long long i_2_start = cur_map.dest + start_offset;
                        unsigned long long i_2_end = cur_map.dest + end_offset;
                        i_2.start = i_2_start;
                        i_2.end = i_2_end;
                        seed_intervals.push_back(i_2);
                    }else if(s_start >= r_start && s_end <= r_end){
                        //fully inside range
                        interval i_2;
                        unsigned long long start_offset = s_start - r_start;
                        unsigned long long end_offset = s_end - r_start;
                        unsigned long long i_2_start = cur_map.dest + start_offset;
                        unsigned long long i_2_end = cur_map.dest + end_offset;
                        i_2.start = i_2_start;
                        i_2.end = i_2_end;
                        seed_intervals.push_back(i_2);
                    }else if(s_start < r_end && s_end > r_end){
                        //starts in range ends out     
                        interval i_1;
                        i_1.start = r_end;
                        i_1.end = s_end;
                        seed_intervals[i] = i_1;

                        interval i_2;
                        unsigned long long start_offset = s_start - r_start;
                        unsigned long long end_offset = (r_end - s_start - 1) - r_start;
                        unsigned long long i_2_start = cur_map.dest + start_offset;
                        unsigned long long i_2_end = cur_map.dest + end_offset;
                        i_2.start = i_2_start;
                        i_2.end = i_2_end;
                        seed_intervals.push_back(i_2);
                    }

                }
            }
            range_map.clear();
        }

        //get seeds
        if(line_count < 2){
            for(int i = 0; i < 2; i++){
                if(i == 0){
                    getline(ss, title, ':');
                }else{
                    getline(ss, numbers, ':');
                }
            }

            string temp;
            stringstream num_s(numbers);
            while(getline(num_s, temp, ' ')){
                if(temp != " " && temp != "" && temp != "\n"){
                    short_seeds.push_back(stoll(temp));
                }
            }


        }else if(line_count == 2){
            for(int i = 0; i < short_seeds.size(); i+=2){
                unsigned long long start = short_seeds[i];
                unsigned long long end = start + short_seeds[i + 1];
                interval cur;
                cur.start = start;
                cur.end = end;
                seed_intervals.push_back(cur);
            }
        }
        

        string temp;
        stringstream num_s(numbers);

        //check that the line doesnt start with text
        range_block block;
        int type = 0;
        if(isdigit(line[0])){
            //current map
            while(getline(ss, temp, ' ')){
                if(temp != " " && temp != ""){
                    if(type == 0){
                        block.dest = stoll(temp);
                    }else if(type == 1){
                        block.source = stoll(temp);
                    }else{
                        block.range = stoll(temp);
                    }
                    type++;
                }
            }
            range_map.push_back(block);
        }

        line_count++;
    }


    //

    
    for(interval seed : seed_intervals) {
        cout << seed.start << " " << endl;
    }
    //cout << find_min(seeds) << endl;
    cout << find_min_intervals(seed_intervals) << endl;

    

    //for(range_block test : range_map){
    //    cout << test.start << endl;
    //}


}

