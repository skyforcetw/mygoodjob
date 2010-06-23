//---------------------------------------------------------------------------

#ifndef TMeasureWindowH
#define TMeasureWindowH
//---------------------------------------------------------------------------
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//�����ؤ��Y���
//#include <cms/measure/MeterMeasurement.h>
//---------------------------------------------------------------------------
/*
 �n���n��TCON Control�Ԩ�measure window��?
 1.��
 �o��TCON�}���N�n�]�bmeasure window
 setRGB���ɭԴN��measure windows�ھ�tcon�}���ӨM�w�e�ƻ�rgb
 �M���d�Ikey press���ɭԤ]�i�H�M�w�n����������٬Ogamma test function off��

 2.����
 �n���~������ӨM�w�O�n����measure windows�٬O��������tcon control
 �o�ӥ~������q�`�N�Ometer measurement(mm), �p�Gmm�S���S��tcon control���ݨD.
 ���ܴN��tcon control�浹measure window

 final: �̫�Mĳ��
 */
class TMeasureWindow:public TForm {
    __published:		// IDE-managed Components
    TButton * Button1;
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
  private:			// User declarations
     bool tconinput;
     bptr < i2c::TCONControl > tconcontrol;
     std::vector < bptr < cms::util::WindowListener > >listenerVector;
     std::vector < bwptr < cms::util::WindowListener > >listenerVector2;
  public:			// User declarations
     __fastcall TMeasureWindow(TComponent * Owner);
    void setRGB(int r, int g, int b);
    void setRGB(RGB_ptr rgb);
    void setTCONControl(bptr < i2c::TCONControl > tconcontrl);
    void setTCONControlOff();
    void setVisible(bool visible);
    void addWindowListener(bptr < cms::util::WindowListener > listener);
};
//---------------------------------------------------------------------------
extern PACKAGE TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
#endif

