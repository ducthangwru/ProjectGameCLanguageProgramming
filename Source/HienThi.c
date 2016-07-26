#include "header.h"

MotO buffer[GameHeight][ConsoleWidth];

void xuatbuffer()
{
    gotoXY(0,0);
    int i, j;
    for(i = 0; i < GameHeight; i++)
    {
        for(j = 0; j < ConsoleWidth; j++)
        {
            TextColor(buffer[i][j].mau);
            putchar(buffer[i][j].kitu);

            buffer[i][j].kitu = ' ';
            TextColor(0);
        }
        gotoXY(0, i+1);
    }
}

void HienThi (NhanVat nv, soluongvatcan sl, ArriTem arritem)
{
     int i, j, x, y;
    //hiển thị biên
    for(i = 0; i < GameHeight; i++)
    {
        for(j = 0; j< ConsoleWidth; j++)
            if(i == 0 || j == 0 || i == GameHeight - 1 || j == ConsoleWidth - 1)
                GanO(i, j, 219, 7);
    }

    //hiển thị nhân vật
    ThoiGianNV(&nv);
	for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++)
		{
			x = j + nv.td.x;
			y = i + nv.td.y;
			GanO (y, x, nv.hd.a[i+1][j+1], nv.Mau);
		}

    //hiển thị tiền
	GanO(arritem.item[0].td.y, arritem.item[0].td.x,'$',8 + rand()%8);

    //hiển thị item bất tử
    if(sl.n > 4 && nv.ThoiGianDoiMau == 0)
        GanO(arritem.item[1].td.y, arritem.item[1].td.x, 219 ,8 + rand()%8);

    //hiển thị item phá vật cản
    if(sl.n > 4 && nv.ThoiGianPhaHuy == 0)
        GanO(arritem.item[2].td.y, arritem.item[2].td.x, 219 , 10);

    //hiển thị vật cản
	for(i = 0;i < sl.n; i++)
		GanO (sl.vc[i].td.y, sl.vc[i].td.x, 219, 12);

    //hiển thị buffer
    xuatbuffer();

    TextColor(14);

    //hiển thị trạng thái game
    TextColor(14);
    gotoXY(ConsoleWidth/2 - 10, GameHeight);
    printf("Level: %2d",sl.n);

    nv.Diem = arritem.dem * 5;
    gotoXY(ConsoleWidth/2 - 25, GameHeight);
    printf("Score: %3d", nv.Diem);

    gotoXY(ConsoleWidth/2 + 3, GameHeight);
    printf("Pow: %3d",nv.Pow);

    gotoXY(ConsoleWidth - 20, GameHeight);
    printf("Life: x%d", nv.Mang);

    gotoXY(ConsoleWidth/2 - 20, GameHeight + 2);
    printf("Remaining time is %4dms", nv.ThoiGianDoiMau);

    gotoXY(ConsoleWidth - 28, GameHeight + 2);
    printf("Press M buy item \"life\"!!!");

    if(nv.Pow == 100)
    {
        TextColor(8 + rand() % 8);
        gotoXY(ConsoleWidth/2 - 14, GameHeight + 4);
        printf("Press SPACE!!!!!");
    }
    else
    {
        TextColor(14);
        gotoXY(ConsoleWidth/2 - 14, GameHeight + 4);
        printf("Press SPACE!!!!!");
    }
    //hiển thị hướng dẫn

    gotoXY(0, GameHeight + 1);
    TextColor(13);

    printf("W: Move Up \n");
    printf("S: Move Down \n");
    printf("A: Turn Left \n");
    printf("D: Turn Right \n");
    printf("P: Pause Game \n");
    printf("Q: Quit Menu");

    gotoXY(ConsoleWidth - 29, ConsoleHeight - 2);
        printf("Created by Nguyen Duc Thang \n");

    gotoXY(ConsoleWidth - 29, ConsoleHeight - 1);
        printf("K57TH3 - CNTT - DH Thuy Loi");

    //hiển thị điểm cao
    FILE *f1 = fopen("score.txt","rt");
    fscanf(f1,"%d", &x);
    TextColor(8 + rand() % 8);
    gotoXY(ConsoleWidth/2 - 14, GameHeight + 5);
    printf("High Score: %d", x);
    fclose(f1);

    TextColor(14);
    gotoXY(ConsoleWidth/2 - 14, GameHeight + 6);
    printf("Dia chi Level: %d", &sl.n);

}

