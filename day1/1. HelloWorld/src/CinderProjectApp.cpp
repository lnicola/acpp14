#include "stdafx.h"

using namespace ci;
using namespace ci::app;
using namespace ci::cairo;
using namespace std;

class CairoBasicApp : public AppBasic
{
    void draw() override
    {
        Context ctx(createWindowSurface());
        
        ctx.setSource(ColorA(1.f, 1.f, 0.98f));
        ctx.rectangle(getWindowBounds());
        ctx.fill();

        ctx.setSource(ColorA(0.3f, 0.5f, 0.9f));
        ctx.selectFontFace("Calibri", FONT_SLANT_NORMAL, FONT_WEIGHT_BOLD);
        ctx.setFontSize(90);
        ctx.setAntiAlias(ANTIALIAS_SUBPIXEL);
        
        string text = "hello, world!";
        TextExtents te = ctx.textExtents(text);
        ctx.moveTo((getWindowWidth() - te.width()) / 2 - te.xBearing(), getWindowHeight() / 2);
        ctx.showText(text);
    }
};

CINDER_APP_BASIC(CairoBasicApp, Renderer2d)
