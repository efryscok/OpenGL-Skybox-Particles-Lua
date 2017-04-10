#pragma once

class CHRTimer {
public:
	CHRTimer();
	virtual ~CHRTimer();
	void Start(void);
	void Stop(void);
	void Reset(void);
	float GetElapsedSeconds(void);
	unsigned long long GetFrequency(void);
private:
	unsigned long long m_elapsedTime;
	unsigned long long m_startTime;
	unsigned long long m_stopTime;
	unsigned long long m_frequency;
};