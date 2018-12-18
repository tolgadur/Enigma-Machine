#ifndef PLUGBOARD_H
#define PLUGBOARD_H

#include "constants.h"

class Plugboard{
private:
  //Data member storing content of configuration file
  int config_[MAX_LENGTH];
  //Data member storing size of configuration file
  int size_of_config_ = 0;
  //Data members storing an alphabet and an alphabet in swaped order according to mappings of configuration file. Latter is
  //initialised as an alphabet in correct order and later swaped by the function: swapAlphabet.
  char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char swaped_alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
public:
  //Constructor function to read in config file into private data member config
  Plugboard(const char filename[]);
  //Checking if the file attempts to connect a contact with itself, or with more than one other contact.
  bool impossiblePlugboardConfig();
  //Checking if the function contains an odd number of numbers.
  bool incorrectNumberOfParameters();
  //Checking if the configuration file does not contain a number that is between 0 and 25.
  bool invalidIndex();
  //Function to swap the data member swaped_alphabet to the order specified by the configuration file
  void swapAlphabet();
  //Function to swap the character passed in it according to the data member swaped alphabet
  char swap(char character);
};

#endif
