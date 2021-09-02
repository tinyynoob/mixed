#include<stdio.h>
#include<stdlib.h>

class role{
private:
	int v;
public:
	role() {
		v = 3;
	}
	int hp_max;
	int hp;
	void bleed(int n){
		if (hp <= n)
			hp = 0;
		hp = hp - n;
	}

};

int main()
{
	int i;
	role lead;
	lead.hp_max = 100;
	lead.hp = lead.hp_max;
	printf("%d\n", lead.hp);
	lead.bleed(3);
	printf("%d\n", lead.hp);
	role* finger = new role;
	printf("%p\n", finger);
	printf("%p\n", &finger);
	printf("%d\n", lead.v);
	system("pause");
	return 0;
}