

int __svc(0x00) svc_service_add(int a, int b);
int __svc(0x01) svc_service_sub(int a, int b);
int __svc(0x02) svc_service_mul(int a, int b);
int __svc(0x03) svc_service_div(int a, int b);

void SVC_Handler_C(unsigned int * svc_args);

int x, y, z;

int main(void) {
	
	x = 2;
	y = 4;
	z = svc_service_add(x, y);

	x = 9;
	y = 4;
	z = svc_service_sub(x, y);

	x = 2;
	y = 3;
	z = svc_service_mul(x, y);

	x = 8;
	y = 4;
	z = svc_service_div(x, y);

	return 0;
}


__asm  SVC_Handler(void)
{
	TST LR, #4 //0b0100
	ITE EQ
	MRSEQ R0, MSP
	MRSNE R0, PSP
	B       __cpp(SVC_Handler_C)
}


void SVC_Handler_C(unsigned int * svc_args) {
	unsigned int svc_number;
	svc_number = ((char *)svc_args[6])[-2];
	switch(svc_number) {
		case 0x00:
			svc_args[0] = svc_args[0] + svc_args[1];
		break;

		case 0x01:
			svc_args[0] = svc_args[0] - svc_args[1];
		break;

		case 0x02:
			svc_args[0] = svc_args[0] * svc_args[1];
		break;

		case 0x03:
			svc_args[0] = svc_args[0] / svc_args[1];
		break;

		default:
			break;
	}
}


