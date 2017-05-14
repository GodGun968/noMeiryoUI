/*
noMeiryoUI (C) 2005,2012-2016 Tatsuhiko Shoji
The sources for noMeiryoUI are distributed under the MIT open source license
*/
#include "FontSel.h"
#include "util.h"

#include <algorithm>
#include <functional>


std::vector<struct FontInfo> fontList;
static bool noMeiryoUI = false;
static bool noTahoma = false;

bool operator<(const FontInfo& left, const FontInfo& right)
{
	return (_tcscmp(left.logFont.lfFaceName, right.logFont.lfFaceName) > 0);
}

bool operator>(const FontInfo& left, const FontInfo& right)
{
	return (_tcscmp(left.logFont.lfFaceName, right.logFont.lfFaceName) < 0);
}

/**
 * EnumFontFamiliesEx�̃R�[���o�b�N
 *
 *
 * @param lpelfe �_���I�ȃt�H���g�f�[�^
 * @param lpntme �����I�ȃt�H���g�f�[�^
 * @param FontType �t�H���g�̎��
 * @param lParam �A�v���P�[�V������`�̃f�[�^
 * @return 0:�񋓂𒆎~���� 1:���̃t�H���g��񋓂���B
 */
int CALLBACK EnumFontFamExProc(
  ENUMLOGFONTEX *lpelfe,    // �_���I�ȃt�H���g�f�[�^
  NEWTEXTMETRICEX *lpntme,  // �����I�ȃt�H���g�f�[�^
  DWORD FontType,           // �t�H���g�̎��
  LPARAM lParam             // �A�v���P�[�V������`�̃f�[�^
)
{
	std::vector<int> charset;
	int fonts;
	struct FontInfo fontInfo;

	if (lpelfe->elfLogFont.lfFaceName[0] == _T('@')) {
		// �c�����t�H���g�͔�΂��B
		return 1;
	}
	if (noMeiryoUI) {
		if (!_tcscmp(_T("Meiryo UI"), lpelfe->elfLogFont.lfFaceName)) {
			return 1;
		}
	}

	if (noTahoma) {
		if (!_tcscmp(_T("Tahoma"), lpelfe->elfLogFont.lfFaceName)) {
			return 1;
		}
	}

	fonts = fontList.size();
	for (int i = 0; i < fonts; i++) {
		// �������O�̕����Z�b�g�Ⴂ
		if (!_tcscmp(fontList[i].logFont.lfFaceName, lpelfe->elfLogFont.lfFaceName)) {
			fontList[i].charsetList.push_back(lpelfe->elfLogFont.lfCharSet);
			return 1;
		}
	}

	// ������Ȃ��ꍇ�͒ǉ�����B
	fontInfo.logFont = lpelfe->elfLogFont;
	fontInfo.charsetList.clear();
	fontInfo.charsetList.push_back(lpelfe->elfLogFont.lfCharSet);
	fontList.push_back(fontInfo);

	return 1;
}

/**
 * �t�H���g���擾����B
 */
int getFont()
{
	LOGFONT lf;
	HDC hDC;

	fontList.clear();

	hDC = GetDC(GetDesktopWindow());
	lf.lfFaceName[0] = _T('\0');

	lf.lfCharSet = DEFAULT_CHARSET;

	EnumFontFamiliesEx(hDC,
		&lf,
		(FONTENUMPROC)EnumFontFamExProc,
		(LPARAM)0,
		0);

	std::sort(fontList.begin(), fontList.end(), std::greater<FontInfo>());

	return 0;
}

/**
 * �R���X�g���N�^
 */
FontSel::FontSel(HWND parent, int resource) : BaseDialog(parent, resource)
{
	m_fontNameList = NULL;
	m_fontSizeList = NULL;
	m_ChersetList = NULL;
	m_styleList = NULL;
	m_underline = NULL;
	previousFont = NULL;
}

/**
 * �f�X�g���N�^
 */
FontSel::~FontSel(void)
{
	if (m_fontSizeList != NULL) {
		delete m_fontSizeList;
	}
	if (m_fontNameList != NULL) {
		delete m_fontNameList;
	}
	if (m_ChersetList != NULL) {
		delete m_ChersetList;
	}
	if (m_styleList != NULL) {
		delete m_styleList;
	}
	if (m_underline != NULL) {
		delete m_underline;
	}
}

/**
 * �_�C�A���O����������
 */
INT_PTR FontSel::OnInitDialog()
{
	getFont();
	m_fontNameList = new TwrCombobox(::GetDlgItem(hWnd, IDC_COMBO_NAME));
	m_fontSizeList = new TwrCombobox(::GetDlgItem(hWnd, IDC_COMBO_SIZE));
	m_ChersetList =  new TwrCombobox(::GetDlgItem(hWnd, IDC_COMBO_CHARSET));
	m_styleList =  new TwrCombobox(::GetDlgItem(hWnd, IDC_COMBO_STYLE));
	m_underline = new TwrCheckbox(::GetDlgItem(hWnd, IDC_CHECK_UNDERLINE));
	m_strike = new TwrCheckbox(::GetDlgItem(hWnd, IDC_CHECK_STRIKE));

	int fonts;

	fonts = fontList.size();
	for (int i = 0; i < fonts; i++) {
		m_fontNameList->addItem(fontList[i].logFont.lfFaceName);
	}

	m_fontSizeList->addItem(_T("6"));
	m_fontSizeList->addItem(_T("7"));
	m_fontSizeList->addItem(_T("8"));
	m_fontSizeList->addItem(_T("9"));
	m_fontSizeList->addItem(_T("10"));
	m_fontSizeList->addItem(_T("11"));
	m_fontSizeList->addItem(_T("12"));
	m_fontSizeList->addItem(_T("13"));
	m_fontSizeList->addItem(_T("14"));
	m_fontSizeList->addItem(_T("15"));
	m_fontSizeList->addItem(_T("16"));
	m_fontSizeList->addItem(_T("17"));
	m_fontSizeList->addItem(_T("18"));
	m_fontSizeList->addItem(_T("19"));
	m_fontSizeList->addItem(_T("20"));
	m_fontSizeList->addItem(_T("21"));
	m_fontSizeList->addItem(_T("22"));
	m_fontSizeList->addItem(_T("23"));
	m_fontSizeList->addItem(_T("24"));
	m_fontSizeList->addItem(_T("26"));
	m_fontSizeList->addItem(_T("28"));
	m_fontSizeList->addItem(_T("36"));
	m_fontSizeList->addItem(_T("48"));
	m_fontSizeList->addItem(_T("72"));

	// �I������B
	if (previousFont != NULL) {
		// �t�H���g�T�C�Y
		int count = m_fontSizeList->getCount();
		int point = getFontPointInt(previousFont, this->getHwnd());
		int selection = 0;
		for (int i = 0; i < count; i++) {
			int itemSize = _tstoi(m_fontSizeList->getItem(i).c_str());
			if (point >= itemSize) {
				selection = i;
			}
		}
		if (selection > -1) {
			m_fontSizeList->setSelectedIndex(selection);
		}

		// �t�H���g�t�F�C�X
		for (int i = 0; i < fonts; i++) {
			if (!_tcscmp(fontList[i].logFont.lfFaceName, previousFont->lfFaceName)) {
				m_fontNameList->setSelectedIndex(i);

				// �t�H���g�ɍ����������R�[�h�Z�b�g��ݒ肷��B
				setCharset();
				int charsetCount = fontList[i].charsetList.size();
				for (int j = 0; j < charsetCount; j++) {
					if (fontList[i].charsetList[j] == previousFont->lfCharSet) {
						m_ChersetList->setSelectedIndex(j);
					}
				}

				// �t�H���g�ɍ������X�^�C��(�����E�C�^���b�N)��ݒ肷��B
				setStyle();
				int style = 0;
				// �C�^���b�N
				if (previousFont->lfItalic) {
					style |= 1;
				}
				// ����
				if (previousFont->lfWeight > 400) {
					style |= 2;
				}
				m_styleList->setSelectedIndex(style);

				// ����
				if (previousFont->lfUnderline) {
					m_underline->setChecked(true);
				}
				// ��������
				if (previousFont->lfStrikeOut) {
					m_strike->setChecked(true);
				}

				break;
			}
		}
	}

	if (useResource) {
		applyResource();
	}

	return (INT_PTR)FALSE;
}



/**
 * �e����ɑ΂��鏈���̕���
 *
 * @param wParam WPARAM
 * @return 0:���b�Z�[�W�����������B 0�ȊO:���b�Z�[�W���������Ȃ������B
 */
INT_PTR FontSel::OnCommand(WPARAM wParam)
{
	INT_PTR result;

	switch (LOWORD(wParam)) {
		case IDC_COMBO_NAME:
			if (HIWORD(wParam) == CBN_SELCHANGE) {
				setCharset();
				setStyle();
			}
			break;
		case IDOK:
			result = onOK();
			if (result == 0) {
				return result;
			}
	}
	return BaseDialog::OnCommand(wParam);

}

/**
 * ���\�[�X���e���ڂɐݒ肷��B
 */
void FontSel::applyResource()
{
	HDC hDC = GetDC(this->hWnd);

	HFONT newFont = CreateFont(
		-MulDiv(9, GetDeviceCaps(hDC, LOGPIXELSY), 72),
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		_tstoi(langResource[70].c_str()),
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, // CLEARTYPE_QUALITY,
		FIXED_PITCH | FF_MODERN,
		langResource[0].c_str());

	ReleaseDC(this->hWnd, hDC);


	// �A�v���^�C�g��
	setText(langResource[27].c_str());

	setChildText(IDC_STATIC_NAME, langResource[28].c_str());
	setChildFont(IDC_STATIC_NAME, newFont);
	setChildText(IDC_STATIC_STYLE, langResource[29].c_str());
	setChildFont(IDC_STATIC_STYLE, newFont);
	setChildText(IDC_STATIC_SIZE, langResource[30].c_str());
	setChildFont(IDC_STATIC_SIZE, newFont);

	setChildText(IDC_CHECK_UNDERLINE, langResource[31].c_str());
	setChildFont(IDC_CHECK_UNDERLINE, newFont);
	setChildText(IDC_CHECK_STRIKE, langResource[32].c_str());
	setChildFont(IDC_CHECK_STRIKE, newFont);
	setChildText(IDC_STATIC_CHARSET, langResource[33].c_str());
	setChildFont(IDC_STATIC_CHARSET, newFont);

	setChildText(IDOK, langResource[34].c_str());
	setChildFont(IDOK, newFont);
	setChildText(IDCANCEL, langResource[35].c_str());
	setChildFont(IDCANCEL, newFont);

	setChildFont(IDC_COMBO_NAME, newFont);
	setChildFont(IDC_COMBO_STYLE, newFont);
	setChildFont(IDC_COMBO_SIZE, newFont);
	setChildFont(IDC_COMBO_CHARSET, newFont);

}

/**
 * �I�������t�H���g�ɍ����������Z�b�g�̑I������ݒ肵�܂��B
 */
void FontSel::setCharset(void)
{
	int selected = m_fontNameList->getSelectedIndex();
	int initialIndex = 0;	// �����I��

	if (selected > -1) {
		m_ChersetList->clear();
		int charsetCount = fontList[selected].charsetList.size();
		for (int i = 0; i < charsetCount; i++) {
			switch (fontList[selected].charsetList[i]) {
				case ANSI_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[36].c_str());
					} else {
						m_ChersetList->addItem(_T("����"));
					}
					break;
				case BALTIC_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[37].c_str());
					} else {
						m_ChersetList->addItem(_T("�o���g��������"));
					}
					break;
				case CHINESEBIG5_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[38].c_str());
					} else {
						m_ChersetList->addItem(_T("�ɑ̎�"));
					}
					break;
				case DEFAULT_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[39].c_str());
					} else {
						m_ChersetList->addItem(_T("�f�t�H���g����"));
					}
					break;
				case EASTEUROPE_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[40].c_str());
					} else {
						m_ChersetList->addItem(_T("�����[���b�p����"));
					}
					break;
				case GB2312_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[41].c_str());
					} else {
						m_ChersetList->addItem(_T("�ȑ̎�"));
					}
					break;
				case GREEK_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[42].c_str());
					} else {
						m_ChersetList->addItem(_T("�M���V������"));
					}
					break;
				case HANGUL_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[43].c_str());
					} else {
						m_ChersetList->addItem(_T("�؍���"));
					}
					break;
				case MAC_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[44].c_str());
					} else {
						m_ChersetList->addItem(_T("Mac�����Z�b�g"));
					}
					break;
				case OEM_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[45].c_str());
					} else {
						m_ChersetList->addItem(_T("OEM�����Z�b�g"));
					}
					break;
				case RUSSIAN_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[46].c_str());
					} else {
						m_ChersetList->addItem(_T("���V�A��"));
					}
					break;
				case SHIFTJIS_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[47].c_str());
					} else {
						m_ChersetList->addItem(_T("���{��"));
					}
					initialIndex = i;
					break;
				case SYMBOL_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[48].c_str());
					} else {
						m_ChersetList->addItem(_T("�V���{��"));
					}
					break;
				case TURKISH_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[49].c_str());
					} else {
						m_ChersetList->addItem(_T("�g���R��"));
					}
					break;
				case VIETNAMESE_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[50].c_str());
					} else {
						m_ChersetList->addItem(_T("�x�g�i����"));
					}
					break;
				case JOHAB_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[51].c_str());
					} else {
						m_ChersetList->addItem(_T("�؍���(�g���^)"));
					}
					break;
				case ARABIC_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[52].c_str());
					} else {
						m_ChersetList->addItem(_T("�A���r�A��"));
					}
					break;
				case HEBREW_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[53].c_str());
					} else {
						m_ChersetList->addItem(_T("�w�u���C��"));
					}
					break;
				case THAI_CHARSET:
					if (useResource) {
						m_ChersetList->addItem(langResource[54].c_str());
					} else {
						m_ChersetList->addItem(_T("�^�C��"));
					}
					break;
				default:
					m_ChersetList->addItem(_T(""));
					break;
			}
		}
	}
	// �����̌����D�悵�đI������B
	m_ChersetList->setSelectedIndex(initialIndex);
}

/**
 * �I�������t�H���g�ɍ������X�^�C���̑I������ݒ肵�܂��B
 */
void FontSel::setStyle(void)
{
	int selected = m_fontNameList->getSelectedIndex();
/*
	int weight = fontList[selected].logFont.lfWeight;
	TCHAR *p = _T("����̑���");

	if (weight < 200) {
		p = _T("�ɍ�");
	} else if (weight < 300) {
		p = _T("����");
	} else if (weight < 400) {
		p = _T("��");
	} else if (weight < 500) {
		p = _T("�W��");	// Normal
	} else if (weight < 600) {
		p = _T("����");	// Medium
	} else if (weight < 700) {
		p = _T("����");	// Semi Bold
	} else if (weight < 800) {
		p = _T("��");	// Bold
	} else if (weight < 900) {
		p = _T("����");	// Ultra Bold
	} else {
		p = _T("�ɑ�");	// Heavy
	}
*/
	m_styleList->clear();

	tstring styleName;
	if (useResource) {
		styleName = langResource[55].c_str();
	} else {
		styleName = _T("�W��");
	}
	m_styleList->addItem(styleName.c_str());

	// styleName = p;
	if (useResource) {
		styleName = langResource[56].c_str();
	} else {
		styleName = _T("�Α�");
	}
	m_styleList->addItem(styleName.c_str());

	if (useResource) {
		styleName = langResource[57].c_str();
	} else {
		styleName = _T("����");
	}
	m_styleList->addItem(styleName.c_str());

	if (useResource) {
		styleName = langResource[58].c_str();
	} else {
		styleName = _T("���� �Α�");

	}
	m_styleList->addItem(styleName.c_str());

	m_styleList->setSelectedIndex(0);
}

/**
 * OK�{�^���������������̓���
 */
INT_PTR FontSel::onOK(void)
{
	int selectedFontIndex = m_fontNameList->getSelectedIndex();
	int selectedCharset = m_ChersetList->getSelectedIndex();
	int selectedStyle = m_styleList->getSelectedIndex();

	tstring error;
	tstring message;

	if (useResource) {
		error = langResource[63].c_str();
	} else {
		error = _T("�G���[");
	}

	if (selectedFontIndex < 0) {
		if (useResource) {
			message = langResource[65].c_str();
		} else {
			message = _T("�t�H���g��I�����Ă��������B");
		}
		MessageBox(this->hWnd,
			message.c_str(),
			error.c_str(),
			MB_ICONEXCLAMATION | MB_OK);
		return (INT_PTR)0;
	}

	if (selectedStyle < 0) {
		if (useResource) {
			message = langResource[66].c_str();
		} else {
			message = _T("�X�^�C����I�����Ă��������B");
		}
		MessageBox(this->hWnd,
			message.c_str(),
			error.c_str(),
			MB_ICONEXCLAMATION | MB_OK);
		return (INT_PTR)0;
	}

	if (selectedCharset < 0) {
		if (useResource) {
			message = langResource[67].c_str();
		} else {
			message = _T("�����Z�b�g��I�����Ă��������B");
		}
		MessageBox(this->hWnd,
			message.c_str(),
			error.c_str(),
			MB_ICONEXCLAMATION | MB_OK);
		return (INT_PTR)0;
	}

	tstring size = m_fontSizeList->getSelectedText();
	if (size.length() < 1) {
		if (useResource) {
			message = langResource[68].c_str();
		} else {
			message = _T("�����Z�b�g��I�����Ă��������B");
		}
		MessageBox(this->hWnd,
			message.c_str(),
			error.c_str(),
			MB_ICONEXCLAMATION | MB_OK);
		return (INT_PTR)0;
	}

	selectedFont = fontList[selectedFontIndex].logFont;
	selectedFont.lfCharSet = fontList[selectedFontIndex].charsetList[selectedCharset];
	if (selectedStyle > 1) {
		if (selectedFont.lfWeight < 600) {
			selectedFont.lfWeight = FW_BOLD;
		}
	} else {
		selectedFont.lfWeight = FW_NORMAL;
	}
	if ((selectedStyle == 1) || (selectedStyle == 3)) {
		selectedFont.lfItalic = TRUE;
	} else {
		selectedFont.lfItalic = FALSE;
	}

	int point = _tstoi(size.c_str());

	// �T�C�Y�̐ݒ�
	HDC hDC = GetDC(this->hWnd);
	selectedFont.lfHeight = -MulDiv(point, GetDeviceCaps(hDC, LOGPIXELSY), 72);
	selectedFont.lfWidth = 0;
	ReleaseDC(this->hWnd, hDC);

	// Windows 8�݊��̏ꍇ�̓s�N�Z��������v�Z�����|�C���g���w�肵���|�C���g��菬�����ꍇ�A
	// �t�H���g�̍����̃s�N�Z�����̐�Βl�𑝂₷�B
	if (WIN8_SIZE) {
		if (abs(getFontPointInt(&selectedFont, this->getHwnd())) < point) {
			// �s�N�Z�����̓}�C�i�X�Ŏw�肷��̂�1���炵�Đ�Βl�𑝂₷�B
			selectedFont.lfHeight--;
		}
	}

	if (m_underline->isChecked()) {
		selectedFont.lfUnderline = TRUE;
	} else {
		selectedFont.lfUnderline = FALSE;
	}

	if (m_strike->isChecked()) {
		selectedFont.lfStrikeOut = TRUE;
	} else {
		selectedFont.lfStrikeOut = FALSE;
	}

	// ���̑��̓f�t�H���g�ɐݒ肷��B
	selectedFont.lfOutPrecision = 0;
	selectedFont.lfClipPrecision = 0;
	selectedFont.lfQuality = 0;
	// lfPitchAndFamily�̓t�H���g���Ԃ������̂�ݒ肷��B
	// selectedFont.lfPitchAndFamily = 50;

	return (INT_PTR)1;
}

void FontSel::setNoMeiryoUI()
{
	noMeiryoUI = true;
}

void FontSel::setNoTahoma()
{
	noTahoma = true;
}