#include "sequence.h"

/*	Function:  Parameterized constructor
                -- Creates an object of the Sequence class with default values and provided number of nodes.
	Inputs:    size 
                -- number of nodes in the sequence (unsigned int)
	Returns:   void
	Side effects:  The new object of Sequence Class is initialized which has
                    sz=value passed as argument, 
                    head = pointer to first sequence node,
                    tail= pointer to last sequence node
                    Doubly linked list of sequence node is created whichh contain size number of nodes
                    and each node contains uninitialized value and two pointers pointing to next and previous nodes            
*/
Sequence::Sequence( size_type sz )
{
    numElts=sz;
    head=tail=NULL;

    //loop to initialize the sequence node with value and pointers
    for (int i = 0; i < sz; i++)
    {
        if (head == NULL) 
        {
            SequenceNode *newSequenceNode = new SequenceNode();
            head = newSequenceNode;
            tail = newSequenceNode;
        }

        else
        { 
            SequenceNode *newSequenceNode = new SequenceNode();
            tail->next = newSequenceNode;
            newSequenceNode->prev = tail;
            tail=newSequenceNode;
        }
    }
}



/*	Function:  Copy constructor
                -- Creates an object of Sequence class whose value is initalized by another object of same class
                    which is passed as an arguments ie it makes deep copy.
	Inputs:     &s
                --Reference to the Object of Sequence Class
	Returns:   void
	Side effects:  The new object of Sequence Class is created and initialized with the value of
                    the object which is passed as argument by making deep copy.
                                
*/
Sequence::Sequence( const Sequence& s )
{
    numElts=s.numElts;
    SequenceNode *current=new SequenceNode();
    current=s.head;
    SequenceNode *copyNode=new SequenceNode(current->elt);
    SequenceNode *previous=nullptr;
    head=copyNode;
    current=current->next;

    //loop to copy the value of object in another object node by node
    while (current !=NULL)
    {   
        SequenceNode *newNode=new SequenceNode(current->elt);
        copyNode->next=newNode;
        

        copyNode->prev=previous;
        previous=copyNode;
        copyNode=copyNode->next;
        current = current->next;
    }
    copyNode->prev=previous;
    tail=copyNode;
}



/*	Function:  Destructor
                -- Release the memory allocated to the object of Sequence Class
	Inputs:     void
	Returns:   void
	Side effects:  Destroy the objects by releasing the allocated memory.             
*/
Sequence::~Sequence()
{
   if(head !=NULL)
    {
        SequenceNode* current = head; 
        SequenceNode* nextNode;

        //loop that free the memory the used by sequence node
        while (current != NULL)
        { 
            nextNode = current->next; 
            delete current; 
            current = nextNode;
        }
    }
}



/*	Function:  operator= 
                -- Overload = operator
	Inputs:     &s
                -- Reference to the Object of Sequence Class
	Returns:   Reference to the copied sequence
	Side effects:  Copy the value from object that is passed as argument to the object that called it.       
*/
Sequence& Sequence::operator=( const Sequence& s )
{
    if (head !=NULL)
    {
        SequenceNode* current = head; 
        SequenceNode* nextNode;

        //loop to free the memory and to delte old nodes
        while (current != NULL)
        { 
            nextNode = current->next; 
            delete current; 
            current = nextNode;
        } 
    }

    numElts=s.numElts;
    SequenceNode *current=new SequenceNode();
    current=s.head;
    SequenceNode *copyNode=new SequenceNode(current->elt);
    SequenceNode *previous=nullptr;
    head=copyNode;
    current=current->next;

    // loop to assign the new value and allocation of memory
    while (current !=NULL)
    {   
        SequenceNode *newNode=new SequenceNode(current->elt);
        copyNode->next=newNode;
        

        copyNode->prev=previous;
        previous=copyNode;
        copyNode=copyNode->next;
        current = current->next;
    }
    copyNode->prev=previous;
    tail=copyNode;
    return (*this);    
}




/*	Function:  operator[]
                -- Overload [] operator
	Inputs:     position
                -- index of the node(unsigned int)
	Returns:   Reference to the value of the node
	Side effects:  Returns the value of the node which is in the index position 
                    Throws an error when out of range index is used     
*/
Sequence::value_type& Sequence::operator[]( size_type position )
{
    if (position>=0 && position<numElts)// condtion checking the range of the position
    {
        int i; 
        SequenceNode* current=head;
        for (i = 0; i < position; i++)
        {
            current = current->next;
        }
        return(current->elt);
    }

    else
    {
        throw exception();
    }

}




/*	Function:  push_back
                -- add new node at the end of the sequence
	Inputs:     &value
                -- Value of the sequence node to be added(int)
	Returns:   void
	Side effects:  New sequence node is added in the end of sequence having the provided value      
*/
void Sequence::push_back( const value_type& value )
{
    SequenceNode* newSequenceNode=new SequenceNode(value);
    if (head==nullptr)
    {
        head=tail=newSequenceNode;
    }
    else
    {
        newSequenceNode->prev=tail;
        tail->next=newSequenceNode;
        tail=newSequenceNode;
    }
    numElts++;
}




/*	Function:  pop_back
                -- remove node from the end of the sequence
	Inputs:    void
	Returns:   void
	Side effects:  Sequence node at the end of the sequence is deleted and pointers are updated accordingly
                    Throw error if it is called on empty sequence   
*/
void Sequence::pop_back()
{
    if (numElts>0)//checking for empty sequence
    {
        if (head==tail)
        {
            SequenceNode* current=tail;
            delete current;
            head=tail=nullptr;
        }
        else
        {        
            SequenceNode* current=tail;
            tail=current->prev;
            tail->next=nullptr;
            delete current;
        }
        numElts--;
    }
    else
    {
        throw exception();
    }
    
}




/*	Function:  insert
                -- add sequence node at the provided postion with provided values
	Inputs:    position--index where the node is to added(unsigned int)
                value -- value hold by the node(int)
	Returns:   void
	Side effects:  New sequence node is added in the provided position with given values and ponters are updated
                  Throw error if insert is made on the invalid position  
*/
void Sequence::insert( size_type position, value_type value )
{
    if (position>=0 && position<numElts)
    {
        SequenceNode* current=head;

        //code to insert at the head position
        if (position==0)
        {
            SequenceNode* newSequenceNode=new SequenceNode(value);
            newSequenceNode->next=head;
            head->prev=newSequenceNode;
            head=newSequenceNode;
        }
        // code to insert in other position
        else
        {
            for (int i = 0; i < position; i++)
            {
                current = current->next;
            }
            SequenceNode* newSequenceNode=new SequenceNode(value);
            newSequenceNode->next=current;
            newSequenceNode->prev=current->prev;
            current->prev->next=newSequenceNode;
            current->prev=newSequenceNode;
        }
        numElts++;
    }
    else
    {
        throw exception();
    }
}




/*	Function:  front
                -- return the value of the node which is pointed by head
	Inputs:    void
	Returns:   reference to the value of head
	Side effects:  reference to the value of the head node is returned 
                    Throw error if it is called on empty  sequence
*/
const Sequence::value_type& Sequence::front() const
{
    if (!this->empty())
    {
        return(head->elt);
    }
    else
    {
        throw exception();
    }
}




/*	Function:  back
                -- return the value of the node which is pointed by tail
	Inputs:    void
	Returns:   reference to the value of tail
	Side effects:  reference to the value of the tail node is returned 
                    Throw error if called on empty sequence
*/
const Sequence::value_type& Sequence::back() const
{
    if (!this->empty())
    {
        return(tail->elt);
    }
    else
    {
        throw exception();
    }
}





/*	Function:  empty
                -- find if the sequence is empty or not
	Inputs:    void
	Returns:   bool: True if empty
                     False if not empty
	Side effects:  True is returned when sequence is empty otherwise false
*/
bool Sequence::empty() const
{
    if (numElts==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}





/*	Function:  size
                -- find the size of the sequence
	Inputs:    void
	Returns:   number of nodes in the sequence (int)
	Side effects:  Number of nodes in the sequence is returned
*/
Sequence::size_type Sequence::size() const
{
    return(numElts);
}




/*	Function:  clear
                -- Use to reset the sequence by deleting all the nodes
	Inputs:    void
	Returns:   void
	Side effects:  Sequence is reset and all the nodes are removed by clearing memory
*/
void Sequence::clear()
{
    if(head !=NULL)
    {
        SequenceNode* current = head; 
        SequenceNode* nextNode;

        //loop to free the memory of the sequence nodes in the seqeunce
        while (current != NULL)
        { 
            nextNode = current->next; 
            delete current; 
            current = nextNode;
        }
    }
    head=nullptr;
    tail=nullptr;
    numElts=0;
}




/*	Function:  erase
                -- delete the number of nodes in the specified position
	Inputs:    position-- index from where nodes are to be deleted(unsigned int)
                count-- number of nodes to be deleted(unsigned int)
	Returns:   void
	Side effects:  Number of nodes are delted from the specified index and parameters are updated.
                    Throw exception if function tried to delete from invalid position
*/
void Sequence::erase( size_type position, size_type count )
{
    if (position>=0 && position<numElts)//checking the position range
    {
        if ((position+count)>=0 && (position+count)<=numElts)// checking range after adding count value
        {
            SequenceNode* current=head;
            for (int i = 0; i < position; i++)
            {
                current = current->next;
            }
            SequenceNode* tmp,*startNode;
            startNode=current->prev;

            //code to delte the node and free memory
            for (int j = 0; j < count; j++)
            {
                tmp=current->next;
                delete current;
                current=tmp;
            }

            //code to update the pointers
            if (startNode==nullptr)
            {
                if (current==nullptr)
                {
                    head=tail=nullptr;
                }
                else
                {
                    current->prev=nullptr;
                    head=current;
                }
            }
            else
            {
                if (current==nullptr)
                {
                    startNode->next=current;
                    tail=startNode;
                }
                else
                {
                    startNode->next=current;
                    current->prev=startNode;
                }

            }
            numElts=numElts-count;
        }
        else
        {
            throw exception();
        }
        
    }
    else
    {
        throw exception();
    }
}





/*	Function:  operator<<
                -- Overlaod << operator
	Inputs:    &os-- referece to ostream object
                &s-- reference to sequence object
	Returns:   reference to ostream object
	Side effects:  << operator is overloaded to print the object of sequence class
*/
ostream& operator<<( ostream& os, Sequence& s )
{
    os<<"<";
    int size=s.size();
    for (int i = 0; i < size; i++)
    {
        if (i==(size-1))
        {
            os<<s[i];
        }
        else
        {
            os<<s[i]<<", ";
        }
    }
    os<<">"<<endl;
    return(os);
}