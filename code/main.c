#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xil_io.h"
#include "xparameters.h"
#include "GPIO_irq.h"
#include "xscugic.h"
#include "xil_exception.h"

XScuGic INTC;	// a XScuGic struct named INTC

static void IntrHandler(void *CallBackRef)
{
	// Prevent interrupted when handling
	// Set Enable flag is 0 to clear irq
	Xil_Out32(XPAR_GPIO_IRQ_0_S00_AXI_BASEADDR, 0);
	// Set Enable flag is 1 to enable trigger
	Xil_Out32(XPAR_GPIO_IRQ_0_S00_AXI_BASEADDR, 1);
	printf("interrupt occured\n");
}

int main()
{
    int status;
	
	XScuGic_Config *INTCConfig;
	// Look up scugic's configuration from memory
	// XPAR_SCUGIC_0_DEVICE_ID in xparameters_ps.h
	INTCConfig = XScuGic_LookupConfig(XPAR_SCUGIC_0_DEVICE_ID);
	//Initialize INTC which is XScuGic
	status = XScuGic_CfgInitialize(&INTC, INTCConfig, INTCConfig->CpuBaseAddress);
	// Check successfully initialize or not
	if(status != XST_SUCCESS) return XST_FAILURE;
	// Connect Interrupt Controller, Interrupt ID, Handler and Input Parameter of handler
	// XPAR_FABRIC_GPIO_IRQ_0_IRQ_INTR in xparameters_ps.h
	status = XScuGic_Connect(&INTC, XPAR_FABRIC_GPIO_IRQ_0_IRQ_INTR, (Xil_ExceptionHandler)IntrHandler, (void*)0);
	// Check successfully initialize or not
	if(status != XST_SUCCESS) return XST_FAILURE;
	// Interrupt Controller enable the GPIO interrupt which ID is XPAR_FABRIC_GPIO_IRQ_0_IRQ_INTR
	// XPAR_FABRIC_GPIO_IRQ_0_IRQ_INTR in xparameters_ps.h
	XScuGic_Enable(&INTC, XPAR_FABRIC_GPIO_IRQ_0_IRQ_INTR);

	// Exception initialize
	Xil_ExceptionInit();
	// Register handler if exception ID "XIL_EXCEPTION_ID_INT" occur,
	// handle by XScuGic_InterruptHandler and its input parameter is &INTC
	// XIL_EXCEPTION_ID_INT in xil_exception.h
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, &INTC);
	// Enable xil_exception
	Xil_ExceptionEnable();

	int x;
	while(1)
	{
		// Convenience to change the Enable flag
		printf("x=");
		scanf("%d", &x);
		printf("%d\n",x);
		Xil_Out32(XPAR_GPIO_IRQ_0_S00_AXI_BASEADDR, x&0x01);
	}
    return 0;
}
