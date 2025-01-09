#pragma once
class AttributeComponent
{
public:
	//Leveling
	unsigned level;
	unsigned expCurrent;
	unsigned expMax;
	unsigned expNext;
	unsigned statPoints;

	//Attributes
	unsigned strenght;
	unsigned intelligence;
	unsigned agility;

	//Stats
	int hp;
	int maxHp;
	int attackDmgMin;
	int attackDmgMax;

	float movementSpeed;
	float attackSpeed;

	int abilityPowerMin;
	int abilityPowerMax;

	//int criticalChance;
	//int criticalDamage;

	//Const&Destr
	AttributeComponent(unsigned level);
	~AttributeComponent();

	//Functions
	std::string debugPrint() const;

	void gainExp(const unsigned exp);

	void updateStats(const bool reset);
	void updateLevel();
	void update();
};
