#ifndef REFLECTOR_H
#define REFLECTOR_H

#include "constants.h"

class Reflector{
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
  //Constructor function reading in the configuration file and calculating the length of it
  Reflector(const char filename[]);
  //Checkingif the configuration file attempts to map an input to itself or pair each index with more than one other.
  bool invalidReflectorMapping();
  //Checking if the configuration file does not contain exactly 13 pairs of numbers as it should
  bool incorrectNumberOfReflectorParameters(const char filename[]);
  //Checking if the configuration file does not contain a number that is between 0 and 25.
  bool invalidIndex();
  //Function to swap the data member swaped_alphabet to the order specified by the configuration file
  void swapAlphabet();
  //Function to swap the character passed in it according to the data member swaped alphabet
  char swap(char character);
};

#endif
