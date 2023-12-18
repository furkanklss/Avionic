#include "SeparationAlgoritm.hpp"
#include "Print.hpp"

void SeparationAlgoritm::SeparationAlgorit(uint16_t altitude) {
	if (altitude < 1000 && IncreaseControl == false && ApogeeControl == false && SeparateControl == false) {
		State = FIRST_CONTROL_0_1000M;
	}
	if (altitude > 1000 && altitude < 2000 && IncreaseControl == false && ApogeeControl == false && SeparateControl == false) {
		State = SECOND_CONTROL_1000_2000M;
	}
	if (altitude > 2000 && altitude < 3000 && IncreaseControl == false && ApogeeControl == false && SeparateControl == false) {
		State = THIRD_CONTROL_2000_3000M;
		IncreaseControl = true;
	}
	if (altitude > 3000 && controlDegree > 10 && controlDegree < 20 && IncreaseControl == true && ApogeeControl == false && SeparateControl == false) {
		State = FOURTH_CONTROL_APOGEE_FIRST_SEPARATE;
		ApogeeControl = true;
	}
	if (altitude > 2000 && altitude < 3000 && IncreaseControl == true && ApogeeControl == true && SeparateControl == false) {
		State = FIFTH_CONTROL_3000_2000M;
	}
	if (altitude > 1000 && altitude < 2000 && IncreaseControl == true && ApogeeControl == true && SeparateControl == false) {
		State = SIXTH_CONTROL_2000_1000M;
	}
	if (altitude > 600 && altitude < 1000 && IncreaseControl == true && ApogeeControl == true && SeparateControl == false) {
		State = SEVENTH_CONTROL_1000_600M;
		ApogeeControl = true;
	}
	if (altitude > 399 && altitude < 600 && IncreaseControl == true && ApogeeControl == true && SeparateControl == true) {
		State = EIGHTH_CONTROL_SECOND_SEPARATE;
	}
	if (altitude < 100 && IncreaseControl == true && ApogeeControl == true && SeparateControl == true ) {
		State = NINETH_CONTROL_100M_SAVE;
	}

	switch (State) {

	case FIRST_CONTROL_0_1000M: {
		blueActive();
		printf( "FIRST_CONTROL_0_1000M \n");
	}
	break;

	case SECOND_CONTROL_1000_2000M: {
		yellowActive();
		printf( "SECOND_CONTROL_1000_2000M \n");
	}
	break;

	case THIRD_CONTROL_2000_3000M: {
		greenActive();
		printf( "THIRD_CONTROL_2000_3000M \n");
	}
	break;

	case FOURTH_CONTROL_APOGEE_FIRST_SEPARATE: {
		mosfet_1_Active();
		redActive();
		printf( "FOURTH_CONTROL_APOGEE_FIRST_SEPARATE \n");
	}
	break;

	case FIFTH_CONTROL_3000_2000M: {
		blueActive();
		printf( "FIFTH_CONTROL_3000_2000M \n");
	}
	break;

	case SIXTH_CONTROL_2000_1000M: {
		yellowActive();
		printf( "SIXTH_CONTROL_2000_1000M \n");
	}
	break;

	case SEVENTH_CONTROL_1000_600M: {
		greenActive();
		printf( "SEVENTH_CONTROL_1000_600M \n");
	}
	break;

	case EIGHTH_CONTROL_SECOND_SEPARATE: {
		redActive();
		mosfet_2_Active();
		printf( "EIGHTH_CONTROL_SECOND_SEPARATE \n");
	}
	break;

	case NINETH_CONTROL_100M_SAVE: {
		buzzerActive();
		printf( "NINETH_CONTROL_100M_SAVE \n");
	}
	break;
	}

}

void SeparationAlgoritm::mosfet_1_Active() {
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, GPIO_PIN_SET);
}

void SeparationAlgoritm::mosfet_2_Active() {
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, GPIO_PIN_SET);
}

void SeparationAlgoritm::blueActive() {
	setRGBColor(0, 0, 255);
}

void SeparationAlgoritm::yellowActive() {
	setRGBColor(255, 255, 0);
}

void SeparationAlgoritm::greenActive() {
	setRGBColor(0, 255, 0);
}

void SeparationAlgoritm::redActive() {
	setRGBColor(255, 0, 0);
}

void SeparationAlgoritm::buzzerActive() {

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, GPIO_PIN_SET);
}

void SeparationAlgoritm::setRGBColor(uint8_t red, uint8_t green, uint8_t blue) {
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, (red > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, (green > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, (blue > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
