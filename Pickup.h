class Pickup
{
public:
	Pickup();
	void setName(std::string);
	std::string getName() const;
	~Pickup();

private:
	const std::string name;
	double spawnChance = 0;
};