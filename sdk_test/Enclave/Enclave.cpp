#include <stdarg.h>
#include <stdio.h>

#include "Enclave.h"
#include "Enclave_t.h"

#include "string.h"

#include "trts_util.h"
#include "trts_emodpr.h"

/* re-define printf inside enclave */
void printf(const char *fmt, ...)
{
	char buf[BUFSIZ] = {'\0'};
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, BUFSIZ, fmt, ap);
	va_end(ap);
	Ocall_PrintString(buf);
}

void Ecall_SomeDataProcessing(char *buf, size_t len)
{
	const char *secret = "I am a secret inside enclave!";
	if (len > strlen(secret))
	{
		memcpy(buf, secret, strlen(secret) + 1);
	}

	//test
	printf("enclave size: 0x%x\n", get_enclave_size());
	printf("enclave end: 0x%x\n", get_enclave_end());

	printf("heap size: 0x%x\n", get_heap_size());
	printf("heap min size: 0x%x\n", get_heap_min_size());

	printf("rsrv size: 0x%x\n", get_rsrv_size());
	printf("rsrv end: 0x%x\n", get_rsrv_end());
	printf("rsrv min size: 0x%x\n", get_rsrv_min_size());
	
	if (is_stack_addr(buf, len))
		printf("buf is in stack!");;
}
