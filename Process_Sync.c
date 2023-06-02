#include <stdint.h>

void send_Signal(int PID1Send, int PID2Recv, uint16_t message_Size, void* buff, char* message)
{
    for (int i=0;i<message_Size;++i)
    {
        buff[i] = message[i];
    }
}
void read_Signal(int PID1Send, int PID2Recv, uint16_t message_Size, void* buff, char* message)
{
        for (int i=0;i<message_Size;++i)
    {
        message[i] = buff[i];
    }
}
