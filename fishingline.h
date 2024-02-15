#ifndef FISHINGLINE_H
#define FISHINGLINE_H


class Fishingline {
private:
	bool broken = false;
	float length = 0.0;
	float tension = 0.0;
	float maxTension = 100.0;
public:
	Fishingline() {}
	float getTension() const { return tension; }
	void setTension(float newTension) { tension = newTension; if (newTension > maxTension) { broken = true; } }
	float getLength() const { return length; }
	void setLength(float newLength) { length = newLength; }
	void slack(float addSlack) { tension -= addSlack; }
	void tighten(float addTight) { tension += addTight; if (tension > maxTension) { broken = true; } }
};


#endif

