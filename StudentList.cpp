	#include "StudentList.h"

	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() {
		head = nullptr;
		tail = nullptr;
		numStudents = 0;
	}

	// return the number of students currently in the list
	int StudentList::listSize() {
		return numStudents;
	}

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
	Node* newNode = new Node(s, head, nullptr);
    if (head != nullptr)
        head->prev = newNode;
    else
        tail = newNode; // if list was empty
    head = newNode;
    numStudents++;
	}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
   Node* newNode = new Node(s, nullptr, tail);
    if (tail != nullptr)
        tail->next = newNode;
    else
        head = newNode; // if list was empty
    tail = newNode;
    numStudents++;
	}

	//Print out the names of each student in the list.
	void StudentList::printList() {
		 if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    Node* current = head;
    while (current != nullptr) {
        cout << current->data.name << endl;
        current = current->next;
    }
	}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
	 if (tail == nullptr) {
        cout << "List is empty. Cannot pop back." << endl;
        return;
    }
    Node* current = tail;
    tail = tail->prev;
    if (tail)
        tail->next = nullptr;
    else
        head = nullptr; // list became empty
    delete current;
    numStudents--;
	}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
	if (head == nullptr) {
        cout << "List is empty. Cannot pop front." << endl;
        return;
    }
    Node* current = head;
    head = head->next;
    if (head)
        head->prev = nullptr;
    else
        tail = nullptr; // list became empty
    delete current;
    numStudents--;
	}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
		 if (index <= 0) {
            addFront(s);
        } else if (index >= numStudents) {
            addBack(s);
        } else {
            Node* current = head;
            for (int i = 1; i < index; ++i) current = current->next;
            Node* node = new Node(s);
            node->next = current->next;
            current->next = node;
            numStudents++;
        }
	}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
		 Node* current = head;
        while (current) {
            if (current->data.id == idNum)
                return current->data;
            current = current->next;
        }
        cout << "Student not found\n";
        return Student();
	}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
		 Node* current = head;
        Node* prev = nullptr;
        while (current != nullptr) {
            if (current->data.id == idNum) {
                if (prev) prev->next = current->next;
                else head = current->next;
                if (current == tail) tail = prev;
                delete current;
                numStudents--;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Student not found\n";
	}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
		Node* current = head;
    while (current != nullptr) {
        if (current->data.id == idNum) {
            current->data.GPA = newGPA;
            cout << "GPA updated successfully.\n";
            return;
        }
        current = current->next;
    }
    cout << "Student not found.\n";
	}

	//Add all students from otherList to this list.
	//otherlist should be empty after this operation.
	/*
	For example, if the list has 3 students:
	s1 <-> s2 <-> s3
	and otherList has 2 students
	s4 <-> s5
	then after mergeList the currently list should have all 5 students
	s1 <-> s2 <-> s3 <-> s4 <-> s5
	and otherList should be empty and have zero students.
	*/
	void StudentList::mergeList(StudentList &otherList) {
		if (otherList.head == nullptr)
        return;
    if (head == nullptr) {
        head = otherList.head;
        tail = otherList.tail;
    } else {
        tail->next = otherList.head;
        otherList.head->prev = tail;
        tail = otherList.tail;
    }
    numStudents += otherList.numStudents;
    otherList.head = otherList.tail = nullptr;
    otherList.numStudents = 0;
	}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
		StudentList honor;
    Node* current = head;
    while (current != nullptr) {
        if (current->data.GPA >= minGPA)
            honor.addBack(current->data);
        current = current->next;
    }
    return honor;
	}

	//remove all students whose GPA is below a given threshold.
	// For example, if threshold = 3.0, all students with GPA less than 3.0
	// should be removed from the list. 
	// Be sure to correctly update both head and tail pointers when removing 
	// from the front or back, and adjust numStudents accordingly.
	// If the list is empty, print a message and do nothing.
	void StudentList::removeBelowGPA(float threshold) {
		if (head == nullptr) {
        cout << "List is empty.\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        if (current->data.GPA < threshold)
            removeStudentById(current->data.id);
        current = next;
    }
	}
