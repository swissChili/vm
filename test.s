@start
	PSH	123
	POP	EAX
	JMP	@end
	PSH	234
	POP	EAX
@end
	LDR	EAX
