#ifndef ROTOR_H
#define ROTOR_H
 
#include <vector>
#include "constants.h"

class Rotor{
private:
  //Data Member to store all Rotor mappings
  int rotor_arguments_[MAX_LENGTH];
  //Data Member to store the number of arguments in the configuration file specifying the rotor mappings
  int number_of_rotor_arguments_;
  //Data members storing the alphabet, the alphabet in swapped order according to the mappings in the configuration file,
  //and the alphabets in inversed order according to the mappings in the configuration file. The latter is used to pass a character
  //through the rotors from left to right after exiting the reflector. The latter two cstrings are initialised with the alphabet in right order
  //and later swapped accordingly from the functions swapAlphabet and swapBackAlphabet.
  char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char swaped_alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char swap_back_alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
public:
  //Vector storing the notches specified in the configuration file
  std::vector<int> notches;
  //Data member specifying how many times the rotor has turned
  int position;
  //Constructor file reading in the rotor arguments, calculating and assigning the number of rotor arguments, and reading in the notches from the configuration file.
  Rotor(const char filename[]);
  //Functions swapping the cstrings swaped_alphabet and swap_back_alphabet according to the mappings in the constructor file. As mentioned above, the prior is used to
  //encyper a character when passed from right to left, and the latter when passed back from right to left after leaving the reflector.
  void swapAlphabet();
  void swapBackAlphabet();
  //Using the data members swaped_alphabet and position in order to map the character according to the configuration file and the number of rotations
  char swap(char character);
  //Using the data members swap_back_alphabet and position in order to map the character back after leaving the reflector file according to the configuration file and the number of rotations
  char swapBack(char character);
  //Functions to check if config files are well formed. The prior checks if therotor file contains a number that is not between 0 and 25 and the latter checks if the configuratio nfile 
  //attempts to map more than one input to the same output, or does not provide a mapping for some input.
  bool invalidIndex();
  bool invalidRotorMapping(char filename[]);
};


#endif
