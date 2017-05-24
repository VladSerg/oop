#ifndef _UNIQUE_DEREFERENCING_ITERATOR_HPP_
#define _UNIQUE_DEREFERENCING_ITERATOR_HPP_

#include <memory>

// ��������-������� ��� �������� �������� ������� ���������, �������� ��� unique_ptr
template <
	typename _Item, // ��� ��������
	template < typename T > typename _Container // ������ ���� ����������
>
class UniqueDereferencingIterator
{
public:
	// ������� ����, ������������ ��� ����
	typedef UniqueDereferencingIterator< _Item, _Container > Self;
	// ������� ���� ��� ��������� ������� ������������� ����������
	typedef
		typename _Container < std::unique_ptr< _Item > >::const_iterator
		BaseIterator;
	// ����������� - ��������� � ���������� �������� �� ����������
	UniqueDereferencingIterator(BaseIterator _baseIt)
		: m_baseIt(_baseIt) {}
	// �������� ������������� � ����� ������: ���������� ����� ��������� � cc����
	_Item & operator * () const
	{
		return *(*m_baseIt).get();
	}
	// �������� ����������� ����������: �������������� ��������� ���������
	Self & operator ++ ()
	{
		++m_baseIt;
		return *this;
	}
	// �������� ��������� �� ���������: �������������� ��������� ���������
	bool operator == (Self _it) const
	{
		return m_baseIt == _it.m_baseIt;
	}
	// �������� ��������� �� �����������: �������������� ��������� ������o��
	bool operator != (Self _it) const
	{
		return m_baseIt != _it.m_baseIt;
	}
private:
	// ��������, ���������� �� ����������
	BaseIterator m_baseIt;
};
#endif // _UNIQUE_DEREFERENCING_ITERATOR_HPP_