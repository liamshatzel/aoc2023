#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <map>
#include <sstream>
#include <cctype>
using namespace std;

class card_hand{
    public:
        string hand;
        int hand_type;
        int bid;
        string type;
        map<char, int> hand_vals;
};

    map<char, int> card_vals;



int compare_hands(card_hand h1, card_hand h2){
    //chekcs if h1 > h2
    if(h1.hand_type > h2.hand_type){
        return 1;
    }else if(h1.hand_type == h2.hand_type){
        for(int i = 0; i < h1.hand.length(); i++){
            //if h1 ever has a card thats bigger
            //return 1
            if(card_vals[h1.hand[i]] > card_vals[h2.hand[i]]){
                return 1;
            }else if(card_vals[h1.hand[i]] < card_vals[h2.hand[i]]){
                return 0;
            }
        }
    }


    return 0;

}

int main() {
    card_vals['A'] = 13;
    card_vals['K'] = 12; 
    card_vals['Q'] = 11;
    card_vals['T'] = 10;
    card_vals['9'] = 9;
    card_vals['8'] = 8;
    card_vals['7'] = 7;
    card_vals['6'] = 6;
    card_vals['5'] = 5;
    card_vals['4'] = 4;
    card_vals['3'] = 3;
    card_vals['2'] = 2;
    card_vals['1'] = 1;
    card_vals['J'] = 0;

    string line;
    int num_lines = 0;

    vector<card_hand> hands;


    while(getline(cin, line)){
        map<char, int> num_cards;
        stringstream ss(line);
        string hand = "";
        string s_bid = "";
        for(int i = 0; i < 2; i++){
            if(i == 0){
                getline(ss, hand, ' ');
            }else{
                getline(ss, s_bid, ' ');
            }
        }

        card_hand cur_hand;
        cur_hand.hand = hand;
        cur_hand.bid = stoi(s_bid);

        //figure out card type
        //hash cards 
        for(int k = 0; k < hand.length(); k++){
            char cur_char = hand[k];
            if(num_cards.count(cur_char) == 0){
                num_cards[cur_char] = 1;
            }else{
                num_cards[cur_char] += 1;
            }
        }
        
        if(num_cards.count('J') > 0){
            cout << num_cards['J'] << endl;
            char max;
            int i_max = -1;
            for(auto const& [key, val] : num_cards){
                if(val > i_max && key != 'J'){
                    max = key;
                    i_max = val;
                }
            }
            num_cards[max] += num_cards['J'];
            num_cards['J'] = 0;
        }


            
        //types:
        //5ok = 5
        //4ok = 4
        //full = 3
        //three = 2
        //two = 1
        //onne = 0
        //high = -1
        //might need to find max type if there are overlaps (i.e. five co
        vector<int> type_list;
        int h_type = -1;
        for(auto const& [key, val] : num_cards)
        {
            //need to make sure all cards are accounted for
            if(val == 5){
                h_type = 5;
                break;
            }else if(val == 4){
                h_type = 4;
                break;
            }else if(val == 3){
                for(auto const& [key2, val2] : num_cards){
                    if(val2 == 2){
                        h_type = 3;
                        break;
                    }else if(val2 == 1){ 
                        h_type = 2;
                        break;
                    }
                }
            }else if(val == 2){
                for(auto const& [key2, val2] : num_cards){
                    if(val2 == 2 && key2 != key){
                        h_type = 1;
                        break;
                    }else if(val2 == 1){
                        for(auto const& [key3, val3] : num_cards){
                            if(val3 == 2 && key3 != key2 && key3 != key){
                                h_type = 1;
                                break;
                            }else{
                                h_type = 0;
                            }
                        }
                    }
                }
            }

        }
        cur_hand.hand_type = h_type;
        hands.push_back(cur_hand);

        //cout << hand << endl;
        //cout << s_bid << endl;


        num_lines++;
    }

    vector<card_hand> sorted;


    int n = hands.size();
    int i, j; 
    for (i = 0; i < n; i++){
        // Last i elements are already 
        // in place 
        for (j = 0; j < n - i - 1; j++){
            if (compare_hands(hands[j], hands[j + 1])){
                swap(hands[j], hands[j + 1]); 
            }
        }
    }

    
    int tot_sum = 0;
    //for(int m = 1; m < hands.size(); m++){
    //    cout << hands[m].bid << endl;
    //    tot_sum += hands[m].bid * m;
    //}

    int counter = 1;
    for(card_hand card : hands){
        tot_sum += card.bid * counter;
        counter++;
        cout << card.hand << ' ' << card.bid <<  ' ' << card.hand_type << endl;
    }
    cout << tot_sum << endl;
}
