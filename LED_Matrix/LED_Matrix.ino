/***************************************************
*
* For 32x16 RGB LED matrix.
*
* @author lg.gang
* @version  V1.0
* @date  2016-10-28
*
* GNU Lesser General Public License.
* See <http://www.gnu.org/licenses/> for details.
* All above must be included in any redistribution
* ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <RGBmatrixPanel.h>  // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE 9
#define A A0
#define B A1
#define C A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
const int trig_start = 10;
const int echo_start = 11;

const int trig_end = 12;
const int echo_end = 13;
extern volatile unsigned long timer0_millis;

void setup() {
  matrix.begin();
  Serial.begin(9600);
  pinMode(trig_start, OUTPUT);
  pinMode(trig_end, OUTPUT);

  pinMode(echo_start, INPUT);
  pinMode(echo_end, INPUT);
}

void loop() {
  unsigned long seconds, minutes, mils;
  mils = millis();
  seconds = millis() / 1000;
  minutes = seconds / 60;
  seconds %= 60;
  //clearScreen();
  if (calculateDistanceForStart() < 10) {
    noInterrupts();
    timer0_millis = 0;
    interrupts();
    clearScreen();
    displayForStart(minutes, seconds);
  }

  else if (calculateDistanceForEnd() < 10) {
    clearScreen();
    int _seconds = seconds;
    int _minutes = minutes;
    int _mils = mils;
    while (1) {
      displayForEnd(_minutes, _second, _mils);
      if (calculateDistanceForStart() < 10)
        break;
    }
  }

  else {
    clearScreen();
    runTime(minutes, seconds, mils)
  }
}

int calculateDistanceForStart() {
  unsigned long duration_start;
  int distance_start;
  digitalWrite(trig_start, 0);
  delayMicroseconds(2);
  digitalWrite(trig_start, 1);
  delayMicroseconds(5);
  digitalWrite(trig_start, 0);

  duration_start = pulseIn(echo_start, HIGH);
  distance_start = int(duration_start / 2 / 29.412);
  Serial.println(distance_start);
  return distance_start;
}

int calculateDistanceForEnd() {
  unsigned long duration_end;
  int distance_end;
  digitalWrite(trig_end, 0);
  delayMicroseconds(2);
  digitalWrite(trig_end, 1);
  delayMicroseconds(5);
  digitalWrite(trig_end, 0);

  duration_end = pulseIn(echo_end, HIGH);
  distance_end = int(duration_end / 2 / 29.412);
  Serial.println(distance_end);
  return distance_end;
}

void clearScreen() {
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(1);
}

void displayForStart(int minutes, int seconds) {
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(minutes / 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(minutes % 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(':');
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(seconds / 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(seconds % 10);

  matrix.setCursor(10, 9);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('0');
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print('0');
}

void displayForEnd(int minutes, int seconds, int mils) {
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(minutes / 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(minutes % 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(':');
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(seconds / 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(seconds % 10);

  matrix.setCursor(10, 9);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print((mils / 10) % 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print((mils % 100) % 10);
}

void runTime(int minutes, int seconds, int mils) {
  matrix.setCursor(1, 0);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);   // size 1 == 8 pixels high

  // print each letter with a rainbow color
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(minutes / 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(minutes % 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(':');
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(seconds / 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print(seconds % 10);

  matrix.setCursor(10, 9);  // start at top left, with one pixel of spacing
  matrix.setTextSize(1);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print((mils / 10) % 10);
  matrix.setTextColor(matrix.Color333(7, 0, 0));
  matrix.print((mils % 100) % 10);
}