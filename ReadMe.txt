This project is to showcase my skills in datastructures. The project is about reading files from the test scripts and coding a dictionary in the C programming language, using a binary search tree as the data structure. There are 2 parts to the project, dict1 and dict2.

dict1-

dict1 takes 2 command line arguments: the first argument is the name of the data file going to be read, the second is the name of the output file.

The data file consists of these 17 columns shown below:

VendorID - Code to indicate the vendor which produced the record
passenger count - Number of passengers
trip_distance - Length of the trip in miles
RatecodeID - Code to represent the fare rate for the trip
store and fwd flag - Indicates whether trip records were stored locally
PULocationID - TLC Taxi Zone where passengers were picked up
DOLocationID - TLC Taxi Zone where passengers were dropped off
payment type - Code to indicate payment type (e.g., cash)
fare amount - Fare for the trip in USD
extra - Extra charges in USD
mta_tax - MTA tax in USD
tip_amount - Tip in USD
tolls_amount - Tolls in USD
improvement surcharge - Improvement surcharge in USD
total_amount - Total cost of the trip in USD
PUdatetime - Date/time passengers were picked up
DOdatetime - Date/time passengers were dropped off
trip duration - Duration of the trip in minutes

The PUdatetime serves as the dictionary key to sort the records in temporal order. The data is sorted and stored in a binary search tree. Keys that are not in unique are stored using a linked list. The data can be searched accordingly. 

Example of use:
- dict1 datafile outputfile then type in keys; or
- dict1 datafile outputfile < keyfile 


dict2-
Simple function that takes a PU location ID as an input and returns the PUdatetime keys in the output file. The search was done using in-order tree traversal. 

Example of use:
- dict2 datafile outputfile then type in keys; or
- dict2 datafile outputfile < idsfile


