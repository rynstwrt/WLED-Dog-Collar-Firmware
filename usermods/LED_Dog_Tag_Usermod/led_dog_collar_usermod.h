#include "wled.h"
#include <Arduino.h>
#include <../usermods/LED_Dog_Tag_Usermod/led_dog_collar_effect_data.h>


#define NUM_EFFECTS 12
#define PALETTE 11 // Rainbow
#define BRIGHTNESS 25

#define LOOP_POLL_DELAY_MS 100

#define BUTTON_PIN 14
#define BUTTON_DEBOUNCE 100
#define BUTTON_HOLD_TIME 1500


class LEDDogCollarUsermod : public Usermod 
{
	private:
		unsigned long lastLoopTime = 0;

		LEDDogCollarEffectData* effectData[NUM_EFFECTS];
		int effectPos = 11;

		long lastButtonPressTime = 0;
		long lastButtonReleaseTime = 0;
		int lastButtonState = LOW;


	public:
		void applyEffect()
		{
			LEDDogCollarEffectData currentEffectData = (*effectData[effectPos]);

			effectCurrent = currentEffectData.getIndex();
			effectSpeed = currentEffectData.getSpeed();
			effectIntensity = currentEffectData.getIntensity();

			strip.restartRuntime();
			colorUpdated(CALL_MODE_DIRECT_CHANGE);
		}


		void setup()
		{
			Serial.begin(115200);
			//while (!Serial);

			pinMode(BUTTON_PIN, INPUT_PULLUP);

			effectPalette = PALETTE;
			bri = BRIGHTNESS;
			colorUpdated(CALL_MODE_DIRECT_CHANGE);
			stateUpdated(CALL_MODE_DIRECT_CHANGE);
			
			effectData[0] = new LEDDogCollarEffectData(8, 80, 255); // Color Loop
			effectData[1] = new LEDDogCollarEffectData(9, 110, 128); // Rainbow
			effectData[2] = new LEDDogCollarEffectData(13, 128, 0); // Theater
			effectData[3] = new LEDDogCollarEffectData(16, 150, 128); // Saw
			effectData[4] = new LEDDogCollarEffectData(40, 255, 100); // Scanner
			effectData[5] = new LEDDogCollarEffectData(72, 128, 255); // Noise 3
			effectData[6] = new LEDDogCollarEffectData(80, 180, 255); // Twinklefox
			effectData[7] = new LEDDogCollarEffectData(90, 255, 255); // Fireworks 1D
			effectData[8] = new LEDDogCollarEffectData(108, 130, 200); // Sine
			effectData[9] = new LEDDogCollarEffectData(109, 120, 255); // Phased noise
			effectData[10] = new LEDDogCollarEffectData(115, 255, 255); // Blends

			applyEffect();
		}


		void loop()
		{
			if (millis() - lastLoopTime > LOOP_POLL_DELAY_MS)
			{
				int buttonState = digitalRead(BUTTON_PIN);

				if (buttonState != lastButtonState && millis() - lastButtonReleaseTime > BUTTON_DEBOUNCE) // If button pressed or released
				{
					if (buttonState) // If was pressed down
					{
						Serial.println("PRESSED");
						lastButtonPressTime = millis();
						
					}
					else // If was released
					{
						

						if (millis() - lastButtonPressTime > BUTTON_HOLD_TIME) // If long hold
						{ 
							Serial.println("LONG PRESS RELEASE");

							bri = (bri == BRIGHTNESS) ? BRIGHTNESS / 2 : BRIGHTNESS;
							stateUpdated(CALL_MODE_DIRECT_CHANGE);
						}
						else // If regular button release
						{
							Serial.println("NORMAL RELEASE");

							++effectPos;
							if (effectPos >= NUM_EFFECTS)
								effectPos = 0;

							applyEffect();
						}

						lastButtonReleaseTime = millis();
					}

					lastButtonState = buttonState;					
				}

				
			}
		}
};