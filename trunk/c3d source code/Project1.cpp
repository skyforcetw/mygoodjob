//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\c3d\TC3DForm.cpp", C3DForm1);
USEFORM("src\gui\c3d\TC3D_SimualteForm.cpp", C3DSimualteForm);
USEFORM("src\gui\c3d\TFormInTarget.cpp", FormInTarget);
USEFORM("src\gui\c3d\TEngineering.cpp", EngineerForm);
USEFORM("src\gui\c3d\TMainForm.cpp", MainForm);
USEFORM("src\gui\c3d\THSVStepSimForm.cpp", HSVStepSimForm);
USEFORM("src\gui\frame\TColorPickerFrame.cpp", ColorPickerFrame);	/* TFrame: File Type */
USEFORM("src\gui\c3d\TTestForm.cpp", TestForm2);
USEFORM("src\gui\frame\TColorFrame.cpp", ColorFrame);	/* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try {
	Application->Initialize();
	Application->CreateForm(__classid(TMainForm), &MainForm);
	Application->CreateForm(__classid(TFormInTarget), &FormInTarget);
	Application->CreateForm(__classid(TC3DForm1), &C3DForm1);
	Application->CreateForm(__classid(TC3DSimualteForm), &C3DSimualteForm);

	Application->CreateForm(__classid(TEngineerForm), &EngineerForm);
	Application->CreateForm(__classid(THSVStepSimForm), &HSVStepSimForm);
	Application->CreateForm(__classid(TColorPickerFrame), &ColorPickerFrame);
	Application->CreateForm(__classid(TColorFrame), &ColorFrame);
	Application->Run();
    }
    catch(Exception & exception) {
	Application->ShowException(&exception);
    }
    catch(...) {
	try {
	    throw Exception("");
	}
	catch(Exception & exception) {
	    Application->ShowException(&exception);
	}
    }
    return 0;
}

//---------------------------------------------------------------------------

