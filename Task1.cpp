#include <stdio.h>

#define Beans 8
#define EspressoWater 30
#define EspressoPrice 3.5
#define CappuccinoWater 30
#define CappuccinoMilk 70
#define CappuccinoPrice 4.5
#define MochaWater 39
#define MochaMilk 160
#define MochaCSyrup 30
#define MochaPrice 5.5

#define adminPass 12341234

#define BeansLow 16
#define WaterLow 80
#define MilkLow 200
#define CSyrupLow 60

float total_amount;
int coffeeBeans, water, milk, cSyrup, price;

void PrepareDrink(int option);

int main(void) {
	coffeeBeans = 100;
	water = 200;
	milk = 400;
	cSyrup = 200;
	while (1) {
		int i;
		printf("||Coffee Machine Menu||\n(Enter the Number to choose functionality)\n1. Order a Coffee\n2. Admin Mode\n0. Exit Application\n ");
		scanf("%i", &i);
		if (i == 1) {
			printf("Choose a drink by typing the number\n1. Espresso - 3.5\n2. Cappuccino - 4.5\n3. Mocha - 5.5\n ");
			int k;
			scanf("%d", &k);
			PrepareDrink(k);

		}
	}
	printf("%-12.2f", 123.31233);
}

void PrepareDrink(int option) {
	if (option == 1) {
		if (coffeeBeans >= Beans || water >= EspressoWater) {
			printf("\n Drink Prepared. Enjoy!\n\n");
		}
	}
	if (option == 2) {
		if (coffeeBeans >= Beans || water >= CappuccinoWater || milk >= CappuccinoMilk) {
			printf("\n Drink Prepared. Enjoy!\n\n");
		}
	}
	if (option == 3) {
		if (coffeeBeans >= Beans || water >= MochaWater || cSyrup >= MochaCSyrup || milk >= MochaMilk) {
			printf("\n Drink Prepared. Enjoy!\n\n");
		}
	}
}