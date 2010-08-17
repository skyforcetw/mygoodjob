//---------------------------------------------------------------------------

#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>
//�����ؤ��Y���
#include <i2c/i2ccontrol.h>
//---------------------------------------------------------------------------

class TMainForm:public TForm {
    __published:		// IDE-managed Components
    TMainMenu * MainMenu1;
    TMenuItem *TargetWhite1;
    TMenuItem *CCTLUT1;
    TMenuItem *Measurement1;
    TMenuItem *About1;
    TMenuItem *Exit1;
    TLabel *Label6;
    TImage *Image1;
    TMenuItem *MatrixCalibration1;
    TMenuItem *GammaAdj1;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TPanel *Panel_TCON;
    TGroupBox *GroupBox_Card;
    TRadioButton *RadioButton_USB;
    TRadioButton *RadioButton_LPTLarge;
    TRadioButton *RadioButton_LPTSmall;
    TGroupBox *GroupBox_DeviceAddress;
    TLabel *Label5;
    TRadioButton *RadioButton_SingleTCON;
    TRadioButton *RadioButton_DualTCON;
    TEdit *Edit_DeviceAddress;
    TEdit *Edit_MasterDeviceAddress;
    TEdit *Edit_SlaveDeviceAddress;
    TComboBox *ComboBox_AddressingSize;
    TGroupBox *GroupBox_GammaTestAddress;
    TLabel *Label4;
    TGroupBox *GroupBox5;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *Edit_GammaTestEnableAddress;
    TEdit *Edit_GammaTestEnableBit;
    TEdit *Edit_GammaTestAddress;
    TCheckBox *CheckBox_GammaTestIndepRGB;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton_PC;
    TRadioButton *RadioButton_TCON;
    TGroupBox *Resolution;
    TLabel *Width;
    TLabel *Height;
    TEdit *Edit_Width;
    TEdit *Edit_Height;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TEdit *Edit_Interval;
    TGroupBox *GroupBox_CHSetting;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TEdit *Edit_SourceCH;
    TEdit *Edit_TargetCH;
    TEdit *Edit_TargetID;
    TGroupBox *GroupBox6;
    TGroupBox *GroupBox8;
    TRadioButton *RadioButton_In6;
    TRadioButton *RadioButton_In8;
    TRadioButton *RadioButton_In10;
    TGroupBox *GroupBox9;
    TRadioButton *RadioButton_Lut10;
    TRadioButton *RadioButton_Lut12;
    TGroupBox *GroupBox10;
    TRadioButton *RadioButton_Out6;
    TRadioButton *RadioButton_Out8;
    TRadioButton *RadioButton_Out10;
    TRadioButton *RadioButton_AnalyzerCA210;
    TRadioButton *RadioButton_AnalyzerMaxMatrix;
    TRadioButton *RadioButton_AnalyzerDebug;
    TLabel *Label10;
    TEdit *Edit_FRCAbility;
    TComboBox *ComboBox_GammaTestType;
    TLabel *Label11;
    TButton *Button_I2CTest;
    TButton *Button_Connect;
    TGroupBox *GroupBox4;
    TLabel *Label12;
    TEdit *Edit_DGLUTAddress;
    TGroupBox *GroupBox7;
    TComboBox *ComboBox_TCONType;
    TGroupBox *GroupBox11;
    TLabel *Label13;
    TLabel *Label14;
    TEdit *Edit_DGEnableAddress;
    TEdit *Edit_DGEnableBit;
    TLabel *Label15;
    TComboBox *ComboBox_DGLUTType;
    TCheckBox *CheckBox_GammaTest;
    TGroupBox *GroupBox12;
    TRadioButton *RadioButton_Normal;
    TRadioButton *RadioButton_HStripe;
    TRadioButton *RadioButton_Indep;
    TRadioButton *RadioButton_HSD;
    TRadioButton *RadioButton_FlickrPixel;
    TRadioButton *RadioButton_FlickrSubPixel;
    TRadioButton *RadioButton_PCTCON;
    TLabel *Label16;
    void __fastcall About1Click(TObject * Sender);
    void __fastcall Exit1Click(TObject * Sender);
    void __fastcall TargetWhite1Click(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CCTLUT1Click(TObject * Sender);
    void __fastcall GammaAdj1Click(TObject * Sender);
    void __fastcall RadioButton_TCONClick(TObject * Sender);
    void __fastcall RadioButton_PCClick(TObject * Sender);
    void __fastcall Button_ConnectClick(TObject * Sender);
    void __fastcall Measurement1Click(TObject * Sender);
    void __fastcall MatrixCalibration1Click(TObject * Sender);
    void __fastcall RadioButton_In6Click(TObject * Sender);
    void __fastcall RadioButton_In8Click(TObject * Sender);
    void __fastcall RadioButton_In10Click(TObject * Sender);
    void __fastcall RadioButton_Lut10Click(TObject * Sender);
    void __fastcall RadioButton_Lut12Click(TObject * Sender);
    void __fastcall RadioButton_Out6Click(TObject * Sender);
    void __fastcall RadioButton_Out8Click(TObject * Sender);
    void __fastcall RadioButton_Out10Click(TObject * Sender);
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall Edit_IntervalChange(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall Button_I2CTestClick(TObject * Sender);
    void __fastcall RadioButton_AnalyzerMaxMatrixClick(TObject * Sender);
    void __fastcall RadioButton_AnalyzerCA210Click(TObject * Sender);
    void __fastcall RadioButton_AnalyzerDebugClick(TObject * Sender);
    void __fastcall RadioButton_NormalClick(TObject * Sender);
    void __fastcall RadioButton_HStripeClick(TObject * Sender);
    void __fastcall RadioButton_IndepClick(TObject * Sender);
    void __fastcall RadioButton_HSDClick(TObject * Sender);
    void __fastcall RadioButton_FlickrPixelClick(TObject * Sender);
    void __fastcall RadioButton_FlickrSubPixelClick(TObject * Sender);
    void __fastcall ComboBox_GammaTestTypeChange(TObject * Sender);
    void __fastcall FormDestroy(TObject * Sender);
    void __fastcall RadioButton_USBClick(TObject * Sender);
    void __fastcall RadioButton_LPTLargeClick(TObject * Sender);
    void __fastcall RadioButton_LPTSmallClick(TObject * Sender);
    void __fastcall ComboBox_TCONTypeChange(TObject * Sender);
    void __fastcall CheckBox_GammaTestClick(TObject * Sender);
    void __fastcall RadioButton_PCTCONClick(TObject * Sender);
  private:			// User declarations
    //==========================================================================
    // meter
    //==========================================================================
     bptr < cms::measure::meter::CA210 > ca210;
     bptr < cms::measure::meter::Meter > meter;
     bptr < cms::measure::meter::CA210 > getCA210();
     bptr < cms::lcd::calibrate::ComponentFetcher > fetcher;
    int getInterval();
     bptr < cms::measure::CA210IntensityAnalyzer > ca210Analyzer;
     bptr < cms::measure::IntensityAnalyzerIF > analyzer;
     bptr < cms::measure::MaxMatrixIntensityAnayzer > nativeWhiteAnalyzer;
    //==========================================================================
    //==========================================================================
    // T-CON
    //==========================================================================
    const i2c::AddressingSize getAddressingSize();
     bptr < i2c::TCONParameter > parameter;
     bptr < i2c::TCONControl > control;
    void setBitDepthEnable(bool lut10, bool lut12, bool out6, bool out8, bool out10);
    void setBitDepthChecked(int lutSelect, int outSelect);
    void setFRCAbility();
    //==========================================================================
    void readTCONSetup(String filename, String section);
    void writeTCONCustomSetup();
    void readSetup();
    void writeSetup();
    void readTCONSections();
    //bptr < TStringList > tconSections;
  public:			// User declarations
    //==========================================================================
    // meter
    //==========================================================================
    void setAnalyzerToTargetChannel();
    void setAnalyzerToSourceChannel();
    bool isCA210Analyzer();
    const bool linkCA210;
    const bool newFunction;
     bptr < cms::measure::MeterMeasurement > mm;
    void setMeterMeasurementWaitTimes();
     bptr < cms::measure::IntensityAnalyzerIF > getAnalyzer();
     bptr < cms::measure::MaxMatrixIntensityAnayzer > getNativeWhiteAnalyzer();
    void setDummyMeterFilename(const std::string & filename);
    void setDummyMeterFile(bptr < cms::colorformat::DGLutFile > dglutFile);
    void resetDummyMeter();
    void setAnalyzerNull();
     bptr < cms::lcd::calibrate::ComponentFetcher > getComponentFetcher();
    void disconnectMeter();
    void connectMeter();
    void initCA210Meter();
    //==========================================================================

    //==========================================================================
    // T-CON
    //==========================================================================
     bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
     bptr < i2c::TCONControl > getTCONControl();
    //==========================================================================
    __fastcall TMainForm(TComponent * Owner);


};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
