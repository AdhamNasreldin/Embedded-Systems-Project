// wait for 1ms
void wait_1ms(){ 
NVIC_ST_RELOAD_R=16000;
NVIC_ST_CURRENT_R = 0;
while((NVIC_ST_CTRL_R & 0x00010000)==0); 
}

// wait for a time of delay*1ms*1000=delay*1sec

void wait(int delay){ 
	int i;
	int data=delay*1000;
	for(i=0;i<data;i++){
	wait_1ms();
}
}
