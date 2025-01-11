#pragma once
class AttributeComponent
{
public:
	//Leveling
	int level;
	int expCurrent;
	int expNext;
	int statPoints;

	//Attributes
	int strenght;
	int intelligence;
	int agility;

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
	AttributeComponent(int level);
	~AttributeComponent();

	//Functions
	std::string debugPrint() const;
	
	void loseHp(const int hp);
	void gainHp(const int hp);
	void gainExp(const int exp);

	void updateStats(const bool reset);
	void updateLevel();
	void update();
};
