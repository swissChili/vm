@start
	; Arg
	PSH 8
	POP EAX
	CAL @fact-iter
	END

@fact-iter
	; Accumulator
	PSH 1
	POP EBX
	; Iters
	PSH 1
	POP ECX

	JMP @fact-iter:condition

@fact-iter:iterate
	LDR EBX
	LDR ECX
	MLT
	POP EBX

@fact-iter:condition
	LDR ECX
	LDR EAX
	CMP
	JEQ @fact-iter:done

	LDR ECX
	INC
	POP ECX
	JMP @fact-iter:iterate

@fact-iter:done
	LDR ECX
	RET
