// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
//The WordFrequency class contains an int indicating the current layer of window,
// another int representing the frequency of the word from the previous window 
// that is associated with the current class object, and finally a map that 
// contains the word frequency statistics of those following words
// To make the window size dynamic, I used a structure which mimics 
// a tree and using pointers to link each sub-layered windows 
// to their parent windows 
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include "word_frequency.h"
#include "MersenneTwister.h"
using namespace std;




typedef  WordFrequency*  MY_MAP; //this is going to be a pointer, which points to the nested map structure 


// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, 
  int window, const std::string &parse_method) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }



  //initiate WordFrequency data structure and 
  //make data point to the top layer
  data=data->Make_WordFrequency_data(window);
  string word;
  //because I will need to pop_front, use list 
  //more efficient O(1)
  list<string> current_working_window;
  //reading words from the file and store them
  //in the data structure
  while (ReadNextWord(istr,word)) {
    // skip the quotation marks 
    //(not used for this part)
    if (word == "\"") continue;
    //keep collecting words until we have 
    //enough to strehgth the data structure
    current_working_window.push_back(word);
    if( current_working_window.size()==window){
      //constructing the data map row by row,make a
      //copy of the list that we currently working on
      // because words_to_add will be altered 
      //by the end of Add_A_Row() function call
      list<string> words_to_add=current_working_window;

      WordFrequency* expand_row=data;

      while(expand_row!=NULL){
        //expand a row and add words into 
        //the corresponding map 
        expand_row=expand_row->Add_A_Row(words_to_add);
      }
      //pop the front word and proceed 
      //to a new set of words for a new row
      current_working_window.pop_front();
    }
    assert(current_working_window.size()<=window);

  }
  //corner case when we have the last word
  //then add that word to the top-layer word_map
  data->Add_A_Word(current_working_window.back());

}

//Print the words in the desired layer of word map
//sentence contains words or phrase that help navigate  
//us to the desired layer of word map
void Print(WordFrequency* data, const vector<string> &sentence){
  WordFrequency* find_last_word=data;
  string output_scree;
  int i=0;
  bool is_sentence_stored;

  //starts from the top, we find the correct layer of word map by
  //find words/ phrase in sentence
  while((find_last_word!=NULL) && (i<sentence.size()-1)){
    find_last_word=find_last_word->NextLayer(sentence[i],is_sentence_stored);
    // to accumulatively collect the phrase used for printing
    output_scree+=sentence[i]+" ";
    if(!is_sentence_stored){
      assert(find_last_word==NULL);
      //if the phrase is not stored in the structure
      cout<< "The word/phrase "<<output_scree<<"is NOT FOUND."<<endl;
      break;
    }
    else{
      ++i;
    }
  }
  assert(i==sentence.size()-1);
  assert((find_last_word->getCurrentLayer() )>0);
  // do the last word search separately since we have a corner case
  //where the phrase has the same size as windows
  //find the last word in sentence
  //and cout all folloing words and their frequencies
  if(find_last_word->isBaseLayer()){
    cout<<output_scree+sentence[i]+" "<< "(" << find_last_word->findword(sentence[i]) << ")"<<endl;
  }

  else{
    // is not in the base layer, just find the 
    //last word and print out all following words in the word_map
    //and cout all folloing words and their frequencies
    cout<<output_scree+sentence[i]+" "<< "("<<find_last_word->findword(sentence[i])<< ")"<<endl;
    find_last_word=find_last_word->NextLayer(sentence[i],is_sentence_stored);
    output_scree+=sentence[i]+" ";
    find_last_word->print_word_map(output_scree);
  }
  cout<<endl;

}



//Clean up function that delete all memory in the heap
void DeleteStructure( WordFrequency* data){
  //if we only have one layer of map for the data structure
  if(data->isBaseLayer()){data->delete_Word_Map();}
  //else we move to the base Layer and delete all word_maps
  //recursively from bottom to top
  else{
    vector<WordFrequency*> all_sub_layers=data->getAllSub_Layer();
    for(int i=0;i<all_sub_layers.size();++i){
      DeleteStructure( all_sub_layers[i]);
    }
  }

  //delete the top layer of word map
  delete data;

}


int main () {
  // a pointer to the map in the first layer
  MY_MAP data; 

  // Parse each command
  std::string command;    
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      int window;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;      

      LoadSampleText(data, filename, window, parse_method);
      //loading all words into the nested map structure
      cout << "Loaded " << filename 
    << " with window = " << window 
    << " and parse method = " << parse_method << endl <<endl;
    } 
  
    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      //to print the word frequency following the pattern
      //of words in the sentence vector
      Print(data,sentence);
    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
        random_flag = true;
      } 
      else {
        assert (selection_method == "most_common");
        random_flag = false;
      }
      
      // How many layers of word map in total
      int window=data->getCurrentLayer();
      assert(sentence.size() <= window);
      string generated_sentence;
      vector<string> collected_Words;
      WordFrequency* find_last_word=data;
      int i=0;
      bool is_word_stored;
      //starts from the top, we find the correct layer of word map by
      //find words/ phrase in sentence
      while((find_last_word!=NULL) && (i<sentence.size()-1)){
        find_last_word=find_last_word->NextLayer(sentence[i],is_word_stored);
        generated_sentence+=sentence[i]+" ";
        // to accumulatively collect the phrase used for printing
        collected_Words.push_back(sentence[i]);
        if(!is_word_stored){
           assert(find_last_word==NULL);
           //if the phrase is not stored in the structure
           cout<< "The word/phrase "<<generated_sentence<<"is NOT FOUND."<<endl;
           break;
        }
        else{
          ++i;
        }
      }
      
      //to find the last word in sentence and navigate
      //to the corresponding layer of word map  
      if(find_last_word!=NULL){
        assert(i==sentence.size()-1);
        assert((find_last_word->getCurrentLayer() )>0);
        string following_word;
        find_last_word->findword(sentence[i], following_word);
        generated_sentence+= following_word +" ";
        collected_Words.push_back(following_word);
        //following_word is the last word from the give phrase
        WordFrequency *find_new_word;

        //before each iteration of the while loop
        //following_word is the last word included in the generated_sentence
        // find_last_word points to the layer where following_word is 
        {
          //after finding all words in sentence, we start adding more 
          //words to the generated sentence until reach the length limit
          while(length>0){

          if(collected_Words.size()<window){
          // if the given phrase is not long enought 
          //to start a new word search fom the top layer 
          // searching and add words untile collected_Words.size()==window;
            assert(collected_Words.size()>0);
            //add more word into the collect_words vector 
            //until we reach the base layer
            for(int x=0;x<(window-collected_Words.size());++x){
              find_last_word=find_last_word->NextLayer(collected_Words[collected_Words.size()-1],is_word_stored);
              find_last_word->word_mostCommon(following_word,random_flag);
              generated_sentence+= following_word +" ";
              collected_Words.push_back(following_word);
              --length;
            }
            //if we've reached the length limit, break 
            if(length==0){break;}
            else{
            }
          }
          if(length==0){break;}


          following_word=collected_Words[collected_Words.size()-window+1];
          WordFrequency*find_new_word=data;
          // if we still haven't reached the length limite
          //keep adding words into the collected_word vector
          //by finding the next most common word from a word_map
          //in the corresponding layer 
          for(int i=collected_Words.size()-window+1;i<collected_Words.size();++i){
            find_new_word=find_new_word->NextLayer(collected_Words[i],is_word_stored);
          if(!is_word_stored){cout<< "The word/phrase "<<generated_sentence<<"CAN NOT be generated further."<<endl; break;}
          }
          assert(find_new_word->isBaseLayer());
          find_new_word->word_mostCommon(following_word,random_flag);
          generated_sentence+= following_word +" ";
          collected_Words.push_back(following_word);
          --length;
          }
        }
        //cout all words we've collected 
        for(int i=0;i<collected_Words.size()-1;++i)
          { cout<<collected_Words[i]+" ";}
        cout<<collected_Words[collected_Words.size()-1]<<endl<<endl;
      }
    }
     else if (command == "quit") {
      // delete all heap memory
      DeleteStructure(data);    
      break;
    } 
    else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}