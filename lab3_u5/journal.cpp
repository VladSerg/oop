#include "journal.hpp"
#include "messages.hpp"

Journal::Journal(std::string const & _title)
	:title(_title)
{
	if (title.empty())
		throw std::logic_error(Messages::InvalidTitle);
};

Journal::Journal(std::string const & _title, std::initializer_list<JournalRelease*> _journalrelizes)
	:title(_title)
{
	if (title.empty())
		throw std::logic_error(Messages::InvalidTitle);

	for (JournalRelease * curent : _journalrelizes)
		addJournalRelise(std::unique_ptr<JournalRelease>(curent));

};

void Journal::addJournalRelise(std::unique_ptr <JournalRelease> _jrelise) 
{
	journalreleases.push_back(std::move(_jrelise)); 
};
