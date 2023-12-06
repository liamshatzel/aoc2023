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
}

int main() {
    string line;

    vector<string> tokens;
    int total_sum = 0;

    //dest(start, end), source(start, end)
    vector<unsigned long long> seeds;
    vector<unsigned long long> short_seeds;
    vector<range_block> range_map;
     
    //get seeds before
    int line_count = 0;
    int num_blocks = 0;
    while(getline(cin, line)){
        stringstream ss(line);
        string title = "";
        string numbers = "";

        if(line == ""){
            for(int i = 0; i < seeds.size(); i++){
                for(int j = 0; j < range_map.size(); j++){
                    range_block cur_map = range_map[j];
                    if(seeds[i] <= cur_map.source + cur_map.range && seeds[i] >= cur_map.source){
                        unsigned long long source_offset = seeds[i] - cur_map.source;
                        unsigned long long dest = cur_map.dest + source_offset;
                        seeds[i] = dest;
                        break;
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
            cout << short_seeds.size() << endl;
            for(int i = 0; i < short_seeds.size(); i+=2){
                cout << i << endl;
                unsigned long long start = short_seeds[i];
                unsigned long long end = start + short_seeds[i + 1];
                //for(unsigned long long j = start; j < end; j++){
                //    clog << j << " of " << end << '\r';
                //    //clog.flush();
                //    seeds.push_back(j);
                //    clog << flush;
                //}

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

    cout << find_min(seeds) << endl;

    ///for(range_block test : range_map){
    ///    cout << test.start << endl;
    ///}


}

