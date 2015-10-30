#include "stdafx.h"
#include "AppendHead.h"
//#include "appdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// sVariableCurrentRec::sVariableCurrentRec(char* name_, int type_var_)
// {
// 	name=name_;
// 	type_var=type_var_;
// }
greenroad::greenroad()
{
	numRoad=0;
}
void greenroad::operator = (const greenroad &gr)
{
	numRoad=gr.numRoad;
	par1=gr.par1;
	par2=gr.par2;
	par3=gr.par3;
	par4=gr.par4;
}
LastAct::LastAct()
{
	type=0;
	ind=-1;
	dw_time=0;
	comment="";
}
sSmartControl_tmp::sSmartControl_tmp()
{
	randVetv=0;
	otk_s=15;
	time_search=60;
	ifElse="";

	typeSear.RemoveAll();
	typeSear.Add(0);
	xl.RemoveAll();
	xl.Add(0);
	xr.RemoveAll();
	xr.Add(0);
	yt.RemoveAll();
	yt.Add(0);
	yb.RemoveAll();
	yb.Add(0);

	typeClick.RemoveAll();
	typeClick.Add(0);
	razrPlay=0;
	hideSM=0;
	nodPicRpl.RemoveAll();
	nodPicRpl.Add(0);
	clickx.RemoveAll();
	clickx.Add(0);
	Rx.RemoveAll();
	Rx.Add(0);
	clicky.RemoveAll();
	clicky.Add(0);
	Ry.RemoveAll();
	Ry.Add(0);
	siApps.RemoveAll();
}
void  forKeyAndMouse::operator = (forKeyAndMouse &key)
{
	sKeys=key.sKeys;
	keys.Copy(key.keys);
	updown.Copy(key.updown);
	QueueWait=key.QueueWait;
	dTime.Copy(key.dTime);
}
void  forMousePress::operator = (forMousePress &mous)
{
	lpars.Copy(mous.lpars);
	xx.Copy(mous.xx);
	yy.Copy(mous.yy);
}

void  forKeyPress::operator = (forKeyPress &key)
{
	lpars.Copy(key.lpars);
	KeyLang.Copy(key.KeyLang);
}

void  Act::operator = (LastAct &ac)
{
	UN=ac.un;
	num_nod=ac.num_nod;
	comment=ac.comment;
}

void  Act::operator = (Act &ac)
{
	UN=ac.UN;
	num_nod=ac.num_nod;
	baTypeAct=ac.baTypeAct;
	W.saWindows=ac.W.saWindows;
	KEY=ac.KEY;
	MOUS=ac.MOUS;
	MK=ac.MK;
	ac.COMS.Copy(COMS);
	comment=ac.comment;
}

// void  sObjsForPC::operator = (sObjsForPC &cur)
// {
// 	saOBJs.RemoveAll();
// 	saOBJs.Copy(cur.saOBJs);
// }
// 
void  sSmartControl_tmp::operator = (const sSmartControl_tmp &ac)
{
	ProvPlayAip=ac.ProvPlayAip;
	time_search=ac.time_search;
	otk_s=ac.otk_s;
	if (ac.OBJs.GetSize())
	{
		OBJs.Copy(ac.OBJs);
	}
	saPlayAip.Copy(ac.saPlayAip);
	typeClick.Copy(ac.typeClick);
	typeSear.Copy(ac.typeSear);
	xl.Copy(ac.xl);
	xr.Copy(ac.xr);
	yt.Copy(ac.yt);
	yb.Copy(ac.yb);
	//typeClick=ac.typeClick;
	nodPicRpl.Copy(ac.nodPicRpl);
	clickx.Copy(ac.clickx);
	Rx.Copy(ac.Rx);
	//clickx=ac.clickx;
	clicky.Copy(ac.clicky);
	Ry.Copy(ac.Ry);
//	nodRplNF=ac.nodRplNF;
	razrPlay=ac.razrPlay;
	randVetv=ac.randVetv;
	saApps.Copy(ac.saApps);
	saParComLine.Copy(ac.saParComLine);
	siApps.Copy(ac.siApps);
	saVarsOpers.Copy(ac.saVarsOpers);
	saPixContr.Copy(ac.saPixContr);
	//	CString deb=ac.saPixContr[0];
	//	deb=deb;
}

// void  sSmartControl::operator = (const sSmartControl &ac)
// {
//	ProvPlayAip=ac.ProvPlayAip;
//	time_search=ac.time_search;
//	otk_s=ac.otk_s;
// 	saPlayAip.RemoveAll();
// 	saPlayAip.Copy(ac.saPlayAip);
// 	typeClick.RemoveAll();
// 	typeClick.Copy(ac.typeClick);
// 	typeSear.RemoveAll();
// 	typeSear.Copy(ac.typeSear);
// 	xl.RemoveAll();
// 	xl.Copy(ac.xl);
// 	xr.RemoveAll();
// 	xr.Copy(ac.xr);
// 	yt.RemoveAll();
// 	yt.Copy(ac.yt);
// 	yb.RemoveAll();
// 	yb.Copy(ac.yb);
	//typeClick=ac.typeClick;
// 	nodPicRpl.RemoveAll();
// 	nodPicRpl.Copy(ac.nodPicRpl);
//	clickx.RemoveAll();
//	clickx.Copy(ac.clickx);
//	Rx.RemoveAll();
//	Rx.Copy(ac.Rx);
	//clickx=ac.clickx;
//	clicky.RemoveAll();
//	clicky.Copy(ac.clicky);
//	Ry.RemoveAll();
//	Ry.Copy(ac.Ry);
//	nodRplNF=ac.nodRplNF;
//	razrPlay=ac.razrPlay;
//	randVetv=ac.randVetv;
// 	saApps.RemoveAll();
// 	saApps.Copy(ac.saApps);
// 	siApps.RemoveAll();
// 	siApps.Copy(ac.siApps);
// 	saVarsOpers.RemoveAll();
// 	saVarsOpers.Copy(ac.saVarsOpers);
// 	saPixContr.RemoveAll();
// 	saPixContr.Copy(ac.saPixContr);
//	CString deb=ac.saPixContr[0];
//	deb=deb;
//}
Act::Act(const Act& ac)
{
	baTypeAct=ac.baTypeAct;
	MK.sKeys=ac.MK.sKeys;
	MK.keys.Copy(ac.MK.keys);
	MK.updown.Copy(ac.MK.updown);
	MK.dTime.Copy(ac.MK.dTime);
	MK.QueueWait=ac.MK.QueueWait;

	KEY.lpars.Copy(ac.KEY.lpars);
	KEY.KeyLang.Copy(ac.KEY.KeyLang);

	MOUS.lpars.Copy(ac.MOUS.lpars);
	MOUS.xx.Copy(ac.MOUS.xx);
	MOUS.yy.Copy(ac.MOUS.yy);

	W.saWindows=ac.W.saWindows;
	W.Name_exe=ac.W.Name_exe;
//	W.Slice=ac.W.Slice;
	W.iWaitCol=ac.W.iWaitCol;
	W.Chi=ac.W.Chi;
	W.Mai=ac.W.Mai;
	W.RazrFocus=ac.W.RazrFocus;
//	W.paint=ac.W.paint;
	W.IndAct=ac.W.IndAct;
	comment=ac.comment;
//	SmartContr=ac.SmartContr;
};

// void  Act::operator = (Act  &ac)
// {
// }
bool  ssBGR::operator == (ssBGR  &bgr)
{
	if (r!=bgr.r) 
		return false;
	if (g!=bgr.g) 
		return false;
	if (b!=bgr.b) 
		return false;
	return true;
}
// bool  Act::operator == (SendStruct  *ac)
// {
// 	if (baTypeAct==1)//случай двойного клика в Просмотрщике
// 	if (ac->baTypeAct==1)
// 	if (message==ac->message)
// 		return true;
// 	//if (lpar!=ac.lpar)
// 	//	return false;
// 	if (baTypeAct!=ac->baTypeAct)
// 		return false;
// 	if (wpar!=ac->wpar)
// 		return false;
// 	if (message!=ac->message)
// 		return false;
// 	if (lpar!=ac->lpar)
// 		return false;
	//if (dw_time!=ac->dw_time)
	//	return false;
//	return true;
//}

//для исключения при действии мышью случая двойного нажатия и отжатия
// bool  Act::Wpar( Act &ac)
// {
// 	if (baTypeAct!=1)
// 		return false;
// 	if (ac.baTypeAct!=1)
// 		return false;
// 	//if (wpar>=ac.wpar)
// 	//	return false;
// // 	if (message!=ac.message)
// // 		return false;
// // 	if (lpar!=ac.lpar)
// // 		return false;
// 	//if (time2!=ac.time2)
// 	//	return false;
// //	return true;
// 	return false;
// }

void struPlaList::strucpy(const struPlaList& pl2)
{
	this->begin=pl2.begin;
	this->endStep=pl2.endStep;
	this->iCurPlay=pl2.iCurPlay;
	this->name_pla=pl2.name_pla;
}
// SendStruct::~SendStruct()
// {
// 	delete csMainWindowCapt;
// 	delete csMainWindowClass;
// 	delete csChildWindowCapt;
// 	delete csChildClassName;
// 	delete KeyLang;
// 	delete ierarh;
// }


StructOCR::StructOCR()
{
	filled = FALSE;
	TypeSrc = 1;
	sr_x1 = 0;
	sr_x2 = GetSystemMetrics(SM_CXSCREEN);
	sr_y1 = 0;
	sr_y2 = GetSystemMetrics(SM_CYSCREEN);
	Wait_Text = FALSE;
	sSearch_Text = "";
	SearchTime = 60000;
	typeRecog = -1;
	langOcr = -1;
	sSuccessResult = "";
	sNsuccessResult = "";
	sCaptLogPass = "";
	sFileImage = "";
	sHttpUrl = "";
}