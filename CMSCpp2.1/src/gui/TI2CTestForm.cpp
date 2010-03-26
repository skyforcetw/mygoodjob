//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

#include "TI2CTestForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TI2CTestForm *I2CTestForm;
//---------------------------------------------------------------------------
__fastcall TI2CTestForm::TI2CTestForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::Button1Click(TObject * Sender)
{
    using namespace cms::i2c;
    bptr < i2cControl > i2c1st;
    bptr < i2cControl > i2c2nd;
    unsigned char first, second;
    bool dual = false;

    if (this->RadioButton_Single->Checked) {
	first = StrToInt("0x" + this->Edit_Single->Text);
    } else {
	first = StrToInt("0x" + this->Edit_Master->Text);
	second = StrToInt("0x" + this->Edit_Slave->Text);
	dual = true;
    }

    if (this->RadioButton_USB->Checked) {
	i2c1st = i2cControl::getUSBInstance(first, _3_3V, _400KHz);
	if (dual) {
	    i2c2nd = i2cControl::getUSBInstance(second, _3_3V, _400KHz);
	};
    } else {
	i2c1st = i2cControl::getLPTInstance(first);
	if (dual) {
	    i2c2nd = i2cControl::getLPTInstance(second);
	};
    };
    bool connect = i2c1st->connect();
    if (dual) {
	i2c2nd->connect();
    }
    if (connect) {
	this->CheckBox_Connecting->Checked = connect;
	this->Edit_GammaTestAddress->Enabled = false;
	this->Edit_GammaTestBit->Enabled = false;
	this->Edit_TestRGBAdress->Enabled = false;
	this->CheckBox_IndepRGB->Enabled = false;


	int gammaTestAddress =
	    StrToInt("0x" + this->Edit_GammaTestAddress->Text);
	int gammaTestBit = StrToInt(this->Edit_GammaTestBit->Text);
	int testRGBAddress =
	    StrToInt("0x" + this->Edit_TestRGBAdress->Text);
	parameter.reset(new
			TCONParameter(gammaTestAddress, gammaTestBit,
				      testRGBAddress, true));
	control.reset(new TCONControl(parameter, i2c));
    }
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::FormCreate(TObject * Sender)
{
    //RW_Func rw;
    i2c = cms::i2c::i2cControl::getLPTInstance(0);
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Edit_RChange(TObject * Sender)
{
    using namespace Dep;
/* TODO : */
    if (true == this->CheckBox_Connecting->Checked) {
	int r = StrToInt(this->Edit_R->Text);
	int g = StrToInt(this->Edit_G->Text);
	int b = StrToInt(this->Edit_B->Text);
	double_array rgbValues(new double[3]);
	rgbValues[0] = r;
	rgbValues[1] = g;
	rgbValues[2] = b;
	RGB_ptr rgb(new
		    RGBColor(RGBColorSpace::unknowRGB, rgbValues,
			     MaxValue::Int12Bit));
	control->setTestRGB(rgb);
    }
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Edit_GChange(TObject * Sender)
{
    Edit_RChange(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Edit_BChange(TObject * Sender)
{
    Edit_RChange(Sender);
}

//---------------------------------------------------------------------------


void __fastcall TI2CTestForm::CheckBox1Click(TObject * Sender)
{
    if (true == this->CheckBox_Connecting->Checked) {
	bool enable = this->CheckBox1->Checked;
	control->setGammaTest(enable);
    }
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::CheckBox_ConnectingClick(TObject * Sender)
{
    if (false == this->CheckBox_Connecting->Checked) {
	this->Edit_GammaTestAddress->Enabled = true;
	this->Edit_GammaTestBit->Enabled = true;
	this->Edit_TestRGBAdress->Enabled = true;
	this->CheckBox_IndepRGB->Enabled = true;
    }
}

//---------------------------------------------------------------------------

