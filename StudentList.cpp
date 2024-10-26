	#include "StudentList.h"
	
	
    struct Node {
    Student student;
    Node* next;

    Node(Student s) : student(s), next(nullptr) {}
};
	// Define a constructor to initialize the list. The list starts with no Students
    StudentList::StudentList() : head(nullptr), tail(nullptr), size(0) {}

   
	// return the number of students currently in the list
	
	int StudentList::listSize() {
    return size;

	//add a Node with a student to the front (head) of the list.
	void StudentList::addFront(Student s) {
    Node* newNode = new Node(s);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}

	//add a Node with a student to the back (tail) of the list.
	void StudentList::addBack(Student s) {
    Node* newNode = new Node(s);
    if (!tail) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

	//Print out the names of each student in the list.
	void StudentList::printList() {
    Node* current = head;
    while (current) {
        cout << current->student.getName() << endl; 
        current = current->next;
    }
}

	// Remove the Node with the student at the back (tail) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popBack() {
    if (!tail) {
        cout << "Error: List is empty!" << endl;
        return;
    }
    if (head == tail) {
        delete tail;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    size--;
}

	// Remove the Node with the student at the front (head) of the list
	// should not fail if list is empty! Print an error message if this occurs
	// Don't forget that your head and tail pointers will be null pointers if the list is empty
	void StudentList::popFront() {
    if (!head) {
        cout << "Error: List is empty!" << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    if (!head) {
        tail = nullptr;
    }
    size--;
}

	//insert a student at the position "index".
	// for this list, count head as index 0
	// if index is outside of current list range, 
	// print a message and insert the student at the back of the list
	// the previous Node at your target index should be moved forward. "For exampe, Node with student at index i, becomes index i+1" 
	// Remember that you already have methods that can add students to the front or back of list if needed! Don't repeat this code.
	void StudentList::insertStudent(Student s, int index) {
    if (index < 0 || index > size) {
        cout << "Index out of bounds. Inserting at back instead." << endl;
        addBack(s);
        return;
    }
    if (index == 0) {
        addFront(s);
        return;
    }
    Node* newNode = new Node(s);
    Node* current = head;
    for (int i = 0; i < index - 1; ++i) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    if (newNode->next == nullptr) {
        tail = newNode;
    }
    size++;
}

	//find the student with the given id number and return them
	// if no student matches, print a message 
	// and create and return a dummy student object
	Student StudentList::retrieveStudent(int idNum) {
    Node* current = head;
    while (current) {
        if (current->student.getId() == idNum) { 
            return current->student;
        }
        current = current->next;
    }
    cout << "Student not found!" << endl;
    return Student(); 
}

	// Remove a Node with a student from the list with a given id number
	// If no student matches, print a message and do nothing
	void StudentList::removeStudentById(int idNum) {
    if (!head) {
        cout << "Error: The List is empty!" << endl;
        return;
    }
    if (head->student.getId() == idNum) {
        popFront();
        return;
    }
    Node* current = head;
    while (current->next && current->next->student.getId() != idNum) {
        current = current->next;
    }
    if (current->next) {
        Node* temp = current->next;
        current->next = current->next->next;
        if (temp == tail) {
            tail = current;
        }
        delete temp;
        size--;
    } else {
        cout << "Student is not found!" << endl;
    }
}

	//Change the gpa of the student with given id number to newGPA
	void StudentList::updateGPA(int idNum, float newGPA) {
    Node* current = head;
    while (current) {
        if (current->student.getId() == idNum) { 
            current->student.setGPA(newGPA);
            return;
        }
        current = current->next;
    }
    cout << "Student not found!" << endl;
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
    if (!otherList.head) return; 
    if (!head) {
        head = otherList.head;
        tail = otherList.tail;
    } else {
        tail->next = otherList.head;
        tail = otherList.tail;
    }
    size += otherList.size;
    otherList.head = otherList.tail = nullptr; 
    otherList.size = 0;
}

	//create a StudentList of students whose gpa is at least minGPA.
	//Return this list.  The original (current) list should
	//not be modified (do not remove the students from the original list).
	StudentList StudentList::honorRoll(float minGPA) {
    StudentList honorRollList;
    Node* current = head;
    while (current) {
        if (current->student.getGPA() >= minGPA) { 
            honorRollList.addBack(current->student);
        }
        current = current->next;
    }
    return honorRollList;
}

