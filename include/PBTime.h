#ifndef PBTIME
#define PBTIME

class PBTime {
public:
	PBTime() : timestep(0.01666f), elapsedTime(0) {}
	PBTime(float timestep, float elapsedTime) : timestep(timestep), elapsedTime(elapsedTime) {}

	float getTimestep() const { return timestep; }
	float getElapsedTime() const { return elapsedTime; }

	void setTimestep(float t) { timestep = t; }
	void setElapsedTime(float ct) { elapsedTime = ct; }

	friend class PhysicallyBased;

private:
	float timestep;
	float elapsedTime;
};

#endif // PBTIME
