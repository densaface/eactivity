#if !defined(AFX_VCBACKDROP_H__E85524FF_EEA0_4432_9D6F_B78AB262C4BC__INCLUDED_)
#define AFX_VCBACKDROP_H__E85524FF_EEA0_4432_9D6F_B78AB262C4BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcShadow;
class CVcFrame;
class CVcFill;

/////////////////////////////////////////////////////////////////////////////
// CVcBackdrop wrapper class

class CVcBackdrop : public COleDispatchDriver
{
public:
	CVcBackdrop() {}		// Calls COleDispatchDriver default constructor
	CVcBackdrop(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcBackdrop(const CVcBackdrop& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CVcShadow GetShadow();
	CVcFrame GetFrame();
	CVcFill GetFill();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCBACKDROP_H__E85524FF_EEA0_4432_9D6F_B78AB262C4BC__INCLUDED_)
