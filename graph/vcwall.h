#if !defined(AFX_VCWALL_H__D1C23717_D408_41A2_95EF_1D700AF40B91__INCLUDED_)
#define AFX_VCWALL_H__D1C23717_D408_41A2_95EF_1D700AF40B91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CVcBrush;
class CVcPen;

/////////////////////////////////////////////////////////////////////////////
// CVcWall wrapper class

class CVcWall : public COleDispatchDriver
{
public:
	CVcWall() {}		// Calls COleDispatchDriver default constructor
	CVcWall(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcWall(const CVcWall& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	float GetWidth();
	void SetWidth(float newValue);
	CVcBrush GetBrush();
	CVcPen GetPen();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VCWALL_H__D1C23717_D408_41A2_95EF_1D700AF40B91__INCLUDED_)
