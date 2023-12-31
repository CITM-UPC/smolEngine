#pragma once

#include <string>

class Editor;

class Panel
{
public:
	Panel(const char* name, Editor* instance);
	virtual ~Panel();

	void SetActive(bool enabled);
	void SwitchActive();
	bool IsActive() const;
	virtual void Start() {}
	virtual void Draw() = 0;
	virtual void Update(){}
	const char* GetName() const { return name; }
public:
	bool active = true;
protected:
	const char* name = NULL;
	Editor* instance;
};