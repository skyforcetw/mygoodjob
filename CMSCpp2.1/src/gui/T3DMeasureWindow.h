//---------------------------------------------------------------------------

#ifndef T3DMeasureWindowH
#define T3DMeasureWindowH
//---------------------------------------------------------------------------
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//�����ؤ��Y���

//---------------------------------------------------------------------------
class TThreeDMeasureWindow:public TForm {
    __published:		// IDE-managed Components
    TPanel * Panel1;
    TPanel *Panel2;
    TButton *Button1;
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall FormPaint(TObject * Sender);
  private:			// User declarations
  public:			// User declarations
     __fastcall TThreeDMeasureWindow(TComponent * Owner);
    void setLeftRGB(int r, int g, int b);
    void setRightRGB(int r, int g, int b);
    void setLeftRGB(RGB_ptr rgb);
    void setRightRGB(RGB_ptr rgb);
};
//---------------------------------------------------------------------------
extern PACKAGE TThreeDMeasureWindow *ThreeDMeasureWindow;
//---------------------------------------------------------------------------
#endif
