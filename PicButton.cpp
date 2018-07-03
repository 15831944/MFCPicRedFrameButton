// PicButton.cpp : 实现文件
//

#include "stdafx.h"
#include "ButtonArrow.h"
#include "PicButton.h"


// CPicButton

IMPLEMENT_DYNAMIC(CPicButton, CButton)

CPicButton::CPicButton()
    :m_bIsMouse(FALSE),m_bIsPressed(FALSE)
{

}

CPicButton::~CPicButton()
{
	DeleteObject(m_bitmap);
}


BEGIN_MESSAGE_MAP(CPicButton, CButton)
	
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CPicButton 消息处理程序



void CPicButton::SetBit(CString strBitPath)
{
	if ( !PathFileExistsW(strBitPath) )
		return;
	//显示图片函数LoadImage  根据位图（或图片）的全路径名TotalName加载图片  
    m_hBitmap = (HBITMAP)LoadImage(NULL,strBitPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);

	// 之前在类中定义了一个CBitmap 类的对象m_bitmap，
    if( m_bitmap.m_hObject )
    {
        m_bitmap.Detach();            //m_bitmap为创建的位图对象
    }
    m_bitmap.Attach(m_hBitmap);   // 让位图对象m_bitmap 和我们加载的位图相关联（加载进来的位图只要提供一个位图句柄就可以）

	 //定义一个位图结构体，将图片信息保存在位图结构体中
    m_bitmap.GetBitmap(&m_sbitmap);      
}



void CPicButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	

	//BOOL m_bIsPressed = (lpDrawItemStruct->itemState & ODS_SELECTED);
	
	// TODO:  添加您的代码以绘制指定项
	CRect rc = lpDrawItemStruct->rcItem;
	//this->GetWindowRect(&rc);
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	
	
    

        


	CDC dcbmp;
	dcbmp.CreateCompatibleDC(&dc);

    CBitmap *pbmpOld = NULL;
    dcbmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境

	
	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(rc.left+6,rc.top+6,rc.Width()-12,rc.Height()-12,&dcbmp,0,0,m_sbitmap.bmWidth,m_sbitmap.bmHeight,SRCCOPY);

	dcbmp.SelectObject(pbmpOld);
	if ( !m_bIsPressed )
	{
	    dc.Draw3dRect(rc,::GetSysColor(COLOR_BTNHILIGHT),::GetSysColor(COLOR_BTNSHADOW));
	}
	else
		dc.Draw3dRect(rc,::GetSysColor(COLOR_BTNSHADOW),::GetSysColor(COLOR_BTNHILIGHT));
	
	if ( m_bIsMouse && !m_bIsPressed )
	{
		CPen p(PS_SOLID,6,RGB(255, 0, 0));
		dc.SelectObject(p);
		dc.MoveTo(0,0);
		dc.LineTo(0,rc.Height());
		dc.LineTo(rc.Width(),rc.Height());
		dc.LineTo(rc.Width(),0);
		dc.LineTo(0,0);
	}
	//dcbmp.Detach();
	dc.Detach();

	//DeleteObject(m_bitmap);
	DeleteDC(dcbmp);
	DeleteDC(dc);
	//CButton::DrawItem(lpDrawItemStruct);
}


void CPicButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsMouse = TRUE;
	Invalidate();
	CButton::OnMouseHover(nFlags, point);
}


void CPicButton::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsMouse = FALSE;
	Invalidate();
	CButton::OnMouseLeave();
}


void CPicButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if(!m_bIsMouse)
	//{
	TRACKMOUSEEVENT csTME;
	csTME.cbSize = sizeof(csTME);
	csTME.dwFlags = m_bIsMouse? TME_LEAVE:TME_HOVER;
	csTME.hwndTrack = m_hWnd;
	csTME.dwHoverTime=HOVER_DEFAULT;
	::_TrackMouseEvent(&csTME);
	//m_bIsMouse = !m_bIsMouse;
	Invalidate();
	//}
	CButton::OnMouseMove(nFlags, point);
}


void CPicButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsPressed = TRUE;
	this->Invalidate();
	CButton::OnLButtonDown(nFlags, point);
}


void CPicButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_bIsPressed = FALSE;
	this->Invalidate();
	CButton::OnLButtonUp(nFlags, point);
}
