#include <iostream>
#include "Graph.h"

using namespace std;

/*displays a menu with options to enqueue and dequeue a message and transmit the entire message and quit*/
void displayMainMenu()
{
    cout << "======Main Menu=====" << endl;
    //cout << "1. Find a movie" << endl;
    cout << "1. Calculate Best Delivery Route" << endl;
    cout << "2. Deliver a Package" << endl;
    cout << "3. Pickup a Package" << endl;
    cout << "4. Recalculate the Delivery Route" << endl;
    cout << "5. Print Current Delivery Progress" << endl;
    cout << "6. Print Current Delivery Route" << endl;
    cout << "7. Print All Deliviery Locations And The Routes Between Them." << endl;
    cout << "8. Erase All Remaining Deliveries" << endl;
    cout << "9. Load a New Set Of Deliveries" << endl;
    cout << "10. Add a Single Delivery" << endl;
    cout << "12. Quit" << endl;
    return;
}

int main(int argc, char*argv[]) {
    // Create a graph
    Graph g;

    // Flag used for exiting menu
    bool quit = false;

    // Input strings and command value integer
    string inputString1;
    string inputString2;
    int input;

    while(quit != true)
    {
        displayMainMenu();
        cin >> input;

        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input){
            // Calculate Best Delivery Route
            case 1:
            {

                break;
			}
            // Deliver a Package
            case 2:
            {

                break;
			}
            // Pickup a Package
            case 3:
            {

                break;
			}
            // Recalculate the Delivery Route
            case 4:
            {

                break;
			}
            // Print Current Delivery Progress
            case 5:
            {

                break;
			}
            // Print Current Delivery Route
            case 6:
            {

				break;
			}
			case 7:
			{
				g.printVertices();
				break;
			}
            // Erase All Remaining Deliveries
            case 8:
            {
				g.clearGraph();

				break;
			}
            // Load a New Set Of Deliveries
            case 9:
            {
				cout << "Enter a file name:" << endl;
                getline(cin,inputString1);
                cout << "If you want to overwrite type 1, to append type 0:" << endl;
                getline(cin,inputString2);
                g.loadDataFromFile(inputString1.c_str(), atoi(inputString2.c_str()));

				break;
			}
            // Add a Single Delivery
            case 10:
            {
				cout << "Enter delivery location name:" << endl;
                getline(cin,inputString1);
                cout << "How many paths to this location will you be entering? (Please enter an integer greater than or equal to 1):" << endl;
                getline(cin,inputString2);

                string inputString3;
                string inputString4;

                int numPaths = atoi(inputString2.c_str());
                for (int i = 0; i < numPaths; i++) {
					cout << "Enter the location that this link connects to:" << endl;
					getline(cin, inputString3);
					cout << "Enter the distance between the two delivery locations, the number of right turns, and the nuber of left turns.  Seperate each value by a comma." << endl;
					getline(cin, inputString4);

					vector <string> data;
					g.parseLine(inputString4, data);
					//data[0] is the distance, data[1] is the number of right turns, data[2] is the number of left turns.  This data needs to be converted to integer format.

                }
				break;
			}
            // Quit
            case 11:
            {
                cout << "Goodbye!" << endl;
                quit = true;
                break;
			}
            // invalid input
            default:
            {
                cout << "Invalid Input" << endl;
                //cin.clear();
                //cin.ignore(10000,'\n');
                break;
			}
        }
    }

    return 0;
}
