#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


/*
1 -> 2 -> 3 -> NULL
|         |     |
v         v     v
4 -> 5 -> 6 -> NULL
|        |     |
v        v     v
7 -> 8 -> 9 -> NULL
|         |       |
v         v       v
NULL     NULL    NULL

*/


//node for linked list 
struct node {
    double num;
    int row;     //stores row of node
    int column;  //stores column of node
    node* right; //points to node on the right
    node* down;  //points to node below
};

class List {
    private:
        node* head;
    public:
        //Constructor
        List() {
            //initialize List
            head = nullptr;
        }

        //Checks if List is empty
        bool isEmpty() {
            return head == nullptr;
        }

        node* getHead() {
            return head;
        }


        void print(ofstream& outputFile1) {
            node* currentRow = head;
            //loop through rows 
            while(currentRow != nullptr) {
                //keep track of row 
                node* currentColumn = currentRow;
                while(currentColumn != nullptr) {
                    //cout << currentColumn->num << " ";
                    outputFile1 << fixed << setprecision(1) << currentColumn->num << " ";
                    currentColumn = currentColumn->right;
                }
                outputFile1 << endl;
                currentRow = currentRow -> down;
            }
        }

        void insert(double n, int r, int c) {
            node* newNode = new node;
            newNode->num = n;
            newNode->row = r;
            newNode->column = c;
            newNode->right = nullptr;
            newNode->down = nullptr;

            if (isEmpty()) {
                head = newNode;
            } else {
                node* currentRow = head;
                node* prevRow = nullptr;

                //Checks if current row is equal to row number in matrix is at 
                //Loop untile correct row is found 
                while (currentRow != nullptr && currentRow->row < r) {
                    //keeps track of the row before
                    prevRow = currentRow;
                    //loop condition 
                    currentRow = currentRow->down;
                }

                node* currentColumn = currentRow;
                node* prevColumn = nullptr;

                // Checks if current column is equal to column number in matrix
                //Loops until correct column is found
                while (currentColumn != nullptr && currentColumn->column < c) {
                    prevColumn = currentColumn;
                    //loop condition
                    currentColumn = currentColumn->right;
                }

                //Check if node in row alread has same column number
                if (currentColumn != nullptr && currentColumn->column == c) {
                    //Insert after that node 
                    newNode->right = currentColumn->right;
                    currentColumn->right = newNode;
                } else {
                    // Node with the same column does not exist, insert in the column
                    if (prevColumn != nullptr) {
                        newNode->right = prevColumn->right;
                        prevColumn->right = newNode;
                    } else {
                        newNode->right = currentRow;
                        if (prevRow != nullptr) {
                            prevRow->down = newNode;
                        } else {
                            head = newNode;
                        }
                    }
                }

                if (currentRow != nullptr && currentRow != newNode) {
                    newNode->down = currentRow;
                }
            }
        }

        

        void add(List l1, List l2, ofstream& outputFile1) {
            
            node* firstListRow = l1.getHead();
            node* secListRow = l2.getHead();

            while(firstListRow != nullptr && secListRow != nullptr ) {
                //keeps track of row 
                node* firstListCol = firstListRow;
                node* secListCol = secListRow;
                while(firstListCol != nullptr && secListCol != nullptr) {
                    double sumNum = firstListCol->num + secListCol->num + 0.0;
                    outputFile1 << fixed << setprecision(1) << sumNum << " ";
                    firstListCol = firstListCol->right;
                    secListCol = secListCol->right;
                }
                outputFile1 << endl;
                firstListRow = firstListRow->down;
                secListRow = secListRow -> down;
            }
        }

        void sub(List l1, List l2, ofstream& outputFile1) {
            node* firstListRow = l1.getHead();
            node* secListRow = l2.getHead();

            while(firstListRow != nullptr && secListRow != nullptr ) {
                //keeps track of row 
                node* firstListCol = firstListRow;
                node* secListCol = secListRow;
                while(firstListCol != nullptr && secListCol != nullptr) {
                    int sumNum = firstListCol->num - secListCol->num + 0.0;
                    double floatsum = static_cast<double>(sumNum);
                    outputFile1 << fixed << setprecision(1) << floatsum << " ";
                    firstListCol = firstListCol->right;
                    secListCol = secListCol->right;
                }
                outputFile1 << endl;
                firstListRow = firstListRow->down;
                secListRow = secListRow -> down;
            }  
        }

        void mul(List l1, List l2, ofstream& outputFile1) {
            List transposed;
            node* currentRow = l2.getHead();
            while(currentRow != nullptr) {
                node* currentColumn = currentRow;
                while(currentColumn != nullptr) {
                    transposed.insert(currentColumn->num, currentColumn->column, currentColumn->row);
                    currentColumn = currentColumn->right;
                }
                currentRow = currentRow -> down;
            }

            node* firstListRow = l1.getHead();
            node* secListRow = transposed.getHead();
            while(firstListRow != nullptr) {
                secListRow = transposed.getHead();
                while(secListRow != nullptr) {
                    node* firstListCol = firstListRow;
                    node* secListCol = secListRow;
                    double sumNum = 0;
                    while(firstListCol != nullptr && secListCol != nullptr) {
                        sumNum += firstListCol->num * secListCol->num;
                        firstListCol = firstListCol->right;
                        secListCol = secListCol->right;
                    }
                    outputFile1 << fixed << setprecision(1) << sumNum << " ";
                    secListRow = secListRow -> down;
                }
                outputFile1 << endl;
                firstListRow = firstListRow -> down;
            }
            
        }

        void tra(List l1, ofstream& outputFile1) {
            List transposed;
            node* currentRow = l1.getHead();
            while(currentRow != nullptr) {
                node* currentColumn = currentRow;
                while(currentColumn != nullptr) {
                    transposed.insert(currentColumn->num, currentColumn->column, currentColumn->row);
                    currentColumn = currentColumn->right;
                }
                currentRow = currentRow -> down;
            }

            transposed.print(outputFile1);
        }

        void det3x3(List l1, ofstream& outputFile1) {
            node* headNode = l1.getHead();
            int a = headNode -> num;
            int b = headNode -> right -> num;
            int c = headNode -> right -> right -> num;

            headNode = headNode -> down;
            int d = headNode -> num;
            int e = headNode -> right -> num;
            int f = headNode -> right -> right -> num;

            headNode = headNode -> down;
            int g = headNode -> num;
            int h = headNode -> right -> num;
            int i = headNode -> right -> right -> num;

            int determinant;
            determinant = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
            double det = static_cast<double>(determinant);
            outputFile1 << fixed << setprecision(1) << det << endl;


        }
/*
        void det5x5(List l1) {
            node* headNode = l1.getHead();
            int a = headNode -> num;
            int b = headNode -> right -> num;
            int c = headNode -> right -> right -> num;
            int d = headNode -> right -> right -> right -> num;
            int e = headNode -> right -> right -> right -> right -> num;

            headNode = headNode -> down;
            int f = headNode -> num;
            int g = headNode -> right -> num;
            int h = headNode -> right -> right -> num;
            int i = headNode -> right -> right -> right -> num;
            int j = headNode -> right -> right -> right -> right -> num;

            headNode = headNode -> down;
            int k = headNode -> num;
            int l = headNode -> right -> num;
            int m = headNode -> right -> right -> num;
            int n = headNode -> right -> right -> right -> num;
            int o = headNode -> right -> right -> right -> right -> num;

            int determinant;

        }
*/

};


int main(int argc, char** argv) {
    //add a.txt b.txt output.txt
    string operation = "";
    string inputFile1 = "";
    string inputFile2 = "";
    string outputFile = "";

    //avoiding Segmentation Fault 
    //input command line arguments to variables
    if(argc-1 >= 3) {
        if(argc-1 == 4) {
            operation = argv[1];
            inputFile1 = argv[2];
            inputFile2 = argv[3];
            outputFile = argv[4];
        }
        if( argc-1 == 3) {
            operation = argv[1];
            inputFile1 = argv[2];
            outputFile = argv[3];
        }
    }

//First input file gets put into a Linked List
    List list1;
    ifstream file1;
    file1.open(inputFile1);
    if (file1.is_open()) {
        string line;
        int numRow = 0;
        int numColumn = 0;
        while(getline(file1,line)) {
            numRow++;
            istringstream iss(line);
            int num;
            numColumn = 0;
            while(iss>>num) {
                double doubleNum = static_cast<double>(num);
                numColumn++;
                list1.insert(doubleNum,numRow,numColumn);
            }
        }
    }

    //checks if inputFile2 is not emtpy -> opens file and adds to list if not
    List list2;
    if (inputFile2 != "") {
        ifstream file2;
        file2.open(inputFile2);
        int num;
        if(file2.is_open()) {
            string line;
            int numRow = 0;
            int numColumn = 0;
            while(getline(file2,line)) {
                numRow++;
                istringstream iss(line);
                int num;
                numColumn = 0;
                while(iss >> num) {
                    double doubleNum = static_cast<double>(num);
                    numColumn++;
                    list2.insert(doubleNum, numRow, numColumn);
                }
            }
        }
    }

    if(operation == "add") {
        List list3;
        ofstream outputFile1(outputFile);
        list3.add(list1,list2, outputFile1);
    }

    if(operation == "sub") {
        List list3;
        ofstream outputFile1(outputFile);
        list3.sub(list1, list2, outputFile1);
    }

    if(operation == "mul") {
        List list3;
        ofstream outputFile1(outputFile);
        list3.mul(list1, list2, outputFile1);
    }

    if(operation == "tra") {
        List list3;
        ofstream outputFile1(outputFile);
        list3.tra(list1, outputFile1);
    }

    if (operation == "det") {
        List list3;
        ofstream outputFile1(outputFile);
        list3.det3x3(list1, outputFile1);
    }


    return 0;
}