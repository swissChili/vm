@start
	PSH 8
	POP EAX
	CAL @fact-iter
	END

@fact-iter
	PSH 123123
	RET
