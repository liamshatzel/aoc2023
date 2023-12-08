#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;

class node_t{
    public:
        string left;
        string right;
        string parent;
};

string clean_node(string node){
    if(node[0] == ' '){
    node = node.substr(1, node.length());
    if(node[0] == '('){
        return node.substr(1, node.length());
    }else{
        return node.substr(0, node.length()-1);
    }
    }else{
        return node.substr(0, node.length()-1);
    }

}

int main() {
    string line;

    int line_count = 0;

    map<string,node_t> adj;
    string moves;
    while(getline(cin, line)){
        stringstream ss(line);

        string input = "";
        getline(ss, input, '=');

        if(line_count == 0){
            moves = input;
        }else{
            string s_left;
            string s_right;
            if(line != ""){
                string node;
                for(int i = 0; i < 2; i++){
                    getline(ss, node, '=');
                    if(i != 0){
                        stringstream ch(node);
                        for(int j = 0; j < 2; j++){
                            if(j == 0){
                                getline(ch, s_left, ',');
                            }else{
                                getline(ch, s_right, ',');
                            }
                        }
                    }
                }

                node_t locs;
                string cur_node = clean_node(input);
                locs.left = clean_node(s_left); 
                locs.right = clean_node(s_right);
                adj[cur_node] = locs;
            }
        }
        line_count++;
    }
    //string key = "AAA";
    vector<int> move_list;
    for(auto const& [key, value] : adj){
        int move_count = 0; 
        if(key[2] == 'A'){
            string next_key = key;
            while(next_key[2] != 'Z'){
                for(int k = 0; k < moves.length(); k++){
                    if(moves[k] == 'R'){
                        next_key = adj[next_key].right;
                    }else{
                        next_key = adj[next_key].left;
                    }
                    move_count++;
                }
                move_list.push_back(move_count);
            }

        }
    }
    
    int max = move_list[0];
    for(int i = 0; i < move_list.size(); i++){
        //cout << move_list[i] << endl;
        if(move_list[i] > max){
            max = move_list[i];
        }
    }

    cout << max << endl;
}
