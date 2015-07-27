#include <stdio.h>
#include "tlvm.h"


int main(int argc, char** argv)
{
    tlvmContext* ctx = 0;
    tlvmInitContext(&ctx, TLVM_CPU_8080);

    printf( "Init: %s\n", tlvmError() );
    
    tlvmByte memBuffer[0xFFFF];

    tlvmSetClockspeed(ctx, TLVM_MHZ(2,0));

    printf( "Clock: %s\n", tlvmError() );

    FILE* fp = fopen("basic8k.bin", "r");
    
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    fread(memBuffer, 1, size, fp);

    fclose(fp);

    tlvmSetMemory(ctx, memBuffer, 0, 0xFFFF, TLVM_FLAG_READ | TLVM_FLAG_WRITE);

    printf( "Memory: %s\n", tlvmError() );

    tlvmRun(ctx);

    printf( "Run: %s\n", tlvmError() );

    tlvmTerminateContext(&ctx);

    printf( "Terminate: %s\n", tlvmError() );
    return 0;
}
