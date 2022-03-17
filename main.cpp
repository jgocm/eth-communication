#include "stdint.h"
#include "commbst_eth.h"

using namespace std;

int main(void)
{
    CommBst_Eth communication;
    communication.setup(NetworkType::ssl);
    usleep(1000);
    while (1)
    {
        for (int i = 0; i < 6; i++)
        {
            communication.sendSpeed(i, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0);
            usleep(500);
        }
    }
}