#include "TimaXLIbJustOneFunction.h"


#define ever (;;)

const double DT = 1.0;

/*struct Vector
    {
    double x, y;
    };   */

/*struct Image
    {
    HDC Texture;
    Vector Len;
    };  */

struct Hero
    {
    const char *Name;

    Image Picture;

    Vec pos;
    Vec V;

    int AnimationNumber;
    int Type;
    };

struct Object
    {
    Image Picture;
    Vec pos;
    };

struct Textures
    {
    Image Steve;
    Image Cat;
    Image Bread;
    Image Butter;
    Image Fon;
    Image Map;
    };
enum {NPC, CHARACTER};
enum {LOSE, WIN, CONTINUE};
enum {NONE, WALL, BREAD, FRIDGE, DOOR};
enum {NO = false, YES = true};

void StartCom ();
void PlsStopSpammingKeysGetYourHandsAwayFromTheKeyBoard_Arrrrrrrr ();
void SuperAnimation (const Hero *object, int Active);
void CircleAnimation (const Hero *object, int Moving);
HDC SuperLoadImage (const char FilePictureName []);
bool HeroSetAnimation (Hero *object, int AnimationNumber);


void HeroMove (Hero *object, double dt);
void ObjectControl (Hero *object, int KeyUp = 'W', int KeyDown = 'S', int KeyLeft = 'A', int KeyRight = 'D', int KeyStopMove = VK_SPACE);
int ClrGreenTest (const COLORREF *Clr);

void GameProcces (const Textures *textures);

int main()
    {
    StartCom ();

    Textures textures = {Image ("steve.bmp", {4, 18})/*,          ExtraPuperSuperLoadImage ("CatTexture.bmp"),
                         ExtraPuperSuperLoadImage ("BreadTexture.bmp"),   ExtraPuperSuperLoadImage ("ButterTexture.bmp"),
                         ExtraPuperSuperLoadImage ("GameFonKitchen.bmp"), ExtraPuperSuperLoadImage ("GameMapKitchen.bmp")*/};

    GameProcces (&textures);

    textures.Map.DeleteTex();
    textures.Fon.DeleteTex();
    textures.Steve.DeleteTex();
    textures.Cat.DeleteTex();
    textures.Bread.DeleteTex();
    textures.Butter.DeleteTex();
    txEnd ();
    PlsStopSpammingKeysGetYourHandsAwayFromTheKeyBoard_Arrrrrrrr ();
    }

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

void GameProcces (const Textures *textures)
    {

    Hero Steve = {"Steve", textures->Steve, {500, 500}, {0, 0}, 0, CHARACTER };
    //Hero MrCat = { {CatTexture, {xcatlen, ycatlen} }, {100, 100}, {0, 0}, NPC};
    //Object GeorgeTheBread = { {BreadTexture, {xlen, ylen} }, {800, 800} };
    //Object ButterThe1st  =  { {ButterTexture, {xlen,ylen} }, {600, 600} }



    COLORREF PrevClr = -1;
    int t = 0;
    while (!GetAsyncKeyState (VK_ESCAPE))
        {
        //txLock ();
        //textures->Map.Draw ({0, 0});
        //COLORREF PointClr = txGetPixel (Steve.pos.x, Steve.pos.y);
        //ImageDraw (&textures->Fon, {0, 0});
        //txUnlock ();


        //ObjectControl (&Steve);
        //GameMove (&Steve, DT)
        Steve.Picture.CircleAnimation (Steve.pos, Steve.AnimationNumber, t/4%4);

        HeroSetAnimation (&Steve, t/9%18);



        //PrevClr = PointClr;
        txSleep (20);
        t++;
        }
    }


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

void HeroMove (Hero *object, double dt)
    {
    object->pos.x += object->V.x * dt;
    object->pos.y += object->V.y * dt;

    }

//-----------------------------------------------------------------------------
void ObjectControl (Hero *object, int KeyStopMove)
    {
     //= (Vector) txMousePos();



    if (GetAsyncKeyState ( KeyStopMove ))
        object->V.x = object->V.y = 0;
    }


//-----------------------------------------------------------------------------

int ClrGreenTest (const COLORREF *Clr)
    {
    int AmountOfRed  =  txExtractColor (*Clr, TX_RED);
    int AmountOfGreen = txExtractColor (*Clr, TX_GREEN);
    int AmountOfBlue  = txExtractColor (*Clr, TX_RED);

    if (AmountOfRed == 255 && AmountOfGreen == 0 && AmountOfBlue == 0)
        return WALL;

    if (AmountOfRed == 255 && AmountOfGreen == 255 && AmountOfBlue == 0)
        return DOOR;

    if (AmountOfRed == 0 && AmountOfGreen == 255 && AmountOfBlue == 0)
        return BREAD;

    if (AmountOfRed == 0 && AmountOfGreen == 0 && AmountOfBlue == 255)
        return FRIDGE;

    return NONE;
    }


//{ slaves::


/*//-----------------------------------------------------------------------------

void CircleAnimation (const Hero *object, int Moving)
    {

    txBitBlt (txDC (), object->pos.x - object->Picture.Len.x/4/2, object->pos.y - object->Picture.Len.y/18/2,
                      object->Picture.Len.x/4, object->Picture.Len.y/18, object->Picture.Texture,
                      object->Picture.Len.x/4 * Moving, object->Picture.Len.y/18 * object->AnimationNumber);

    $ (object->AnimationNumber); $n;
    //$ (object->pos.y - object->Picture.Len.y/18/2); $n;
    //$ (object->Picture.Len.x/4);   $n;
    //$ (object->Picture.Len.y/18); $n;
    //$ (object->Picture.Len.y/18 * object->AnimationNumber);  $n;
    //getch ();

    }
            */
//-----------------------------------------------------------------------------

/*void SuperAnimation (const Hero *object, int Active)
    {
    int ActiveMirror = 0;
    if (object->V.x >= 0) ActiveMirror = 1; else ActiveMirror = 0;

    txAlphaBlend (txDC (), object->pos.x - object->Picture.Len.x/2, object->pos.y - object->Picture.Len.y/2,
                      object->Picture.Len.x, object->Picture.Len.y, object->Picture.Texture,
                      object->Picture.Len.x * Active, object->Picture.Len.y *(object->AnimationNumber * 2 + ActiveMirror));
    }
         */
//-----------------------------------------------------------------------------
bool HeroSetAnimation (Hero *object, int AnimationNumber)
    {
    if (AnimationNumber >= object->Picture.nFramesReturn().y || AnimationNumber < 0)
        {
        printf ("ERROR: wrong AnimationNumber\n"
                "       %s's AnimationNumber = %d\n"
                "       trying to set AnimationNumber = %d\n\n", object->Name, object->Picture.nFramesReturn().y, AnimationNumber);
        return NO;
        }

    object->AnimationNumber = AnimationNumber;

    return YES;
    }
//-----------------------------------------------------------------------------


void StartCom ()
    {
    txCreateWindow (1800, 1000);

    txSetFillColor     (RGB (255, 255, 255));
    txClear ();
    txSetColor         (RGB(0, 0, 0));

    txBegin ();
    txDisableAutoPause();
    }

//-----------------------------------------------------------------------------

void PlsStopSpammingKeysGetYourHandsAwayFromTheKeyBoard_Arrrrrrrr ()
    {
    while (GetAsyncKeyState ('A') || GetAsyncKeyState ('S') ||
           GetAsyncKeyState ('W') || GetAsyncKeyState ('D'))
        Sleep (0);
    }

//}
//-----------------------------------------------------------------------------


