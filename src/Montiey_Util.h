#ifndef MONTIEY_UTIL_H
#define MONTIEY_UTIL_H

class HandyTimer {
	public:
		HandyTimer(unsigned long);
		bool trigger();
	private:
		unsigned long checkTime;
		unsigned long lastTime;
		unsigned long interval;
};

#endif
