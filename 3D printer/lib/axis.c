//
//
//
//void initAxis(){
	//
//}
//
//unsigned char pins[] = [];
//
//void initXAxis(){
	//// CTC
	//TCCR1B |= (1 << WGM12);
	//// Prescaler 1
	//TCCR1B |= 1;
	//// Output Compare Match A Interrupt Enable
	//TIMSK1 |= (1 << OCIE1A);
//}
//
//void initYAxis(){
	//// CTC
	//TCCR3B |= (1 << WGM32);
	//// Prescaler 1
	//TCCR3B |= 1;
	//// Output Compare Match A Interrupt Enable
	//TIMSK3 |= (1 << OCIE3A);
//}
//
//void initZAxis(){
	//// CTC
	//TCCR4B |= (1 << WGM42);
	//// Prescaler 1
	//TCCR4B |= 1;
	//// Output Compare Match A Interrupt Enable
	//TIMSK4 |= (1 << OCIE4A);
//}
//
//void initEAxis(){
	//// CTC
	//TCCR5B |= (1 << WGM52);
	//// Prescaler 1
	//TCCR5B |= 1;
	//// Output Compare Match A Interrupt Enable
	//TIMSK4 |= (1 << OCIE5A);
//}
//
//unsigned char StepsToGo[] = [200,100,50,20];
//
//
//
//
//
////ISR(TIMER1_COMPA_vect)
////{
	////PORTH ^= (1<<pins[0]);
	////StepsToGo[0]--;
////};
////
////ISR(TIMER3_COMPA_vect)
////{
	////PORTH ^= (1<<pins[2]);
	////StepsToGo[1]--;
////};
////ISR(TIMER4_COMPA_vect)
////{
	////PORTH ^= (1<<pins[4]);
	////StepsToGo[2]--;
////};
////ISR(TIMER5_COMPA_vect)
////{
	////PORTH ^= (1<<pins[6]);
	////StepsToGo[3]--;
////};