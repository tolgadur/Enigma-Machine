#include "enigma.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include <iostream>
#include <fstream>
 
using namespace std;

Reflector::Reflector(const char filename[]){
  int count = 0;
  int number;
  ifstream in;
  in.open(filename);

  while(in >> number){
    config_[count] = number;
    count++;
  }
  size_of_config_ = count;

  swapAlphabet();
  in.close();
}

void Reflector::swapAlphabet(){
  for(int i = 0; i < size_of_config_; i += 2){
    swaped_alphabet[config_[i]] = alphabet[config_[i+1]];
    swaped_alphabet[config_[i+1]] = alphabet[config_[i]];
  }
}

char Reflector::swap(char character){
  for(int j = 0; j < 26; j++){
    if(character == alphabet[j]){
      character = swaped_alphabet[j];
      return character;
    }
  }
  return character;
}

//ERROR FUNCTIONS
bool Reflector::invalidReflectorMapping(){
  for(int i = 0; i < size_of_config_; i++){
    for(int k = i+1; k < size_of_config_; k++){
      if(config_[i] == config_[k]){
        return true;
      }
    }
  }
  return false;
}

bool Reflector::incorrectNumberOfReflectorParameters(const char filename[]){
  int count = 0;
  int number;
  ifstream in;
  in.open(filename);

  while(in >> number){
    config_[count] = number;
    count++;
  }
  in.close();

  if(count != 26 && count % 2 != 0){
    cerr << "Incorrect (odd) number of parameters in reflector file " << filename << endl;
    return true;
  }
  else if (count < 26){
    cerr << "Insufficient number of mappings in reflector file: " <<  filename << endl;
    return true;
  }
  else if(count != 26){
    cerr << "Incorrect number of parameters in reflector file " << filename << endl;
    return true;
  }
  else{
    return false;
  }
}

bool Reflector::invalidIndex(){
  for(int i = 0; i < size_of_config_; i++){
    if(config_[i] > 25 && config_[i] < 0){
      return true;
    }
  }
  return false;
}
