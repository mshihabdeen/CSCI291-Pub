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
void Payment(int option);

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

		if (i == 0) {
			break;
		}

		if (i == 2) {

		}
	}
	printf("%-12.2f", 123.31233);
}

void PrepareDrink(int option) {
	if (option == 1) {
		if (coffeeBeans >= Beans || water >= EspressoWater) {
			Payment(option);
			printf("\n Drink Prepared. Enjoy!\n\n");
		}
		else {
			printf("\n Unavailable due to insufficient ingredients\n\n");
		}

		return;
	}
	if (option == 2) {
		if (coffeeBeans >= Beans || water >= CappuccinoWater || milk >= CappuccinoMilk) {
			printf("\n Drink Prepared. Enjoy!\n\n");
		}
		else {
			printf("\n Unavailable due to insufficient ingredients\n\n");
		}

		return;
	}
	if (option == 3) {
		if (coffeeBeans >= Beans || water >= MochaWater || cSyrup >= MochaCSyrup || milk >= MochaMilk) {
			printf("\n Drink Prepared. Enjoy!\n\n");
		}
		else {
			printf("\n Unavailable due to insufficient ingredients\n\n");
		}

		return;

	}

	else {
		printf("\n Invalid Selection\n\n");
		printf("Choose a drink by typing the number\n1. Espresso - 3.5\n2. Cappuccino - 4.5\n3. Mocha - 5.5\n ");
		scanf("%d", &option);
		PrepareDrink(option);
	}
}

void Payment(int option) {
	if (option == 1) {
		float price = 3.50;
		float k;
		bool paid;
		paid = false;
		while (paid == false) {
			printf("\nCurrent amount to be paid is: %f \nInsert either 1 AED or 0.50 AED Coins\n\n", &price);
			scanf("%f", &k);
			if (k == 1 || k == 0.5) {
				price = price - k;
				if (price == 0) {
					paid = true;
				}
			}
			else {
				printf("\nOnly insert either 1 AED or 0.5 AED Coins\n");
			}
		}
	}
}