#include "wordcount.h"
#include <iostream>
#include <sstream>


#define MAX_WORDS 30


int Dictionary::get_value(const std::string& word){
  int cur_size = get_size();
  for (int i=0; i<cur_size; i++) {
    if (word_key[i]==word){
      return num_value[i];
    }
  }
  return -1;
}

int Dictionary::get_idx(const std::string& word){
  int cur_size = get_size();
  for (int i=0; i<cur_size; i++) {
    if (word_key[i]==word){
      return i;
    }
  }
  return cur_size;
}

void Dictionary::put(const std::string& word){
  int val = get_value(word);
  int idx;
  int cur_size = get_size();
  if (val==-1) {
    word_key[cur_size]=word;
    num_value[cur_size]=1;
    size_up();
    std::cout << "Put action on ("<< word <<") : first time" << std::endl;
  }
  else {
    idx = get_idx(word);
    num_value[idx]+=1;
    std::cout << "Put action on ("<< word <<") : value change " << num_value[idx]-1 << " -> " << num_value[idx] << std::endl;;
  }
}

void num_to_string(int x){
  if (x==1){ std::cout << "once";}
  else if (x==2){ std::cout << "twice";}
  else {std::cout << x << " times";}
}

void wordcount(std::string sentences) {
  // store number of total words
  unsigned int total_words = 0;

  // TODO: calculate word counts
  std::string tmp_string;
  std::stringstream mystream(sentences);
  Dictionary mydict;
  while (mystream>>tmp_string){
    mydict.put(tmp_string);
    total_words++;
  }
  // total_words=mydict.get_size();
  std::cout << "Total number of words: " << total_words << std::endl;

  // TODO: print number of appearances for each word
  for (int i=0; i<mydict.get_size(); i++){
    std::cout << "Word \"" << mydict.word_key[i]<< "\" appears ";
    num_to_string(mydict.num_value[i]);
    std::cout<<".\n";
  }
}


// Word "love" appears once.