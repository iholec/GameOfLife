#pragma once
class GOLField
{
private:
	int height_;
	int width_;
	char** field_;
	char** field_minus_one_;

public:
	explicit GOLField(char** read_field, int width, int height);
	char** life(int generations) const;
	~GOLField();
};

