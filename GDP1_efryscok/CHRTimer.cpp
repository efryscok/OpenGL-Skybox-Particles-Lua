#include "CHRTimer.h"
#include "windows.h"

CHRTimer::CHRTimer() {
	this->m_elapsedTime = 0;
	this->m_startTime = 0;
	this->m_stopTime = 0;

	LARGE_INTEGER tempTime;

	QueryPerformanceFrequency(&tempTime);

	this->m_frequency = static_cast<unsigned long long>(tempTime.QuadPart);
}

CHRTimer::~CHRTimer() {}

void CHRTimer::Start(void) {
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter(&tempTime);
	this->m_startTime = static_cast<unsigned long long>(tempTime.QuadPart);
}

void CHRTimer::Stop(void) {
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter(&tempTime);
	this->m_stopTime = static_cast<unsigned long long>(tempTime.QuadPart);
}

void CHRTimer::Reset(void) {
	this->m_elapsedTime = 0;
	this->m_startTime = 0;
	this->m_stopTime = 0;
}

float CHRTimer::GetElapsedSeconds(void) {
	// Update current time
	LARGE_INTEGER tempTime;
	QueryPerformanceCounter(&tempTime);
	this->m_stopTime = static_cast<unsigned long long>(tempTime.QuadPart);

	// Calculate elapsed time
	this->m_elapsedTime = this->m_stopTime - this->m_startTime;
	float elapsedTimeSec = static_cast<float>(this->m_elapsedTime) / static_cast<float>(this->m_frequency);
	return elapsedTimeSec;
}

unsigned long long CHRTimer::GetFrequency(void) {
	return this->m_frequency;
}