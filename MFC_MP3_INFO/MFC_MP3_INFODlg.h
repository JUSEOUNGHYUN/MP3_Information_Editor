
// MFC_MP3_INFODlg.h: 헤더 파일
//

#pragma warning(disable:4996)

#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <Windows.h>

using namespace std;

class CtestEncodingDlgAutoProxy;

enum CharSet { ISO_8859_1 = 0x00, UCS_2 = 0x01, UTF_16BE = 0x02, UTF_8 = 0x03 };

// CMFCMP3INFODlg 대화 상자
class CMFCMP3INFODlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCMP3INFODlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CString m_strPathName;						// 파일 절대 경로
	CString m_JstrPathname;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_MP3_INFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	static wstring mbstowstr(const char* buffer, int size);
	wstring ConvertToText(const char* buffer, int size, CharSet enc);

	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	unsigned char* apic_image;
	afx_msg void OnBnClickedMp3MusicRead();
	afx_msg void OnStnClickedMp3Image();
	CStatic m_mp3_image_draw;
};
