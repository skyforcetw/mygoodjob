//---------------------------------------------------------------------------

#ifndef TI2CTestFormH
#define TI2CTestFormH
//---------------------------------------------------------------------------
//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//本項目內頭文件
#include <java/lang.h>
//---------------------------------------------------------------------------
class TI2CTestForm:public TForm {
    __published:		// IDE-managed Components
    TButton * Button1;
    TGroupBox *GroupBox1;
    TRadioButton *RadioButton_Single;
    TEdit *Edit_Single;
    TRadioButton *RadioButton_Dual;
    TEdit *Edit_Master;
    TEdit *Edit_Slave;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton_USB;
    TRadioButton *RadioButton_LPT;
    TCheckBox *CheckBox_Connecting;
    TGroupBox *GroupBox3;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TCheckBox *CheckBox1;
    TEdit *Edit_R;
    TEdit *Edit_G;
    TEdit *Edit_B;
    TCheckBox *CheckBox_IndepRGB;
    TGroupBox *GroupBox4;
    TEdit *Edit_GammaTestAddress;
    TEdit *Edit_GammaTestBit;
    TEdit *Edit_TestRGBAdress;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TGroupBox *GroupBox5;
    TEdit *Edit1;
    TEdit *Edit2;
    TButton *Button2;
    TButton *Button3;
    TCheckBox *CheckBox_2ByteAddress;
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall CheckBox_ConnectingClick(TObject * Sender);
    void __fastcall CheckBox1Click(TObject * Sender);
    void __fastcall Edit_RChange(TObject * Sender);
    void __fastcall Edit_GChange(TObject * Sender);
    void __fastcall Edit_BChange(TObject * Sender);
  private:			// User declarations
    //bptr < cms::i2c::i2cControl > i2c;
     bptr < cms::i2c::TCONParameter > parameter;
     bptr < cms::i2c::TCONControl > control;
  public:			// User declarations
     __fastcall TI2CTestForm(TComponent * Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TI2CTestForm *I2CTestForm;
//---------------------------------------------------------------------------
#endif

