//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件
#include <FileCtrl.hpp>
//本項目內頭文件
#include "TCCTLUTForm.h"
#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOutputFileFrame"
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
__fastcall TCCTLUTForm::TCCTLUTForm(TComponent * Owner)
:TForm(Owner), serialid(0), run(false)
{
}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------


void TCCTLUTForm::setMeasureInfo()
{
    using namespace cms::util;
    int start = bitDepth->getMeasureStart();
    int step = bitDepth->getMeasureStep();
    this->Edit_StartLevel->Text = Util::toString(start).c_str();
    this->ComboBox_LevelStep->Text = Util::toString(step).c_str();
};


//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::RadioButton_P1P2Click(TObject * Sender)
{
    this->CheckBox_NewMethod->Checked = false;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_MeaRunClick(TObject * Sender)
{
    using namespace std;
    using namespace Dep;
    using namespace cms::lcd::calibrate;
    using namespace cms::colorformat;

    run = true;
    try {			//為了對應__finally使用的try
	String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
	string filename = astr->c_str();

	MainForm->getAnalyzer();
	if (MainForm->isCA210Analyzer()) {
	    MainForm->setAnalyzerToTargetChannel();
	}
	MainForm->setMeterMeasurementWaitTimes();
	bptr < ComponentFetcher > fetcher =
	    MainForm->getComponentFetcher();
	LCDCalibrator calibrator(fetcher, bitDepth);

	//==========================================================================
	// P1P2和RBInterp的選擇
	//==========================================================================
	if (this->RadioButton_P1P2->Checked) {
	    //選了P1P2
	    int p1 = this->Edit_P1->Text.ToInt();
	    int p2 = this->Edit_P2->Text.ToInt();
	    calibrator.setP1P2(p1, p2);
	} else if (this->RadioButton_RBInterp->Checked) {
	    //選了RBInterp
	    int rbunder = this->Edit_RBInterpUnder->Text.ToInt();
	    calibrator.setRBInterpolation(rbunder);
	} else if (this->RadioButton_DefinedDim->Checked) {
	    //新低灰階修正方法
	    int under = this->Edit_DefinedDimUnder->Text.ToInt();
	    bool averageDim = this->CheckBox_AverageDimDG->Checked;
	    double gamma = this->Edit_DimGamma->Text.ToDouble();
	    calibrator.setDefinedDim(under, gamma, averageDim);
	} else if (this->RadioButton_None->Checked) {
	    calibrator.setNonDimCorrect();
	}
	//==========================================================================

	//==========================================================================
	// gamma的處理
	//==========================================================================
	if (this->RadioButton_Gamma->Checked) {
	    double gamma = this->ComboBox_Gamma->Text.ToDouble();
	    calibrator.setGamma(gamma);
	} else if (this->RadioButton_GammaCurve->Checked) {
	    double_vector_ptr gammaCurve = rgbGamma->w;
	    calibrator.setGammaCurve(gammaCurve);
	}
	calibrator.setGByPass(this->CheckBox_GByPass->Checked);
	//==========================================================================

	//==========================================================================
	// blue correction
	//==========================================================================
	if (this->CheckBox_BGain->Checked) {
	    double gain = this->Edit_BGain->Text.ToDouble();
	    calibrator.setBIntensityGain(gain);
	}
	calibrator.setBMax(this->CheckBox_BMax->Checked);
	if (true == CheckBox_BMax2->Checked) {
	    int begin = Edit_BMax2Begin->Text.ToInt();
	    double gamma = Edit_BMax2Gamma->Text.ToDouble();
	    calibrator.setBMax2(CheckBox_BMax2->Checked, begin, gamma);
	}
	//==========================================================================

	//==========================================================================
	// others
	//==========================================================================
	calibrator.setAvoidFRCNoise(this->CheckBox_AvoidNoise->Checked);
	calibrator.setNewMethod(this->CheckBox_NewMethod->Checked);
	if (CheckBox_BTargetIntensity->Checked) {
	    double bTargetIntensity =
		Edit_BTargetIntensity->Text.ToDouble();
	    calibrator.setBTargetIntensity(bTargetIntensity);
	}
	//==========================================================================

	//==========================================================================
	// Keep Max Luminance
	//==========================================================================
	if (true == RadioButton_MaxYNone->Checked) {
	    calibrator.setKeepMaxLuminance(KeepMaxLuminance::None);
	} else if (true == RadioButton_MaxYTarget->Checked) {
	    calibrator.setKeepMaxLuminance(KeepMaxLuminance::TargetWhite);
	} else if (true == RadioButton_MaxYNative->Checked) {
	    calibrator.setKeepMaxLuminance(KeepMaxLuminance::NativeWhite);
	} else if (true == RadioButton_MaxYNativeAdv->Checked) {
	    int over = this->Edit_MaxYAdvOver->Text.ToInt();
	    double gamma = this->Edit_MaxYAdvGamma->Text.ToDouble();
	    calibrator.setKeepMaxLuminanceNativeWhiteAdvanced(over, gamma);
	}
	//==========================================================================


	try {
	    if (this->TOutputFileFrame1->createDir() == false) {
		return;
	    }

	    RGB_vector_ptr dglut =
		calibrator.getCCTDGLut(getMeasureCondition());
	    if (dglut == null) {
		//被中斷就直接return
		return;
	    }

	    bptr < DGLutFile > dgLutFile =
		calibrator.storeDGLutFile(filename, dglut);
	    //MainForm->setDummyMeterFilename(dgLutFile);
	    //要release掉, 才可以讀取該檔
	    dgLutFile.reset();
            //寫到文字檔
	    //this->Button_Run->Enabled = true;
	    ShowMessage("Ok!");
	    Util::shellExecute(filename);
	}
	catch(java::lang::IllegalStateException & ex) {
	    ShowMessage(ex.toString().c_str());
	}
    }
    __finally {
	run = false;
    }
}

//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::FormCreate(TObject * Sender)
{
    using namespace cms::lcd::calibrate;


    //==========================================================================
    // debug模式的設定
    //==========================================================================
    bool debug = !MainForm->linkCA210;
    this->Button_Debug->Visible = debug;
    this->Button_Reset->Visible = debug;
    //==========================================================================
#ifdef DEBUG_NEWFUNC
    this->GroupBox_KeepMaxLuminance->Visible = true;
    this->Button_Run->Visible = true;


    RadioButton_None->Visible = true;
    RadioButton_DefinedDim->Visible = true;
    CheckBox_AverageDimDG->Visible = true;
    Label14->Visible = true;
    Label17->Visible = true;
    Edit_DefinedDimUnder->Visible = true;
    Edit_DimGamma->Visible = true;

    Label18->Visible = true;
    Label19->Visible = true;
    CheckBox_BMax2->Visible = true;
    Edit_BMax2Begin->Visible = true;
    Edit_BMax2Gamma->Visible = true;

    CheckBox_NewMethod->Visible = true;
#endif
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_DebugClick(TObject * Sender)
{
    using namespace std;
    OpenDialog1->Filter = "DGCode Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	MainForm->setDummyMeterFilename(string(filename.c_str()));
	ShowMessage("Dummy meter setting Ok!");
    };

}

//---------------------------------------------------------------------------





void __fastcall TCCTLUTForm::FormShow(TObject * Sender)
{
    using namespace Dep;
    using namespace cms::lcd::calibrate;

    const MaxValue & input = bitDepth->getInputMaxValue();
    bool avoidNoise = (input == MaxValue::Int6Bit
		       || input == MaxValue::Int8Bit);
    this->CheckBox_AvoidNoise->Enabled = avoidNoise;

    bool tconInput = bitDepth->isTCONInput();
    this->CheckBox_Expand->Visible = !tconInput;
    Button_Run->Enabled = false;

    setMeasureInfo();
}

void __fastcall TCCTLUTForm::RadioButton_GammaCurveClick(TObject * Sender)
{
    using namespace cms::util;
    OpenDialog1->Filter = "Desired Gamma Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	rgbGamma = RGBGamma::loadFromDesiredGamma(filename.c_str());
	unsigned int n = bitDepth->getLevel();
	if (rgbGamma != null && rgbGamma->w->size() == n) {
	    this->RadioButton_GammaCurve->Checked = true;
	    this->CheckBox_GByPass->Visible = true;
	    return;
	} else {
	    ShowMessage("Desired Gamma File Format is wrong!");
	}
    }
    this->RadioButton_Gamma->Checked = true;
}


//---------------------------------------------------------------------------
void TCCTLUTForm::setBitDepthProcessor(bptr <
				       cms::lcd::calibrate::
				       BitDepthProcessor > bitDepth)
{
    this->bitDepth = bitDepth;
}

void __fastcall TCCTLUTForm::
TOutputFileFrame1Button_BrowseDirClick(TObject * Sender)
{
    TOutputFileFrame1->Button_BrowseDirClick(Sender);

}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (27 == Key) {
	if (true == run) {
	    ShowMessage("Interrupt!");
	} else {
	    this->Close();
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_GammaClick(TObject * Sender)
{
    this->CheckBox_GByPass->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::ComboBox_GammaChange(TObject * Sender)
{
    RadioButton_GammaClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_ExpandClick(TObject * Sender)
{
    bool checked = this->CheckBox_Expand->Checked;
    this->Panel_Expand->Visible = checked;
}

//---------------------------------------------------------------------------
bptr < cms::lcd::calibrate::MeasureCondition >
    TCCTLUTForm::getMeasureCondition()
{
    using namespace cms::lcd::calibrate;
    bool expand = this->CheckBox_Expand->Checked;
    bptr < MeasureCondition > condition;
    if (expand) {
	int lowstart = this->Edit_LowStartLevel->Text.ToInt();
	int lowend = this->Edit_LowEndLevel->Text.ToInt();
	int lowstep = this->ComboBox_LowStep->Text.ToInt();
	int highstart = this->Edit_HighStartLevel->Text.ToInt();
	int highend = this->Edit_HighEndLevel->Text.ToInt();
	int highstep = this->ComboBox_HighStep->Text.ToInt();
	condition = bptr < MeasureCondition > (new
					       MeasureCondition
					       (lowstart, lowend,
						lowstep, highstart,
						highend, highstep));
    } else {
	int start = this->Edit_StartLevel->Text.ToInt();
	int end = this->Edit_EndLevel->Text.ToInt();
	int step = this->ComboBox_LevelStep->Text.ToInt();

	//預設的第一階
	int firstStep = bitDepth->getMeasureFirstStep();
	if (bitDepth->getMeasureStart() != start
	    || bitDepth->getMeasureEnd() != end
	    || bitDepth->getMeasureStep() != step) {
	    //如果量測條件被改變, 則不要採用原本的第一階
	    firstStep = step;
	}

	condition =
	    bptr < MeasureCondition > (new
				       MeasureCondition(start, end,
							firstStep, step));
    }
    return condition;

}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::Button_ResetClick(TObject * Sender)
{
    MainForm->resetDummyMeter();
}

//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::CheckBox_BMax2Click(TObject * Sender)
{
    bool enable = this->CheckBox_BMax2->Checked;
    Edit_BMax2Begin->Enabled = enable;
    Edit_BMax2Gamma->Enabled = enable;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_NewMethodClick(TObject * Sender)
{
    if (CheckBox_NewMethod->Checked) {
	RadioButton_P1P2->Enabled = false;
	RadioButton_DefinedDim->Enabled = true;
	RadioButton_MaxYNativeAdv->Enabled = true;
	if (RadioButton_P1P2->Checked) {
	    this->RadioButton_DefinedDim->Checked = true;
	}

    } else {
	RadioButton_P1P2->Enabled = true;
	RadioButton_DefinedDim->Enabled = false;
	RadioButton_MaxYNativeAdv->Enabled = false;
	if (RadioButton_DefinedDim->Checked) {
	    this->RadioButton_P1P2->Checked = true;
	}
	if (RadioButton_MaxYNativeAdv->Checked) {
	    this->RadioButton_MaxYTarget->Checked = true;
	}
    }

}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_MaxYNativeAdvClick(TObject *
							    Sender)
{
    bool checked = RadioButton_MaxYNativeAdv->Checked;
    Edit_MaxYAdvOver->Enabled = checked;
    Edit_MaxYAdvGamma->Enabled = checked;
}

//---------------------------------------------------------------------------


void __fastcall TCCTLUTForm::FormClose(TObject * Sender,
				       TCloseAction & Action)
{
    if (Button_Run->Enabled) {
	MainForm->setAnalyzerNull();
    }
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::Button_RunClick(TObject * Sender)
{
    Button_ResetClick(Sender);
    Button_MeaRunClick(Sender);
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_BTargetIntensityClick(TObject *
							    Sender)
{
    bool check = this->CheckBox_BTargetIntensity->Checked;
    this->Edit_BTargetIntensity->Enabled = check;
}

//---------------------------------------------------------------------------

