// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// C++ TLBWRTR : $Revision:   1.151.1.0.1.27  $
// File generated on 2006/7/11 �U�� 08:47:59 from Type Library described below.

// ************************************************************************  //
// Type Lib: C:\WINDOWS\system32\hwinterface.ocx (1)
// LIBID: {BD6BB71B-5C9A-4FB3-877E-8B513D28B951}
// LCID: 0
// Helpfile: C:\WINDOWS\system32\hwinterface.hlp
// HelpString: hwinterface ActiveX Control module
// DepndLst: 
//   (1) v2.0 stdole, (C:\WINDOWS\system32\Stdole2.tlb)
// ************************************************************************ //
#ifndef   HWINTERFACELib_TLBH
#define   HWINTERFACELib_TLBH

#pragma option push -b -w-inl

#include <utilcls.h>
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0600)
//
// The code generated by the TLIBIMP utility or the Import|TypeLibrary 
// and Import|ActiveX feature of C++Builder rely on specific versions of
// the header file UTILCLS.H found in the INCLUDE\VCL directory. If an 
// older version of the file is detected, you probably need an update/patch.
//
#error "This file requires a newer version of the header UTILCLS.H" \
       "You need to apply an update/patch to your copy of C++Builder"
#endif
#include <olectl.h>
#include <ocidl.h>
#if defined(USING_ATLVCL) || defined(USING_ATL)
#if !defined(__TLB_NO_EVENT_WRAPPERS)
#include <atl/atlmod.h>
#endif
#endif


// *********************************************************************//
// Forward reference of some VCL types (to avoid including STDVCL.HPP)    
// *********************************************************************//
namespace Stdvcl {class IStrings; class IStringsDisp;}
using namespace Stdvcl;
typedef TComInterface<IStrings> IStringsPtr;
typedef TComInterface<IStringsDisp> IStringsDispPtr;

namespace Hwinterfacelib_tlb
{

// *********************************************************************//
// HelpString: hwinterface ActiveX Control module
// Version:    1.0
// *********************************************************************//


// *********************************************************************//
// GUIDS declared in the TypeLibrary. Following prefixes are used:        
//   Type Libraries     : LIBID_xxxx                                      
//   CoClasses          : CLSID_xxxx                                      
//   DISPInterfaces     : DIID_xxxx                                       
//   Non-DISP interfaces: IID_xxxx                                        
// *********************************************************************//
extern __declspec (package) const GUID LIBID_HWINTERFACELib;
extern __declspec (package) const GUID DIID__DHwinterface;
extern __declspec (package) const GUID DIID__DHwinterfaceEvents;
extern __declspec (package) const GUID CLSID_Hwinterface;

// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                    
// *********************************************************************//
interface DECLSPEC_UUID("{39F91450-46FA-41A9-910B-66273D105EBB}") _DHwinterface;
typedef TComInterface<_DHwinterface, &DIID__DHwinterface> _DHwinterfacePtr;

interface DECLSPEC_UUID("{D7A782FE-F757-4C7C-9A29-8CF022760AD6}") _DHwinterfaceEvents;
typedef TComInterface<_DHwinterfaceEvents, &DIID__DHwinterfaceEvents> _DHwinterfaceEventsPtr;


// *********************************************************************//
// Declaration of CoClasses defined in Type Library                       
// (NOTE: Here we map each CoClass to its Default Interface)              
//                                                                        
// The LIBID_OF_ macro(s) map a LIBID_OF_CoClassName to the GUID of this  
// TypeLibrary. It simplifies the updating of macros when CoClass name    
// change.                                                                
// *********************************************************************//
typedef _DHwinterface Hwinterface;
typedef _DHwinterfacePtr HwinterfacePtr;

#define LIBID_OF_Hwinterface (&LIBID_HWINTERFACELib)
// *********************************************************************//
// Interface: _DHwinterface
// Flags:     (4112) Hidden Dispatchable
// GUID:      {39F91450-46FA-41A9-910B-66273D105EBB}
// *********************************************************************//
interface _DHwinterface : public TDispWrapper<IDispatch>
{
  short __fastcall InPort(short Address)
  {
    _TDispID _dispid(/* InPort */ DISPID(1));
    TAutoArgs<1> _args;
    _args[1] = Address /*[VT_I2:0]*/;
    OleFunction(_dispid, _args);
    return _args.GetRetVariant();
  }

  void __fastcall OutPort(short Address, short Data)
  {
    _TDispID _dispid(/* OutPort */ DISPID(2));
    TAutoArgs<2> _args;
    _args[1] = Address /*[VT_I2:0]*/;
    _args[2] = Data /*[VT_I2:0]*/;
    OleProcedure(_dispid, _args);
  }

  void __fastcall AboutBox()
  {
    _TDispID _dispid(/* AboutBox */ DISPID(-552));
    OleProcedure(_dispid);
  }


};
// *********************************************************************//
// Interface: _DHwinterfaceEvents
// Flags:     (4096) Dispatchable
// GUID:      {D7A782FE-F757-4C7C-9A29-8CF022760AD6}
// *********************************************************************//
interface _DHwinterfaceEvents : public TDispWrapper<IDispatch>
{

};
#if !defined(__TLB_NO_INTERFACE_WRAPPERS)
// *********************************************************************//
// DispIntf:  _DHwinterface
// Flags:     (4112) Hidden Dispatchable
// GUID:      {39F91450-46FA-41A9-910B-66273D105EBB}
// *********************************************************************//
template<class T>
class _DHwinterfaceDispT : public TAutoDriver<_DHwinterface>
{
public:
  _DHwinterfaceDispT(){}

  _DHwinterfaceDispT(_DHwinterface *pintf)
  {
    TAutoDriver<_DHwinterface>::Bind(pintf, false);
  }

  _DHwinterfaceDispT(_DHwinterfacePtr pintf)
  {
    TAutoDriver<_DHwinterface>::Bind(pintf, true);
  }

  _DHwinterfaceDispT& operator=(_DHwinterface *pintf)
  {
    TAutoDriver<_DHwinterface>::Bind(pintf, false);
    return *this;
  }

  _DHwinterfaceDispT& operator=(_DHwinterfacePtr pintf)
  {
    TAutoDriver<_DHwinterface>::Bind(pintf, true);
    return *this;
  }

  HRESULT BindDefault()
  {
    return OLECHECK(Bind(CLSID_Hwinterface));
  }

  HRESULT BindRunning()
  {
    return BindToActive(CLSID_Hwinterface);
  }

  short           __fastcall InPort(short Address);
  void            __fastcall OutPort(short Address, short Data);
  void            __fastcall AboutBox();

};
typedef _DHwinterfaceDispT<_DHwinterface> _DHwinterfaceDisp;

// *********************************************************************//
// DispIntf:  _DHwinterfaceEvents
// Flags:     (4096) Dispatchable
// GUID:      {D7A782FE-F757-4C7C-9A29-8CF022760AD6}
// *********************************************************************//
template <class T>
class _DHwinterfaceEventsDispT : public TAutoDriver<_DHwinterfaceEvents>
{
public:
  _DHwinterfaceEventsDispT(){}

  void Attach(LPUNKNOWN punk)
  { m_Dispatch = static_cast<T*>(punk); }


};
typedef _DHwinterfaceEventsDispT<_DHwinterfaceEvents> _DHwinterfaceEventsDisp;

// *********************************************************************//
// DispIntf:  _DHwinterface
// Flags:     (4112) Hidden Dispatchable
// GUID:      {39F91450-46FA-41A9-910B-66273D105EBB}
// *********************************************************************//
template <class T> short __fastcall
_DHwinterfaceDispT<T>::InPort(short Address)
{
  _TDispID _dispid(*this, OLETEXT("InPort"), DISPID(1));
  TAutoArgs<1> _args;
  _args[1] = Address /*[VT_I2:0]*/;
  OleFunction(_dispid, _args);
  return _args.GetRetVariant();
}

template <class T> void __fastcall
_DHwinterfaceDispT<T>::OutPort(short Address, short Data)
{
  _TDispID _dispid(*this, OLETEXT("OutPort"), DISPID(2));
  TAutoArgs<2> _args;
  _args[1] = Address /*[VT_I2:0]*/;
  _args[2] = Data /*[VT_I2:0]*/;
  OleProcedure(_dispid, _args);
}

template <class T> void __fastcall
_DHwinterfaceDispT<T>::AboutBox()
{
  _TDispID _dispid(*this, OLETEXT("AboutBox"), DISPID(-552));
  OleProcedure(_dispid);
}

// *********************************************************************//
// DispIntf:  _DHwinterfaceEvents
// Flags:     (4096) Dispatchable
// GUID:      {D7A782FE-F757-4C7C-9A29-8CF022760AD6}
// *********************************************************************//
#endif  //   __TLB_NO_INTERFACE_WRAPPERS


#if !defined(__TLB_NO_EVENT_WRAPPERS) && defined(USING_ATLVCL)
// *********************************************************************//
// CONNECTIONPOINT/EVENT PROXY
// CoClass         : Hwinterface
// Event Interface : _DHwinterfaceEvents
// *********************************************************************//
template <class T>
class TEvents_Hwinterface : public IConnectionPointImpl<T,
                                                 &DIID__DHwinterfaceEvents,
                                                 CComUnkArray<CONNECTIONPOINT_ARRAY_SIZE> >
 /* Note: if encountering problems with events, please change CComUnkArray to CComDynamicUnkArray in the line above. */
{
public:
protected:
  _DHwinterfaceEventsDisp m_EventIntfObj;
};

#endif  //   __TLB_NO_EVENT_WRAPPERS

};     // namespace Hwinterfacelib_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Hwinterfacelib_tlb;
#endif

#pragma option pop

#endif // HWINTERFACELib_TLBH