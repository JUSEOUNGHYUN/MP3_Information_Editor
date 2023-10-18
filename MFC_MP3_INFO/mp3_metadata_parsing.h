#pragma once
#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <Windows.h>
#include <tchar.h>

// TALB == ALBUM
// TPE1 == ARTIST
// TPE2 == ALBUMARTIST
// TPOS == DISCNUMBER
// TCON == GENRE
// TIT2	== TITLE
// TRCK == TRACK
// TYER == YEAR
// COMM == COMMNET
// TCOM == COMPOSER
// APIC == MP3IMAGEDATA

// TALB
typedef struct MP3TALB {
	char	TALB[4];
	char	TALBSIZE[4];
	char	TALBFLAG[2];
}MP3TALB;

// ALBUM
typedef struct MP3ALBUM {
	char	ALBUM[30];
}MP3ALBUM;

// TPE1
typedef struct MP3TPE1 {
	char	TPE1[4];
	char	TPE1SIZE[4];
	char	TPE1FLAG[2];
}MP3TPE1;

// ARTIST 
typedef struct MP3ARTIST {
	char	ARTIST[30];
}MP3ARTIST;

// TPE2
typedef struct MP3TPE2 {
	char	TPE2[4];
	char	TPE2SIZE[4];
	char	TPE2FLAG[2];
}MP3TPE2;

// ALBUMARTIST
typedef struct MP3ALBUMARTIST {
	char	ALBUMARTIST[30];
}MP3ALBUMARTIST;

// TPOS
typedef struct MP3TPOS {
	char	TPOS[4];
	char	TPOSSIZE[4];
	char	TPOSFLAG[2];
}MP3TPOS;

// DISCNUMBER
typedef struct MP3DISCNUMBER {
	char	DISCNUMBER[10];
}MP3DISCNUMBER;

// TCON
typedef struct MP3TCON {
	char	TCON[4];
	char	TCONSIZE[4];
	char	TCONFLAG[2];
}MP3TCON;

// GENRE
typedef struct MP3GENRE {
	char	GENRE[30];
}MP3GENRE;

// TIT2
typedef struct MP3TIT2 {
	char	TIT2[4];
	char	TIT2SIZE[4];
	char	TIT2FLAG[2];
}MP3TIT2;

// TITLE
typedef struct MP3TITLE {
	char	TITLE[30];
}MP3TITLE;

// TRCK
typedef struct MP3TRCK {
	char	TRCK[4];
	char	TRCKSIZE[4];
	char	TRCKFLAG[2];
}MP3TRCK;

// TRACK
typedef struct MP3TRACK {
	char	TRACK[3];
}MP3TRACK;

// TYER
typedef struct MP3TYER {
	char	TYER[4];
	char	TYERSIZE[4];
	char	TYERFLAG[2];
}MP3TYER;

// YEAR
typedef struct MP3YEAR {
	char	YEAR[10];
}MP3YEAR;

// COMM
typedef struct MP3COMM {
	char	COMM[4];
	char	COMMSIZE[4];
	char	COMMFLAG[2];
}MP3COMM;

// COMMENT
typedef struct MP3COMMENT {
	char	COMMENT[10];
}MP3COMMENT;

// TCOM
typedef struct MP3TCOM {
	char	TCOM[4];
	char	TCOMSIZE[4];
	char	TCOMFLAG[2];
}MP3TCOM;

// COMPOSER	
typedef struct MP3COMPOSER {
	char	COMPOSER[30];
}MP3COMPOSER;

// APIC
typedef struct MP3APIC {
	char	APIC[4];
	char	APICSIZE[4];
	char	APICFLAG[2];
}MP3APIC;

// FILEFORMAT
typedef struct MP3FILEFORMAT {
	char	FILEFOMAT[11];
}MP3FILEFORMAT;

	// Blackswan
	// Butter1
	// 003 IVE (���̺�) - LOVE DIVE
	// 004 NAYEON (TWICE) - POP!
	// 005 ���̶������
	// 006 (����)���̵� - TOMBOY
	// 010 aespa - Girls

char			audioheader[3000]{};
MP3TALB			talb;				// TALB
MP3ALBUM		album;				// ALBUM
MP3TPE1			tpe1;				// TPE1
MP3ARTIST		artist;				// ARTIST
MP3TPE2			tpe2;				// TPE2
MP3ALBUMARTIST	albumartist;		// ALBUMARTIST
MP3TPOS			tpos;				// TPOS
MP3DISCNUMBER	discnumber;			// DISCNUMBER
MP3TCON			tcon;				// TCON
MP3GENRE		genre;				// GENRE
MP3TIT2			tit2;				// TIT2
MP3TITLE		title;				// TITLE
MP3TRCK			trck;				// TRCK
MP3TRACK		track;				// TRACK
MP3TYER			tyer;				// TYER
MP3YEAR			year;				// YEAR
MP3COMM			comm;				// COMM
MP3COMMENT		comment;			// COMMENT
MP3TCOM			tcom;				// TCOM
MP3COMPOSER		composer;			// COMPOSER
MP3APIC			apic;				// APIC
MP3FILEFORMAT	fileformat;			// FILEFORMAT

int find_TALB = 0;
int find_TPE1 = 0;
int find_TPE2 = 0;
int find_TPOS = 0;
int find_TCON = 0;
int find_TIT2 = 0;
int find_TRCK = 0;
int find_TYER = 0;
int find_COMM = 0;
int find_TCOM = 0;
int find_APIC = 0;