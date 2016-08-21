#include "tableout.h"
#include <wiringPi.h>
#include <string>
#include <iostream>
#include <bitset>
#include <cmath>
#include <unistd.h>

using namespace std;
//Variables

const int ser = 14, clk = 15, latchIn = 18, pwmC = 8, pwmR = 25, pwmG = 24, pwmB = 23; // Pin numbers on the RPi
int allPins [7] = {ser,clk,latchIn,pwmC,pwmR,pwmG,pwmB}; //Pin array for easy pin mode settings
int ledRow = 1; //Table rows (0-7)
int ledCol = 1; //Table columns (0-31)
int ledNum = 1; //LED number (0-255)
string binRow = ""; //Binary string to be shifted into shift registers - controls row
string binCol = ""; //Binary string to be shifted into shift registers - controls column
string binCup = "101111"; //Temporary placeholder until table's cup lights work
string binOut = ""; //Concatenated final string to be pushed to shift registers
int i = 0;
//Variables


tableout::tableout(){
}
string convBinRow(int& ledRow){ //Converts ledRow to a binary string
    bitset<5>      mybits(ledRow); // 5 binary digits
    string mystring = mybits.to_string<char,string::traits_type,string::allocator_type>();
	return mystring;
}
string convBinCol(int& ledCol){ //Converts ledCol to a binary String
    bitset<3>      mybits(ledCol); //3 binary digits
    string mystring = mybits.to_string<char,string::traits_type,string::allocator_type>();
	return mystring;
}
string concatBin(string& binCol,string& binRow){ //Concatenates the binary strings for the shift registers
    string binOut = "";
    binOut = "00"+ binCup + binRow + binCol + binRow + "000" + binRow + "000"; //The zeroes are placeholders to accommodate hardware(shift registers)
    return binOut;
}
int splitColRow(int& ledNum){ //Takes an led number and splits it into column and row numbers
	ledRow = int(floor(ledNum / 8));
    ledCol = int(ledNum % 8);
	return ledRow, ledCol;
}


//**************************************************RPI CODE********************************************************
/*
void tableout::setDefaultShift() // Sets up the default RPi GPIO pins for output
{
    wiringPiSetupGpio();
    pinMode(14,OUTPUT);
    pinMode(15,OUTPUT);
    pinMode(18,OUTPUT);
    pinMode(25,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(23,OUTPUT);
    digitalWrite(25,HIGH);
    digitalWrite(24,HIGH);
    digitalWrite(23,HIGH);
}
void latch(){ // latches the shift registers
    digitalWrite(18,HIGH);
    digitalWrite(18,LOW);
}
void tableout::pwmBLo(){ //Turns blue pwm low ...
    digitalWrite(25,LOW);
}
void tableout::pwmBHi(){
    digitalWrite(25,HIGH);
}
void tableout::pwmGLo(){
    digitalWrite(24,LOW);
}
void tableout::pwmGHi(){
    digitalWrite(24,HIGH);
}
void tableout::pwmRLo(){
    digitalWrite(23,LOW);
}
void tableout::pwmRHi(){
    digitalWrite(23,HIGH);
}
void tableout::shift(int ledNum,int delay){
    ledRow,ledCol = splitColRow(ledNum);
    binRow = convBinRow(ledRow);
    binCol = convBinCol(ledCol);
    binOut = concatBin(binCol,binRow);

    for (int y = 0;y < 32;y = y + 1){
        if(binOut[y] == '1'){
            digitalWrite(14,HIGH);
        }
        else{
            digitalWrite(14,LOW);
        }
      digitalWrite(15,HIGH);
      digitalWrite(15,LOW);
    }
    latch();
    usleep(delay);
}
*/
//**************************************************RPI CODE********************************************************


//------------------------------------------------EMULATOR CODE------------------------------------------------------------------

//Allows code to be tested and ran without the table hardware (without c++ wirePi)

void tableout::setDefaultShift() // Sets up the default RPi GPIO pins for output
{
}
void latch() // latches the shift registers
{
}
void tableout::pwmBLo() //Turns blue pwm low ...
{
}
void tableout::pwmBHi()
{
}
void tableout::pwmGLo()
{
}
void tableout::pwmGHi()
{
}
void tableout::pwmRLo()
{
}
void tableout::pwmRHi()
{
}
void tableout::shift(int ledNum,int delay)
{
}

//------------------------------------------------EMULATOR CODE------------------------------------------------------------------
