#include "enigma.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include <iostream>
#include <fstream>

using namespace std;

Rotor::Rotor(const char filename[]){
  ifstream in;
  in.open(filename);
  int count = 0;
  int number;

  while(in >> number){
    rotor_arguments_[count] = number;
    count++;
  }
  number_of_rotor_arguments_= count;

  //Storing Notches in seperate Vector
  for(int i = 0; i < number_of_rotor_arguments_ - 26; i++){
    notches.push_back(rotor_arguments_[i+26]);
  }
  in.close();
}

void Rotor::swapAlphabet(){
  for(int i = 0; i < 26; i++){
    swaped_alphabet[i] = alphabet[rotor_arguments_[i]];
  }
}

void Rotor::swapBackAlphabet(){
  for(int i = 0; i < 26; i++){
    for(int j = 0; j < 26; j++){
      if(alphabet[i] == swaped_alphabet[j]){
        swap_back_alphabet[i] = alphabet[j];
      }
    }
  }
}

char Rotor::swap(char character){
  for(int i = 0; i < 26; i++){
    if(character == alphabet[i]){
      character = swaped_alphabet[(i+position)%26]- position;
      if(character < 'A'){
        character += 26;
      }
      return character;
    }
  }
  return character;
}

char Rotor::swapBack(char character){
  for(int i = 0; i < 26; i++){
    if(character == alphabet[i]){
      character = swap_back_alphabet[(i+position)%26]- position;
      if(character < 'A'){
        character += 26;
      }
      return character;
    }
  }
  return character;
}

//ERROR FUNCTIONS
bool Rotor::invalidIndex(){
  for(int i = 0; i < number_of_rotor_arguments_; i++){
    if(rotor_arguments_[i] > 25 && rotor_arguments_[i] < 0){
      return true;
    }
  }
  return false;
}

bool Rotor::invalidRotorMapping(char filename[]){
  if(number_of_rotor_arguments_ < 26){
    cerr << "Not all inputs mapped in rotor file: " << filename << endl;
    return true;
  }

  for(int i = 0; i < 26; i++){
    for(int k = i+1; k < 26; k++){
      if(rotor_arguments_[i] == rotor_arguments_[k]){
        cerr << "Invalid mapping for output in file: " << filename << ". The rotor is attempting to map output " << rotor_arguments_[i] << " to more than one input!" << endl;
        return true;
      }
    }
  }
  return false;
}
