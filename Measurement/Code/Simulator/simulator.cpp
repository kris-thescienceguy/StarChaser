/******************************************************************************

                              Online C++ Debugger.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Debug" button to debug it.

*******************************************************************************/

#include <iostream>
#include <bitset>
#include <fstream>

using namespace std;

const signed int encoderDirections[] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};
volatile long encCount = 0;

int currentPins = 0;
int timeOfNoMove = 0;

int directionToMove(int oldEncoderState, int currentEncoder){

		cout << "Current State: " << bitset<2>(currentEncoder) << ". Old State: " << bitset<2>(oldEncoderState) << ". ";

        oldEncoderState <<= 2;
		oldEncoderState |= (currentEncoder & 0x03);
		int direction = encoderDirections[(oldEncoderState & 0x0F)];
		encCount += direction;
		
		cout << "Direction: " << direction << ". Total Position: " << encCount << "." << endl;

		//home = ((PINB >> 3) & 1); // Get state of home pin (shifts to LSB and then sets the rest of the array to 0)
		
		if (direction == 1) {
			//cout << "+AND " << ~(1 << 5); // Turns off -Az pin so that PORTB = XX0X XXXX
			currentPins &= ~(1 << 5);
			cout << "Current pins: " << bitset<8>(currentPins) << endl;
			//cout << "+OR " << (1 << 4) << endl;// Turns on +Az pin so that PORTB = XXX1 XXXX
			currentPins |= (1 << 4);
			cout << "Current pins: " << bitset<8>(currentPins) << endl;
		}else if(direction == -1){
			//cout << "-ANDS " << ~(1 << 4) << endl; // Turns off +Az pin so that PORTB = XX0X XXXX
			currentPins &= ~(1 << 4);
			cout << "Current pins: " << bitset<8>(currentPins) << endl;
			//cout << "-ORS " << (1 << 5) << endl; // Turns on -Az pin
			currentPins |= (1 << 5);
			cout << "Current pins: " << bitset<8>(currentPins) << endl;
		}else{
		    currentPins &= ~(3 << 4); // Turns off both +Az pin and -Az pin
			cout << "Something broke. Current pins: " << bitset<8>(currentPins) << endl;
		}
		
		return direction;
}


int main(void)
{
    /* Replace with your application code */
	static unsigned int oldEncoderState = 0;
	bool home = 0;
	int oldState = -10;

  	ifstream data ("simulator_tests/10rpm.txt", ifstream::in);
	ofstream output ("output.txt");

	int i = 0;
	//ofstream out ("simulator_tests/output.txt");
	if ( data.is_open() ) {
		int state;
		while ( data >> state ) {
			if (oldState == -10) { oldState = state; cout << "First run." << endl; continue;}
			directionToMove(oldState, state);
			oldState = state;
			int LED1 = ((currentPins >> 4) & 1);
			int LED2 = ((currentPins >> 5) & 1);
			output << i << " " << encCount << " " << LED1 << " " << LED2 << endl;
			i +=1;
		}
		data.close();
	}else{ cout << "Something went wrong" << endl; }
	
}


