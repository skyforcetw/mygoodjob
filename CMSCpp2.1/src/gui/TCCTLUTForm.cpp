//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <FileCtrl.hpp>
//�����ؤ��Y���
#include "TCCTLUTForm.h"
#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
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



void __fastcall TCCTLUTForm::RadioButton_RBInterpClick(TObject * Sender)
{
    setLowLevelCorrectionEditDisable();
    this->Edit_RBInterpUnder->Enabled = true;
    this->CheckBox_NewMethod->Checked = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_P1P2Click(TObject * Sender)
{
    setLowLevelCorrectionEditDisable();
    this->Edit_P1->Enabled = true;
    this->Edit_P2->Enabled = true;
    this->CheckBox_NewMethod->Checked = false;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_RunClick(TObject * Sender)
{
    using namespace std;
    using namespace Dep;
    using namespace cms::lcd::calibrate;

    run = true;

    MainForm->getAnalyzer();
    if (MainForm->isCA210Analyzer()) {
	MainForm->setAnalyzerToTargetChannel();
    }
    MainForm->setMeterMeasurementWaitTimes();
    bptr < ComponentFetcher > fetcher = MainForm->getComponentFetcher();
    LCDCalibrator calibrator(fetcher, bitDepth);

    //==========================================================================
    // P1P2�MRBInterp�����
    //==========================================================================
    if (this->RadioButton_P1P2->Checked) {
	//��FP1P2
	int p1 = this->Edit_P1->Text.ToInt();
	int p2 = this->Edit_P2->Text.ToInt();
	calibrator.setP1P2(p1, p2);
    } else if (this->RadioButton_RBInterp->Checked) {
	//��FRBInterp
	int rbunder = this->Edit_RBInterpUnder->Text.ToInt();
	calibrator.setRBInterpolation(rbunder);
    } else if (this->RadioButton_DefinedDim->Checked) {
	//�s�C�Ƕ��ץ���k
	int under = this->Edit_DefinedDimUnder->Text.ToInt();
	bool averageDim = this->CheckBox_AverageDimDG->Checked;
	calibrator.setDefinedDim(under, averageDim);
    } else {
	calibrator.setNonDimCorrect();
    }
    //==========================================================================

    //==========================================================================
    // gamma���B�z
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
    calibrator.setAvoidFRCNoise(this->CheckBox_AvoidNoise->Checked);
    calibrator.setNewMethod(this->CheckBox_NewMethod->Checked,
			    this->CheckBox_AvoidHook->Checked);

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
    try {			//���F����__finally�ϥΪ�try
	try {
	    this->TOutputFileFrame1->createDir();

	    RGB_vector_ptr dglut =
		calibrator.getCCTDGLut(getMeasureCondition());
	    if (dglut == null) {
		//�Q���_�N����return
		return;
	    }

	    String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
	    string filename = astr->c_str();
	    calibrator.storeDGLut(filename, dglut);
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
    // debug�Ҧ����]�w
    //==========================================================================
    bool debug = !MainForm->linkCA210;
    this->Button_Debug->Visible = debug;
    this->Button_Reset->Visible = debug;
    //==========================================================================
#ifdef DEBUG_NEWFUNC
    this->Button_Process->Visible = true;



    /*
       this->CheckBox_KeepMaxAdv->Visible = true;
       Label15->Visible = true;
       Label16->Visible = true;
       Edit_AdvOver->Visible = true;
       Edit_AdvGamma->Visible = true;
     */

    CheckBox_AverageDimDG->Visible = true;

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

	//�w�]���Ĥ@��
	int firstStep = bitDepth->getMeasureFirstStep();
	if (bitDepth->getMeasureStart() != start
	    || bitDepth->getMeasureEnd() != end
	    || bitDepth->getMeasureStep() != step) {
	    //�p�G�q������Q����, �h���n�ĥέ쥻���Ĥ@��
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
void TCCTLUTForm::setLowLevelCorrectionEditDisable()
{
    this->Edit_P1->Enabled = false;
    this->Edit_P2->Enabled = false;
    this->Edit_RBInterpUnder->Enabled = false;
    //this->Edit_NewP1->Enabled = false;
    //this->Edit_NewP2->Enabled = false;
    //this->Edit_GammaShift->Enabled = false;
    this->Edit_DefinedDimUnder->Enabled = false;
    this->CheckBox_AverageDimDG->Enabled = false;
    this->Edit_DimGamma->Enabled = false;
};

void __fastcall TCCTLUTForm::RadioButton_NoneClick(TObject * Sender)
{
    setLowLevelCorrectionEditDisable();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::Button_ResetClick(TObject * Sender)
{
    MainForm->resetDummyMeter();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_DefinedDimClick(TObject * Sender)
{
    setLowLevelCorrectionEditDisable();
    this->Edit_DefinedDimUnder->Enabled = true;
    this->CheckBox_AverageDimDG->Enabled = true;
    this->Edit_DimGamma->Enabled = true;
    this->CheckBox_NewMethod->Checked = false;
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
    this->RadioButton_None->Checked = true;
}

//---------------------------------------------------------------------------
