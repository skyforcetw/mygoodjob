//---------------------------------------------------------------------------

#ifndef TTestFormH
#define TTestFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "colorpicker.h"
//---------------------------------------------------------------------------
class TTestForm2 : public TForm
{
__published:	// IDE-managed Components
        TColorPickerFrame *TColorPickerFrame1;
private:	// User declarations
public:		// User declarations
        __fastcall TTestForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTestForm2 *TestForm2;
//---------------------------------------------------------------------------
#endif
