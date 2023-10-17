#pragma once

#include <string>
#include <memory>

class Texture2D
{
	unsigned int _id;

public:

	inline unsigned int id() const { return _id; }

	explicit Texture2D(const std::string& path);
	Texture2D(Texture2D&& tex) noexcept;

	~Texture2D();
	
	void bind() const;

private:
	Texture2D(const Texture2D&);

};

