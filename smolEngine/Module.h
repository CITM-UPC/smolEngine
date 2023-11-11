#pragma once


class Module
{
public:

	Module(bool startEnabled = false) : active(startEnabled)
	{}

	virtual bool Init()
	{
		return true;
	}

	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool OnRenderUI()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	void Enable() {
		if (!active) {
			active = true;
			Start();
		}
	}

	void Disable() {
		if (active) {
			active = false;
			CleanUp();
		}
	}

	inline bool IsEnabled() const { return active; }

public:
	bool active = 0;

};