import processing.serial.*;

Serial myPort;         // The serial port connected to the Arduino
String angle = "";      // Holds the incoming angle value as text
String distanceStr = ""; // Holds the incoming distance value as text
String data = "";        // Holds one full chunk of incoming data
int iAngle, iDistance;   // Numeric versions of angle/distance
int detectRange = 20;    // Same threshold as your Arduino code (cm) - change if you change it there too

void setup() {
  size(1200, 700); // size of the radar window

  // ---- IMPORTANT ----
  // This line prints every available COM port to the console.
  // Run the sketch once, look at the console output, find the one
  // that matches your Arduino (usually something like "COM5" or "/dev/ttyUSB0"),
  // then change the index number below (currently 0) to match its position in the list.
  printArray(Serial.list());

  String portName = "COM3";
  myPort = new Serial(this, portName, 9600); // must match Serial.begin(9600) in your Arduino code
  myPort.bufferUntil('.'); // Arduino sends a "." after each reading, so read up to that point
}

void draw() {
  fill(0, 4);            // slight fade effect for the sweep trail
  noStroke();
  rect(0, 0, width, height - height * 0.065);

  drawRadarBackground();
  drawSweepLine();
  drawText();
}

void serialEvent(Serial myPort) {
  data = myPort.readStringUntil('.'); // read one full chunk, ending in "."
  data = data.substring(0, data.length() - 1); // remove the trailing "."

  int index = data.indexOf(","); // find the comma separating angle and distance
  angle = data.substring(0, index);
  distanceStr = data.substring(index + 1, data.length());

  iAngle = int(angle);
  iDistance = int(distanceStr);
}

void drawRadarBackground() {
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);

  // Draws the concentric arcs of the radar
  arc(0, 0, (width - width * 0.0625), (width - width * 0.0625), PI, TWO_PI);
  arc(0, 0, (width - width * 0.27), (width - width * 0.27), PI, TWO_PI);
  arc(0, 0, (width - width * 0.479), (width - width * 0.479), PI, TWO_PI);
  arc(0, 0, (width - width * 0.687), (width - width * 0.687), PI, TWO_PI);

  // Draws the angle lines (0, 30, 60, 90, 120, 150, 180 degrees)
  line(-width / 2, 0, width / 2, 0);
  for (int a = 30; a < 180; a += 30) {
    line(0, 0, (width / 2) * cos(radians(a)), -(width / 2) * sin(radians(a)));
  }
  popMatrix();
}

void drawSweepLine() {
  pushMatrix();
  translate(width / 2, height - height * 0.074);
  strokeWeight(9);

  // Line turns red when something is detected within range, green otherwise
  if (iDistance < detectRange && iDistance > 0) {
    stroke(255, 10, 10);
  } else {
    stroke(30, 250, 60);
  }

  // The sweeping line, position driven by the live angle from Arduino
  line(0, 0, (width / 2) * cos(radians(iAngle)), -(width / 2) * sin(radians(iAngle)));
  popMatrix();
}

void drawDetectedObject() {
  // Only draw a red marker if something is within your detection range
  if (iDistance < detectRange && iDistance > 0) {
    pushMatrix();
    translate(width / 2, height - height * 0.074);

    // Scale the distance to fit the radar display radius
    float pixelDistance = map(iDistance, 0, detectRange, 0, width / 2);

    noStroke();
    fill(255, 10, 10);
    ellipse(pixelDistance * cos(radians(iAngle)), -pixelDistance * sin(radians(iAngle)), 16, 16);
    popMatrix();
  }
}

void drawText() {
  pushMatrix();
  fill(0, 0, 0);
  noStroke();
  rect(0, height - height * 0.0648, width, height);

  fill(98, 245, 31);
  textSize(16);
  text("Angle: " + iAngle + " deg", 20, height - 20);
  text("Distance: " + iDistance + " cm", 260, height - 20);

  if (iDistance < detectRange && iDistance > 0) {
    fill(255, 10, 10);
    textSize(20);
    text("OBJECT DETECTED", width / 2 - 90, height - 20);
  }
  popMatrix();
}
