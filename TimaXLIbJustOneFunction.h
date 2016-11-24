#include "TXlib.h"


template <typename T = double>
struct Vector
    {
    T x, y;
    };

typedef Vector <> Vec;     //typedef какой-то_тип пробел название_синонима_к_этому_типу Vec = Vector <>

class Image
    {

    public:
    Image (const char FilePictureName [], Vector <int> nFrames = {1, 1});
    Image ();


    void  Draw (Vec pos) const;
    void  CircleAnimation (Vec pos, int AnimationNumber, int Frame) const;
    void  DeleteTex ();
    Vector <int> nFramesReturn ();


    private:
    HDC Texture_;
    Vector <> Len_;
    Vector <int> nFrames_;
    };


//-----------------------------------------------------------------------------
Vector <int> Image::nFramesReturn ()
    {
    return nFrames_;
    }
//-----------------------------------------------------------------------------
void  Image::DeleteTex ()
    {
    txDeleteDC (Texture_);
    Texture_ = NULL;
    }
//-----------------------------------------------------------------------------
Image::Image () :
    Texture_ (NULL),
    Len_     ({0, 0}),
    nFrames_ ({0, 0})
    {
    }
//-----------------------------------------------------------------------------

Image::Image (const char FilePictureName [], Vector <int> nFrames) :
    Texture_ (txLoadImage (FilePictureName)),
    Len_     ({0, 0}),
    nFrames_ (nFrames)
    {

    if (Texture_ == NULL)
        {
        char Message [999] = "";
        sprintf (Message, "”пс, %s не загружаетс€", FilePictureName);
        txMessageBox (Message, "программа не работает", MB_ICONEXCLAMATION);;
        return;
        }

    HBITMAP hbitmap = (HBITMAP) Win32::GetCurrentObject (Texture_, OBJ_BITMAP);

    BITMAP bitmap = {};

    Win32::GetObject (hbitmap, sizeof(bitmap), &bitmap);

    Len_.x = bitmap.bmWidth;
    Len_.y = bitmap.bmHeight;

    }

//-----------------------------------------------------------------------------
void Image::Draw (Vec pos) const
    {
    txTransparentBlt (txDC (), pos.x, pos.y, Len_.x, Len_.y,
                      Texture_, 0, 0, RGB (0, 0, 0));
    }


//-----------------------------------------------------------------------------
void Image::CircleAnimation (Vec pos, int AnimationNumber, int Frame) const
    {

    txBitBlt (txDC (), pos.x - Len_.x/nFrames_.x/2, pos.y - Len_.y/nFrames_.y/2,
                      Len_.x/nFrames_.x, Len_.y/nFrames_.y, Texture_,
                      Len_.x/nFrames_.x * Frame, Len_.y/nFrames_.y * AnimationNumber);
    }
//-----------------------------------------------------------------------------
















