//---------------------------------------------------------------------------


#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TMeasureWindow.h"
//運用若參考指標去儲存WindowListener
#define WEAK_PTR

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
__fastcall TMeasureWindow::TMeasureWindow(TComponent * Owner)
:TForm(Owner)
{

    DoubleBuffered = true;
    this->Button1->OnClick = Button1Click;
    //pattern = Indepedent;
    pattern = Normal;

}

//---------------------------------------------------------------------------
void __fastcall TMeasureWindow::FormKeyPress(TObject * Sender, char &Key)
{
    switch (Key) {
    case 27:			//esc
	this->Close();
	break;
    case 32:			//space
	this->Button1->Visible = true;
    }
}

//---------------------------------------------------------------------------


void TMeasureWindow::setRGB(int r, int g, int b)
{
    //this->Repaint();
    this->Update();
    //Application->ProcessMessages();

    if (true == tconinput) {
	tconcontrol->setTestRGB(r, g, b);
    } else {
	int color = (b << 16) + (g << 8) + r;
	switch (pattern) {
	case HStripe:{
		TCanvas *canvas = this->Canvas;
		int w = this->Width;
		int h = this->Height;
		for (int y = 0; y < h; y++) {
		    canvas->PenPos = TPoint(0, y);
		    if (y % 2 == 0) {
			canvas->Pen->Color = (TColor) color;
		    } else {
			canvas->Pen->Color = clBlack;
		    }
		    canvas->LineTo(w, y);
		}

	    }
	    break;
	case HSD:{
		TCanvas *canvas = this->Canvas;

		int w = this->Width;
		int h = this->Height;
		int w2 = w / 2;
		int gcolor = g << 8;
		int color1 = (b << 16) + r;

		for (int x = 0; x < w2; x++) {
		    int start = x * 2;
		    canvas->Pen->Color = color1;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);

		    start += 1;
		    canvas->Pen->Color = gcolor;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);
		}

		canvas->Pen->Color = clBlack;
		for (int y = 1; y < h; y += 2) {
		    canvas->PenPos = TPoint(0, y);
		    canvas->LineTo(w, y);
		}
	    }
	    break;
	case Indepedent:{
		this->Color = clBlack;
		TCanvas *canvas = this->Canvas;
		//TCanvas *c = new TCanvas();

		int w = this->Width;
		int h = this->Height;
		int w4 = w / 4;
		int rcolor = r;
		int gcolor = g << 8;
		int bcolor = (b << 16);

		for (int x = 0; x < w4; x++) {
		    int start = x * 4;
		    canvas->Pen->Color = rcolor;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);

		    start += 1;
		    canvas->Pen->Color = gcolor;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);

		    start += 1;
		    canvas->Pen->Color = bcolor;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);

		    /*start += 1;
		       canvas->Pen->Color = clBlack;
		       canvas->PenPos = TPoint(start, 0);
		       canvas->LineTo(start, h); */
		}

		canvas->Pen->Color = clBlack;
		for (int y = 1; y < h; y += 2) {
		    canvas->PenPos = TPoint(0, y);
		    canvas->LineTo(w, y);
		}
	    }
	    break;
	case Normal:
	    this->Color = (TColor) color;
	    break;
	case FlickrPixel:
	    break;
	case FlickrSubPixel:
	    break;
	}
    }
}

void TMeasureWindow::setRGB(bptr < Dep::RGBColor > rgb)
{
    double_array values(new double[3]);
    /*if (true == tconinput) {
       //若是tcon input, 要轉到該lut強度下
       rgb->getValues(values, tconcontrol->getLUTBit());
       } else { */
    rgb->getValues(values);
    //}
    int r = static_cast < int >(values[0]);
    int g = static_cast < int >(values[1]);
    int b = static_cast < int >(values[2]);
    setRGB(r, g, b);
}

//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::Button1Click(TObject * Sender)
{
    pattern = Indepedent;
    setRGB(255, 255, 255);
    /*int color = (255 << 16) + (255 << 8) + 255;
       this->Canvas->Pen->Color = color;
       this->Canvas->LineTo(100, 100); */
}

//---------------------------------------------------------------------------
void TMeasureWindow::setTCONControl(bptr < i2c::TCONControl > tconcontrol)
{
    this->tconcontrol = tconcontrol;
    tconinput = true;
};

//---------------------------------------------------------------------------
void TMeasureWindow::setTCONControlOff()
{
    tconinput = false;
};

//---------------------------------------------------------------------------
void TMeasureWindow::setVisible(bool visible)
{
    this->Visible = visible;
    if (visible) {
	this->BringToFront();
    }
    if (tconinput) {
	tconcontrol->setGammaTest(visible);
    }
};

//---------------------------------------------------------------------------
void TMeasureWindow::
addWindowListener(bptr < cms::util::WindowListener > listener)
{
#ifndef WEAK_PTR
    listenerVector.push_back(listener);
#else
    bwptr < cms::util::WindowListener > wptr(listener);
    listenerVector2.push_back(wptr);
#endif
}

//---------------------------------------------------------------------------


void __fastcall TMeasureWindow::
FormClose(TObject * Sender, TCloseAction & Action)
{
#ifndef WEAK_PTR
    foreach(bptr < cms::util::WindowListener > listener, listenerVector) {
	if (null != listener) {
	    listener->windowClosing();
	}
    }
#else
    foreach(bwptr < cms::util::WindowListener > listener, listenerVector2) {
	bptr < cms::util::WindowListener > l = listener.lock();
	if (null != l) {
	    l->windowClosing();
	}
    }
#endif
}

//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::FormShow(TObject * Sender)
{
    Image1->Width = this->Width;
    Image1->Height = this->Height;
}

//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::Button2Click(TObject * Sender)
{
    Image1->Picture->LoadFromFile("sponge.jpg");
}

//----\-----------------------------------------------------------------------
void TMeasureWindow::setImageFilename(const std::string & filename)
{
    Image1->Picture->LoadFromFile(filename.c_str());
    Image1->Visible = true;
}

void TMeasureWindow::setImageOff()
{
    Image1->Visible = false;
}

void TMeasureWindow::setPattern(Pattern pattern)
{
    this->pattern = pattern;
};

