#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class range
{
    public:
    unsigned long long dest;
    unsigned long long source;
    unsigned long long length;
};

class map
{
    public:
    string name;
    vector<range> mapping;
};

class seed
{
    public:
    vector<int> dest_values; 
};

unsigned long long dest_value(unsigned long long source, range r)
{
    unsigned long long offset = source - r.source;
    if(offset < 0) { cout << "ERROR: offset is negative" << endl; }
    return r.dest + offset;
}

bool falls_in_range(unsigned long long value, range r)
{
    if(value >= r.source && value <= r.source + r.length)
    {
        return true;
    }
    return false;
}

unsigned long long get_lowest_location(vector<map> maps, vector<seed> seeds)
{
    for(unsigned long long i = 0; i < seeds.size(); i++)
    {
        for(unsigned long long j = 0; j < maps.size(); j++)
        {
            for(unsigned long long k = 0; k < maps[j].mapping.size(); k++)
            {
                if(falls_in_range(seeds[i].dest_values[j], maps[j].mapping[k]))
                {
                    seeds[i].dest_values.push_back(dest_value(seeds[i].dest_values[j], maps[j].mapping[k]));
                    break;
                } 
                else if (k == maps[j].mapping.size() - 1)
                {
                    seeds[i].dest_values.push_back(seeds[i].dest_values[j]);
                    break;
                }
            }
        }
    }

    unsigned long long lowest_location = seeds[0].dest_values[seeds[0].dest_values.size()-1];
    for(unsigned long long i = 1; i < seeds.size(); i++)
    {
        /* for(unsigned long long j = 0; j < seeds[i].dest_values.size(); j++) */
        /* { */
        /*     cout << seeds[i].dest_values[j] << " "; */
        /* } */
        /* cout << endl; */

        if(seeds[i].dest_values[seeds[i].dest_values.size()-1] < lowest_location)
        {
            lowest_location = seeds[i].dest_values[seeds[i].dest_values.size()-1];
        }
    }
    return lowest_location;
}

void parse_input()
{
    vector<map> maps; 
    for(unsigned long long i = 0; i < 7; i++)
    {
        map m;
        maps.push_back(m);
    }
    vector<seed> seeds;
    
    string line;
    getline(cin, line);
    line = line.substr(7, line.length()-7);
    stringstream ss(line);


    string token;
    // get seeds
    int count = 1;
    unsigned long long range_start;
    unsigned long long range_end;
    while (ss >> token)
    {
        if(count % 2 == 0)
        {
            range_end = stoll(token);
            for(unsigned long long i = 1; i < range_end; i++)
            {
                seed s;
                s.dest_values.push_back(range_start + i);
                seeds.push_back(s);
            }
        }
        else
        {
            range_start = stoll(token);
            seed s;
            s.dest_values.push_back(range_start);
        }
        count++;
    }

    bool new_map = true;
    unsigned long long map_index = -1;
    while (getline(cin, line))
    {
        if(line == "")
        {
            map_index++;
            continue;
        }
        ss = stringstream(line);
        if(!isdigit(line[0]))
        {
            ss >> token;
            maps[map_index].name = token;
            continue;
        }
        unsigned long long i = 0;
        range r;
        while (ss >> token)
        {
            if(i == 0)
            {
                r.dest = stoll(token);
            }
            else if(i == 1)
            {
                r.source = stoll(token);
            }
            else if(i == 2)
            {
                r.length = stoll(token);
            }
            i++;
        }
        maps[map_index].mapping.push_back(r);
    }

    unsigned long long output = get_lowest_location(maps, seeds);
    cout << output << endl;

    return;
}

int main()
{
    parse_input();
    return 0;
}
