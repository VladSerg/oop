#include "texteditorcore.hpp"
#include "messages.hpp"
#include <algorithm>
#define datasizeX (int)data.size() - 1
#define datasizeY (int)data[datasizeX].size()


TextEditorCore::TextEditorCore()
{
	data.push_back("");

	pointer.x = 0;
	pointer.y = 0;
}

TextEditorCore::TextEditorCore(std::istream & _s)
{
	while (!_s.eof())
	{
		std::string tmp;
		std::getline(_s, tmp);
		data.push_back(tmp);

	}
	pointer.x = datasizeX;
	pointer.y = data[pointer.x].size();
}

//TextEditorCore::~TextEditorCore()
//{
//	for (std::string * curent : data)
//		delete curent;
//}

void TextEditorCore::MovePointerUp()
{
	if (pointer.x == 0)
		return;
	pointer.x--;
	if ((int)data[pointer.x].size() < pointer.y )
	{
		pointer.y = data[pointer.x].size();
	}

	HighlightingInvalidator();
}

void TextEditorCore::MovePointerRight()
{
	if (data[pointer.x].size() == pointer.y)
	{
		if (pointer.x == datasizeX)
			return;
		++pointer.x;
		pointer.y = 0;
		return;
	}
	++pointer.y;

	HighlightingInvalidator();
}

void TextEditorCore::MovePointerDown()
{
	if (pointer.x == datasizeX)
		return;
	++pointer.x;
	if ((int)data[pointer.x].size() < pointer.y)
	{
		pointer.y = data[pointer.x].size();
	}

	HighlightingInvalidator();
}

void TextEditorCore::MovePointerLeft()
{
	if (pointer.y == 0)
	{
		if (pointer.x == 0)
			return;
		--pointer.x;
		pointer.y = data[pointer.x].size();
		return;
	}
	--pointer.y;

	HighlightingInvalidator();
}

void TextEditorCore::MovePointerTo(int _x, int _y)
{
	if (_x > datasizeX || _x < 0)
		throw std::logic_error(Messages::InvalidPointerCoordinates);
	pointer.x = _x;
	if (_y > (int)data[pointer.x].size() || _y < 0)
		throw std::logic_error(Messages::InvalidPointerCoordinates);
	pointer.y = _y;

	HighlightingInvalidator();
}

void TextEditorCore::PushCharAfterPointer(char _ch)
{
	if (IsHighlighted())
		DeleteMarkedPart();

	if (_ch == '\n')
	{
		if (pointer.y == data[pointer.x].size())
		{
			++pointer.x;
			pointer.y = 0;
			//data.insert()
			//std::string * tmp = new std::string;
			data.insert(data.begin() + pointer.x, "");
		}
		else if (pointer.y == 0)
		{
			//std::string * tmp = new std::string;
			data.insert(data.begin() + pointer.x, "");
			++pointer.x;
		}
		else
		{
			std::string tmp;
			tmp = data[pointer.x].substr(pointer.y);
			data.insert(data.begin() + pointer.x + 1, tmp);
			data[pointer.x].erase(pointer.y);
			++pointer.x;
			pointer.y = 0;
		}
	}
	else
	{
		data[pointer.x].insert(pointer.y, 1, _ch);
		++pointer.y;
	}
}

void TextEditorCore::DeleteCharBeforePointer()
{
	if (IsHighlighted())
	{
		DeleteMarkedPart();
		return;
	}
	if (pointer.y == 0)
		{
			if (pointer.x == 0)
				return;
			if (data[pointer.x - 1].size() == 0)
			{
				// delete data[pointer.x - 1];
				data.erase(data.begin() + pointer.x - 1);
			}
			else
			{
				pointer.y = data[pointer.x - 1].size();
				data[pointer.x - 1] += data[pointer.x];
				//delete data[pointer.x];
				data.erase(data.begin() + pointer.x);
			}
			--pointer.x;
		}
	else
		{
			data[pointer.x].erase(data[pointer.x].begin() + pointer.y - 1);
			--pointer.y;
		}
}

void TextEditorCore::PushStringAfterPointer(const std::string & _str)
{
	if (IsHighlighted())
		DeleteMarkedPart();
	for (char _ch : _str) // Т.к. в строке могут быть символы новой строки
	{
		PushCharAfterPointer(_ch);
	}
}

void TextEditorCore::DeleteMarkedPart()
{
	if (!IsHighlighted())
		throw std::logic_error(Messages::IsntHighlighting);

	if (highlited.InOneLine())
	{
		data[highlited.first.x].erase(highlited.first.y, highlited.second.y);
	}
	else
	{ 
		data[highlited.first.x].erase(data[highlited.first.x].begin() + highlited.first.y, data[highlited.first.x].end());
		data[highlited.first.x] += data[highlited.second.x].substr(highlited.second.y);
		//for (int i = highlited.first.x + 1; i <= highlited.second.x ; i++)
		//{
		//	delete data[i];
		//}
		data.erase(data.begin() + highlited.first.x + 1, data.begin() + highlited.second.x + 1);
	}

	MovePointerTo(highlited.first.x, highlited.first.y);
	ResetMarking();
}

void TextEditorCore::SortHighlightingPoints()
{
	highlited.sort();
}

void TextEditorCore::Save(std::ostream & _s) const
{
	if (datasizeX == 0 && data[0].size() == 0)
		return;

	for (std::string _str : data)
	{
		_s << _str << '\n';		
	}
}

void TextEditorCore::StartMarking()
{
	if (IsHighlighting())
		throw std::logic_error(Messages::InvalidStartHighlighting);

	if ( IsHighlighted() )
		highlited.second = { -1,-1 };
	else
		highlited.first = pointer;
}

void TextEditorCore::StopMarking()
{
	if (highlited.first == Pointer{ -1,-1 })
		throw std::logic_error(Messages::InvalidEndHighlighting);

	if (highlited.first == pointer)
		ResetMarking();

	highlited.second = pointer;

	SortHighlightingPoints();
}

std::string TextEditorCore::ReturnMarkedText() const
{
	if (!IsHighlighted())
		throw std::logic_error(Messages::IsntHighlighted);
	
	std::string subdata;

	if (highlited.InOneLine())
	{
		subdata = data[highlited.first.x].substr(highlited.first.y, highlited.second.y);
	}
	else
	{
		subdata = data[highlited.first.x].substr( highlited.first.y);
		subdata += '\n';
		for (int i = highlited.first.x + 1; i < highlited.second.x; i++)
		{
			subdata += data[i];
			subdata += '\n';
		}
		subdata +=  data[highlited.second.x].substr(0, highlited.second.y);
	}

	return subdata;
}

void TextEditorCore::HighlightingInvalidator()
{
	if (IsHighlighted())
		ResetMarking();
}

bool TextEditorCore::PointerInvalidator(Pointer curent) const
{
	if (curent.x > datasizeX || curent.x < 0)
		return false;
	if (curent.y > (int)data[pointer.x].size() || curent.y < 0)
		return false;
	return true;
}

bool TextEditorCore::IsHighlighted()const
{
	return highlited.first != Pointer{ -1,-1 } && highlited.second != Pointer{ -1,-1 };
}

bool TextEditorCore::IsHighlighting()const
{
	return highlited.first != Pointer{ -1,-1 } && highlited.second == Pointer{ -1,-1 };
}

Pointer TextEditorCore::Find(const std::string & _str, Pointer _curent) const
{
	if (_str.empty())
		throw std::logic_error(Messages::InvalidSearch);

	if (!PointerInvalidator(_curent))
		throw std::logic_error(Messages::InvalidPointerCoordinates);

	Pointer temp = { -1 , -1 };

	if (data[_curent.x].find(_str, _curent.y) != -1)
	{
		temp.x = _curent.x;
		temp.y = data[_curent.x].find(_str, _curent.y);
		return temp;
	}

	for (int i = _curent.x + 1; i <= datasizeX; i++)
	{
		if (data[i].find(_str, 0) != -1)
		{
			temp.x = i;
			temp.y = data[i].find(_str, 0);
			return temp;
		}
	}
	temp = { datasizeX, datasizeY };
	return temp;
}

Pointer TextEditorCore::FindNext(Pointer _curent, const std::string & _str) const
{
	return Find(_str, { _curent.x , _curent.y + 1 });
}

bool TextEditorCore::Replace(const std::string & _str, const std::string & _replace)
{
	Pointer first = Find(_str);
	if (first == Pointer{ datasizeX, datasizeY })
		return false;
	data[first.x].replace(first.y, _str.size(), _replace);
	return true;
}

bool TextEditorCore::ReplaceAll(const std::string & _str, const std::string & _replace)
{
	Pointer temp = Find(_str);
	Pointer end { datasizeX, datasizeY };

	if (temp == end)
		return false;

	while (temp != end )
	{
		data[temp.x].replace(temp.y, _str.size(), _replace);
		if (temp.x == datasizeX)
			end = { datasizeX, datasizeY };
		temp = FindNext(temp, _str);		
	}
	return true;
}
