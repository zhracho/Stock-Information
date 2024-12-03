<H1> COP3530 - Market Matrix </h1>
This project is meant to distinguish the difference between the Max Heap 
and Hash Map Data Structures. The dataset proj3_sp500_stocks.csv contains
~27,000 records with four columns of the most recent six months worth of transactions
in the stock market. The source code is located in the src folder with all of the necessary
files and dependencies. Additionally, the csv file is located in the cmake-build-debug folder
since CLion requires this path for any external files.
<h2> Table of Contents </h2>

- [Functionality](#functionality)
	- [Getting Started with the Project](#getting-started-with-the-project)
		- [Top X Stocks Total](#top-x-stocks-total)
		- [Search by Company](#search-by-company)
		- [Top X Prices by Company](#top-x-prices-by-company)
		- [Search by Date Range](#search-by-date-range)

# Functionality
## Getting Started with the Project
The user will be prompted with a menu option each time the previous execution ends until
it is specified they want to end their session. There are five main queries that will be performed:
1. Top X Stocks Total
2. Search by Company
3. Top X Prices by Company
4. Get Maximum Price
5. Search by Data Range

After each of these actions are specified, users will be prompted to select the data structure
they want it to be executed on. The end result will be the desired output as well as the time
it took to perform the operation on the data structure.

## Loading in Data

The data for this project comes in the .csv format. The specific location to put this file depends on the IDE
that the code is run on. Since I coded this project in CLion, the data must be inserted into the cmake-build-debug
folder to perform input/ouput operations.

### Top X Stocks Total

This function is meant to query the top stocks based on closing price in the entire dataset.
The user is able to specify how many stocks they want to see as they are prompted for input.

### Search By Company

A user is able to type in the stock ticker ("AAPL" for Apple) that they want to search for and the program
will provide all of the relevant information for that specific company. See the next function for a more 
limited output based on price.

### Top X Prices by Company

A more selective version of the above Search By Company, this function prompts the user for a stock ticker
as well as the desired amount of stocks they want to see. The program outputs a table with the top closing prices
in descending order for the given company.

### Get Maximum Price

As mentioned in the name, this function gets the maximum price in the entire dataset and prints
out its information as a table.

### Search by Date Range:

The user is prompted for a date in the m/dd/yyyy format. This value will act as the lower bound in the interval.
The program will then provide all of the relevant information for dates that occur **after** the date specified
by the user