#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time
#include <string>  // For std::string
#include <stack>   // For std::stack

using namespace std;

// Forward declaration of classes
class Command;
class Cards;
class Solitaire;
class Control;

// Utility function to check if a number is already in an array
#include <iostream>
using namespace std;
#include <stack>
// Card class definition
bool check(int num, int arr[])
{
    for (int i = 0; i < 52 && arr[i] != -1; i++)
    {
        if (num == arr[i])
            return false;
    }
    return true;
}

// Function to get a random number not already in the array
int getRandomNumber(int arr[])
{
    int newNum;
    do
    {
        newNum = rand() % 52; // Generate a random number between 0 and 51
    } while (!check(newNum, arr)); // Ensure it is different from previous numbers
    return newNum;
}
class Cards
{
private:
    char color; // 'r' for red, 'w' for white
    int number; // A, 2-10, J, Q, K
    char sign;  // 'h' = hearts, 's' = spade, 'l' = leaf, 'd' = diamond

public:
    Cards() : color('\0'), number(0), sign('\0') {}

    char getsign() { return sign; }
    int getnumber() { return number; }

    void print()
    {
        if (color == 'r')
        {
            cout << "\033[31m"; // Red color code for red cards
        }

        if (number == 1)
            cout << "A";
        else if (number == 11)
            cout << "J";
        else if (number == 12)
            cout << "Q";
        else if (number == 13)
            cout << "K";
        else
            cout << number;

        if (sign == 'h')
            cout << "\u2665"; // Hearts symbol
        else if (sign == 'd')
            cout << "\u2666"; // Diamonds symbol
        else if (sign == 's')
            cout << "\u2660"; // Spades symbol
        else if (sign == 'l')
            cout << "\u2618"; // Leaf symbol
        cout << "\033[0m ";   // Reset color
    }

    void initialize(char c, int num, char s)
    {
        color = c;
        sign = s;
        number = num;
    }

    bool comparelist(Cards *c2)
    {
        return c2->color != color && c2->number == number - 1;
    }

    bool comparefoundation(Cards *c2)
    {
        return c2->color == color && c2->number == number + 1;
    }
};

// Linked list definition
template <typename T>
class List
{
public:
    class Node
    {
    public:
        T *card;
        Node *next;
        Node *prev;

        Node() : card(nullptr), next(nullptr), prev(nullptr) {}
        Node(T *c, Node *n = nullptr, Node *p = nullptr) : card(c), next(n), prev(p) {}
    };

    Node *head;
    Node *tail;
    int size;

public:
    class iterator
    {
    private:
        Node *current;

    public:
        iterator(Node *node = nullptr) : current(node) {}

        iterator &operator++()
        {
            current = current ? current->next : nullptr;
            return *this;
        }
        iterator &operator--()
        {
            current = current ? current->prev : nullptr;
            return *this;
        }
        bool operator==(const iterator &rhs) const { return current == rhs.current; }
        bool operator!=(const iterator &rhs) const { return current != rhs.current; }
        T &operator*() const { return *(current->card); }
    };

    List() : head(nullptr), tail(nullptr), size(0) {}

    void insertAtHead(T *c)
    {
        Node *temp = new Node(c);
        size++;
        if (!head)
        {
            head = tail = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }

    void print(int show = 1)
    {
        Node *temp = tail;
        if (!temp)
        {
            cout << "[]" << " ";
            return;
        }
        int i = 0;
        while (i < size - show && temp)
        {
            cout << "[]" << " ";
            i++;
            temp = temp->prev;
        }
        while (temp && i < size)
        {
            temp->card->print(); // Print each card
            temp = temp->prev;
            i++; // Move to the next Node
        }
    }

    int getSize() { return size; }
    T *gethead() { return head ? head->card : nullptr; }
    bool checkempty() { return head == nullptr; }

    void deleteathead()
    {
        if (head)
        {
            Node *temp = head;
            head = head->next;
            if (head)
                head->prev = nullptr;
            delete temp;
            size--;
        }
    }
    Node *getthead()
    {
        return head;
    }
    Node *getHeadNode() { return head; }
    iterator begin() const
    {
        return iterator(head);
    }

    iterator end() const
    {
        return iterator(nullptr);
    } // New function to return the head node
};

// Column class definition
class Column
{
private:
    List<Cards> cl;
    int show;

public:
    Column() { show = 1; }

    void addtocolumn(Cards *c) { cl.insertAtHead(c); }
    void insertl(Cards *c)
    {
        if (cl.checkempty())
            show = 1;
        else
            show++;
        cl.insertAtHead(c);
    }

    int getSize() { return cl.getSize(); }
    void print() { cl.print(show); }
    Cards *gethead() { return cl.gethead(); }
    bool checkempty() { return cl.checkempty(); }
    void deleteathead()
    {
        cl.deleteathead();
    }
    Cards *getshowhead(int n)
    {
        List<Cards>::Node *temp = cl.getthead();
        int i = 0;
        while (i < n - 1 && temp->next)
        {
            temp = temp->next;
            i++;
        }
        return temp->card;
    }
    void changellshows(Column &src, int num, bool undo = false)
    {
        if (undo)
        {
            show--;
            // src.show++;
            return;
        }
        show = show + src.show;
        src.show = src.show - num + 1;
    }
    void decshow()
    {
        if (show > 1)
            show--;
    }
    void incshow() { show++; }

    List<Cards>::Node *getHeadNode() { return cl.getHeadNode(); } // New function to return head node of the list
};

// Stack definition using a linked list
template <typename T>
class Stack
{
private:
    List<T> clist;
    int toppos;

public:
    Stack() : toppos(-1) {}

    void push(T *c)
    {
        clist.insertAtHead(c);
        toppos++;
    }

    void peek()
    {
        if (!clist.checkempty())
        {
            Cards *c = clist.gethead();
            c->print();
        }
        else
            cout << "[]";
    }
    T *top() { return clist.gethead(); }
    bool pop()
    {
        if (!clist.checkempty())
        {
            clist.deleteathead();
            toppos--;
            return true;
        }
        return false;
    }
    int getNum() { return 1 + toppos; }
    bool empty() { return toppos == -1; }
};

// Foundation class definition
class Foundation
{
private:
    Stack<Cards> fd;
    char sign;

public:
    Foundation() : sign('\0') {}

    void insertf(Cards *c)
    {
        if (sign == '\0' || sign == c->getsign())
        {
            if (fd.empty() && c->getnumber() == 1)
            {
                sign = c->getsign();
                fd.push(c);
            }
            else if (!fd.empty() && fd.top()->getnumber() == c->getnumber() - 1)
            {
                fd.push(c);
            }
        }
    }

    void peek() { fd.peek(); }
    int getNum() { return fd.getNum(); }
    Cards *top() { return fd.top(); }
    void pop() { fd.pop(); }
    bool empty() { return fd.empty(); }
};

// Command class definition
class Command
{
private:
    char first;         // Command type
    string source;      // Source location
    string destination; // Destination location
    int number;

public:
    Command() : first('\0'), number(0) {}

    void setcommand(char f, const string &s, const string &d, int num)
    {
        first = f;
        source = s;
        destination = d;
        number = num;
    }

    char getFirst() const { return first; }
    string getSource() const { return source; }
    string getDestination() const { return destination; }
    int getNumber() const { return number; }
};

// Solitaire game class definition
class Solitaire;
class Undo
{
private:
    stack<Command> commandStack; // Standard stack to keep track of commands

public:
    void addCommand(const Command &cmd) { commandStack.push(cmd); }

    void undo(Solitaire *game);
};

class Solitaire
{
private:
    Stack<Cards> st;           // Stock Stack
    Stack<Cards> waste;        // Waste Stack
    Foundation foundations[4]; // Four foundation Stacks
    Column columns[7];         // Seven columns for tableau
    Cards deck[52];
    int rannum[52]; // Deck of Cards
    Undo undos;     // Undo stack

public:
    Solitaire()
    {
        const char signs[4] = {'h', 'd', 'l', 's'};
        const char colors[4] = {'r', 'r', 'w', 'w'};

        for (int i = 0; i < 4; i++)
        {
            for (int j = 1; j <= 13; j++)
            {
                deck[i * 13 + j - 1].initialize(colors[i], j, signs[i]);
            }
        }
        for (int i = 0; i < 52; i++)
        {
            rannum[i] = -1;
        }
    }
    void undoDraw()
    {
        if (!waste.empty())
        {
            Cards *topCard = waste.top();
            waste.pop();      // Remove from waste
            st.push(topCard); // Push back to stock
        }
    }

    void undoMove(const Command &lastCommand)
    {
        char srcType = lastCommand.getSource()[0];             // Get source type
        char destType = lastCommand.getDestination()[0];       // Get destination type
        int srcIndex = lastCommand.getSource()[1] - '1';       // Get source index (0-based)
        int destIndex = lastCommand.getDestination()[1] - '1'; // Get destination index (0-based)

        if (srcType == 'w' && destType == 'c')
        { // Move from waste to column
            // This should be handled by undoDraw, as drawing from stock to waste
            Cards *undocard = columns[destIndex].gethead();
            columns[destIndex].deleteathead();
            columns[destIndex].decshow();
            waste.push(undocard);
            // undoDraw();
        }
        else if (srcType == 'c' && destType == 'c')
        {                                                                       // Move from column to column
            moveListToList(destIndex, srcIndex, lastCommand.getNumber(), true); // Move back
        }
        else if (srcType == 'c' && destType == 'f')
        {
            // Move from column to foundation
            moveFoundationToList(destIndex, srcIndex); // Move back
        }
        else if (srcType == 'f' && destType == 'c')
        {                                              // Move from foundation to column
            moveListToFoundation(srcIndex, destIndex); // Move back
        }
        else if (srcType == 'w' && destType == 'f')
        {
            movefoundationtowaste(destIndex);
        }
        else if (srcType == 'f' && destType == 'w')
        {
            moveWasteToFoundation(srcIndex);
        }
    }

    void movefoundationtowaste(int Index)
    {
        if (!foundations[Index].empty())
        {
            Cards *topcard = foundations[Index].top();
            foundations[Index].pop();
            waste.push(topcard);
        }
    }
    void initializedeck()
    {
        srand(static_cast<unsigned int>(time(0))); // Seed RNG

        for (int i = 0; i < 52; ++i)
        {
            int randomNum = getRandomNumber(rannum);
            if (i < 1)
                columns[0].addtocolumn(&deck[randomNum]);
            else if (i < 3)
                columns[1].addtocolumn(&deck[randomNum]);
            else if (i < 6)
                columns[2].addtocolumn(&deck[randomNum]);
            else if (i < 10)
                columns[3].addtocolumn(&deck[randomNum]);
            else if (i < 15)
                columns[4].addtocolumn(&deck[randomNum]);
            else if (i < 21)
                columns[5].addtocolumn(&deck[randomNum]);
            else if (i < 28)
                columns[6].addtocolumn(&deck[randomNum]);
            else
                st.push(&deck[randomNum]); // Push to stock
            rannum[i] = randomNum;         // Update previous number
        }
    }

    void print()
    {
        cout << "Stock " << "[] " << "(" << st.getNum() << ")" << endl;
        cout << "Waste ";
        waste.peek();
        cout << "(" << waste.getNum() << ")" << endl;
        for (int i = 0; i < 4; i++)
        {
            cout << "Foundation " << i + 1 << " ";
            foundations[i].peek();
            cout << "(" << foundations[i].getNum() << ")" << endl;
        }
        for (int i = 0; i < 7; i++)
        {
            cout << "Column " << (i + 1) << ": ";
            columns[i].print();
            cout << endl;
        }
    }
 bool checkmoves()
{
    // Check if there are valid moves available
    if (!st.empty()) // If the waste is empty and there's still a stockpile to draw from
        return true;

    // Check if any cards in the waste can be moved
    if (!waste.empty())
    {
        Cards *checkWaste = waste.top();

        // Check all columns for valid moves from waste to column
        for (int i = 0; i < 7; i++)
        {
            if ((columns[i].checkempty() && checkWaste->getnumber() == 13) ||
                (!columns[i].checkempty() && columns[i].gethead()->comparelist(checkWaste)))
            {
                return true; // Valid move from Waste to Column
            }
        }

        // Check all foundations for valid moves from waste to foundation
        for (int i = 0; i < 4; i++)
        {
            if ((foundations[i].top() == nullptr && checkWaste->getnumber() == 1) ||
                (foundations[i].top() != nullptr && foundations[i].top()->comparefoundation(checkWaste)))
            {
                return true; // Valid move from Waste to Foundation
            }
        }
    }

    // Check moves between columns
    for (int i = 0; i < 7; i++)
    {
        Cards *listCard = columns[i].gethead();
        if (listCard)
        {
            // Check against other columns for valid moves
            for (int j = 0; j < 7; j++)
            {
                if (i != j) // Skip self
                {
                    Cards *otherCard = columns[j].gethead();
                    if (otherCard && listCard->comparelist(otherCard))
                    {
                        return true; // Valid move from Column to Column
                    }
                }
            }

            // Check against foundations for valid moves
            for (int j = 0; j < 4; j++)
            {
                if ((foundations[j].top() == nullptr && listCard->getnumber() == 1) ||
                    (foundations[j].top() != nullptr && foundations[j].top()->comparefoundation(listCard)))
                {
                    return true; // Valid move from Column to Foundation
                }
            }
        }
    }

    // Check deeper moves within the waste stack
    Stack<Cards> temp;
    while (!waste.empty())
    {
        temp.push(waste.top());
        waste.pop();
        Cards *cardtop = temp.top();

        // Check all columns for valid moves
        for (int i = 0; i < 7; i++)
        {
            if ((columns[i].checkempty() && cardtop->getnumber() == 13) ||
                (!columns[i].checkempty() && columns[i].gethead()->comparelist(cardtop)))
            {
                toptowaste(temp); // Restore cards to waste
                return true; // Valid move from Waste to Column
            }
        }

        // Check all foundations for valid moves
        for (int i = 0; i < 4; i++)
        {
            if ((foundations[i].top() == nullptr && cardtop->getnumber() == 1) ||
                (foundations[i].top() != nullptr && foundations[i].top()->comparefoundation(cardtop)))
            {
                toptowaste(temp); // Restore cards to waste
                return true; // Valid move from Waste to Foundation
            }
        }
    }

    toptowaste(temp); // Restore all cards back to waste
    return false; // No valid moves found
}

    void toptowaste(Stack<Cards> temp)
    {
        while(!temp.empty())
        {
            waste.push(temp.top());
            temp.pop();
        }
    }
    void move(Command &current)
    {
        if (current.getFirst() == 's')
        { // Draw from stockpile to waste
            if (!st.empty())
            {
                waste.push(st.top());
                st.pop();
                undos.addCommand(current);
            }
            else if (st.empty() && !waste.empty())
            {

                for (int j = waste.getNum(); j > 0; j--)
                {
                    st.push(waste.top());
                    waste.pop();
                }
            }
        }
        else if (current.getFirst() == 'z')
        { // Undo the last move
            undos.undo(this);
            return;
        }
        else if (current.getFirst() == 'm')
        {                                                // Handle move commands
            char srcType = current.getSource()[0];       // Get source type
            char destType = current.getDestination()[0]; // Get destination type

            int srcIndex = current.getSource()[1] - '1';       // Get source index (0-based)
            int destIndex = current.getDestination()[1] - '1'; // Get destination index (0-based)

            if (srcType == 'w' && destType == 'c')
            { // Waste to list (column)
                moveWasteToList(destIndex);
            }
            else if (srcType == 'c' && destType == 'c')
            { // List to list
                moveListToList(srcIndex, destIndex, current.getNumber());
            }
            else if (srcType == 'c' && destType == 'f')
            { // List to foundation
                moveListToFoundation(srcIndex, destIndex);
            }
            else if (srcType == 'f' && destType == 'c')
            { // Foundation to list
                moveFoundationToList(srcIndex, destIndex);
            }
            else if (srcType == 'w' && destType == 'f')
            { // Waste to foundation
                moveWasteToFoundation(destIndex);
            }
            undos.addCommand(current); // Add the move command to undo stack
        }
    }

    void moveWasteToList(int destIndex)
    {
        if (!waste.empty() && destIndex >= 0 && destIndex < 7)
        {
            Cards *topCard = waste.top();
            if (columns[destIndex].checkempty() || columns[destIndex].gethead()->comparelist(topCard))
            {
                waste.pop();                         // Remove from waste
                columns[destIndex].insertl(topCard); // Add to column
            }
        }
    }

    void moveListToList(int srcIndex, int destIndex, int num, bool undo = false)
    {
        if (srcIndex >= 0 && srcIndex < 7 && destIndex >= 0 && destIndex < 7)
        {
            Cards *srcHead = columns[srcIndex].getshowhead(num);
            Cards *destHead = columns[destIndex].gethead();
            if (srcHead && ((columns[destIndex].checkempty() && srcHead->getnumber() == 13) || destHead->comparelist(srcHead)) || undo)
            {
                Stack<Cards> cd;
                // change shows
                if (!undo)
                    columns[destIndex].changellshows(columns[srcIndex], num);
                if (undo)
                    columns[srcIndex].changellshows(columns[destIndex], num, undo);
                for (int i = 0; i < num; i++)
                {
                    cd.push(columns[srcIndex].gethead());
                    columns[srcIndex].deleteathead();
                }

                for (int i = 0; i < num; i++)
                { // Move `num` cards
                    Cards *cardToMove = cd.top();
                    cd.pop();
                    // Remove from source column
                    columns[destIndex].addtocolumn(cardToMove); // Add to destination column
                }
                // columns[srcIndex].incshow();
            }
        }
    }

    void moveListToFoundation(int srcIndex, int destIndex)
    {
        if (srcIndex >= 0 && srcIndex < 7 && destIndex >= 0 && destIndex < 4)
        {
            Cards *srcHead = columns[srcIndex].gethead();
            if (srcHead && (foundations[destIndex].top() == nullptr || foundations[destIndex].top()->comparefoundation(srcHead)))
            {
                columns[srcIndex].deleteathead(); // Remove from column
                foundations[destIndex].insertf(srcHead);
                columns[srcIndex].decshow(); // Add to foundation
            }
        }
    }

    void moveFoundationToList(int srcIndex, int destIndex)
    {
        if (srcIndex >= 0 && srcIndex < 4 && destIndex >= 0 && destIndex < 7)
        {
            Cards *foundationTop = foundations[srcIndex].top();
            if (foundationTop && (columns[destIndex].checkempty() || columns[destIndex].gethead()->comparelist(foundationTop)))
            {
                foundations[srcIndex].pop();                   // Pop from foundation stack
                columns[destIndex].addtocolumn(foundationTop); // Add to column
            }
        }
    }

    void moveWasteToFoundation(int destIndex)
    {
        if (destIndex >= 0 && destIndex < 4 && !waste.empty())
        {
            Cards *topCard = waste.top();
            if (foundations[destIndex].top() == nullptr || foundations[destIndex].top()->comparefoundation(topCard))
            {
                waste.pop();                             // Remove from waste
                foundations[destIndex].insertf(topCard); // Add to foundation
            }
        }
    }
    bool checkWin()
    {
        // Check if all foundations have 13 cards
        for (int i = 0; i < 4; ++i)
        {
            if (foundations[i].getNum() != 13) // Each foundation should have 13 cards
            {
                return false;
            }
        }
        // If all foundation stacks have 13 cards, the player has won
        return true;
    }
};

void Undo::undo(Solitaire *game)
{
    if (!commandStack.empty())
    {
        Command lastCommand = commandStack.top();
        commandStack.pop();

        // Determine the type of command to undo
        if (lastCommand.getFirst() == 's')
        { // Undo draw
            game->undoDraw();
        }
        else if (lastCommand.getFirst() == 'm')
        { // Undo move
            game->undoMove(lastCommand);
        }
    }
    else
    {
        cout << "No commands to undo!" << endl;
    }
}

// Control class definition
class Control
{
private:
    Solitaire game;
    Command current;

public:
    void startGame()
    {
        game.initializedeck();
        startPreview();
    }

    void startPreview()
    {
        cout << "WELCOME TO CONSOLE BASED SOLITAIRE GAME" << endl;
        cout << "HOW TO PLAY:" << endl;
        cout << "1. To draw a card from stockpile, use command 's'" << endl;
        cout << "2. To move a card, use command 'm' followed by the source, destination, and number (for number of Cards)." << endl;
        cout << "   For example: 'm c6,c1,2' means move two Cards from column 6 to column 1." << endl;
        cout << "   Command 'm w, c1, 1' means move 1 card from waste pile to column 1." << endl;
        cout << "3. To undo a move or draw operation use command 'z'" << endl;
        cout << endl;
        game.print();

        while (game.checkmoves())
        {
            getcommand();
            game.move(current);
            game.print();
        }
        if (game.checkWin())
        {
            cout << "Congratulations! You've won the game!" << endl;
        }
        else
            cout << "Better luck next time" << endl;
    }

    void getcommand()
    {
        char first;
        string source;
        string destination;
        int number = 0;

        cout << "\nCOMMAND: ";
        cin >> first;
        if (first != 's' && first != 'z')
        {
            if (first != 'm')
            {
                cout << "ERROR WRONG ";
                cin >> first;
            }
            cin >> source >> destination >> number;
        }

        current.setcommand(first, source, destination, number);
    }
};

// Main function
int main()
{
    Control game;
    game.startGame(); // Start the game
    return 0;
}
