#ifndef _WORD_FREQUENCY_H_
#define _WORD_FREQUENCY_H_

#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <cassert>
#include "MersenneTwister.h"
using namespace std;

class WordFrequency{
public:
	//initiator
	static WordFrequency* Make_WordFrequency_data(int i)  {return new WordFrequency(i);}
	//accessor
	const int getCurrentLayer() { return current_layer_number;}
	int getNumFollowingWord();
    int findword(const string &word);
	const int getCurrentLayer()const { return current_layer_number;}
	vector<WordFrequency*> getAllSub_Layer();
	WordFrequency* NextLayer(const string& word, bool &is_word_found);

    //modifier
	WordFrequency* Add_A_Row(list<string> &currently_working);
	void Add_A_Word(const string &word);
    int findword(const string &word, string &following_word);
    const string& word_mostCommon( string &following_word, bool random_flag);

    // check 
	bool isBaseLayer() ;
	//deconstructor
	void delete_Word_Map();
    //print 
	void print_word_map(const string &pre);


private:
  //private constructor
    WordFrequency(int i) {
    assert (i >= 0);
    current_layer_number = i;
    word_frequency = 1;}

  int current_layer_number;
  int word_frequency;
  std::map<std::string,WordFrequency*> word_map;

};

#endif