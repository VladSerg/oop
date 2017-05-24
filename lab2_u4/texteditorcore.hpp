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
	// Конструктор по умолчанию(новый пустой документ).
	TextEditorCore();

	// Конструктор из указанного входного потока(считать ранее сохраненный документ).
	TextEditorCore (std::istream & _s);
	
	// Копирование и присвоение таких объектов должно быть запрещено.
	TextEditorCore (const TextEditorCore&) = delete;
	void operator = (const TextEditorCore&) = delete;

	// Деструктор(если он необходим).
	//~TextEditorCore ();

	// ------------------------------------- Работа с курсором : -------------------------------------
	// Метод для определения текущего положения курсора(номер строки, номер столбца)
	Pointer CurentPointerPosition() const { return pointer; };
	
	// Методы для перемещения на 1 позицию в любом из 4 возможных направлений.
	void MovePointerUp();
	void MovePointerRight();
	void MovePointerDown();
	void MovePointerLeft();

	// Метод для перемещения курсора в произвольную точку(клик мышкой) - точка должна существовать.
	void MovePointerTo(int _x, int _y);
	
	// ----------------------------- Редактирование конкретной строки : -----------------------------
	// Методы для вставки и удаления одиночного символа. Особый случай - вставка или удаление элемента, соответствующего символу новой строки.
	void PushCharAfterPointer(char _ch);
	void DeleteCharBeforePointer();

	// Метод для вставки фрагмента текста за одно действие(например, пользовательский интерфейс может вставить скопированный из буфера обмена фрагмент текста).
	void PushStringAfterPointer(const std::string & _str);
	
	// Метод для удаления выделенного фрагмента текста.
	void DeleteMarkedPart();
	
	// Методы для перехода на начало / конец строки / документа (понадобится для реакции на клавиши Home / End и Ctrl + Home / End).
	void MovePointerHome() { pointer.y = 0; HighlightingInvalidator(); };
	void MovePointerEnd() {	pointer.y = data[pointer.x].size(); HighlightingInvalidator();};
	void MovePointerCtrlHome() { MovePointerTo(0, 0); HighlightingInvalidator();};
	void MovePointerCtrlEnd() { MovePointerTo(data.size() - 1, data[data.size() - 1].size()); HighlightingInvalidator();};

	// Метод для сохранения содержимого текста в указанный выходной поток.
	void Save (std::ostream & _s) const;

	// ----------------------------- Работа с выделением текста : -----------------------------
	// Метод начала выделения переключает редактор в особый режим, запоминая место начала выделения.
	void StartMarking();

	// Метод завершения выделения переключает редактор в обычный режим. Однако выделение может быть восстановлено и продолжено, если курсор не перемещался.
	void StopMarking();

	// Метод сброса выделения.
	void ResetMarking() { highlited.first = { -1,-1 }; highlited.second = { -1,-1 }; };

	// Метод, возвращающий текущий выделенный текст.
	std::string ReturnMarkedText() const;

	Highlighting ReturnHighlightingPoints() const { return highlited; };

	// ----------------------------- Методы для поиска и замены : -----------------------------
	// Метод, реализующий первый поиск в файле по фрагменту.
	Pointer Find(const std::string & _str, Pointer _curent = {0,0}) const;
	// Метод, продолжающий поиск по фрагменту с предыдущей найденной позиции.
	Pointer FindNext(Pointer _curent, const std::string & _str) const;
	// Метод, осуществляющий замену первого встречаемого образца текста на другой.
	bool Replace(const std::string & _str, const std::string & _replace);
	// Метод, осуществляющий замену всех встречаемых образцов текста на другой.
	bool ReplaceAll(const std::string & _str, const std::string & _replace);

};

#endif // _TEXTEDITORCORE_HPP_