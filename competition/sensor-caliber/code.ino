// —— 5-Sensor Calibration Sketch ——
// Reads A0–A4, tracks min/max values under “white” and “black”

const uint8_t SENS_PINS[] = {A0, A1, A2, A3, A4};
const uint8_t N = sizeof(SENS_PINS);

int whiteMin[N], whiteMax[N];
int blackMin[N], blackMax[N];

void setup()
{
    Serial.begin(9600);
    for (uint8_t i = 0; i < N; i++)
    {
        whiteMin[i] = whiteMax[i] = analogRead(SENS_PINS[i]);
        blackMin[i] = blackMax[i] = whiteMin[i];
    }
    Serial.println(F("=== Calibration Start ==="));
    Serial.println(F("First, place sensors over WHITE surface."));
    Serial.println(F("Then type ‘w’ + ENTER to record WHITE values."));
}

void loop()
{
    if (Serial.available())
    {
        char c = Serial.read();
        if (c == 'w' || c == 'W')
        {
            // record white
            for (uint8_t i = 0; i < N; i++)
            {
                int v = analogRead(SENS_PINS[i]);
                whiteMin[i] = min(whiteMin[i], v);
                whiteMax[i] = max(whiteMax[i], v);
            }
            Serial.println(F("Recorded WHITE. Now place on BLACK line and type ‘b’ + ENTER."));
        }
        else if (c == 'b' || c == 'B')
        {
            // record black
            for (uint8_t i = 0; i < N; i++)
            {
                int v = analogRead(SENS_PINS[i]);
                blackMin[i] = min(blackMin[i], v);
                blackMax[i] = max(blackMax[i], v);
            }
            // print results
            Serial.println(F("\n=== Calibration Results ==="));
            for (uint8_t i = 0; i < N; i++)
            {
                int whiteMid = (whiteMin[i] + whiteMax[i]) / 2;
                int blackMid = (blackMin[i] + blackMax[i]) / 2;
                int threshold = (whiteMid + blackMid) / 2;
                Serial.print("Sensor ");
                Serial.print(i);
                Serial.print(": WHITE [");
                Serial.print(whiteMin[i]);
                Serial.print("–");
                Serial.print(whiteMax[i]);
                Serial.print("], BLACK [");
                Serial.print(blackMin[i]);
                Serial.print("–");
                Serial.print(blackMax[i]);
                Serial.print("] → THRESH = ");
                Serial.println(threshold);
            }
            Serial.println(F("==========================="));
            Serial.println(F("Copy those THRESH values into your main sketch’s thresholds[] array."));
        }
    }
}
