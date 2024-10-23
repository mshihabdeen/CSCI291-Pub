#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*Defining Ingredient Minimums*/
#define Beans_Min 8

#define MOCHA_WATER_Min 30
#define MOCHA_MILK_Min 160
#define MOCHA_SYRUP_Min 30

#define CAPPUCCINO_WATER_Min 30
#define CAPPUCCINO_MILK_Min 70

#define ESPRESSO_WATER_Min 30

/* Drink Prices */
float CappuccinoPrice = 4.5;
float MochaPrice = 5.5;
float EspressoPrice = 3.5;

/*Admin Password*/
#define adminPass 1234

/*Init Variables*/
float total_amount;

/*Set Initial ingredient amounts*/
int coffeeBeans = 400;
int water = 200;
int milk = 400;
int cSyrup = 200;

/*Function Prototypes*/

void Menu(int MenuOption);
void AdminMode();
void OrderCoffee(int OrderOption);
void Replenish();
/*bool Payment(int option);*/


/*Main Function*/
int main(void) {
	while (1) {
		int i;
		printf("||Coffee Machine Menu||\n(Enter the Number to choose functionality)\n1. Order a Coffee\n2. Admin Mode\n0. Exit Application\n ");
		scanf("%i", &i);
		
		if (i == 0) {
			break;
		}
		Menu(i);

	}
}

void Menu(int MenuOption) {
	switch (MenuOption) {

	case 1:
		printf("Choose a drink by typing the number\n1. Espresso - 3.5\n2. Cappuccino - 4.5\n3. Mocha - 5.5\n ");
		int k;
		scanf("%d", &k);
		OrderCoffee(k);
		break;
	case 2:
		AdminMode();
		break;

	default:
		printf("\nInput valid option!\n\n");
	}
}

void OrderCoffee(int OrderOption) {
	switch (OrderOption) {
	case 1:
		if (coffeeBeans >= Beans_Min || water >= ESPRESSO_WATER_Min) {
			/*Payment(option);*/
			printf("\n Drink Prepared. Enjoy!\n\n");
			break;
		}
		else {
			printf("\n Unavailable due to insufficient ingredients\n\n");
			break;
		}

	case 2:
		if (coffeeBeans >= Beans_Min || water >= CAPPUCCINO_WATER_Min || milk >= CAPPUCCINO_MILK_Min) {
			/*Payment(option);*/
			printf("\n Drink Prepared. Enjoy!\n\n");
			break;
		}
		else {
			printf("\n Unavailable due to insufficient ingredients\n\n");
			break;
		}
	case 3:
		if (coffeeBeans >= Beans_Min || water >= MOCHA_WATER_Min || cSyrup >= MOCHA_SYRUP_Min || milk >= MOCHA_MILK_Min) {
			/*Payment(option);*/
			printf("\n Drink Prepared. Enjoy!\n\n");
			break;
		}
		else {
			printf("\n Unavailable due to insufficient ingredients\n\n");
			break;
		}
	default:
		printf("\n\nInput valid option!\n");
	}
}

void AdminMode() {
	int pass;
	printf("Input PIN (4 Digits): ");
	scanf("%d", &pass);
	
	if (pass == adminPass) {

		int j;
		printf("Choose Admin Mode function:\n0.Quit\n1.Display Ingredient Quantities and Total Sales\n2. Replenish Ingredients\n3. Change Coffee Price\n\n");
		scanf("%d", &j);

		switch (j) {
		case 0:
			break;
		case 1:
			printf("Ingredient Balance:\nCoffee Beans: %d\nWater: %d\nMilk: %d\nChocolate Syrup: %d\n\nTotal Sales: %d\n\n", coffeeBeans, water, milk, cSyrup, total_amount);
			break;
		case 2:
			Replenish();
			printf("Ingredients Replenished!\n\n");
			break;
		}
	}
	else {
		printf("PIN is Incorrect!");
	}
}

void Replenish() {
	coffeeBeans = 10 + rand() % 99;
	water = 10 + rand() % 99;
	milk = 10 + rand() % 99;
	cSyrup = 10 + rand() % 99;
}