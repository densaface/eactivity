// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "../stdafx.h"
#include "vcseries.h"

// Dispatch interfaces referenced by this interface
#include "VcPen.h"
#include "VcSeriesPosition.h"
#include "VcSeriesMarker.h"
#include "VcStatLine.h"
#include "VcDataPoints.h"


/////////////////////////////////////////////////////////////////////////////
// CVcSeries properties

/////////////////////////////////////////////////////////////////////////////
// CVcSeries operations

BOOL CVcSeries::GetSecondaryAxis()
{
	BOOL result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVcSeries::SetSecondaryAxis(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CVcSeries::GetSeriesType()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CVcSeries::SetSeriesType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CVcPen CVcSeries::GetGuideLinePen()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcPen(pDispatch);
}

BOOL CVcSeries::GetShowLine()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CVcSeries::SetShowLine(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CVcPen CVcSeries::GetPen()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcPen(pDispatch);
}

CVcSeriesPosition CVcSeries::GetPosition()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcSeriesPosition(pDispatch);
}

CVcSeriesMarker CVcSeries::GetSeriesMarker()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcSeriesMarker(pDispatch);
}

CVcStatLine CVcSeries::GetStatLine()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcStatLine(pDispatch);
}

CVcDataPoints CVcSeries::GetDataPoints()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CVcDataPoints(pDispatch);
}

CString CVcSeries::GetLegendText()
{
	CString result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CVcSeries::SetLegendText(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void CVcSeries::Select()
{
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CVcSeries::GetShowGuideLine(long axisID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		axisID);
	return result;
}

void CVcSeries::SetShowGuideLine(long axisID, BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 axisID, bNewValue);
}

long CVcSeries::GetTypeByChartType(long chartType)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		chartType);
	return result;
}
