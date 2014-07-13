#include "stdafx.h"

using namespace ci;
using namespace ci::app;
using namespace ci::cairo;
using namespace ci::gl;
using namespace std;

class CairoBasicApp : public AppBasic
{
    unique_ptr<SurfaceImage> surface_image_;
  
    void paint(Context ctx)
    {
        GradientRadial radialGrad(getWindowCenter(), 0.0f, getWindowCenter(), getWindowWidth());
        radialGrad.addColorStop(0, Color(1, 1, 1));
        radialGrad.addColorStop(1, Color(0.6f, 0.6f, 0.6f));

        ctx.setSource(radialGrad);	
        ctx.paint();
        
        ctx.setSource(ColorA(0.3f, 0.5f, 0.9f));
        ctx.selectFontFace("Calibri", FONT_SLANT_NORMAL, FONT_WEIGHT_BOLD);
        ctx.setFontSize(90);
        
        string text = "hello, world!";
        TextExtents te = ctx.textExtents(text);
        ctx.moveTo((getWindowWidth() - te.width()) / 2 - te.xBearing(), getWindowHeight() / 2);
        ctx.showText(text);
    }

    void draw() override
    {
        gl::draw(Texture(surface_image_->getSurface()));
    }

    void keyDown(KeyEvent event) override
    {
        if (event.isAltDown() && event.getCode() == KeyEvent::KEY_F4)
            quit();
    }

    void resize() override
    {
        surface_image_.reset(new SurfaceImage(getWindowWidth(), getWindowHeight()));

        paint(*surface_image_);
    }
};

CINDER_APP_BASIC(CairoBasicApp, RendererGl)
