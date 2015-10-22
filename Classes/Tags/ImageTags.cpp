#include "ImageTags.h"

namespace SNovel
{
	TagRegitser<Image_newTag> _imagenewTag("image_new");
	TagRegitser<Image_showTag> _imageshowTag("image_show");
	TagRegitser<FadeoutTag> _fadeoutTag("fadeout");
	TagRegitser<FadeinTag> _fadeinTag("fadein");
	TagRegitser<MoveTag> _moveTag("move");
	TagRegitser<RemoveTag> _removeTag("remove");
}