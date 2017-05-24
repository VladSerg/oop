#ifndef _TEXTEDITORCORE_HPP_
#define _TEXTEDITORCORE_HPP_

#include <vector>
#include <string>
#include "pointer.hpp"
#include "highlighting.hpp"

class TextEditorCore
{
private:
	Pointer pointer;
	Highlighting highlited;
	std::vector<std::string> data;
	
	void HighlightingInvalidator();
	bool IsHighlighted()const;
	bool IsHighlighting()const;
	void SortHighlightingPoints();
	bool PointerInvalidator(Pointer curent)const;

public:
	// ����������� �� ���������(����� ������ ��������).
	TextEditorCore();

	// ����������� �� ���������� �������� ������(������� ����� ����������� ��������).
	TextEditorCore (std::istream & _s);
	
	// ����������� � ���������� ����� �������� ������ ���� ���������.
	TextEditorCore (const TextEditorCore&) = delete;
	void operator = (const TextEditorCore&) = delete;

	// ����������(���� �� ���������).
	//~TextEditorCore ();

	// ------------------------------------- ������ � �������� : -------------------------------------
	// ����� ��� ����������� �������� ��������� �������(����� ������, ����� �������)
	Pointer CurentPointerPosition() const { return pointer; };
	
	// ������ ��� ����������� �� 1 ������� � ����� �� 4 ��������� �����������.
	void MovePointerUp();
	void MovePointerRight();
	void MovePointerDown();
	void MovePointerLeft();

	// ����� ��� ����������� ������� � ������������ �����(���� ������) - ����� ������ ������������.
	void MovePointerTo(int _x, int _y);
	
	// ----------------------------- �������������� ���������� ������ : -----------------------------
	// ������ ��� ������� � �������� ���������� �������. ������ ������ - ������� ��� �������� ��������, ���������������� ������� ����� ������.
	void PushCharAfterPointer(char _ch);
	void DeleteCharBeforePointer();

	// ����� ��� ������� ��������� ������ �� ���� ��������(��������, ���������������� ��������� ����� �������� ������������� �� ������ ������ �������� ������).
	void PushStringAfterPointer(const std::string & _str);
	
	// ����� ��� �������� ����������� ��������� ������.
	void DeleteMarkedPart();
	
	// ������ ��� �������� �� ������ / ����� ������ / ��������� (����������� ��� ������� �� ������� Home / End � Ctrl + Home / End).
	void MovePointerHome() { pointer.y = 0; HighlightingInvalidator(); };
	void MovePointerEnd() {	pointer.y = data[pointer.x].size(); HighlightingInvalidator();};
	void MovePointerCtrlHome() { MovePointerTo(0, 0); HighlightingInvalidator();};
	void MovePointerCtrlEnd() { MovePointerTo(data.size() - 1, data[data.size() - 1].size()); HighlightingInvalidator();};

	// ����� ��� ���������� ����������� ������ � ��������� �������� �����.
	void Save (std::ostream & _s) const;

	// ----------------------------- ������ � ���������� ������ : -----------------------------
	// ����� ������ ��������� ����������� �������� � ������ �����, ��������� ����� ������ ���������.
	void StartMarking();

	// ����� ���������� ��������� ����������� �������� � ������� �����. ������ ��������� ����� ���� ������������� � ����������, ���� ������ �� �����������.
	void StopMarking();

	// ����� ������ ���������.
	void ResetMarking() { highlited.first = { -1,-1 }; highlited.second = { -1,-1 }; };

	// �����, ������������ ������� ���������� �����.
	std::string ReturnMarkedText() const;

	Highlighting ReturnHighlightingPoints() const { return highlited; };

	// ----------------------------- ������ ��� ������ � ������ : -----------------------------
	// �����, ����������� ������ ����� � ����� �� ���������.
	Pointer Find(const std::string & _str, Pointer _curent = {0,0}) const;
	// �����, ������������ ����� �� ��������� � ���������� ��������� �������.
	Pointer FindNext(Pointer _curent, const std::string & _str) const;
	// �����, �������������� ������ ������� ������������ ������� ������ �� ������.
	bool Replace(const std::string & _str, const std::string & _replace);
	// �����, �������������� ������ ���� ����������� �������� ������ �� ������.
	bool ReplaceAll(const std::string & _str, const std::string & _replace);

};

#endif // _TEXTEDITORCORE_HPP_