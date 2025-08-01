vaf_fingerprint_device.ino#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Set up the software serial port for the fingerprint sensor
SoftwareSerial mySerial(2, 3); // RX, TX
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Set up the LCD display with I2C address 0x27 and 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {12, 11, 10, 9}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6, 5};    // Connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(10); } // For Leonardo/Micro/Zero

  lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Fingerprint");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  // Set the data rate for the sensor serial port
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Found!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor Not Found");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  lcd.setCursor(0, 1);
  lcd.print("Templates: ");
  lcd.print(finger.templateCount);
  delay(2000); // Display info for 2 seconds
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Press 1 to Enroll");
  lcd.setCursor(0, 1);
  lcd.print("Press 2 to Print");
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
    lcd.clear();
    if (key == '1') {
      lcd.setCursor(0, 0);
      lcd.print("Enroll Fingerprint");
      enrollFingerprint();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press 1 to Enroll");
      lcd.setCursor(0, 1);
      lcd.print("Press 2 to Print");
    } else if (key == '2') {
      lcd.setCursor(0, 0);
      lcd.print("Printing Info");
      printInfo(); // Placeholder for printing name and phone number
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press 1 to Enroll");
      lcd.setCursor(0, 1);
      lcd.print("Press 2 to Print");
    } else {
      lcd.setCursor(0, 0);
      lcd.print("Invalid Option");
      delay(1000); // Display the message for 1 second
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Press 1 to Enroll");
      lcd.setCursor(0, 1);
      lcd.print("Press 2 to Print");
    }
  }
  
  delay(50);  // Small delay to prevent overwhelming the sensor
}

void enrollFingerprint() {
  int id = finger.templateCount + 1; // New ID for the fingerprint
  Serial.print("Enrolling ID #");
  Serial.println(id);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place Finger...");

  while (getFingerprintEnroll(id) != FINGERPRINT_OK) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Place Finger...");
    delay(2000);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enrolled ID:");
  lcd.setCursor(0, 1);
  lcd.print(id);
  delay(2000);
}

uint8_t getFingerprintEnroll(uint8_t id) {
  int p = -1;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for finger");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
    delay(100);
  }

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.println("Remove finger");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
    delay(100);
  }

  Serial.println("Place same finger again");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place same finger");
  lcd.setCursor(0, 1);
  lcd.print("again");
  p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        Serial.println("Image taken");
        break;
      case FINGERPRINT_NOFINGER:
        Serial.print(".");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        Serial.println("Communication error");
        break;
      case FINGERPRINT_IMAGEFAIL:
        Serial.println("Imaging error");
        break;
      default:
        Serial.println("Unknown error");
        break;
    }
    delay(100);
  }

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.print("Creating model for #");
  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  return p;
}

void printInfo() {
  // Placeholder function to print name and phone number
  Serial.println("Printing Name and Phone Number...");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Name: John Doe");
  lcd.setCursor(0, 1);
  lcd.print("Phone: 123-456-7890");
}
