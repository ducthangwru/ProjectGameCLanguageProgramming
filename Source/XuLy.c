#include "header.h"

void DiChuyen (soluongvatcan *psl)
{
    int i;

    for(i = 0; i < (*psl).n; i++)
        switch((*psl).vc[i].TrangThai)
        {
            case up:               (*psl).vc[i].td.y--;                            break;
            case down:             (*psl).vc[i].td.y++;                            break;
            case left:             (*psl).vc[i].td.x--;                            break;
            case right:            (*psl).vc[i].td.x++;                            break;
            case upleft:           (*psl).vc[i].td.x--;    (*psl).vc[i].td.y--;    break;
            case upright:          (*psl).vc[i].td.x++;    (*psl).vc[i].td.y--;    break;
            case downleft:         (*psl).vc[i].td.x--;    (*psl).vc[i].td.y++;    break;
            case downright:        (*psl).vc[i].td.x++;    (*psl).vc[i].td.y++;    break;
        }
}

void VatCanChamBien(soluongvatcan *psl)
{
    int i;
    for(i = 0; i < (*psl).n; i++)
        switch((*psl).vc[i].TrangThai)
        {
            case up:               if((*psl).vc[i].td.y <= 1)                 (*psl).vc[i].TrangThai = down;         break;
            case down:             if((*psl).vc[i].td.y >= GameHeight - 2)    (*psl).vc[i].TrangThai = up;           break;
            case left:             if((*psl).vc[i].td.x <= 1)                 (*psl).vc[i].TrangThai = right;        break;
            case right:            if((*psl).vc[i].td.x >= ConsoleWidth - 2)  (*psl).vc[i].TrangThai = left ;        break;
            case upleft:
                if((*psl).vc[i].td.y <= 1)                (*psl).vc[i].TrangThai = downleft;
                if((*psl).vc[i].td.x <= 1)                (*psl).vc[i].TrangThai = upright;
                break;
            case upright:
                if((*psl).vc[i].td.y <= 1)                (*psl).vc[i].TrangThai = downright;
                if((*psl).vc[i].td.x >= ConsoleWidth - 2) (*psl).vc[i].TrangThai = upleft;
                break;
            case downleft:
                if((*psl).vc[i].td.y >= GameHeight - 2)   (*psl).vc[i].TrangThai = upleft;
                if((*psl).vc[i].td.x <= 1)                (*psl).vc[i].TrangThai = downright;
                break;
            case downright:
                if((*psl).vc[i].td.y >= GameHeight - 2)    (*psl).vc[i].TrangThai = upright;
                if((*psl).vc[i].td.x >= ConsoleWidth - 2)  (*psl).vc[i].TrangThai = downleft;
                break;
        }
}

void XuLyLevel(soluongvatcan *psl)
{
    int i;
    for(i = 1; i < (*psl).n; i++)
        {
            if(i %4 == 3)
            {
                (*psl).vc[i - 2].td.x = (*psl).vc[i - 3].td.x + 1;
                (*psl).vc[i - 2].td.y = (*psl).vc[i - 3].td.y;
                (*psl).vc[i - 1].td.x = (*psl).vc[i - 3].td.x;
                (*psl).vc[i - 1].td.y = (*psl).vc[i - 3].td.y + 1;
                (*psl).vc[i].td.x     = (*psl).vc[i - 3].td.x + 1;
                (*psl).vc[i].td.y     = (*psl).vc[i - 3].td.y + 1;

                (*psl).vc[i - 2].TrangThai = (*psl).vc[i - 3].TrangThai;
                (*psl).vc[i - 1].TrangThai = (*psl).vc[i - 3].TrangThai;
                (*psl).vc[i].TrangThai     = (*psl).vc[i - 3].TrangThai;
            }
        }
}

void DieuKhien(NhanVat *pnv, soluongvatcan *psl)
{
    if (GetAsyncKeyState(0x57) && (*pnv).td.y > 2)              	(*pnv).td.y--;
	if (GetAsyncKeyState(0x53) && (*pnv).td.y < GameHeight - 3)	    (*pnv).td.y++;
	if (GetAsyncKeyState(0x44) && (*pnv).td.x < ConsoleWidth - 3)	(*pnv).td.x++;
	if (GetAsyncKeyState(0x41) && (*pnv).td.x > 2)	                (*pnv).td.x--;

	if (GetAsyncKeyState(0x50))
    {
        gotoXY(ConsoleWidth/2 - 5, GameHeight/2);
        printf("Pause game!");
        while(!GetAsyncKeyState(0x50));
    }

    if(GetAsyncKeyState(0X51))
        exit(0);

}

int XuLy(NhanVat *pnv, ArriTem *parritem, soluongvatcan *psl)
{
    int i, khoangcach1, khoangcach, khoangcach2, khoangcach3;
    XuLyLevel(&(*psl));
    ThoiGianNV(&(*pnv));

    //xử lý khi chọn POW
    if(GetAsyncKeyState(VK_SPACE) && (*pnv).Pow == 100)
    {
        (*pnv).Pow = 0;
        (*psl).n = 1;
    }

    if(GetAsyncKeyState(0x4D) && (*parritem).dem >= 10)
    {
        (*pnv).Mang++;
        (*parritem).dem -= 10;
    }
    //ăn tiền
    khoangcach1 = sqrt(pow(((*pnv).td.x - (*parritem).item[0].td.x), 2) + pow(((*pnv).td.y -(*parritem).item[0].td.y), 2));

    if(khoangcach1 <= 1)
    {
        Beep(5000,100);

        (*parritem).dem++;

        if((*pnv).Pow < 100)
            (*pnv).Pow += 5;

        (*parritem).item[0].td.x = 1 + rand() % (ConsoleWidth- 2);
        (*parritem).item[0].td.y = 1 + rand() % (GameHeight - 2);

        (*psl).n++;
        khoitaovatcan(*(&psl), (*psl).n - 1);
    }

    //va chạm item bất tử
    khoangcach2 = sqrt(pow(((*pnv).td.x- (*parritem).item[1].td.x), 2) + pow(((*pnv).td.y- (*parritem).item[1].td.y), 2));

    if((*psl).n <= 4)
        khoangcach2 = 2;

    if(khoangcach2 <= 1)
    {
        (*pnv).ThoiGianDoiMau = 5000;

        Beep(5000,100);
        (*parritem).item[1].td.x = 1 + rand() % (ConsoleWidth- 2);
        (*parritem).item[1].td.y = 1 + rand() % (GameHeight - 2);
    }

    //va chạm item phá vật cản
    khoangcach3 = sqrt(pow(((*pnv).td.x - (*parritem).item[2].td.x), 2) + pow(((*pnv).td.y - (*parritem).item[2].td.y), 2));
    if((*psl).n <= 4)
        khoangcach3 = 2;

    if(khoangcach3 <= 1)
    {
        (*pnv).ThoiGianPhaHuy = 6000;

        Beep(5000,100);
        (*parritem).item[2].td.x = 1 + rand() % (ConsoleWidth- 2);
        (*parritem).item[2].td.y = 1 + rand() % (GameHeight - 2);

        (*psl).n--;
    }

    //va chạm vật cản
    for(i = 0; i < (*psl).n; i++)
    {
        khoangcach = sqrt(pow(((*pnv).td.x - (*psl).vc[i].td.x), 2) + pow(((*pnv).td.y - (*psl).vc[i].td.y), 2));
        if(khoangcach <= 1)
        {
            if((*pnv).ThoiGianDoiMau > 0)
                khoangcach = 2;
            else if ((*pnv).Mang >= 1)
            {
                 Beep(700,140);
                (*pnv).Mang--;
                (*pnv).ThoiGianDoiMau = 5000;
                (*pnv).td.x = ConsoleWidth / 2;
                (*pnv).td.y = GameHeight / 2;

            }
            else
            {
                Beep(700,140);
                return 1;
            }
        }
    }

    return 0;
}

