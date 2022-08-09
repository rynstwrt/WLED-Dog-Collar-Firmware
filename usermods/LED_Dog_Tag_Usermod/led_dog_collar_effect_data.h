#include "wled.h"


class LEDDogCollarEffectData
{
	private: 
		int index;
		byte speed;
		byte intensity;

	public: 
		LEDDogCollarEffectData(int index, byte speed, byte intensity)
		{
			this->index = index;
			this->speed = speed;
			this->intensity = intensity;
		}

		int getIndex()
		{
			return index;
		}

		long getSpeed()
		{
			return speed;
		}

		long getIntensity()
		{
			return intensity;
		}
};