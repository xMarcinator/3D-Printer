#define xSpeed = 20000;
#define ySpeed = 20000;
#define zSpeed = 20000;
#define eSpeed = 20000;


const speed = 8;

Vector ToMove;
Vector MoveCounter;
Vector speeds;

void moveLinear(Vector move){
	ToMove = move;
	Vector norm;
	norm = normalizeVector(move);
	norm = VectorScale(norm,speed);
	norm = VectorDivideVector(speeds,norm)
}

void setAxisSpeed(Vector){
	setXAxisSpeed(Vector.x);
	setYAxisSpeed(Vector.y);
	setZAxisSpeed(Vector.z);
}

void setXAxisSpeed(double speed){
	OCR1A = speed;
	
	PORTH = (1<<5)&speed<0;
	
	TIMSK1 |= (1<<OCIE1A);
}

void setYAxisSpeed(double speed){

}

void setZAxisSpeed(double speed){

}

void init(){
	speeds.x = xSpeed;
	speeds.y = ySpeed;
	speeds.z = zSpeed;
	
	sei();
	// CTC
	TCCR1B |= (1 << WGM12);
	// Prescaler 1
	TCCR1B |= 1;
	// Output Compare Match A Interrupt Enable
	TIMSK1 |= (1 << OCIE1A);
	
	DDRH = 3<<5;
	/* Replace with your application code */
	PORTH = 1<<5;
}


ISR(TIMER1_COMPA_vect)
{
	PORTH ^= (1<<6);
	
	if(PORTH & (1<<6)){
		ToMove.x -= 0.00125;
		if(ToMove.x <= 0.000625){
			TIMSK1 &= ~(1<<OCIE1A); //stop interupt
		}
	}
}