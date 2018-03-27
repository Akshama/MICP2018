/*
 Microsoft Interview Coaching Pilot Program MICP 2018
Author: Akshama
Language: C++

/**********WEEK SIX***********/
/*
Problem description:
Design a vending machine.

//TEBOW IT

/*
1. T - TALK

Clarify:
No more restrictions, just design a general vending machine we are familiar with.

Use case list:

select item and get price
accept bills/coins
dispense items purchased and return change
refund when cancelling the request
Possible exceptions:

Sold out
Not fully paid
Not enough changes

What is it? Simple vending machine
Who's going to use it? Customer
When will it be used? Anytime
Where will it be used? Any place
Why will it be used? Automatic sales of general use products
How will it be used? Upon request by the customer, fetch prices, accept payment, render the product.


2. E - EXAMPLES
VendingMachine vm = new VendingMachine();		Create a new vending machine with unique id;
vm.addStock(item, amount);						Add a certain amount of items into item list;
vm.getRequest(request);							User send a request(with a selected item)
vm.cancelRequest();								Cancel current user request;


3. B - BRUTE-FORCE

Create one class: VendingMachine, which contains all the state and behavior.

4. O - OPTIMISE

Create different classes for User requests, products, currency and Vending Machine

5. W - WALK THROUGH

Explained as comments in the code

6. I - IMPLEMENT
*/
#include <iostream>
#include <stdlib.h>
using namespace std;
//class for coins
class currency
{
    public:
        int coins_5;
        int coins_10;
    public:
        currency()
        {
            coins_5=100;
            coins_10=50;
        }
};
int id=0;
class Product
{
	int p_id;
	float p_price;
	public:
        int p_count;
        Product()
        {
            p_id=id++;
            p_price=100;
            p_count=10;
        }

        void increase_p_count()
        {
            p_count++;
        }
        void decrease_p_count()
        {
            p_count--;
        }
        float get_price()
        {
            return p_price;
        }
};

class Vending_Machine : public currency
{
	float curr_balance;
	int available_items[3];
	currency* coin;
	public:
        Product* items_list[3];
        Vending_Machine()
        {
            curr_balance=1000;
            for (int i=0;i<3;i++)
            {
                items_list[i]= new Product();
                available_items[i]=1;
            }
            coin=new currency();
        }

void add_coins(int cnt_5,int cnt_10)
{
    coins_10+=cnt_10;
    coins_5+=cnt_5;
}
void pay_price(float bal)
{
    float total=0;
    if(curr_balance>=bal)
    {
        while(total<=bal && coins_10>0)
        {
            total+=10;
	      	coins_10-=1;
        }
        while(total<=bal && coins_5>0)
        {
	      	total+=5;
	      	coins_5-=1;
        }

        if(total<bal)
	      	cout <<"Insufficient change";
    }
    else
     	cout <<"Insufficient change";
}

void update_VM(float amount,int item_id)
{
    float x=items_list[item_id]->get_price();
    curr_balance+=x;
    float bal=amount-x;
    items_list[item_id]->decrease_p_count();
    pay_price(bal);
}
};

int main()
{
    Vending_Machine VM;
	cout<< "Welcome!";
	cout<<"\nChoose your option\n 1.Request the price of an item\n2. Select and buy items\n3. Cancel request";
	char ch;
	cin>>ch;
	int p_id;
	do
	{
	  switch(ch)
	  {
	    case '1':
        {
            cout<<"\nEnter the Item ID";
            cin>>p_id;
            cout<<"Price: "<<VM.items_list[p_id]->get_price();
            break;
        }
	    case '2':
        {
            cout<<"\nEnter the Item ID which you want to buy";
            cin>>p_id;
            if(VM.items_list[p_id]->p_count==0)
            cout<< "Item Unavailable";
            float pay;
            cin>>pay;
            cout<< "Enter the coins added";
            int cnt_10,cnt_5;
            cin>>cnt_10>>cnt_5;
            VM.add_coins(cnt_5,cnt_10);
            VM.update_VM(pay,p_id);
            break;
        }
	    case '3':
        {
            cout<<"\nEnter the Item ID which you want to cancel";
            cin>>p_id;
            VM.items_list[p_id]->increase_p_count();
            float price=VM.items_list[p_id]->get_price();
            VM.pay_price(price);
            break;
        }
        case '4': {exit(0);break;}
	    default: {cout<< "invalid choice entered";break;}

	  }
	 cin>>ch;
	} while(ch!='4');
	return 0;
}
/*T - TEST
Checked by running the code for different cases:
Not fully paid
Not enough changes
The requested item not available
Successful sale.
*/
