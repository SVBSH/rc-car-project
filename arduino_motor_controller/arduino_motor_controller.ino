#include <AFMotor.h>

const int LED_PIN = 13;
const int MOTOR_FREQUENCY = 255;

AF_DCMotor motor_1(1);
AF_DCMotor motor_2(2);
AF_DCMotor motor_3(3);
AF_DCMotor motor_4(4);

void setup()
{
  // Inicializácia sériovej komunikácie
  Serial.begin(9600);
  initLED();
  motor_1.setSpeed(MOTOR_FREQUENCY);
  motor_2.setSpeed(MOTOR_FREQUENCY);
  motor_3.setSpeed(MOTOR_FREQUENCY);
  motor_4.setSpeed(MOTOR_FREQUENCY);
}

void initLED()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);
  delay(3000);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    Serial.print("Command:");
    Serial.println(command);
    command.trim();
    Serial.println("");

    handleCommand(command);
    delay(2000);
    motor_1.run(RELEASE);
    motor_2.run(RELEASE);
    motor_3.run(RELEASE);
    motor_4.run(RELEASE);
  }
}

void handleCommand(String command)
{
  if (command == "LEDON")
  {
    digitalWrite(LED_PIN, HIGH); // Zapnúť LED
  }
  else if (command == "LEDOFF")
  {
    digitalWrite(LED_PIN, LOW); // Vypnúť LED
  }
  else if (command == "CONTROL_FORWARD")
  {
    motor_1.run(BACKWARD);
    motor_2.run(BACKWARD);
    motor_3.run(BACKWARD);
    motor_4.run(BACKWARD);
  }
  else if (command == "CONTROL_BACKWARD")
  {
    motor_1.run(BACKWARD);
    motor_2.run(BACKWARD);
    motor_3.run(BACKWARD);
    motor_4.run(BACKWARD);
  }
  else if (command == "CONTROL_LEFT")
  {
    motor_2.run(BACKWARD);
    motor_3.run(BACKWARD);

    motor_1.run(RELEASE);
    motor_4.run(RELEASE);
  }
  else if (command == "CONTROL_RIGHT")
  {
    motor_1.run(BACKWARD);
    motor_4.run(BACKWARD);

    motor_2.run(RELEASE);
    motor_3.run(RELEASE);
  }
  else if (command == "CONTROL_STOP")
  {
    motor_1.run(RELEASE);
    motor_2.run(RELEASE);
    motor_3.run(RELEASE);
    motor_4.run(RELEASE);
  }
}