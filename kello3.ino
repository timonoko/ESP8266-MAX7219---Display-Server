
#include <ESP8266WiFi.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <string.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 8

#define CLK_PIN   2 
#define DATA_PIN  1 
#define CS_PIN    0 

int INTENSITY = 2 ;

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

char* ssid = "****"; 
char* password = "*****";

WiFiServer server(80);

#define CHAR_SPACING  1 // pixels between characters

#define BUF_SIZE  75


void printText(uint8_t modStart, uint8_t modEnd, String Viesti)
{
  uint8_t   state = 0;
  uint8_t   curLen;
  uint16_t  showLen;
  uint8_t   cBuf[8];
  int16_t   col = ((modEnd + 1) * COL_SIZE) - 1;
  char p1[BUF_SIZE];

  strcpy(p1,Viesti.c_str());

  char *p = p1 ;

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::OFF);

  do     // finite state machine to print the characters in the space available
  {
    switch(state)
    {
      case 0: // Load the next character from the font table
        // if we reached end of message, reset the message pointer
        if (*p == '\0')
        {
          showLen = col - (modEnd * COL_SIZE);  // padding characters
          state = 2;
          break;
        }

        // retrieve the next character form the font file
        showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]), cBuf);
        curLen = 0;
        state++;
        // !! deliberately fall through to next state to start displaying

      case 1: // display the next part of the character
        mx.setColumn(col--, cBuf[curLen++]);

        // done with font character, now display the space between chars
        if (curLen == showLen)
        {
          showLen = CHAR_SPACING;
          state = 2;
        }
        break;

      case 2: // initialize state for displaying empty columns
        curLen = 0;
        state++;
        // fall through

      case 3:	// display inter-character spacing or end of message padding (blank columns)
        mx.setColumn(col--, 0);
        curLen++;
        if (curLen == showLen)
          state = 0;
        break;

      default:
        col = -1;   // this definitely ends the do loop
    }
  } while (col >= (modStart * COL_SIZE));

  mx.control(modStart, modEnd, MD_MAX72XX::UPDATE, MD_MAX72XX::ON);
}

void printLong(String s) {
  int x;
  if (s.length()<16) {
    printText(0, MAX_DEVICES-1, s); }
  else {
    for (x=0;x<(s.length()-15);x++) {
    printText(0, MAX_DEVICES-1, s.substring(x,x+24)); 
    delay(500); }}}
      
void setup()
{
  mx.begin();
  WiFi.begin (ssid,password);     // Connecting to the wifi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000); }
  server.begin();                           // Starting the server
  printText(0, MAX_DEVICES-1, "Hello!") ;
  mx.control(MD_MAX72XX::INTENSITY, INTENSITY);
}

void loop()
{
  WiFiClient client = server.available();     //Checking if any client request is available or not
  if (client)
  {
    boolean currentLineIsBlank = true;
    String buffer = "";  
    while (client.connected())
    {
      if (client.available())                    // if there is some client data available
      {
        char c = client.read(); 
        buffer+=c;                              // read a byte
        if (c == '\n' && currentLineIsBlank)    // check for newline character, 
        {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();    
          client.print("<HTML><title>MD722-naytto</title>");
          client.print("<body><center><h1>MD722-naytto</h1>");
          client.print("<a href=\"/M/Kokeilu\"\"> <button>KOE</button></a> <p>");
          client.print("<a href=\"/BP\"\"> <button>B+</button></a> <p>");
          client.print("<a href=\"/BM\"\"> <button>B-</button></a> <p>");
          client.print("</body></HTML>");
          break;        // break out of the while loop:
        }
        if (c == '\n') { 
          currentLineIsBlank = true;
          buffer="";       
        } 
        else 
          if (c == '\r') {     
	    if (buffer.indexOf("GET /M/")>=0)
	      { printLong(buffer.substring(7,buffer.length()-9)) ; };
	    if (buffer.indexOf("GET /BP")>=0)
	      { if (INTENSITY<16 ) { INTENSITY=INTENSITY+1; }
		mx.control(MD_MAX72XX::INTENSITY, INTENSITY); };
	    if (buffer.indexOf("GET /BM")>=0)
	      { if (INTENSITY>1) { INTENSITY=INTENSITY-1; }
		mx.control(MD_MAX72XX::INTENSITY, INTENSITY); };
	  }
        else {
          currentLineIsBlank = false;
        }  
      }
    }
    client.stop();
  }
}


