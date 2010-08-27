//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include "inifiles.hpp"

//�����ؤ��Y���
#include "TMainForm.h"
//#include "TTargetWhiteForm.h"
#include "TTargetWhiteForm2.h"
#include "TAboutBox.h"
#include "TCCTLUTForm.h"
#include "../TMatrixCalibration.h"
#include "TGammaAdjustmentForm.h"
#include "TGammaMeasurementForm.h"
#include "../TI2CTestForm.h"

#define SETUPFILE "cctv3.ini"
#define TCONFILE "tcon.ini"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner),
linkCA210(!FileExists(DEBUG_FILE)), newFunction(FileExists(DEBUG_NEWFUNC_FILE))
{

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::About1Click(TObject * Sender)
{
    if (AboutBox == null) {
	Application->CreateForm(__classid(TAboutBox), &AboutBox);
    }
    AboutBox->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject * Sender)
{
    this->Close();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::TargetWhite1Click(TObject * Sender)
{
    if (TargetWhiteForm2 == null) {
	Application->CreateForm(__classid(TTargetWhiteForm2), &TargetWhiteForm2);
    }
    TargetWhiteForm2->setBitDepthProcessor(bitDepth);
    TargetWhiteForm2->ShowModal();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject * Sender)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;

    bitDepth = bptr < BitDepthProcessor > (new BitDepthProcessor(8, 10, 8, false));
    if (true == linkCA210) {
	initCA210Meter();
    } else {
	setDummyMeterFilename(METER_FILE);
	this->Caption = this->Caption + " (debug mode)";
	this->GroupBox_CHSetting->Visible = false;
	//this->Button_I2CTest->Visible = true;
    }
    initTCONFile();
    readTCONSections();
    readSetup();
    ComboBox_TCONTypeChange(this);
}

void TMainForm::initTCONFile()
{
    using namespace cms::util;
    tconFilename = ExtractFilePath(Application->ExeName) + TCONFILE;
    if (!Util::isFileExist(tconFilename.c_str())) {
	//=========================================================================================
	// produce tcon ini file
	//=========================================================================================
	bptr_ < TIniFile > ini(new TIniFile(tconFilename));
	//=========================================================================
	// 11306
	//=========================================================================
	ini->WriteInteger("11306", "AddressingSize", 5);

	ini->WriteString("11306", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("11306", "DigitalGammaEnableBit", 0);
	ini->WriteString("11306", "DigitalGammaLUTAddress", "3C0");
	ini->WriteInteger("11306", "DigitalGammaLUTType", 10);

	ini->WriteBool("11306", "GammaTestFunc", false);
	//=========================================================================
	// 12306
	//=========================================================================
	ini->WriteInteger("12306", "AddressingSize", 5);

	ini->WriteString("12306", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("12306", "DigitalGammaEnableBit", 0);
	ini->WriteString("12306", "DigitalGammaLUTAddress", "302");
	ini->WriteInteger("12306", "DigitalGammaLUTType", 12);

	ini->WriteBool("12306", "GammaTestFunc", true);
	ini->WriteString("12306", "GammaTestEnableAddress", "29");
	ini->WriteInteger("12306", "GammaTestEnableBit", 0);
	ini->WriteString("12306", "GammaTestAddress", "154");
	ini->WriteBool("12306", "IndepRGB", true);
	//=========================================================================
    }
}

void TMainForm::readTCONSections()
{
    bptr_ < TIniFile > ini(new TIniFile(tconFilename));
    bptr_ < TStringList > tconSections(new TStringList());
    ini->ReadSections(tconSections.get());
    int size = tconSections->Count;
    for (int x = 0; x < size; x++) {
	String section = (*tconSections)[x];
	ComboBox_TCONType->AddItem(section, null);
    }
    ComboBox_TCONType->AddItem("Custom", null);
    ComboBox_TCONType->ItemIndex = 0;
}

void TMainForm::readTCONSetup(String filename, String section)
{
    //=========================================================================
    bptr_ < TIniFile > ini(new TIniFile(filename));
    this->ComboBox_AddressingSize->ItemIndex = ini->ReadInteger(section, "AddressingSize", 5);
    bool gammaTestFunc = ini->ReadBool(section, "GammaTestFunc", false);

    //if (custom) {
    this->CheckBox_GammaTest->Checked = gammaTestFunc;
    //}

    if (gammaTestFunc) {
	GroupBox_GammaTestAddress->Visible = true;
	this->Edit_GammaTestEnableAddress->Text =
	    ini->ReadString(section, "GammaTestEnableAddress", "29");
	this->Edit_GammaTestEnableBit->Text = ini->ReadInteger(section, "GammaTestEnableBit", 0);
	this->Edit_GammaTestAddress->Text = ini->ReadString(section, "GammaTestAddress", "154");
	this->ComboBox_GammaTestType->ItemIndex = ini->ReadBool(section, "IndepRGB", true) ? 0 : 1;
	ComboBox_GammaTestTypeChange(this);
    } else {
	GroupBox_GammaTestAddress->Visible = false;
    }
    this->Edit_DGEnableAddress->Text = ini->ReadString(section, "DigitalGammaEnableAddress", "28");
    this->Edit_DGEnableBit->Text = ini->ReadInteger(section, "DigitalGammaEnableBit", 0);
    this->Edit_DGLUTAddress->Text = ini->ReadString(section, "DigitalGammaLUTAddress", "302");
    this->ComboBox_DGLUTType->Text = ini->ReadInteger(section, "DigitalGammaLUTType", 10);
}

void TMainForm::writeTCONCustomSetup()
{
    if (ComboBox_TCONType->Text == "Custom") {
	bptr_ < TIniFile > ini(new TIniFile(ExtractFilePath(Application->ExeName) + SETUPFILE));

	ini->WriteString("Custom", "DigitalGammaEnableAddress", this->Edit_DGEnableAddress->Text);
	ini->WriteInteger("Custom", "DigitalGammaEnableBit", this->Edit_DGEnableBit->Text.ToInt());
	ini->WriteString("Custom", "DigitalGammaLUTAddress", this->Edit_DGLUTAddress->Text);
	ini->WriteInteger("Custom", "DigitalGammaLUTType", ComboBox_DGLUTType->Text.ToInt());

	bool gammaTest = CheckBox_GammaTest->Checked;
	ini->WriteBool("Custom", "GammaTestFunc", gammaTest);
	if (gammaTest) {
	    ini->WriteString("Custom", "GammaTestEnableAddress",
			     this->Edit_GammaTestEnableAddress->Text);
	    ini->WriteInteger("Custom", "GammaTestEnableBit",
			      this->Edit_GammaTestEnableBit->Text.ToInt());
	    ini->WriteString("Custom", "GammaTestAddress", this->Edit_GammaTestAddress->Text);
	    ini->WriteBool("Custom", "IndepRGB", this->CheckBox_GammaTestIndepRGB->Checked);
	}
    }

};

void TMainForm::readSetup()
{
    bptr_ < TIniFile > ini(new TIniFile(ExtractFilePath(Application->ExeName) + SETUPFILE));
    //=========================================================================
    int cardIndex = ini->ReadInteger("I2C", "Card", 2);
    switch (cardIndex) {
    case 0:
	this->RadioButton_USB->Checked = true;
	break;
    case 1:
	this->RadioButton_LPTLarge->Checked = true;
	break;
    case 2:
	this->RadioButton_LPTSmall->Checked = true;
	break;
    };
    //=========================================================================
    int tconIndex = ini->ReadInteger("TCON", "Count", 0);
    switch (tconIndex) {
    case 0:
	this->RadioButton_SingleTCON->Checked = true;
	break;
    case 1:
	this->RadioButton_DualTCON->Checked = true;
	break;
    }
    //=========================================================================
    int typeIndex = ini->ReadInteger("TCON", "Type", 0);
    ComboBox_TCONType->ItemIndex = typeIndex;
    /*this->ComboBox_AddressingSize->ItemIndex = ini->ReadInteger("TCON ", "AddressingSize ", 5);
       this->Edit_GammaTestEnableAddress->Text =
       ini->ReadString("TCON ", "GammaTestEnableAddress ", "4 A1 ");
       this->Edit_GammaTestEnableBit->Text = ini->ReadInteger("TCON ", "GammaTestEnableBit ", 1);
       this->Edit_GammaTestAddress->Text = ini->ReadString("TCON ", "GammaTestAddress ", "4 A7 ");
       ComboBox_GammaTestType->ItemIndex = ini->ReadBool("TCON ", "IndepRGB ", true) ? 0 : 1;
       ComboBox_GammaTestTypeChange(this); */
    //=========================================================================
}

void TMainForm::writeSetup()
{
    bptr_ < TIniFile > ini(new TIniFile(ExtractFilePath(Application->ExeName) + SETUPFILE));
    //=========================================================================
    int cardIndex = this->RadioButton_LPTLarge->Checked ? 1 : 0;
    cardIndex += this->RadioButton_LPTSmall->Checked ? 2 : 0;
    ini->WriteInteger("I2C", "Card", cardIndex);
    //=========================================================================
    int tconIndex = this->RadioButton_DualTCON->Checked ? 1 : 0;
    ini->WriteInteger("TCON", "Count", tconIndex);
    //=========================================================================
    int typeIndex = ComboBox_TCONType->ItemIndex;
    ini->WriteInteger("TCON", "Type", typeIndex);

    /*ini->WriteInteger("TCON ", "AddressingSize ", this->ComboBox_AddressingSize->ItemIndex);
       ini->WriteString("TCON ", "GammaTestEnableAddress ", this->Edit_GammaTestEnableAddress->Text);
       ini->WriteInteger("TCON ", "GammaTestEnableBit ", this->Edit_GammaTestEnableBit->Text.ToInt());
       ini->WriteString("TCON ", "GammaTestAddress ", this->Edit_GammaTestAddress->Text);
       ini->WriteBool("TCON ", "IndepRGB ", ComboBox_GammaTestType->ItemIndex == 0); */

}

//---------------------------------------------------------------------------
void TMainForm::initCA210Meter()
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    try {
	meter = bptr < Meter > (new CA210());
	mm = bptr < MeterMeasurement > (new MeterMeasurement(meter, false));
	mm->setWaitTimes(this->getInterval());
    }
    catch(EOleException & ex) {
	ShowMessage("CA210 cannot be linked.");
    }
};

//---------------------------------------------------------------------------
bptr < cms::measure::IntensityAnalyzerIF > TMainForm::getAnalyzer()
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    if (null == analyzer) {
	//����ca210
	bptr < cms::measure::meter::CA210 > ca210 = getCA210();
	if (null == ca210) {
	    return bptr < IntensityAnalyzerIF > ((IntensityAnalyzerIF *) null);
	}
	if (null == ca210Analyzer) {
	    ca210Analyzer = bptr < CA210IntensityAnalyzer > (new CA210IntensityAnalyzer(ca210, mm));
	}
	//����max matrix
	bptr < MaxMatrixIntensityAnayzer > ma(new MaxMatrixIntensityAnayzer(mm));


	if (true == this->RadioButton_AnalyzerCA210->Checked) {
	    analyzer = ca210Analyzer;
	} else if (true == this->RadioButton_AnalyzerMaxMatrix->Checked) {
	    analyzer = ma;
	} else if (true == this->RadioButton_AnalyzerDebug->Checked) {
	    //���ͨ�̪��X��
	    analyzer = bptr < IntensityAnalyzerIF > (new IntensityAnayzer(ma, ca210Analyzer));
	}
    }
    return analyzer;
}

bptr < cms::measure::MaxMatrixIntensityAnayzer > TMainForm::getNativeWhiteAnalyzer()
{
    return nativeWhiteAnalyzer;
};

//---------------------------------------------------------------------------
void TMainForm::setAnalyzerToTargetChannel()
{
    using namespace std;


    if (true == linkCA210) {
	if (null == ca210Analyzer) {
	    throw java::lang::IllegalStateException("call getAnalyzer()first !");
	}
	//���Xchannel no�Mid
	int channel = this->Edit_TargetCH->Text.ToInt();
	string targetid = Edit_TargetID->Text.c_str();
	//�Y�S���ȱj����w���ťզr�����r��
	targetid = targetid.empty()? string("") : targetid;
	string_ptr id(new string(targetid));
	//�]�w�bca210
	ca210Analyzer->setChannel(channel, id);

    }
};

//---------------------------------------------------------------------------

void TMainForm::setAnalyzerToSourceChannel()
{
    using namespace std;
    if (true == linkCA210) {
	if (null == ca210Analyzer) {
	    throw java::lang::IllegalStateException("call getAnalyzer()first !");
	}
	//���Xchannel no�Mid
	int channel = this->Edit_SourceCH->Text.ToInt();
	string_ptr id(new string(""));
	//�]�w�bca210
	ca210Analyzer->setChannel(channel, id);

    }
};

//---------------------------------------------------------------------------
bool TMainForm::isCA210Analyzer()
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    CA210IntensityAnalyzer *ca210Analyzer =
	dynamic_cast < CA210IntensityAnalyzer * >(analyzer.get());
    return ca210Analyzer != null;
};

//---------------------------------------------------------------------------
void TMainForm::setDummyMeterFilename(const std::string & filename)
{
    using namespace cms::colorformat;
    bptr < DGLutFile > dglutFile(new DGLutFile(filename, ReadOnly));
    setDummyMeterFile(dglutFile);
}

//---------------------------------------------------------------------------
void TMainForm::setDummyMeterFile(bptr < cms::colorformat::DGLutFile > dglutFile)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    using namespace Indep;
    using namespace Dep;

    meter = bptr < Meter > (new DGLutFileMeter(dglutFile));
    mm = bptr < MeterMeasurement > (new MeterMeasurement(meter, false));
    mm->setFakeMeasure(true);

    fetcher = bptr < ComponentFetcher > ((ComponentFetcher *) null);

    bptr < DGLutProperty > property = dglutFile->getProperty();
    if (null != property) {
	//�Y��property�h���s��
	bptr < MaxMatrixIntensityAnayzer > matrixAnalyzer(new MaxMatrixIntensityAnayzer(mm));
	analyzer = matrixAnalyzer;

	//=====================================================================
	// �]�wtarget analyzer
	//=====================================================================
	xyY_ptr targetwxyY = property->getTargetReferenceColor(Channel::W);
	if (null != targetwxyY) {
	    xyY_ptr rxyY = property->getTargetReferenceColor(Channel::R);
	    xyY_ptr gxyY = property->getTargetReferenceColor(Channel::G);
	    xyY_ptr bxyY = property->getTargetReferenceColor(Channel::B);


	    matrixAnalyzer->setupComponent(Channel::W, targetwxyY->toXYZ());
	    matrixAnalyzer->setupComponent(Channel::R, rxyY->toXYZ());
	    matrixAnalyzer->setupComponent(Channel::G, gxyY->toXYZ());
	    matrixAnalyzer->setupComponent(Channel::B, bxyY->toXYZ());
	    matrixAnalyzer->enter();

	    string_ptr comment = property->getProperty("reference white comment");
	    if (null != comment) {
		matrixAnalyzer->setReferenceColorComment(*comment);
	    }
	}
	//=====================================================================

	//=====================================================================
	// �]�wnative analyzer
	//=====================================================================
	xyY_ptr nativewxyY = property->getNativeReferenceColor(Channel::W);
	if (null != nativewxyY) {
	    bptr < MaxMatrixIntensityAnayzer > matrixAnalyzer2(new MaxMatrixIntensityAnayzer(mm));
	    nativeWhiteAnalyzer = matrixAnalyzer2;
	    xyY_ptr rxyY = property->getNativeReferenceColor(Channel::R);
	    xyY_ptr gxyY = property->getNativeReferenceColor(Channel::G);
	    xyY_ptr bxyY = property->getNativeReferenceColor(Channel::B);

	    matrixAnalyzer2->setupComponent(Channel::W, nativewxyY->toXYZ());
	    matrixAnalyzer2->setupComponent(Channel::R, rxyY->toXYZ());
	    matrixAnalyzer2->setupComponent(Channel::G, gxyY->toXYZ());
	    matrixAnalyzer2->setupComponent(Channel::B, bxyY->toXYZ());
	    matrixAnalyzer2->enter();
	}
	//=====================================================================

	//=====================================================================
	// BitDepthProcessor
	//=====================================================================
	bptr < BitDepthProcessor > bitDepth = property->getBitDepthProcessor();
	switch (bitDepth->getInputMaxValue().bit) {
	case 6:
	    RadioButton_In6->Checked = true;
	    break;
	case 8:
	    RadioButton_In8->Checked = true;
	    break;
	case 10:
	    RadioButton_In10->Checked = true;
	    break;
	}
	switch (bitDepth->getLutMaxValue().bit) {
	case 10:
	    RadioButton_Lut10->Checked = true;
	    break;
	case 12:
	    RadioButton_Lut12->Checked = true;
	    break;
	}
	switch (bitDepth->getOutputMaxValue().bit) {
	case 6:
	    RadioButton_Out6->Checked = true;
	    break;
	case 8:
	    RadioButton_Out8->Checked = true;
	    break;
	case 10:
	    RadioButton_Out10->Checked = true;
	    break;
	}
	//=====================================================================

    } else {
	ShowMessage("Old version Raw Data.");
	//�Lproperty�h���ª�
	analyzer = bptr < CA210IntensityAnalyzer > (new CA210IntensityAnalyzer(mm));
    }
}


//---------------------------------------------------------------------------

void TMainForm::resetDummyMeter()
{
    using namespace cms::measure::meter;
    using namespace cms::lcd::calibrate;
    DGLutFileMeter *dgc = dynamic_cast < DGLutFileMeter * >(meter.get());
    dgc->reset();
};

//---------------------------------------------------------------------------
void TMainForm::setAnalyzerNull()
{
    analyzer.reset();
    fetcher.reset();
}

//---------------------------------------------------------------------------
bptr < cms::lcd::calibrate::ComponentFetcher > TMainForm::getComponentFetcher()
{
    using namespace cms::lcd::calibrate;
    if (null == fetcher) {
	bptr < cms::measure::IntensityAnalyzerIF > analyzer = getAnalyzer();
	fetcher = bptr < ComponentFetcher > (new cms::lcd::calibrate::
					     ComponentFetcher(analyzer, bitDepth));
	MeasureWindow->addWindowListener(fetcher);
    }

    return fetcher;
};

//---------------------------------------------------------------------------
bptr < cms::measure::meter::CA210 > TMainForm::getCA210()
{
    if (null == ca210 && true == linkCA210) {
	using namespace cms::measure::meter;
	if (null == meter) {
	    //throw IllegalStateException("CA210 cannot be linked.");
	    ShowMessage("CA210 cannot be linked.");
	    return bptr < CA210 > ((CA210 *) null);
	}

	cms::measure::meter::Meter * pointer = meter.get();
	ca210 = bptr < CA210 > (dynamic_cast < CA210 * >(pointer));
    }
    return ca210;
};

//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
int TMainForm::getInterval()
{
    return Edit_Interval->Text.ToInt();
};

//---------------------------------------------------------------------------

void __fastcall TMainForm::CCTLUT1Click(TObject * Sender)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::lcd::calibrate;
    if (CCTLUTForm == null) {
	Application->CreateForm(__classid(TCCTLUTForm), &CCTLUTForm);
    }

    if (true == this->RadioButton_AnalyzerMaxMatrix->Checked) {
	MaxMatrixIntensityAnayzer *ma =
	    dynamic_cast < MaxMatrixIntensityAnayzer * >(analyzer.get());
	if (null == ma || ma->isInverseMatrixNull()) {
	    ShowMessage("Set \"Target White \"first.");
	    return;
	}
    }

    CCTLUTForm->setBitDepthProcessor(bitDepth);
    CCTLUTForm->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::GammaAdj1Click(TObject * Sender)
{
    if (GammaAdjustmentForm == null) {
	Application->CreateForm(__classid(TGammaAdjustmentForm), &GammaAdjustmentForm);
    }
    GammaAdjustmentForm->setBitDepthProcessor(bitDepth);
    GammaAdjustmentForm->ShowModal();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_TCONClick(TObject * Sender)
{
    this->Panel_TCON->Visible = true;
    //this->bitDepth->setTCONInput(true);
    ShowMessage("Please Turn On DG and FRC for Measurement when T-CON Input Source is selected!!!");
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_PCClick(TObject * Sender)
{
    this->Panel_TCON->Visible = false;
    bitDepth->setTCONInput(false);
    MeasureWindow->setTCONControlOff();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Button_ConnectClick(TObject * Sender)
{
    using namespace i2c;
    using namespace Dep;
    bptr < i2cControl > i2c1st;
    bptr < i2cControl > i2c2nd;
    unsigned char first, second;
    bool dual = false;

    //bool bindepRGB = this->ComboBox_Type->ItemIndex == 1;
    if (this->RadioButton_SingleTCON->Checked) {
	first = StrToInt("0x" + this->Edit_DeviceAddress->Text);
    } else {
	first = StrToInt("0x" + this->Edit_MasterDeviceAddress->Text);
	second = StrToInt("0x" + this->Edit_SlaveDeviceAddress->Text);
	dual = true;
    }
    AddressingSize addressingSize = getAddressingSize();
    if (this->RadioButton_USB->Checked) {
	i2c1st = i2cControl::getUSBInstance(first, addressingSize, _3_3V, _400KHz);
	if (dual) {
	    i2c2nd = i2cControl::getUSBInstance(second, addressingSize, _3_3V, _400KHz);
	};
    } else {

	const LPTCard card = this->RadioButton_LPTLarge->Checked ? Large : Small;
	i2c1st = i2cControl::getLPTInstance(first, addressingSize, card);
	if (dual) {
	    i2c2nd = i2cControl::getLPTInstance(second, addressingSize, card);
	};
    };
    bool connect = i2c1st->connect();
    if (dual) {
	i2c2nd->connect();
    }

    if (true == connect) {
	//=====================================================================
	// digital gamma
	//=====================================================================
	int dgEnableAddress = StrToInt("0x" + Edit_DGEnableAddress->Text);
	int dgEnableBit = this->Edit_DGEnableBit->Text.ToInt();
	int dgLUTAddress = StrToInt("0x" + Edit_DGLUTAddress->Text);
	int dgLUTType = ComboBox_DGLUTType->Text.ToInt();
	//=====================================================================
	//=====================================================================
	// gamma test
	//=====================================================================
	bool gammaTest = CheckBox_GammaTest->Checked;
	if (gammaTest) {
	    int gammaTestAddress = StrToInt("0x" + this->Edit_GammaTestEnableAddress->Text);
	    int gammaTestBit = this->Edit_GammaTestEnableBit->Text.ToInt();
	    int testRGBAddress = StrToInt("0x" + this->Edit_GammaTestAddress->Text);
	    bool indepRGB = this->ComboBox_GammaTestType->ItemIndex == 0;
	    const TestRGBBit & testRGBBit = indepRGB ? TestRGBBit::
		IndependentInstance : TestRGBBit::DependentInstance;

	    parameter =
		bptr < TCONParameter >
		(new
		 TCONParameter(dgLUTType == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
			       dgLUTAddress, dgEnableAddress, dgEnableBit, gammaTestAddress,
			       gammaTestBit, testRGBAddress, testRGBBit));
	} else {
	    parameter =
		bptr < TCONParameter >
		(new
		 TCONParameter(dgLUTType == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
			       dgLUTAddress, dgEnableAddress, dgEnableBit));
	}

	//=====================================================================


	if (!dual) {
	    control = bptr < TCONControl > (new TCONControl(parameter, i2c1st));
	} else {
	    control = bptr < TCONControl > (new TCONControl(parameter, i2c1st, i2c2nd));
	}
	this->Button_Connect->Enabled = false;
	if (!this->RadioButton_PCTCON->Checked) {
	    MeasureWindow->setTCONControl(control);
	    this->bitDepth->setTCONInput(true);
	}
    } else {
	MeasureWindow->setTCONControlOff();
    }
}

//---------------------------------------------------------------------------
const i2c::AddressingSize TMainForm::getAddressingSize()
{
    using namespace i2c;
    int index = this->ComboBox_AddressingSize->ItemIndex;
    switch (index) {
    case 0:
	return _2k;
    case 1:
	return _4k;
    case 2:
	return _8k;
    case 3:
	return _16k;
    case 4:
	return _32k;
    case 5:
	return _64k;
    case 6:
	return _128k;
    case 7:
	return _256k;
    case 8:
	return _512k;
    default:
	return _2k;
    }
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Measurement1Click(TObject * Sender)
{
    if (GammaMeasurementForm == null) {
	Application->CreateForm(__classid(TGammaMeasurementForm), &GammaMeasurementForm);
    }
    GammaMeasurementForm->setBitDepthProcessor(bitDepth);
    GammaMeasurementForm->ShowModal();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::MatrixCalibration1Click(TObject * Sender)
{
    if (MatrixCalibrationForm == null) {
	Application->CreateForm(__classid(TMatrixCalibrationForm), &MatrixCalibrationForm);
    }

    if (true == linkCA210 && true == MatrixCalibrationForm->setMeter(getCA210()->getCA210API(), mm)) {
	MatrixCalibrationForm->ShowModal();
    } else {
	MatrixCalibrationForm->ShowModal();
    }

}

//---------------------------------------------------------------------------

void TMainForm::setBitDepthEnable(bool lut10, bool lut12, bool out6, bool out8, bool out10)
{
    this->RadioButton_Lut10->Enabled = lut10;
    this->RadioButton_Lut12->Enabled = lut12;
    this->RadioButton_Out6->Enabled = out6;
    this->RadioButton_Out8->Enabled = out8;
    this->RadioButton_Out10->Enabled = out10;
};

//---------------------------------------------------------------------------
void TMainForm::setBitDepthChecked(int lutSelect, int outSelect)
{

    switch (lutSelect) {
    case 0:
	this->RadioButton_Lut10->Checked = true;
	break;
    case 1:
	this->RadioButton_Lut12->Checked = true;
	break;
    };
    switch (outSelect) {
    case 0:
	this->RadioButton_Out6->Checked = true;
	break;
    case 1:
	this->RadioButton_Out8->Checked = true;
	break;
    case 2:
	this->RadioButton_Out10->Checked = true;
	break;
    };
};

//---------------------------------------------------------------------------
void TMainForm::setFRCAbility()
{
    string_ptr ability = bitDepth->getFRCAbility();
    this->Edit_FRCAbility->Text = ability->c_str();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_In6Click(TObject * Sender)
{
    using namespace boost;
    bitDepth->setInBit(6);
    // �]�wlut/out bit depth checked
    setBitDepthChecked(0, 0);
    // �]�wenable
    setBitDepthEnable(true, false, true, false, false);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_In8Click(TObject * Sender)
{
    using namespace cms::util;
    bitDepth->setInBit(8);
    // �]�wlut/out bit depth checked
    setBitDepthChecked(0, 1);
    // �]�wenable
    setBitDepthEnable(true, true, true, true, false);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_In10Click(TObject * Sender)
{
    using namespace cms::util;
    bitDepth->setInBit(10);
    // �]�wlut/out bit depth checked
    setBitDepthChecked(1, 1);
    // �]�wenable
    setBitDepthEnable(false, true, false, true, true);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Lut10Click(TObject * Sender)
{
    bitDepth->setLUTBit(10);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Lut12Click(TObject * Sender)
{
    bitDepth->setLUTBit(12);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out6Click(TObject * Sender)
{
    bitDepth->setOutBit(6);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out8Click(TObject * Sender)
{
    bitDepth->setOutBit(8);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out10Click(TObject * Sender)
{
    if (!bitDepth->isTCONInput()) {
	ShowMessage("Recommend using T-CON Input.");
    };
    bitDepth->setOutBit(10);
    setFRCAbility();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Button1Click(TObject * Sender)
{
    MeasureWindow->setVisible(true);
    MeasureWindow->Visible = true;
    MeasureWindow->setRGB(255, 0, 0);
    Application->ProcessMessages();
    Sleep(300);
    MeasureWindow->setRGB(0, 255, 0);
    Application->ProcessMessages();
    Sleep(300);
    MeasureWindow->setRGB(0, 0, 255);
    Application->ProcessMessages();
    Sleep(1000);
    MeasureWindow->setVisible(false);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit_IntervalChange(TObject * Sender)
{
    mm->setWaitTimes(this->getInterval());
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject * Sender)
{
    if (null == meter) {
	ShowMessage("CA210 cannot be linked.");
	//Application->Terminate();
    }
}

//---------------------------------------------------------------------------
void TMainForm::setMeterMeasurementWaitTimes()
{
    this->mm->setWaitTimes(this->getInterval());
};
void __fastcall TMainForm::Button_I2CTestClick(TObject * Sender)
{
    if (I2CTestForm == null) {
	Application->CreateForm(__classid(TI2CTestForm), &I2CTestForm);
    }
    I2CTestForm->Edit_GammaTestAddress->Text = this->Edit_GammaTestEnableAddress->Text;
    I2CTestForm->Edit_GammaTestBit->Text = this->Edit_GammaTestEnableBit->Text;
    I2CTestForm->Edit_TestRGBAdress->Text = this->Edit_GammaTestAddress->Text;
    I2CTestForm->ComboBox_AddressingSize->ItemIndex = this->ComboBox_AddressingSize->ItemIndex;
    I2CTestForm->RadioButton_LPTLarge->Checked = this->RadioButton_LPTLarge->Checked;
    I2CTestForm->RadioButton_LPTSmall->Checked = this->RadioButton_LPTSmall->Checked;
    I2CTestForm->RadioButton_USB->Checked = this->RadioButton_USB->Checked;
    I2CTestForm->RadioButton_Single->Checked = this->RadioButton_SingleTCON->Checked;
    I2CTestForm->RadioButton_Dual->Checked = this->RadioButton_DualTCON->Checked;
    I2CTestForm->CheckBox_IndepRGB->Checked = this->CheckBox_GammaTestIndepRGB->Checked;
    I2CTestForm->setBitDepthProcessor(bitDepth);
    I2CTestForm->ShowModal();
}

//---------------------------------------------------------------------------

void TMainForm::disconnectMeter()
{
    getCA210();
    if (null != ca210) {
	ca210->getCA210API()->setRemoteMode(ca210api::Off);
    }
};
void TMainForm::connectMeter()
{

    getCA210();
    if (null != ca210) {
	ca210->getCA210API()->setRemoteMode(ca210api::Locked);
    }
};
void __fastcall TMainForm::RadioButton_AnalyzerMaxMatrixClick(TObject * Sender)
{
    setAnalyzerNull();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_AnalyzerCA210Click(TObject * Sender)
{
    setAnalyzerNull();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_AnalyzerDebugClick(TObject * Sender)
{
    setAnalyzerNull();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_NormalClick(TObject * Sender)
{
    MeasureWindow->setPattern(Normal);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_HStripeClick(TObject * Sender)
{
    MeasureWindow->setPattern(HStripe);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_IndepClick(TObject * Sender)
{
    MeasureWindow->setPattern(Indepedent);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_HSDClick(TObject * Sender)
{
    MeasureWindow->setPattern(HSD);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_FlickrPixelClick(TObject * Sender)
{
    MeasureWindow->setPattern(FlickrPixel);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_FlickrSubPixelClick(TObject * Sender)
{
    MeasureWindow->setPattern(FlickrSubPixel);
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::ComboBox_GammaTestTypeChange(TObject * Sender)
{
    bool indepRGB = this->ComboBox_GammaTestType->ItemIndex == 0;
    CheckBox_GammaTestIndepRGB->Checked = indepRGB;
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::FormDestroy(TObject * Sender)
{
    writeSetup();
    writeTCONCustomSetup();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_USBClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_LPTLargeClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_LPTSmallClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox_TCONTypeChange(TObject * Sender)
{
    using namespace cms::util;
    String section = this->ComboBox_TCONType->Text;
    if (section != "Custom") {
	CheckBox_GammaTest->Visible = false;
	//�Y���̫�@�ӴN�Ocustom, ���θ��J
	if (Util::isFileExist(tconFilename.c_str())) {
	    readTCONSetup(tconFilename, section);
	}
    } else {
	readTCONSetup(ExtractFilePath(Application->ExeName) + SETUPFILE, "Custom");
	CheckBox_GammaTest->Visible = true;
	CheckBox_GammaTestClick(null);
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox_GammaTestClick(TObject * Sender)
{
    bool gammaTest = this->CheckBox_GammaTest->Checked;
    GroupBox_GammaTestAddress->Visible = gammaTest;
}

//---------------------------------------------------------------------------
bptr < i2c::TCONControl > TMainForm::getTCONControl()
{
    return control;
};

void __fastcall TMainForm::RadioButton_PCTCONClick(TObject * Sender)
{
    this->Panel_TCON->Visible = true;
    bitDepth->setTCONInput(false);
    MeasureWindow->setTCONControlOff();
}

//---------------------------------------------------------------------------
