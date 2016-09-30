#include <stdio.h>
#include "tlvm.h"

void io_callback(tlvmContext* context, tlvmByte port)
{
    tlvmByte val = 0;
    tlvmGetPort(context, port, &val);
    if(port == 0x02)
    {
        if(val == '$')
        {
            printf("\n");
        }
        else
        {
            printf("%c", val);
        }
        fflush(stdout);
    }
}

void load_file(const char* filename, tlvmByte* buffer)
{

    FILE* fp = fopen(filename, "r");
    
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    fread(buffer, 1, size, fp);

    fclose(fp);    
}

int main(int argc, char** argv)
{
    tlvmContext* ctx = 0;
    tlvmInitContext(&ctx, TLVM_CPU_8080);

    printf( "Init: %s\n", tlvmError() );
    
    tlvmByte memBuffer[0xFFFF];

    //tlvmSetClockspeed(ctx, TLVM_MHZ(2,0));

    printf( "Clock: %s\n", tlvmError() );

    load_file("bdos.bin",    &memBuffer[0x0000]);
    load_file("cpudiag.bin", &memBuffer[0x0100]);
              
    tlvmSetMemory(ctx, memBuffer, 0, 0xFFFF, TLVM_FLAG_READ | TLVM_FLAG_WRITE);

    printf( "Memory: %s\n", tlvmError() );

    tlvmSetIOCallback(ctx, io_callback);

    printf( "IO: %s\n", tlvmError() );
    
    tlvmRun(ctx);

    printf( "Run: %s\n", tlvmError() );

    tlvmTerminateContext(&ctx);

    printf( "Terminate: %s\n", tlvmError() );
    return 0;
}
