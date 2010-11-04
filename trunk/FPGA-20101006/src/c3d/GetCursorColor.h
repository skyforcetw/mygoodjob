//---------------------------------------------------------------------------

#ifndef GetCursorColorH
#define GetCursorColorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <java/lang.h>
//---------------------------------------------------------------------------

class RGBInfoCallbackIF {
  public:
    virtual void callback(int_array rgbValues) = 0;
};
class TPColorThread1:public TThread {
    typedef struct tagTHREADNAME_INFO {
	DWORD dwType;		// must be 0x1000
	LPCSTR szName;		// pointer to name (in user addr space)
	DWORD dwThreadID;	// thread ID (-1=caller thread)
	DWORD dwFlags;		// reserved for future use, must be zero
    } THREADNAME_INFO;
  private:
    void SetName();
    /*TEdit *Edit_RGB;
       TEdit *Edit_HSV;
       double_array cursorRGBValues; */
    RGBInfoCallbackIF *callback;
  protected:
    void __fastcall Execute();
  public:
     /*__fastcall TPColorThread1(bool CreateSuspended, TEdit * Edit_RGB);

    __fastcall TPColorThread1(bool CreateSuspended, TEdit * Edit_RGB, TEdit * Edit_HSV,
			      double_array cursorRGBValues);*/
     __fastcall TPColorThread1(bool CreateSuspended, RGBInfoCallbackIF * callback);
    //int r, g, b;
};

//---------------------------------------------------------------------------
#endif
