#pragma once
class GOLField
{
private:
	int height_;
	int width_;
	bool** field_;
	bool** field_minus_one_;

public:
	explicit GOLField(bool** read_field, int width, int height);
	bool** life(int generations) const;
	~GOLField();
};

