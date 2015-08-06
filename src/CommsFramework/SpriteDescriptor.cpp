#include "SpriteDescriptor.h"

#include <stdio.h>

SpriteDescriptor::SpriteDescriptor()
{
	Frames = new BaseList<std::string>();

	FrameLists = new PointerList<Framelist*>();
}

SpriteDescriptor::~SpriteDescriptor()
{
	delete(position);
	delete(size);

	delete(Frames);

	FrameLists->Release();
	delete(FrameLists);
}

BaseList<std::string>* Framelist::GetFrames()
{
	BaseList<std::string>* frames = new BaseList<std::string>();

	int substringIndexStart = pattern.find("%s");

	for (int i = startIndex; i < endIndex; i += step)
	{
		std::string newString = pattern.substr(0, substringIndexStart);

		newString.append(std::to_string(i));

		frames->Add(newString);
	}

	return frames;
}
