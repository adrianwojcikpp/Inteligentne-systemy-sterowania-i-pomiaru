#include <stdio.h>
#include "AS5600.h"

int main()
{
    int as5600;
    AS5600_Init(&as5600);
    while (1)
    {
        float d = convertRawAngleToDegrees(getRawAngle());
		//int d = getMagnetStrength();
        printf("Raw angle: %f \n",d);
    }
    
    return 0;
}
// g++ main.cpp AS5600.cpp AS5600.h -lwiringPi