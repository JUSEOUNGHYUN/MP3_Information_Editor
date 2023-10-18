
// MFC_MP3_INFODlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_MP3_INFO.h"
#include "MFC_MP3_INFODlg.h"
#include "afxdialogex.h"
#include "mp3_metadata_parsing.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCMP3INFODlg 대화 상자



CMFCMP3INFODlg::CMFCMP3INFODlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_MP3_INFO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMP3INFODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MP3_IMAGE, m_mp3_image_draw);
}

BEGIN_MESSAGE_MAP(CMFCMP3INFODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MP3_MUSIC_READ, &CMFCMP3INFODlg::OnBnClickedMp3MusicRead)
	ON_STN_CLICKED(IDC_MP3_IMAGE, &CMFCMP3INFODlg::OnStnClickedMp3Image)
END_MESSAGE_MAP()


// CMFCMP3INFODlg 메시지 처리기

BOOL CMFCMP3INFODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 동적 할당 NULL로 초기화
	apic_image = NULL;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCMP3INFODlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCMP3INFODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCMP3INFODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

wstring CMFCMP3INFODlg::mbstowstr(const char* buffer, int size)
{
	char* temp = (char*)malloc(size + 1);
	memset(temp, 0, size + 1);
	memcpy(temp, buffer, size);

	int dest_size = (size + 1) * sizeof(wchar_t);
	wchar_t* destBuffer = (wchar_t*)malloc(dest_size);
	memset(destBuffer, 0, dest_size);
	mbstowcs(destBuffer, temp, size);

	wstring result(destBuffer);

	free(destBuffer);
	free(temp);

	return result;
}


wstring CMFCMP3INFODlg::ConvertToText(const char* buffer, int size, CharSet enc)
{
	wstring result;

	switch (enc) {
	case UTF_8:
		result.assign((wchar_t*)buffer, size);
		break;
	case UCS_2:
		result.assign((wchar_t*)buffer, size);
		break;
	case ISO_8859_1: default:
		result.assign(mbstowstr(buffer, size));
		break;
	}

	return result;
}


void CMFCMP3INFODlg::OnBnClickedMp3MusicRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TCHAR fileFilter[] = _T("mp3(*.mp3)|*.mp3|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, fileFilter);


	if (dlg.DoModal() == IDOK)
	{
		m_strPathName = dlg.GetPathName();
		FILE* fp;
		fp = fopen((CStringA)m_strPathName, "rb");

		fread(audioheader, sizeof(audioheader), 1, fp);

		// TIT2 위치 구하기 == TITLE
		int cnt_tit2 = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'I' && audioheader[i + 2] == 'T' && audioheader[i + 3] == '2') {
				find_TIT2 = i;
				cnt_tit2++;
			}
		}

		if (cnt_tit2 == 1) {
			fseek(fp, find_TIT2, SEEK_SET);

			// TIT2
			fread(&tit2, sizeof(tit2), 1, fp);
			int titleLength = 0;
			for (int i = 0; i < sizeof(tit2.TIT2SIZE); i++) {
				titleLength = tit2.TIT2SIZE[3];
			}

			// TITLE
			fread(&title, titleLength, 1, fp);
			CString CstrTitle;
			std::string strTitle;
			wstring str;
			//char testText[20] = { 0xFF, 0xFE, 0xF4, 0xBC, 0xE0, 0xAC, 0xF6, 0xC2, 0xC8, 0xC5, 0xB4, 0xC5 };

			for (int i = 0; i < titleLength; i++) {
				strTitle = title.TITLE[i];
				str += ConvertToText(strTitle.c_str(), titleLength, UTF_8);
			}
			SetDlgItemText(IDC_MP3_TITLE, str.c_str());
		} // IDC_MP3_TITLE

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// TPE1 위치 구하기 == ARTIST
		int cnt_tpe1 = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'P' && audioheader[i + 2] == 'E' && audioheader[i + 3] == '1') {
				find_TPE1 = i;
				cnt_tpe1++;
			}
		}

		if (cnt_tpe1 == 1) {
			// TPE1 위치로 이동
			fseek(fp, find_TPE1, SEEK_SET);

			// TPE1
			fread(&tpe1, sizeof(tpe1), 1, fp);
			int artistLength = 0;
			for (int i = 0; i < sizeof(tpe1.TPE1SIZE); i++) {
				artistLength = tpe1.TPE1SIZE[3];
			}

			// ARTIST
			fread(&artist, artistLength, 1, fp);
			CString CstrArtist;
			std::string strArtist;
			for (int i = 3; i < artistLength; i++) {
				strArtist = artist.ARTIST[i];
				CstrArtist += CA2CT(strArtist.c_str());
			}
			SetDlgItemTextW(IDC_MP3_ARTIST, CstrArtist);
		}

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// TALB 위치 구하기 == ALBUM
		int cnt_talb = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'A' && audioheader[i + 2] == 'L' && audioheader[i + 3] == 'B') {
				find_TALB = i;
				cnt_talb++;
			}
		}
		if (cnt_talb == 1) {
			// TALB 위치로 이동
			fseek(fp, find_TALB, SEEK_SET);

			// TALB
			fread(&talb, sizeof(talb), 1, fp);
			int albumLength = 0;
			for (int i = 0; i < sizeof(talb.TALBSIZE); i++) {
				albumLength = talb.TALBSIZE[3];
			}

			// ALBUM
			fread(&album, albumLength, 1, fp);
			CString CstrAlbum;
			std::string strAlbum;
			for (int i = 3; i < albumLength; i++) {
				strAlbum = album.ALBUM[i];
				CstrAlbum += CA2CT(strAlbum.c_str());
			}
			// strTemp = CA2CT(strAlbum.c_str());
			SetDlgItemTextW(IDC_MP3_ALBUM, CstrAlbum);
		}

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// TYER 위치 구하기
		int cnt_year = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'Y' && audioheader[i + 2] == 'E' && audioheader[i + 3] == 'R') {
				find_TYER = i;
				cnt_year++;
			}
		}
		if (cnt_year == 1) {
			// TYER 위치로 이동
			fseek(fp, find_TYER, SEEK_SET);

			// TYER
			fread(&tyer, sizeof(tyer), 1, fp);
			int yearLength = 0;
			for (int i = 0; i < sizeof(tyer.TYERSIZE); i++) {
				yearLength = tyer.TYERSIZE[3];
			}

			// YEAR
			fread(&year, yearLength, 1, fp);
			CString CstrYear;
			std::string strYear;
			for (int i = 0; i < yearLength; i++) {
				strYear = year.YEAR[i];
				CstrYear += CA2CT(strYear.c_str());
			}
			SetDlgItemTextW(IDC_MP3_YEAR, CstrYear);
		}

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// TRCK 위치 구하기
		int cnt_track = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'R' && audioheader[i + 2] == 'C' && audioheader[i + 3] == 'K') {
				find_TRCK = i;
				cnt_track++;
			}
		}

		if (cnt_track == 1) {
			fseek(fp, find_TRCK, SEEK_SET);

			// TRCK
			fread(&trck, sizeof(trck), 1, fp);
			int trackLength = 0;
			for (int i = 0; i < sizeof(trck.TRCKSIZE); i++) {
				trackLength = trck.TRCKSIZE[3];
			}

			// TRACK
			fread(&track, trackLength, 1, fp);
			CString CstrTrack;
			std::string strTrack;
			for (int i = 0; i < trackLength; i++) {
				strTrack = track.TRACK[i];
				CstrTrack += CA2CT(strTrack.c_str());
			}
			SetDlgItemTextW(IDC_MP3_TRACK, CstrTrack);
		}

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// TCON 위치 구하기
		int cnt_tcon = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'C' && audioheader[i + 2] == 'O' && audioheader[i + 3] == 'N') {
				find_TCON = i;
				cnt_tcon++;
			}
		}

		if (cnt_tcon == 1) {
			fseek(fp, find_TCON, SEEK_SET);

			// TCON
			fread(&tcon, sizeof(tcon), 1, fp);
			int genreLength = 0;
			for (int i = 0; i < sizeof(tcon.TCONSIZE); i++) {
				genreLength = tcon.TCONSIZE[3];
			}

			// GENRE
			fread(&genre, genreLength, 1, fp);
			CString CstrGenre;
			std::string strGenre;
			for (int i = 3; i < genreLength; i++) {
				strGenre = genre.GENRE[i];
				CstrGenre += CA2CT(strGenre.c_str());
			}
			SetDlgItemTextW(IDC_MP3_GENRE, CstrGenre);
		}

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);
		
		// COMM 위치 구하기 == COMMENT
		int cnt_comm = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'C' && audioheader[i + 1] == 'O' && audioheader[i + 2] == 'M' && audioheader[i + 3] == 'M') {
				find_COMM = i;
				cnt_comm++;
			}
		}
		if (cnt_comm == 1) {
			// COMM 위치로 이동
			fseek(fp, find_COMM, SEEK_SET);

			// COMM
			fread(&comm, sizeof(comm), 1, fp);
			int commentLenght = 0;
			for (int i = 0; i < sizeof(comm.COMMSIZE); i++) {
				commentLenght = comm.COMMSIZE[3];
			}

			// COMMENT
			fread(&comment, commentLenght, 1, fp);
			CString CstrComment;
			std::string strComment;
			for (int i = 0; i < commentLenght; i++) {
				strComment = comment.COMMENT[i];
				CstrComment += CA2CT(strComment.c_str());
			}
			SetDlgItemTextW(IDC_MP3_COMMENT, CstrComment);
		}

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// Directory
		SetDlgItemTextW(IDC_MP3_DIRECTORY, m_strPathName);

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// TPE2 위치 구하기
		int cnt_tpe2 = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'P' && audioheader[i + 2] == 'E' && audioheader[i + 3] == '2') {
				find_TPE2 = i;
				cnt_tpe2++;
			}
		}

		if (cnt_tpe2 == 1) {
			// TPE2 위치로 이동
			fseek(fp, find_TPE2, SEEK_SET);

			// TPE2
			fread(&tpe2, sizeof(tpe2), 1, fp);
			int albumaristLength = 0;
			for (int i = 0; i < sizeof(tpe2.TPE2SIZE); i++) {
				albumaristLength = tpe2.TPE2SIZE[3];
			}

			// ALBUMARTIST
			fread(&albumartist, albumaristLength, 1, fp);
			CString CstrAlbumArtist;
			std::string strAlbumArtist;
			for (int i = 3; i < albumaristLength; i++) {
				strAlbumArtist = albumartist.ALBUMARTIST[i];
				CstrAlbumArtist += CA2CT(strAlbumArtist.c_str());
			}
			SetDlgItemTextW(IDC_MP3_ALBUM_ARTIST, CstrAlbumArtist);
		}

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// TCOM 위치 구하기
		int cnt_tcom = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'C' && audioheader[i + 2] == 'O' && audioheader[i + 3] == 'M') {
				find_TCOM = i;
				cnt_tcom++;
			}
		}
		//std::cout << cnt << "\n";
		if (cnt_tcom == 1) {
			// TCOM 위치로 이동
			fseek(fp, find_TCOM, SEEK_SET);

			// TCOM
			fread(&tcom, sizeof(tcom), 1, fp);
			int composerLenght = 0;
			for (int i = 0; i < sizeof(tcom.TCOMSIZE); i++) {
				composerLenght = tcom.TCOMSIZE[3];
			}

			// COMPOSER
			fread(&composer, composerLenght, 1, fp);
			CString CstrComposer;
			std::string strComposer;
			for (int i = 0; i < composerLenght; i++) {
				strComposer = composer.COMPOSER[i];
				CstrComposer += CA2CT(strComposer.c_str());
			}
			SetDlgItemTextW(IDC_MP3_COMPOSER, CstrComposer);
		}

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// TPOS 위치 구하기
		int cnt_tpos = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'T' && audioheader[i + 1] == 'P' && audioheader[i + 2] == 'O' && audioheader[i + 3] == 'S') {
				find_TPOS = i;
				cnt_tpos++;
			}
		}

		if (cnt_tpos == 1) {
			fseek(fp, find_TPOS, SEEK_SET);

			// TPOS
			fread(&tpos, sizeof(tpos), 1, fp);
			int discnumberLength = 0;
			for (int i = 0; i < sizeof(tpos.TPOSSIZE); i++) {
				discnumberLength = tpos.TPOSSIZE[3];
			}

			// DISCNUMBER
			fread(&discnumber, discnumberLength, 1, fp);
			CString CstrDiscnumber;
			std::string strDiscnumber;
			for (int i = 0; i < discnumberLength; i++) {
				strDiscnumber = discnumber.DISCNUMBER[i];
				CstrDiscnumber += CA2CT(strDiscnumber.c_str());
			}
			SetDlgItemTextW(IDC_DISCNUMBER, CstrDiscnumber);
		}
		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);


		// 파일 형식 바꿀 문자열
		std::string RstrPathName = std::string(CT2CA(m_strPathName));

		// 파일 포인터 다시 처음으로 원위치
		fseek(fp, 0, SEEK_SET);

		// APIC 단어 찾기
		int find_APIC = 0;
		for (int i = 0; i < sizeof(audioheader); i++) {
			if (audioheader[i] == 'A' && audioheader[i + 1] == 'P' && audioheader[i + 2] == 'I' && audioheader[i + 3] == 'C') {
				// APIC라는 단어가 있으면 그 위치 반환
				find_APIC = i;
			}
		}

		// APIC 단어가 있는 위치로 이동
		fseek(fp, find_APIC, SEEK_SET);

		// APIC SIZE를 알기 위한 fread
		fread(&apic, sizeof(apic), 1, fp);

		// 16진수로 되어있는 문자를 일단 integer로 바꾼다.
		int apicIndex = 0;

		// 16진수 문자들을 합칠 문자열
		std::string strApic;

		// APIC Header에 있는 SIZE로 APIC IMAGE 길이 알기
		for (int i = 0; i < sizeof(apic.APICSIZE); i++) {
			apicIndex = apic.APICSIZE[i];
			char hexadecimal[20] = { 0, };
			int position = 0;
			while (1) {
				int mod = apicIndex % 16;
				if (mod < 10) {
					hexadecimal[position] = 48 + mod;
				}
				else {
					hexadecimal[position] = 65 + (mod - 10);
				}
				apicIndex = apicIndex / 16;
				position++;
				if (apicIndex == 0)
					break;
			}
			for (int i = position - 1; i >= 0; i--) {
				strApic += hexadecimal[i];
			}
		}

		int APIC_IMAGE_SIZE = 0;
		APIC_IMAGE_SIZE = strtol(strApic.c_str(), NULL, 16);
		int real_apic_image_size = APIC_IMAGE_SIZE - 14;

		fread(&fileformat, sizeof(fileformat), 1, fp);
		std::string strFileformat;
		for (int i = 7; i < sizeof(fileformat.FILEFOMAT); i++) {
			strFileformat += fileformat.FILEFOMAT[i];
		}

		int pos = RstrPathName.find('.');
		std::string first = RstrPathName.substr(0, pos);

		for (int i = 0; i < RstrPathName.length(); i++) {
			if (RstrPathName[i] == '.') {
				RstrPathName.erase(i + 1);
			}
		}

		std::string WstrPathName = RstrPathName + strFileformat;
		m_JstrPathname = CA2CT(WstrPathName.c_str());

		// APIC 단어가 있는 위치로 이동
		fseek(fp, find_APIC, SEEK_SET);

		// APIC SIZE를 알기 위한 fread
		fread(&apic, sizeof(apic), 1, fp);

		// 파일 Write
		FILE* wfp = fopen((CStringA)m_JstrPathname, "wb");

		// APIC_IMAGE_SIZE에 대한 동적 할당
		unsigned char* apic_image = /*&ch[0]*/ NULL;

		if (apic_image != NULL) {
			delete apic_image;
		}

		// APIC_IMAGE_SIZE 동적 할당
		apic_image = new unsigned char[real_apic_image_size];
		fseek(fp, 14, SEEK_CUR);

		fread(apic_image, real_apic_image_size, 1, fp);
		fwrite(apic_image, real_apic_image_size, 1, wfp);

		fclose(fp);
		fclose(wfp);

		CRect rect;
		m_mp3_image_draw.GetWindowRect(rect);
		CDC* dc;
		dc = m_mp3_image_draw.GetDC();
		CImage image;
		image.Load(m_JstrPathname);

		image.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);
		ReleaseDC(dc);
		

	}
}

void CMFCMP3INFODlg::OnStnClickedMp3Image()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
