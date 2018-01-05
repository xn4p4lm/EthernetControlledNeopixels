/*
 Name:		AurdinoCode.ino
 Created:	5/27/2015 10:33:54 PM
 Author:	dmoore
*/

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <Adafruit_NeoPixel.h>

#define PIN 4

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);
int incomingByte = 0;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
	0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 5, 80);

unsigned int localPort = 12;      // local port to listen on

								  // buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

											// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;


void setup() {
	//Ethernet Setup
	Ethernet.begin(mac, ip);
	Udp.begin(localPort);

	//Adafruit Library Setup
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'

	Serial.begin(9600);
}

void loop() {
	// if there's data available, read a packet
	int packetSize = Udp.parsePacket();

	if (packetSize)
	{
		memset(packetBuffer, 0, sizeof(packetBuffer));
		Serial.print("Received packet of size ");
		Serial.println(packetSize);
		Serial.print("From ");
		IPAddress remote = Udp.remoteIP();
		for (int i = 0; i < 4; i++)
		{
			Serial.print(remote[i], DEC);
			if (i < 3)
			{
				Serial.print(".");
			}
		}
		Serial.print(", port ");
		Serial.println(Udp.remotePort());

		// read the packet into packetBufffer
		Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
		Serial.println("Contents:");

		String output = packetBuffer;

		Serial.println(output);

		// send a reply, to the IP address and port that sent us the packet we received
		Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
		Udp.write(ReplyBuffer);
		Udp.endPacket();

		if (output == "green") {
			colorWipe(strip.Color(0, 5, 0), 2); // Green
		}
		if (output == "red") {
			colorWipe(strip.Color(5, 0, 0), 2); // Red
		}
		if (output == "blue") {
			colorWipe(strip.Color(0, 0, 5), 2); // Blue
		}
		if (output == "white") {
			colorWipe(strip.Color(5, 5, 5), 2); // White
		}
		if (output == "clear") {
			colorWipe(strip.Color(0, 0, 0), 2); // Reset
		}

		String compare = String(output.charAt(0));
		String key = "c";

		Serial.println(compare);
		Serial.println(key);

		if (compare == key) {
			String q = output.substring(1, 4);
			String w = output.substring(4, 7);
			String e = output.substring(7, 10);

			int r = q.toInt();
			int g = w.toInt();
			int b = e.toInt();

			Serial.println(q + " : " + w + " : " + e);

			colorWipe(strip.Color(r, g, b), 2); // custom
		}
	}
	delay(10);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
	for (uint16_t i = 0; i<strip.numPixels(); i++) {
		strip.setPixelColor(i, c);
		strip.show();
		delay(wait);
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	if (WheelPos < 85) {
		return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}
	else if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	else {
		WheelPos -= 170;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}
