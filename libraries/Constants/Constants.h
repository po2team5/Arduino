//Line sensor						Notes:
	//Pins
	#define LINE_EMITTER	2		//Unused
	#define LINE_ONE		4
	#define LINE_TWO		7
	#define LINE_THREE		8
	#define LINE_FOUR		11
	#define LINE_FIVE		12
	#define LINE_SIX		13
	//Settings
	#define LINE_NUM		6
	#define LINE_TIMEOUT	2500
	#define LINE_TRESHOLD	400		//Treshold for boolean conversion
//Motors
	//Pins
	#define MOTOR_L1		5
	#define MOTOR_L2		6
	#define MOTOR_R1		9
	#define MOTOR_R2		10
	//Settings
	#define BASIS_SNELHEID	15
//PID Tuning Parameters
	#define K_PROP			1		//Increase overshoot, decrease constant error
	#define K_INT			0		//Increase overshoot, eliminate constant error
	#define K_DIFF			0		//Decrease overshoot, keep small for stability