#include <stdio.h>
#include <stdbool.h> /*Boolean Library*/
#include <stdlib.h> /*Library for Random number function and exit() function*/

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
int total_amount;

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
void IngerdientsLow();
void Payment(int PaymentOption);


/*Main Function*/
int main(void) {
	while (1) {
		IngredientsLow(); /*Checks and alerts if ingredient quantity is low*/

		int i; /*gather input for main Menu function*/
		printf("||Coffee Machine Menu||\n(Enter the Number to choose functionality)\n1. Order a Coffee\n2. Admin Mode\n0. Exit Application\n ");
		scanf("%i", &i);
		
		if (i == 0) {
			exit(0); /*Quit loop since 0 means to close the application*/
		}

		Menu(i);

	}
}

void Menu(int MenuOption) { /*Menu function*/
	switch (MenuOption) {

	case 1:
		printf("Choose a drink by typing the number\n1. Espresso - 3.5\n2. Cappuccino - 4.5\n3. Mocha - 5.5\n ");
		int k;
		scanf("%d", &k);
		OrderCoffee(k); /*Call Function to order drink*/
		break;
	case 2:
		AdminMode(); /*Call admin mode function*/
		break;

	default:
		printf("\nInput valid option!\n\n");
	}
}

void OrderCoffee(int OrderOption) {
	switch (OrderOption) {
	case 1:
		if (coffeeBeans >= Beans_Min || water >= ESPRESSO_WATER_Min) {
			Payment(OrderOption);
			break;
		}
		else {
			printf("\n Unavailable due to insufficient ingredients\n\n");
			break;
		}

	case 2:
		if (coffeeBeans >= Beans_Min || water >= CAPPUCCINO_WATER_Min || milk >= CAPPUCCINO_MILK_Min) {
			Payment(OrderOption);
			break;
		}
		else {
			printf("\n Unavailable due to insufficient ingredients\n\n");
			break;
		}
	case 3:
		if (coffeeBeans >= Beans_Min || water >= MOCHA_WATER_Min || cSyrup >= MOCHA_SYRUP_Min || milk >= MOCHA_MILK_Min) {
			Payment(OrderOption);
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
	printf("Input PIN (4 Digits): "); /*Input Password to access Admin Mode*/
	scanf("%d", &pass);
	
	if (pass == adminPass) {

		int j;
		printf("Choose Admin Mode function:\n0.Quit\n1.Display Ingredient Quantities and Total Sales\n2. Replenish Ingredients\n3. Change Coffee Price\n\n");
		scanf("%d", &j);

		switch (j) {
		case 0:
			exit(0); /*Quit Application*/
		case 1: /*Display ingredients and sales*/
			printf("Ingredient Balance:\nCoffee Beans: %-12d\nWater: %-12d\nMilk: %-12d\nChocolate Syrup: %-12d\n\nTotal Sales: %12d\n\n", coffeeBeans, water, milk, cSyrup, total_amount);
			break;
		case 2:
			Replenish();
			printf("Ingredients Replenished!\n\n");
			break;
		case 3:
			float newprice;
			int drinkoption;
			printf("Which Drink would you like to change the price of?\n1. Espresso\n2. Cappuccino\n3. Mocha\n");
			scanf("%d",&drinkoption);
			switch (drinkoption){

				case 1:
				printf("\nEnter new price for Espresso\n");
				scanf("%f",&newprice);
				EspressoPrice = newprice;
				printf("Price Updated.\n");
				break;

				case 2:
				printf("\nEnter new price for Cappuccino\n");
				scanf("%f",&newprice);
				CappuccinoPrice = newprice;
				printf("Price Updated.\n");
				break;

				case 3:
				printf("\nEnter new price for Mocha\n");
				scanf("%f",&newprice);
				MochaPrice = newprice;
				printf("Price Updated.\n");
				break;

				default:
				printf("Choose Valid Drink!");
				break;
			}
		}
	}
	else {
		printf("PIN is Incorrect!");
	}
}

void Replenish() { /*replenishes ingredients randomly between minimum required and minimum+99*/
	coffeeBeans = 10 + rand() % 99;
	water = 30 + rand() % 99;
	milk = 70 + rand() % 99;
	cSyrup = 40 + rand() % 99;
}

void IngredientsLow() { /*Alert User that ingredients are lower than the minimum required for a drink*/
	if (coffeeBeans < Beans_Min){
		printf("Beans Quantity is low");
	}
	if (milk < CAPPUCCINO_MILK_Min){
		printf("Milk Quantity is low");
	}
	if (water < ESPRESSO_WATER_Min){
		printf("Water Quantity is low");
	}
	if (cSyrup < MOCHA_SYRUP_Min){
		printf("Chocolate Syrup Quantity is Low");
	}
}

void Payment(int PaymentOption){
	float coins;
	float payment;
	bool paid = false;

	switch (PaymentOption){
		case 1:
		while (paid == false){
			printf("The Price is AED %12.2f\nThe amount to be paid is %12.2f \nInsert Coins:\n\n 1. 1 AED Coin\n 2. .50 AED Coin\n",EspressoPrice,(EspressoPrice-payment));
			scanf("%f",&coins);

			if (coins == 1){			/*Validate coins*/
				payment++;
			}
			else if (coins == 2){
				payment += 0.5;
			}
			else{
				printf("Insert Valid Coin!");
			}

			if (payment == EspressoPrice){			/*check if payment matches price*/
				paid = true;
				total_amount++;
				printf("\n Drink Prepared. Enjoy! The Price of your drink is: %.2f\n\n",EspressoPrice);
				coffeeBeans -= Beans_Min;
				water -= ESPRESSO_WATER_Min; /*Subtract ingredients used from reservoir*/
			}
			else{
				paid = false;			/*loop continues if price is not paid*/
			}
		}
		case 2:
		while (paid == false){
			printf("The Price is AED %12.2f\nThe amount to be paid is %12.2f \nInsert Coins:\n\n 1. 1 AED Coin\n 2. .50 AED Coin\n",CappuccinoPrice,(CappuccinoPrice-payment));
			scanf("%f",&coins);

			if (coins == 1){
				payment++;
			}
			else if (coins == 2){
				payment += 0.5;
			}
			else{
				printf("Insert Valid Coin!");
			}

			if (payment == CappuccinoPrice){
				paid = true;
				total_amount++;
				printf("\n Drink Prepared. Enjoy! The Price of your drink is: %.2f\n\n",CappuccinoPrice);
				coffeeBeans -= Beans_Min;
				water -= CAPPUCCINO_WATER_Min;
				milk -= CAPPUCCINO_MILK_Min;
			}
			else{
				paid = false;
			}
		}
		case 3:
		while (paid == false){
			printf("The Price is AED %12.2f\nThe amount to be paid is %12.2f \nInsert Coins:\n\n 1. 1 AED Coin\n 2. .50 AED Coin\n",MochaPrice,(MochaPrice-payment));
			scanf("%f",&coins);

			if (coins == 1){
				payment++;
			}
			else if (coins == 2){
				payment += 0.5;
			}
			else{
				printf("Insert Valid Coin!");
			}

			if (payment == MochaPrice){
				paid = true;
				total_amount++;
				printf("\n Drink Prepared. Enjoy! The Price of your drink is: %.2f\n\n",MochaPrice);
				coffeeBeans -= Beans_Min;
				water -= MOCHA_WATER_Min;
				milk -= MOCHA_MILK_Min;
				cSyrup -= MOCHA_SYRUP_Min;
			}
			else{
				paid = false;
			}
		}
	}
}