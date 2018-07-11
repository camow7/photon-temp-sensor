#include "Particle.h"
#include <math.h>

void publishData(); //Initial the function publishData()

//Initialise Constants & Variables
const unsigned long PUBLISH_PERIOD_MS = 10000; //Interval which firebase is updated in MS
const unsigned long FIRST_PUBLISH_MS = 5000; //Initial firebase update delay
const char *PUBLISH_EVENT_NAME = "Tempdata"; //Variable to save data under on firebase

unsigned long lastPublish = FIRST_PUBLISH_MS - PUBLISH_PERIOD_MS; //Last time published

int photoresistor = A0; //Assigns the Alias photoresistor to the pin A0 & store an integer
int power = D7; //Assigns the Alias Power to pin A5 & stores an integer
int analogvalue; //Initialises an integer variable called analogvalue

//Initialise the board and assign pins to their appropriate functions.
void setup() {
Serial.begin(9600); //Sets baud rate to 9600bps

	pinMode(photoresistor,INPUT);  //Assigns the pin A0 as an input
 	pinMode(power,OUTPUT); //Assigns the pin A5 as an output
   	digitalWrite(power,HIGH); //Sets the pin A5 to HIGH/ON
    	Particle.variable("analogvalue", &analogvalue, INT); //Expose a variable through the cloud

}

//Main part of the program that loops until shutdwon
void loop()
{
    	analogvalue = analogRead(photoresistor); //Reads analog data from pin A0
	if (millis() - lastPublish >= PUBLISH_PERIOD_MS) //Determines if the interval period is reached

	{
		lastPublish = millis(); //Updates lastPublish variable time
		publishData(); //Enters publishData function
	}
}

void publishData()
{

	int lux = 300; //Sets lux variable from the variable analogvalue

	char buf[256]; //creates a character buffer with a maximum size of 256 characters long
	snprintf(buf, sizeof(buf), "{\"lux\":%d}", lux); //Creates the buffer with the appropriate information
	Serial.printlnf("publishing %s", buf); //Prints output to serial. Used for debugging purposes.
	Particle.publish(PUBLISH_EVENT_NAME, buf, PRIVATE); //Sends buffer to firebase
}
