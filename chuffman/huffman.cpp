/**
 * HUFFMAN ENCODER
 * TODO: - nodes instead of pairs
 * - add comments...
 * 
 **/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
//#include <rtmidi/RtMidi.h> //not necessary right now...

using namespace std; 

template <class T>
class Node {
	private: 
		Node *left_child = NULL, *right_child = NULL;
		T value = 0;

	public:

		Node () : value (0) {} ;
		Node (T pvalue) : value (pvalue) {} ;
		~Node () {} ; //Destructor

		void add_child(T new_child){
			if (new_child>value)
				if (right_child == NULL)
				{
					right_child = new Node<T>;
					right_child->set_value(new_child);
				}
				else right_child->add_child(new_child);
			else
				if (left_child == NULL)
				{
					left_child = new Node<T>;
					left_child->set_value(new_child);
				}
				else left_child->add_child(new_child);
		}

		void set_value(T nvalue){
			value = nvalue;
		}

		T get_value(){
			return value;
		}

		void set_left_child(Node<T> *lchild){
			left_child = lchild;
		}

		void set_right_child(Node<T> *rchild){
			right_child = rchild;
		}

		Node<T> *get_left_child(){
			return left_child;
		}

		Node<T> *get_right_child(){
			return right_child;
		}

		int print_children(int index = 0){
			printf("index: %d, value: %d\n", index, value);
			if (left_child != NULL)
			{
				printf("LEFT\n");
				index = left_child->print_children(++index);
			}
			if (right_child != NULL)
			{
				printf("RIGHT\n");
				index = right_child->print_children(++index);
			}
			return index;
		}	


};

int main(){
	Node<int> tree (5);

    /**** TEMPORARY START ****/
	map<char, int> freq_table;
	string hello = "hello my name is karl johannes";

	for (int index = 0; index<hello.length(); index++)
	{
		char curr_char = hello.at(index);
		if(freq_table.count(curr_char)!=0)
			freq_table[curr_char]++;
		else freq_table.insert(pair<char,int>(curr_char,1));
	}

    /*** ORDERING ***/
    vector<pair<char,int>> ordered_table;
    copy(freq_table.begin(), 
            freq_table.end(),
            back_inserter<vector<pair<char,int>>>(ordered_table)
        );

    sort(ordered_table.begin(), ordered_table.end(),
            [](const pair<char,int> & left, const pair<char,int> & right){
                return left.second > right.second;
            }
        );

    Node<pair<char,int>> *last_element = new Node<pair<char,int>>(ordered_table.back());
    ordered_table.pop_back();

    Node<pair<char,int>> *second_element = new Node<pair<char,int>>(ordered_table.back());
    ordered_table.pop_back();

    Node<pair<char,int>> new_node (pair<char,int>(last_element->get_value().first, last_element->get_value().second + second_element->get_value().second));
    new_node.set_left_child(last_element);
    new_node.set_right_child(second_element);

    printf("%c and %d\n",new_node.get_value().first,new_node.get_value().second);

    //printf("char: %c and num: %d\n", last_element.first, last_element.second);
    //printf("char: %c and num: %d\n", second_element.first, second_element.second);

    /**** TEMPORARY END ****/

    return 0;

}
