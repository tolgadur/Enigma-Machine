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
#include <exception>


using namespace std;

bool insufficientNumberOfParameters(int number_of_arguments);

int main(const int argc, char** argv){
  //Checking if sufficient parameters were passed
  if(insufficientNumberOfParameters(argc)){
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  try{
    Enigma enigma(argc, argv);

    //Inputting message which is to be encrypted
    enigma.encryption();
  }
  catch(int error){
    return error;
  }

  return NO_ERROR;
}

bool insufficientNumberOfParameters(int number_of_arguments){
  if(number_of_arguments <= 2){
    return true;
  }
  return false;
}
