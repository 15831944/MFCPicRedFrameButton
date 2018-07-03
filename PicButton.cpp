// PicButton.cpp : ʵ���ļ�
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



// CPicButton ��Ϣ�������



void CPicButton::SetBit(CString strBitPath)
{
	if ( !PathFileExistsW(strBitPath) )
		return;
	//��ʾͼƬ����LoadImage  ����λͼ����ͼƬ����ȫ·����TotalName����ͼƬ  
    m_hBitmap = (HBITMAP)LoadImage(NULL,strBitPath,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);

	// ֮ǰ�����ж�����һ��CBitmap ��Ķ���m_bitmap��
    if( m_bitmap.m_hObject )
    {
        m_bitmap.Detach();            //m_bitmapΪ������λͼ����
    }
    m_bitmap.Attach(m_hBitmap);   // ��λͼ����m_bitmap �����Ǽ��ص�λͼ����������ؽ�����λͼֻҪ�ṩһ��λͼ����Ϳ��ԣ�

	 //����һ��λͼ�ṹ�壬��ͼƬ��Ϣ������λͼ�ṹ����
    m_bitmap.GetBitmap(&m_sbitmap);      
}



void CPicButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	

	//BOOL m_bIsPressed = (lpDrawItemStruct->itemState & ODS_SELECTED);
	
	// TODO:  ������Ĵ����Ի���ָ����
	CRect rc = lpDrawItemStruct->rcItem;
	//this->GetWindowRect(&rc);
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	
	
    

        


	CDC dcbmp;
	dcbmp.CreateCompatibleDC(&dc);

    CBitmap *pbmpOld = NULL;
    dcbmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����

	
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsMouse = TRUE;
	Invalidate();
	CButton::OnMouseHover(nFlags, point);
}


void CPicButton::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsMouse = FALSE;
	Invalidate();
	CButton::OnMouseLeave();
}


void CPicButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsPressed = TRUE;
	this->Invalidate();
	CButton::OnLButtonDown(nFlags, point);
}


void CPicButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_bIsPressed = FALSE;
	this->Invalidate();
	CButton::OnLButtonUp(nFlags, point);
}
