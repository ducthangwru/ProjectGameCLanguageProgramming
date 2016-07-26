#include "header.h"
int main()
{
    while(1)
    {
        mciSendStringA("play Sounds\\nhacnen.wav", NULL, 0, NULL);
        menu();
    }
    return 0;
}
