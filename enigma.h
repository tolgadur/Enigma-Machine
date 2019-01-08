#include "enigma.h"
#include "rotor.h"
#include "reflector.h"
#include "plugboard.h"
#include "errors.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <cstring>
#include <exception>
 
using namespace std;

Enigma::Enigma(const int& argc, char**& argv){
  //Constructing Plugboard
  const char* plugboard_config = *(argv+1);
  if(nonNumericCharacter(plugboard_config)){
    cerr << "Non-numeric character in plugboard file plugboard.pb" << endl;
    throw NON_NUMERIC_CHARACTER;
  }
  plugboard = new Plugboard(plugboard_config);

  //Constructing Rotors
  for(int i = 3; i < argc-1; i++){
    if(nonNumericCharacter(*(argv+i))){
      cerr << "Non-numeric character for mapping in rotor file " << *(argv+i) << endl;
      throw NON_NUMERIC_CHARACTER;
    }
    rotor_objects.push_back(Rotor(*(argv+i)));
  }
  //Store Rotor positions in Vector and then pass to rotor position
  const char* rotor_position_filename = *(argv+(argc-1));
  if(nonNumericCharacter(rotor_position_filename)){
    cerr << "Non-numeric character in rotor positions file " << rotor_position_filename << endl;
    throw NON_NUMERIC_CHARACTER;
  }
  vector<int> rotor_position;
  storeRotorPos(rotor_position_filename, rotor_position);
  int number_of_rotors = argc-4;
  int rotor_position_size = rotor_position.size();
  if(rotor_position_size < number_of_rotors && number_of_rotors > 0){
    cerr << "No starting position for ";
    for(int i = 0; i < number_of_rotors - rotor_position_size; i++){
      cerr << "rotor " << i;
      if(number_of_rotors - rotor_position_size - i - 1){
        cerr << " and ";
      }
    }
    cerr << " in rotor position file: " << rotor_position_filename << endl;
    throw NO_ROTOR_STARTING_POSITION;
  }
  for(int i = 0; i <  argc-4; i++){
    rotor_objects[i].position = rotor_position[i];
  }

  //Constructing Reflector
  const char* reflector_config = *(argv+2);
  if(nonNumericCharacter(reflector_config)){
    cerr << "Non-numeric character in reflector file reflector.rf" << endl;
    throw NON_NUMERIC_CHARACTER;
  }
  reflector = new Reflector(reflector_config);

  //Checking for errors
  errors(reflector_config, argv);

  //Putting the rotors in place
  for(unsigned int i = 0; i < rotor_objects.size(); i++){
    rotor_objects[i].swapAlphabet();
    rotor_objects[i].swapBackAlphabet();
  }
}

void Enigma::encryption(){
  char character;
  cin >> ws;
  while(cin.get(character)){
    if(isInvalidCharacter(character)){
      cerr << character << " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
      throw INVALID_INPUT_CHARACTER;
    }
    character = plugboard->swap(character);
    if(rotor_objects.size() > 0){
      turnRotor(rotor_objects.size()-1,rotor_objects);
      character = passMessageThroughRotorsFirstWay(character, rotor_objects);
    }
    character = reflector->swap(character);
    if(rotor_objects.size() > 0){
      character = passMessageThroughRotorsSecondWay(character, rotor_objects);
    }
    character = plugboard->swap(character);
    cout << character;
    cin >> ws;
  }
}

void Enigma::storeRotorPos(const char filename[], std::vector<int>& rotor_position){
  int number;
  ifstream in;
  in.open(filename);

  while(in >> number){
    rotor_position.push_back(number);
  }
  in.close();
}

void Enigma::turnRotor(int rotor_count, vector<Rotor>& rotor_objects){
  if(rotor_count >= 0){
    if(rotor_objects[rotor_count].position < 25){
      rotor_objects[rotor_count].position++;
    }
    else{
      rotor_objects[rotor_count].position = 0;
    }
    for(unsigned int i = 0; i < rotor_objects[rotor_count].notches.size(); i++){
      if(rotor_objects[rotor_count].notches[i] == rotor_objects[rotor_count].position){
        turnRotor(rotor_count-1, rotor_objects);
      }
    }
  }
}

char Enigma::passMessageThroughRotorsFirstWay(char character, vector<Rotor>& rotor_objects){
  vector<Rotor>::reverse_iterator rit = rotor_objects.rbegin();
  for(; rit!=rotor_objects.rend(); ++rit){
    character = rit->swap(character);
  }
  return character;
}

char Enigma::passMessageThroughRotorsSecondWay(char character, vector<Rotor>& rotor_objects){
  for(unsigned int i = 0; i < rotor_objects.size(); i++){
    character = rotor_objects[i].swapBack(character);
  }
  return character;
}

//ERROR Functions
void Enigma::errors(const char* reflector_config, char**& argv){
  if(plugboard->incorrectNumberOfParameters()){
    cerr << "Incorrect number of parameters in plugboard file plugboard.pb" << endl;
    throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  if(plugboard->impossiblePlugboardConfig()){
    cerr << "The plugboard is either trying to connect a contact with itself, or it is trying to connect a contact to more than one contact. Neither will work!" << endl;
    throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
  }
  if(plugboard->invalidIndex()){
    cerr << "The configuration file contains a number that is not between 0 and 25. As the alphabet only has 26 characters, this will not work!" << endl;
    throw INVALID_INDEX;
  }
  if(reflector->incorrectNumberOfReflectorParameters(reflector_config)){
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  if(reflector->invalidReflectorMapping()){
    cerr << "The reflector is attempting to map an input to itself or pair each index with more than one other. Neither will work!" << endl;
    throw INVALID_REFLECTOR_MAPPING;
  }
  if(reflector->invalidIndex()){
    cerr << "The configuration file contains a number that is not between 0 and 25. As the alphabet only has 26 characters, this will not work!" << endl;
    throw INVALID_INDEX;
  }
  for(unsigned int i = 0; i < rotor_objects.size(); i++){
    if(rotor_objects[i].invalidIndex()){
      cerr << "The configuration file contains a number that is not between 0 and 25. As the alphabet only has 26 characters, this will not work!" << endl;
      throw INVALID_INDEX;
    }
    else if(rotor_objects[i].invalidRotorMapping(*(argv+i+3))){
      throw INVALID_ROTOR_MAPPING;
    }
  }
}

bool Enigma::isInvalidCharacter(char character){
  if(character < 65 || character > 90){
    return true;
  }
  return false;
}

bool Enigma::nonNumericCharacter(const char filename[]){
  //Read file into cstring
  ifstream in;
  in.open(filename);
  char number;
  char holder[MAX_LENGTH];
  int count = 0;

  while(in >> number){
    holder[count] = number;
    count++;
  }
  holder[count] = '\0';
  in.close();

  //check if cstring contains any non-numbers
  for(int i = 0; i < MAX_LENGTH && holder[i]; i++){
    if(!((holder[i] >= '0' && holder[i] <= '9') || holder[i] == ' ')){
      return true;
    }
  }
  return false;
}
