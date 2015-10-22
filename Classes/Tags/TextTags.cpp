#include "TextTags.h"

namespace SNovel
{
	TagRegitser<RTag> _rTag("r");
	TagRegitser<PTag> _pTag("p");
	TagRegitser<CmTag> _cmTag("cm");
	TagRegitser<LTag> _lTag("l");
	TagRegitser<CurrentTag> _currentTag("current");
	TagRegitser<SetnameTag> _setnameTag("setname");
	TagRegitser<PrintTag> _printTag("print");
}