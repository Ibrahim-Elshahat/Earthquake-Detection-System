import processing.serial.*;

Serial myPort;
int xPos = 0;
float y1 = 0;
float y2 = 0;
float y3 = 0;

void setup() {
  initializeSerial();
  initializeGraph();
}

void draw() {
  visualizeData();
}

void initializeSerial() {
  myPort = new Serial(this, "COM10", 9600);
  myPort.bufferUntil('\n');
}

void initializeGraph() {
  size(1200, 700);
  background(80);
}

void visualizeData() {
  String inString = myPort.readStringUntil('$');

  if (inString != null) {
    int l1 = inString.indexOf("x=") + 2;
    String temp1 = inString.substring(l1, l1 + 3);
    int l2 = inString.indexOf("y=") + 2;
    String temp2 = inString.substring(l2, l2 + 3);
    int l3 = inString.indexOf("z=") + 2;
    String temp3 = inString.substring(l3, l3 + 3);

    float inByte1 = float(temp1 + (char)9);
    inByte1 = map(inByte1, -80, 80, 0, height - 80);
    float inByte2 = float(temp2 + (char)9);
    inByte2 = map(inByte2, -80, 80, 0, height - 80);
    float inByte3 = float(temp3 + (char)9);
    inByte3 = map(inByte3, -80, 80, 0, height - 80);
    float x = map(xPos, 0, 1120, 40, width - 40);

    strokeWeight(2);
    stroke(175);
    Line(0, 0, 0, 100);
    textFont(createFont("Arial", 24, true));
    fill(0, 0, 255);
    textAlign(RIGHT);
    xmargin("EarthQuake Graph (SESMIOGRAPH)", 200, 100);

    fill(100);
    strokeWeight(100);
    line(1050, 80, 1200, 80);

    strokeWeight(1);
    textAlign(RIGHT);
    fill(0, 0, 255);
    String temp = "X:" + temp1;
    Text(temp, 100, 95);

    fill(0, 255, 0);
    temp = "Y:" + temp2;
    Text(temp, 100, 92);

    fill(255, 0, 0);;
    temp = "Z:" + temp3;
    Text(temp, 100, 89);

    strokeWeight(2);
    int shift = 40;

    stroke(0, 0, 255);
    if (y1 == 0)
      y1 = height - inByte1 - shift;
    line(x, y1, x + 2, height - inByte1 - shift);
    y1 = height - inByte1 - shift;

    stroke(0, 255, 0);
    if (y2 == 0)
      y
