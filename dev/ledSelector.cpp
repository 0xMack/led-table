#include "ledSelector.h"
#include "tableout.h"
#include <string.h>
#include <map>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define MAX_WORD_SIZE 100
ledSelector::ledSelector(){
    //ctor
}

ledSelector::~ledSelector(){
    //dtor
}

int** getascii(){
	char filename[25] = "ascii_table.txt";
	int** ascii =  (int**)malloc(128 *sizeof(int*));
	FILE *fp = fopen(filename,"r");
	char delim[3] = " \n";
	if(fp==NULL){//Catch missing file
		perror("Error: Missing ascii table file\n");
		exit(EXIT_FAILURE);
	}
	char* in = (char*)malloc(sizeof(char));
	char* token = (char*)malloc(100 * sizeof(char));
	int askey = 0,ledCount = 0;
	while(fgets(in,100*sizeof(char),fp)){
		token = strtok(in,delim);
		ledCount = 0;
		ascii[askey] = (int*)malloc(sizeof(int)*25);
		token = strtok(NULL,delim);
		while(token!= NULL){
			sscanf(token,"%d",&ascii[askey][ledCount]);
			token = strtok(NULL,delim);
			ledCount++;
		}
		askey++;
	}
	return ascii;	
}
void testRun(){
    tableout output;
    int delay = 0;
    int ledNum = 0;
    int colour[3];
    cout << "Enter a delay in Microseconds: \n";
    cin >> delay;
    for(int i=0;i<100000000;i++){
        if(ledNum == 256){
            ledNum = 0;
        }
        else{
            ledNum++;
        }
        output.shift(ledNum,delay);
    }
}

void wave(int *ledArray){

}

void ball(int *ledArray){
    int randNum;
    int direction;
    randNum = rand()%4;

    if(ledArray[9]%8 == 7){
        randNum = 3;
    }
    if(ledArray[2]%8 == 0){
        randNum = 2;
    }
    if(ledArray[0]<8){
        randNum = 0;
    }
    if(ledArray[15]>248){
        randNum = 1;
    }
	switch(randNum){
			case 0:
					direction = 8;
					break;
			case 1:
					direction = -8;
					break;
			case 2: 
					direction = 1;
					break;
			case 3:
					direction = -1;
					break;
			default:
					printf("Default\n");
	}
    for(int i = 0; i < 12;i++){
        ledArray[i] = ledArray[i] + direction;
    }
}
void pwmLight(int red, int green, int blue){
    tableout output;
    output.pwmRHi();
    output.pwmGHi();
    output.pwmBHi();
    for(int j = 0;j<255;j++){
        if(red > j){
            output.pwmRLo();
        }
        if(green > j){
            output.pwmGLo();
        }
        if(blue > j){
            output.pwmBLo();
        }

    }
}

void colourFader(){
    for(int i = 0;i<1000000;i++){
        int green, red, blue = 0;
        int randColour = rand()%3;
		int ledArray[12] = {1,2,8,9,10,11,16,17,18,19,25,26}; //Ball

        if(randColour == 0){
            if(red == 0){
                for(red = 0;red<255;red++){
                    pwmLight(red,green,blue);
                }
            }
            else{
                for(red = 0;red>0;red--){
                    pwmLight(red,green,blue);
                }
            }
        }
        if(randColour == 1){
            if(green == 0){
                for(green = 0;green<255;green++){
                    pwmLight(red,green,blue);
                }
            }
            else{
                for(green = 0;green>0;green--){
                    pwmLight(red,green,blue);
                }
            }
        }
        if(randColour == 2){
            if(blue == 0){
                for(blue = 0;blue<255;blue++){
                    pwmLight(red,green,blue);
                }
            }
            else{
                for(blue = 0;blue>0;blue--){
                    pwmLight(red,green,blue);
                }
            }
        }
    }
}

void colourBall(){
    tableout output;
    int ledNum = 0, delay = 0;
    int definition = 10; //definition of colour variants (too big causes delay)
    int red = 0,green = 0,blue=0;
    int colCheck1 = 0, colCheck2 = 0, colCheck3 = 0;
    int ledArray[12] = {1,2,8,9,10,11,16,17,18,19,25,26}; // Ball
    for(int i = 0;i<10000000;i++){
        for(red=0;red<definition;red++){
            for(green=0;green<definition;green++){
                for(blue=0;blue<definition;blue++){
                    for (int colourVal = 0;colourVal<definition;colourVal++){
                        if(colourVal == red && colCheck1 == 0){
                            output.pwmRLo();
                            colCheck1 = 1;
                        }
                        if(colourVal == blue && colCheck2 == 0){
                            output.pwmBLo();
                            colCheck2 = 1;
                        }
                        if(colourVal == green && colCheck3 == 0){
                            output.pwmGLo();
                            colCheck3 = 1;
                        }
                        for(ledNum = 0;ledNum<12;ledNum++){
                            output.shift(ledArray[ledNum],delay);
                        }
                    }
                        output.pwmRHi();
                        output.pwmGHi();
                        output.pwmBHi();
                        colCheck1 = 0;
                        colCheck2 = 0;
                        colCheck3 = 0;
                        ball(ledArray);
                }
            }
        }
    }
}
void display(pattern* thePattern,int reps){
	tableout output;
	for(int i = 0; i < reps;i++){
		for(int colourVal = 0;colourVal<255;colourVal++){
			if(colourVal == thePattern->red){
				output.pwmRLo();
			}
			if(colourVal == thePattern->green){
				output.pwmGLo();
			}
			if(colourVal == thePattern->blue){
				output.pwmBLo();
			}
			for(int k = 0;k<thePattern->count;k++){
				output.shift(thePattern->ledPattern[k],0);
			}
		}
		output.pwmRHi();
		output.pwmGHi();
		output.pwmBHi();
	}
	//update pattern here?
}

pattern* getWordPattern(int** tab2ascii){
    char* word = (char*)malloc(sizeof(char)*MAX_WORD_SIZE);
	pattern* wordPattern = (pattern*)malloc(sizeof(pattern));
	cout << "Please Enter a word you want displayed:\n";
	fgets(word,100,stdin);
	cin >> word;
	for(int i = 0;i<strlen(word);i++){
		int* temp = tab2ascii[word[i]];
		int j = 0;
		int offset = 8 * 6 * (wordPattern->count + 1); //Pushes next letter forward 
		while(temp[j] != 0){
			wordPattern->ledPattern[wordPattern->count] = temp[j] + offset;
			wordPattern->count++;
			j++;
		}
	}
	return wordPattern;
}
void setColour(pattern* thePattern,int r,int g, int b){
	thePattern->red = r;
	thePattern->green = g;
	thePattern->blue = b;
}
void getColour(pattern* thePattern,int magnitude){
	//Changes the colour of a pattern by randomly incrementing/decrementing colours by magnitude
	int randColour = rand()%6;
	
	switch(randColour){
		case 0:
			if(255 > thePattern->red + magnitude){	
				thePattern->red += magnitude;
			}
			break;
		case 1:
			if(0 < thePattern->red -magnitude){
				thePattern->red -= magnitude;
			}
			break;
		case 2:
			if(255 > thePattern->green + magnitude){
				thePattern->green += magnitude;
			}
			break;
		case 3:
			if(0 < thePattern->green - magnitude){
				thePattern->green -= magnitude;
			}
			break;
		case 4:
			if(255 > thePattern->blue + magnitude){
				thePattern->blue += magnitude;
			}
			break;
		case 5:
			if(0 < thePattern->blue - magnitude){
				thePattern->blue -= magnitude;
			}
			break;
	}
}
void controlPattern(pattern* thePattern,int** tab2ascii){
	setColour(thePattern,255,255,255);//Initialize to white
	while(1){//Get pattern --> Get Colour --> Get position -->display
		getColour(thePattern,10);
		display(thePattern,1000);
		printf("R:%d G:%d B:%d\n",thePattern->red,thePattern->green,thePattern->blue);
	}
}
void ledSelector::mainMenu()
{   
	static int** tab2ascii = getascii();
	tableout output;
    pattern* thePattern;
	int ledNum = 0,choice = 0;
    cout << "Main Menu\n-------------------------------\n";
    cout << "Choose a Display Mode:\n";
    cout << "1:   Test Program\n";
    cout << "2:   Word Display\n";
    cout << "3:   Colour Fader\n";
        retry:
    cin >> choice;
	switch(choice){
		case 1:
			testRun();
			break;
		case 2:
			thePattern = getWordPattern(tab2ascii);
			controlPattern(thePattern,tab2ascii);
			break;
		case 3:
			colourFader();
			break;
		default:
			cout << "Please Reconsider...\n";
			goto retry;
	}
}
