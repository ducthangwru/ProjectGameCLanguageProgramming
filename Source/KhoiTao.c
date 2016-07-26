#include "header.h"
extern MotO buffer[GameHeight][ConsoleWidth];

void GanO (int dong, int cot, char kitu, int mau)
{
    buffer[dong][cot].kitu = kitu;
    buffer[dong][cot].mau = mau;
}

void khoitaovatcan(soluongvatcan *psl, int i)
{
    int z = 1 + rand()%8;
    (*psl).vc[i].td.x = 2 + rand()%(ConsoleWidth - 4);
    (*psl).vc[i].td.y = 2 + rand()%(GameHeight - 4);
    (*psl).vc[i].TrangThai = z;
}

void KhoiTao (NhanVat *pnv, soluongvatcan *psl, ArriTem *parritem)
{
    int i;
    //khởi tạo tiền
    (*parritem).item[0].td.x = 1 + rand() % (ConsoleWidth - 2);
    (*parritem).item[0].td.y = 1 + rand() % (GameHeight - 2);

    //khởi tạo item bất tử
    (*pnv).ThoiGianDoiMau = 0;
    (*parritem).item[1].td.x = 1 + rand() % (ConsoleWidth- 2);
    (*parritem).item[1].td.y = 1 + rand() % (GameHeight - 2);

    //khởi tạo item phá 1 vật cản
    (*pnv).ThoiGianPhaHuy = 0;
    (*parritem).item[2].td.x = 1 + rand() % (ConsoleWidth- 2);
    (*parritem).item[2].td.y = 1 + rand() % (GameHeight - 2);

    //khởi tạo điểm, level, pow, Mang
    (*pnv).Mang = 3;
    (*pnv).Pow = 0;
    (*pnv).Diem = 0;
    (*psl).n = 0;
    (*parritem).dem = 0;
    //khởi tạo nhân vật

    #define pHD (*pnv).hd.a
    (*pnv).td.x = ConsoleWidth/2;
    (*pnv).td.y = GameHeight/2;

    pHD[0][0] = pHD[0][2] = '-';
    pHD[0][1] = '.';
    pHD[1][0] = pHD[1][2] = pHD[2][1] = ' ';
    pHD [2][0] = pHD[2][2] = '^';
    pHD[1][1] = '@';

    //khởi tạo vật cản
    for(i = 0; i < (*psl).n; i++)
        khoitaovatcan(&psl, i);

}

void ThoiGianNV(NhanVat *pnv)
{
    //thời gian đổi màu
    if((*pnv).ThoiGianDoiMau == 0)
       (*pnv).Mau = 11;
    else if((*pnv).ThoiGianDoiMau > 0)
    {
        (*pnv).Mau = 8 + rand() % 8;
        (*pnv).ThoiGianDoiMau -= 100;
    }

    //thời gian phá hủy
    if((*pnv).ThoiGianPhaHuy > 0)
       (*pnv).ThoiGianPhaHuy -= 100;
}

