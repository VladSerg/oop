#ifndef _UNIQUE_DEREFERENCING_ITERATOR_HPP_
#define _UNIQUE_DEREFERENCING_ITERATOR_HPP_

#include <memory>

// Итератор-адаптер для удобства перебора дочених элементов, хранимых как unique_ptr
template <
	typename _Item, // Тип элемента
	template < typename T > typename _Container // Шаблон типа контейнера
>
class UniqueDereferencingIterator
{
public:
	// Синоним типа, обозначающий сам себя
	typedef UniqueDereferencingIterator< _Item, _Container > Self;
	// Синоним типа для итератора реально используемого контейнера
	typedef
		typename _Container < std::unique_ptr< _Item > >::const_iterator
		BaseIterator;
	// Конструктор - принимает и запоминает итератор от контейнера
	UniqueDereferencingIterator(BaseIterator _baseIt)
		: m_baseIt(_baseIt) {}
	// Оператор разыменования с целью чтения: превращаем умный указатель в ccылку
	_Item & operator * () const
	{
		return *(*m_baseIt).get();
	}
	// Оператор префиксного инкремента: перенаправляем дочернему итератору
	Self & operator ++ ()
	{
		++m_baseIt;
		return *this;
	}
	// Оператор сравнения на равенство: перенаправляем дочернему итератору
	bool operator == (Self _it) const
	{
		return m_baseIt == _it.m_baseIt;
	}
	// Оператор сравнения на неравенство: перенаправляем дочернему итератoру
	bool operator != (Self _it) const
	{
		return m_baseIt != _it.m_baseIt;
	}
private:
	// Итератор, полученный от контейнера
	BaseIterator m_baseIt;
};
#endif // _UNIQUE_DEREFERENCING_ITERATOR_HPP_