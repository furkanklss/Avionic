#ifndef INC_SEPARATIONALGORITM_HPP_
#define INC_SEPARATIONALGORITM_HPP_

#include "stm32f4xx_hal.h"
using namespace std;

// MOSFET_1  -->  GPIO_PIN_9  E
// MOSFET_2  -->  GPIO_PIN_10 E
// RGB_1     -->  GPIO_PIN_11 E
// RGB_2     -->  GPIO_PIN_12 E
// RGB_3     -->  GPIO_PIN_13 E
// BUZZER    -->  GPIO_PIN_14 E

class SeparationAlgoritm {

public:
	void SeparationAlgorit(uint16_t altitude); // ALGORITM FOR SEPARATE
	void mosfet_1_Active(); // MOSFET ACTIVE
	void mosfet_2_Active(); // MOSFET ACTIVE
	void blueActive(); // BLUE LED
	void yellowActive(); // YELLOW RED
 	void greenActive(); // GREEN LED
	void redActive(); // RED LED
	void setRGBColor(uint8_t red, uint8_t green, uint8_t blue); // SETTINGS RGB LED
	void buzzerActive(); // BUZZER ACTIVE
private:
	typedef enum {
		/* STATE CONTROL NAME */
		FIRST_CONTROL_0_1000M,
		SECOND_CONTROL_1000_2000M,
		THIRD_CONTROL_2000_3000M,
		FOURTH_CONTROL_APOGEE_FIRST_SEPARATE,
		FIFTH_CONTROL_3000_2000M,
		SIXTH_CONTROL_2000_1000M,
		SEVENTH_CONTROL_1000_600M,
		EIGHTH_CONTROL_SECOND_SEPARATE,
		NINETH_CONTROL_100M_SAVE
	} StateControl;

	StateControl State; // INSTANT STATUS
	uint16_t controlDegree=15; // ROCKET DEGREE FROM BNO055
	bool ApogeeControl = false;  // is APOGEE ?
	bool SeparateControl = false; // is SECOND SEPARATE ?
	bool IncreaseControl=false; // is RISING ?
};


#endif /* INC_SEPARATIONALGORITM_HPP_ */
