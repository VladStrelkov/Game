#include "Books/TXNetwork.h"
#include "Books/TXLib.h"

const double Fast          = 0.4;
const int    TimeGameFast  = 10;

const int    Stop          = 0,
             Continue      = 1;

const int    WinX          = 1350, WinY = 750;
const int    HeroOfWindow  = 30;
const int    TimeFact      = 4;

const char   Level1Pered[] = "Image/Òðîïèíêà/òðîïèíêà_ïåðåä.bmp";
const char   Level1Ser[]   = "Image/Òðîïèíêà/òðîïèíêà_ñåðåäèíà.bmp";
const char   Level1Zad[]   = "Image/Òðîïèíêà/òðîïèíêà_çàä.bmp";

const char   Level2Pered[] = "Image/Ýâåðåñò/Ýâåðåñò_ïåðåä.bmp";
const char   Level2Ser[]   = "Image/Ýâåðåñò/Ýâåðåñò_ñåðåäèíà.bmp";
const char   Level2Zad[]   = "Image/Ýâåðåñò/Ýâåðåñò_çàä.bmp";

const char   Player1[]     = "Image/Ãåðîè/êîøêà.bmp";
const char   Player2[]     = "Image/Ãåðîè/åðê3.bmp";

const char   LovePlayer[]  = "Image/Ãåðîè/êîëáàñà.bmp";
const char   Scoreboard[]  = "Image/Ãåðîè/òàáëî.bmp";

#include "Books/LEONLib.h"

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Capture_the_Sausage           ();

void Image                         (Hero* heroCat, Hero* heroDog2, Hero* heroDog1, Hero* heroSausage, int xmap, int ymap,
                                    int t, HDC FonZad, HDC FonSer, HDC Dog, HDC LoveCat, HDC Cat, HDC FonPered, HDC TimeGame);

void DrawTime                      (int timeStart);

void Downloud                      (HDC *FonPered, HDC *FonSer, HDC *FonZad, HDC *Dog, HDC *Cat, HDC *LoveCat, HDC *TimeGame);

void Receive (void*);

volatile Network Dog2_network = {-1, -1};

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

int main()
    {
    txCreateWindow                 (WinX, WinY);
    txBegin                        ();

    Capture_the_Sausage            ();

    return 0;
    }

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Capture_the_Sausage()
    {


    Hero    Dog1         = {900,  300, 3, 3, 150, 150};
    Hero    Cat          = {150,  300, 0, 0, 100, 99};
    Hero    Sausage      = {1250, 100, 0, 0, 90,  50};

    int xmap     = 0, ymap   = 0;
    int t        = 0;

    HDC FonPered = NULL, FonSer = NULL, FonZad = NULL, Dog = NULL, CatImage = NULL, LoveCat = NULL, TimeGame = NULL;

    Downloud                       (&FonPered, &FonSer, &FonZad, &Dog, &CatImage, &LoveCat, &TimeGame);

    _beginthread (Receive, 0, NULL);

    txSelectFont                   ("Arial", 35);

    int timeStart = GetTickCount();


    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        txSetFillColor             (TX_BLACK);


        if (!GetAsyncKeyState      (VK_SHIFT))  txClear ();

        Hero Dog2 = { Dog2_network.x, Dog2_network.y, 0, 0, Dog1.SizeImageX, Dog1.SizeImageY };

        Image                      (&Cat, &Dog1, &Dog2, &Sausage, xmap, ymap,
                                    t, FonZad, FonSer, Dog, LoveCat, CatImage, FonPered, TimeGame);

        Physics                    (&Dog1);
        Physics                    (&Cat);

        Button                     (VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, VK_SPACE, 'Q', &Cat, &Sausage);

        LeftRightWindow            (VK_NUMPAD4, VK_NUMPAD6, &xmap, &ymap);

        int StopGame = Touching    (&Sausage,  &Dog1,    "Õîòèòå ïåðåéòè íà 2 level???",
                                    &FonPered, &FonSer,  &FonZad, Level2Pered, Level2Ser, Level2Zad);
        if (StopGame == Stop)
            {
            break;
            }

       /*
        int StopGame = Touching    (&Sausage,  &Cat,    "Õîòèòå ïåðåéòè íà 2 level???",
                                    &FonPered, &FonSer,  &FonZad, Level2Pered, Level2Ser, Level2Zad);
        if (StopGame == Stop)
            {
            break;
            }
        StopGame     = Touching    (&Sausage,  &Cat,    "Âû âûèãðàëè !!!!!!!!!!!!!!!!",
                                    &FonPered, &FonSer,  &FonZad, Level1Pered, Level1Ser, Level1Zad);
        if (StopGame == Stop)
            {
            break;
            }
        StopGame     = Touching    (&Cat, &Dog1, "Õîòèòå çàíîâî ñûãðàòü???",
                                    &FonPered,  &FonSer, &FonZad, Level1Pered, Level1Ser, Level1Zad);
        if (StopGame == Stop)
            {
            break;
            }
         */

        Logic                      (&Dog1, &Cat);

        DrawTime                   (timeStart);

       /*
        StopGame    = UpdateTime   (&Cat, &timeStart, "Âû ÏÐÎÈÃÐÀËÈ, âû ËÓÇÅÐ!!! ",
                                    &FonPered,  &FonSer, &FonZad, Level1Pered, Level1Ser, Level1Zad);
        if (StopGame == Stop)
            {
            break;
            }
         */

        while (GetAsyncKeyState (VK_SHIFT)) Sleep (100);

        txSleep (10);
        t++;
        }

    }

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Receive (void*)
    {
    TX_SOCKET Capture_the_Sausage_server = txCreateSocket (TX_CLIENT, TX_BROADCAST, TX_STD_PORT, TX_BLOCK, false);

    for (;;)
        {
        txRecvFrom (Capture_the_Sausage_server, (void*) &Dog2_network, sizeof (Dog2_network));

        Sleep (0);
        }
     }

//===================================================================================================================================================================================================================================================================================================================================================================================================================================================

void Downloud      (HDC *FonPered, HDC *FonSer, HDC *FonZad, HDC *Dog, HDC *Cat, HDC *LoveCat, HDC *TimeGame)
    {

    *FonPered = txLoadImage (Level1Pered);
    *FonSer   = txLoadImage (Level1Ser);
    *FonZad   = txLoadImage (Level1Zad);
    *Dog      = txLoadImage (Player2);
    *Cat      = txLoadImage (Player1);
    *LoveCat  = txLoadImage (LovePlayer);
    *TimeGame = txLoadImage (Scoreboard);

    }

void Image         (Hero* heroCat, Hero* heroDog2, Hero* heroDog1, Hero* heroSausage, int xmap, int ymap,
                    int t, HDC FonZad, HDC FonSer, HDC Dog, HDC LoveCat, HDC Cat, HDC FonPered, HDC TimeGame)
    {

    txBitBlt         (xmap - ROUND ((*heroCat).x/HeroOfWindow) + 50,   ymap - ROUND ((*heroCat).x/HeroOfWindow),                FonZad);
    txTransparentBlt (xmap, ymap, FonSer);

    txTransparentBlt (txDC(), (*heroDog1).x,    (*heroDog1).y,    (*heroDog1).SizeImageX,    (*heroDog1).SizeImageY,    Dog,    (t/TimeFact)%2 * (*heroDog1).SizeImageX);
    txTransparentBlt (txDC(), (*heroSausage).x, (*heroSausage).y, (*heroSausage).SizeImageX, (*heroSausage).SizeImageY, LoveCat, (t/TimeFact)%2 * (*heroSausage).SizeImageX);
    txTransparentBlt (txDC(), (*heroCat).x,     (*heroCat).y,     (*heroCat).SizeImageX,     (*heroCat).SizeImageY,     Cat,     (t/TimeFact)%2 * (*heroCat).SizeImageX);
    txTransparentBlt (txDC(), (*heroDog2).x,    (*heroDog2).y,    (*heroDog2).SizeImageX,    (*heroDog2).SizeImageY,    Dog,     (t/TimeFact)%2 * (*heroDog2 ).SizeImageX);

    txTransparentBlt (xmap + ROUND ((*heroCat).x/HeroOfWindow) - 50,   ymap + ROUND ((*heroCat).y/HeroOfWindow) - 50, FonPered);

    txTransparentBlt (txDC(), 0, 0, 100, 70, TimeGame);

    }

//==================================================================================================================================================================================================================================================================================================================================================================================================================================================

void DrawTime      (int timeStart)
    {
    int  time           = GetTickCount();

    char Temporary [50] = "";

    sprintf    (Temporary, "%d", (time-timeStart)/1000);
    txSetColor (TX_YELLOW);
    txDrawText (0, 25, 100, 70, Temporary);
}
