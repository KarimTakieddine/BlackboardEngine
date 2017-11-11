/*	--------------------###############################################################################----------------------

*	Copyright (c) 2017 Karim Takieddine

*	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
*	documentation files (the "Software"), to deal in the Software without restriction, including without limitation
*	the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and
*	to permit persons to whom the Software is furnished to do so, subject to the following conditions:

*	The above copyright notice and this permission notice shall be included in allcopies or substantial portions of
*	the Software.

*	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
*	TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
*	TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*	--------------------###############################################################################--------------------- */

#include "stdafx.h"
#include "AudioDevice.h"

AudioDevice::AudioDevice()
:
m_device	(nullptr),
m_context	(nullptr)
{ }

ALCboolean AudioDevice::initialize
(
	ALCchar const * deviceName
)
{
	/*
		When initializing OpenAL, at least one device has to be opened.

		Within that device, at least one context will be created.
		
		Within that context, one listener object is implied, and a multitude
		of source objects can be created. Each source can have one or more
		buffer objects attached to it.
		
		Buffer objects are not part of a specific context – they are shared
		among all contexts on one device.
	*/

	m_device = alcOpenDevice(deviceName);
	
	if (!m_device)
	{
		return ALC_FALSE;
	}

	m_context = alcCreateContext(m_device, nullptr);

	if (!m_context)
	{
		return ALC_FALSE;
	}

	alcMakeContextCurrent(m_context);

	return ALC_TRUE;
}

ALCdevice * AudioDevice::get() const
{
	return m_device;
}

AudioDevice::~AudioDevice()
{
	alcDestroyContext(m_context);
	alcCloseDevice(m_device);
}