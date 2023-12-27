#include <FastLED.h>
 
#define NUM_LEDS 179

#define DATA_PIN 12 // Change this to the appropriate pin for your setup
 
#define SOUND_SENSOR_PIN A0 // Change this to the appropriate pin for your sound sensor
 
// Define the color palette

DEFINE_GRADIENT_PALETTE(soundPalette) {
    0,    255, 255, 255,   // White
    32,   255, 69,  0,     // Red-Orange
    64,   255, 140, 0,     // Dark Orange
    96,   255, 255, 0,     // Yellow
    128,  0,   255, 0,     // Green
    160,  0,   255, 255,   // Cyan
    192,  0,   0,   255,   // Blue
    224,  75,  0,   130,   // Indigo
    255,  128, 0,   128,   // Purple
    50,   255, 0,   0,     // Red
    80,   255, 165, 0,     // Orange
    110,  255, 255, 0,     // Yellow
    140,  0,   128, 0,     // Dark Green
    170,  0,   255, 255,   // Turquoise
    200,  0,   0,   128,   // Navy Blue
    230,  128, 0,   128    // Maroon
};
 
CRGBPalette16 currentPalette = soundPalette;
 
CRGB leds[NUM_LEDS];
 
void setup() {

    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);

    Serial.begin(115200);

}
 
void loop() {

    int soundValue = analogRead(SOUND_SENSOR_PIN);

    Serial.println(soundValue);
 
    // Adjust the threshold based on your sensor characteristics

    int soundThreshold = 586;

    if (soundValue > 600) {

        soundValue = 600;

    }
 
    if (soundValue > soundThreshold) {

        int numLEDsToGlow = map(soundValue, soundThreshold, 600, 3, 6);
 
        // Randomly choose a color when the sound intensity changes

        CRGB bundleColor = ColorFromPalette(currentPalette, random8());
 
        // Snake animation with a dynamic color based on sound intensity

        for (int i = 0; i < NUM_LEDS - numLEDsToGlow + 1; i++) {

            for (int j = 0; j < numLEDsToGlow; j++) {

                leds[i + j] = bundleColor;

            }

            FastLED.show();

            delay(0); // Adjust the delay to control the animation speed

            // Clear the LEDs

            for (int j = 0; j < numLEDsToGlow; j++) {

                leds[i + j] = CRGB::Black;

            }

        }

    } else {

        // If no sound, turn off all LEDs

        fill_solid(leds, NUM_LEDS, CRGB::Black);

        FastLED.show();

    }

}