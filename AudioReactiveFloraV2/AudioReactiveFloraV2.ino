// 
/*
    Name:       AudioReactiveFloraV2.ino
    Created:	9/10/2018 11:58:38 PM
    Author:     LF-A\Kirsten
*/

const int maxScale = 8;
const int redZone = 5;
#define MICPIN A9
#define REDPIN 12
#define GREENPIN 6
#define BLUEPIN 10

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
// The setup() function runs once each time the micro-controller starts
void setup()
{
	pinMode(REDPIN, OUTPUT);
	pinMode(GREENPIN, OUTPUT);
	pinMode(BLUEPIN, OUTPUT);
	analogWrite(BLUEPIN, random(0, 255));
	analogWrite(GREENPIN, random(0, 255));
	analogWrite(REDPIN, random(0, 255));
}

// Add the main program code into the continuous loop() function
void loop()
{
	unsigned long startMillis = millis();  // Start of sample window
	unsigned int peakToPeak = 0;   // peak-to-peak level

	unsigned int signalMax = 0;
	unsigned int signalMin = 2048;

	while (millis() - startMillis < sampleWindow)
	{
		sample = analogRead(MICPIN);
		if (sample < 1024)  // toss out spurious readings
		{
			if (sample > signalMax)
			{
				signalMax = sample;  // save just the max levels
			}
			else if (sample < signalMin)
			{
				signalMin = sample;  // save just the min levels
			}
		}
	}
	peakToPeak = signalMax - signalMin;
	// map 1v p-p level to the max scale of the display
	int displayPeak = map(peakToPeak, 0, 1023, 0, maxScale);

	// draw the new sample
	for (int i = 0; i <= maxScale; i++)
	{
		 if ((i < displayPeak) &&i < redZone) // draw in green
		{
			if (i == 1)
			{
				analogWrite(BLUEPIN, random(0, 255));
				analogWrite(GREENPIN, random(0, 255));
				analogWrite(REDPIN, random(0, 255));
				Serial.print("Beat");
			}
			
		}
		
	}

}
