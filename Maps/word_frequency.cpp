#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include "MersenneTwister.h"
#include "word_frequency.h"
using namespace std;


//This function is used to construct and expand 
//a entire row of the nested map structure
//Words in the currently_working list will 
//be place in the corresponding sub layers
// this function can never be used in the base layer
WordFrequency* WordFrequency::Add_A_Row(list<string> &currently_working)
{ 
	if(currently_working.size()==0){
        assert(current_layer_number==0); // if the current_layer_number==0
        assert(word_map.size()==0); // if the word_map.size()==0
        return NULL;
    }
    else{
    	assert(current_layer_number>0);
	  	assert(currently_working.size()==current_layer_number);
	  	map<string,WordFrequency*>::iterator add_word;
	  	add_word=word_map.find(*(currently_working.begin()));
	  	//this is a new word that hasn't be included yet
	  	if(add_word==word_map.end()){
	  		WordFrequency* new_word=Make_WordFrequency_data(current_layer_number-1);
	  	    add_word=(word_map.insert(make_pair( (*(currently_working.begin())),new_word))).first;
	  	}
	  	else {
	  	    ++(add_word->second->word_frequency);
	  	}
	  	currently_working.pop_front();
	  	return add_word->second;
	}	

}

//This function simply add the word string 
//into the word_map within the layer
void WordFrequency::Add_A_Word(const string &word)
{++(word_map[word]->word_frequency);}

//This function finds the word from the 
//word_map within the current layer and
//return a pointer to the next sublayer 
WordFrequency* WordFrequency::NextLayer(const string& word, bool &is_word_found){

		map<string,WordFrequency*>::iterator find_word;
	  	find_word=word_map.find(word);
	  	//if the word is not included in the current word_map,
	  	// then the sentence is not printable, return null
	  	if(find_word==word_map.end()){ is_word_found=false; return NULL;}
	  	//else if we found the word, proceed to the next layer
	  	else{
	  		is_word_found=true;
	  		return find_word->second;
	  	}

}


//This function returns how many words 
//is included within the currently layer
int WordFrequency::getNumFollowingWord(){
	return word_map.size();
}

//This function checks if we are currently 
//at the baseLayer, which is the last layer
//containing a word_map 
bool WordFrequency::isBaseLayer() { 
	//NOTE: we are checking 
    // is it the lase layer that contains a map of following words
	// but not the last one in the linked wordfrequency class chain 
	bool base_layer=true;
	map<string, WordFrequency*>::iterator itr;
	for(itr = word_map.begin();itr!=word_map.end();++itr){
		if(itr->second->getNumFollowingWord()>0){base_layer=false;}
	}
	return base_layer;
}


//This funciton returns a vector that contains all
//pointers to all next layers, which is used for 
//checking each following word's frequency
vector<WordFrequency*> WordFrequency::getAllSub_Layer(){
	assert(current_layer_number>0);
	vector<WordFrequency*> all_sub_layers;
	map<string, WordFrequency*>::iterator itr;
	for(itr=word_map.begin();itr!=word_map.end();++itr){
		all_sub_layers.push_back(itr->second);
	}
	return all_sub_layers;
}


//This function returns the frequency of word
int WordFrequency::findword(const string &word){
	map<string,WordFrequency*>::iterator find_word;
  	find_word=word_map.find(word);
  	//if the word is not included in the current word_map,
  	//return 0 for frquency
  	if(find_word==word_map.end()){ return 0;}
  	//else if we found the word, return its frequency
  	else{		
  		return find_word->second->word_frequency;
  	}
}


//This function is similar to the previous findword function
//But this one is used to obtatin changes to string following_word
int WordFrequency::findword(const string &word, string &following_word){
	map<string,WordFrequency*>::iterator find_word;
  	find_word=word_map.find(word);
  	//if the word is not included in the current word_map,
  	//return 0 for frquency
  	if(find_word==word_map.end()){ return 0;}
  	//else if we found the word, return its frequency
  	else{
  		following_word=find_word->first;		
  		return find_word->second->word_frequency;
  	}
}



//Use this function to delete all sub_layers 
//within the word_map second colume
void WordFrequency::delete_Word_Map(){
	assert(word_map.size()>0);
	map<string, WordFrequency*>::iterator itr;
	for(itr=word_map.begin();itr!=word_map.end();++itr){
		assert(itr->second->getNumFollowingWord()==0);
		delete itr->second;
	}
} 



//Use this function to print all words in the word_map
//and their frequencies in a particular format
void WordFrequency::print_word_map(const string &pre){
	map<string, WordFrequency*>::iterator itr;
	for(itr=word_map.begin();itr!=word_map.end();++itr){
		cout<<pre<<itr->first<<" ("<< itr->second->word_frequency<<")"<<endl;
	}
}








//find either the most common word within the 
//current layer's word_map or find a randomly 
//generated word from word_map to form phrase

const string& WordFrequency::word_mostCommon( string &following_word, bool random_flag){
  	MTRand mtrand;
 	map<string, WordFrequency*>::iterator itr;
 	int max=0;
 	string most_common;
 	string random_word;
 	int selected_random=mtrand.randInt(word_map.size()-1);
    int random_number=0;
     //look over all words in word_map
	for(itr=word_map.begin();itr!=word_map.end();++itr){
		if(!random_flag){
			//if we find a word whose frequency is greater
			//save that word to most_common
			if((itr->second->word_frequency) > max){
				most_common=itr->first;
				max=(itr->second->word_frequency);
			}
			//else if two words have the same frequency
			//keep the alphabetically smaller one 
			else if( (itr->second->word_frequency)==max){
				if( most_common> (itr->first )){most_common=itr->first;}
				else continue;
			}
			else {}
		}
	    // if we are asked to randomly 
	    //select a word from word_map
	    else{
	    	if(random_number ==  selected_random){ 
	    		random_word=itr->first;
	    		++random_number;
	    	}
	    	else {++random_number;};
	    }
	}

        
    //return the word found
	if(random_flag){following_word=random_word;}
	else{following_word=most_common; }
	return following_word;
   
}