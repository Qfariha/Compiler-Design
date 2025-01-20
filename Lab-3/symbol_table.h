#include "scope_table.h"

class symbol_table
{
private:
    scope_table *current_scope; //pointer
    int bucket_count; //index in hash/scope table
    int current_scope_id;
    ofstream& outlog;
public:

    
    symbol_table(int bucket_count, ofstream& log_stream) // Constructor
        : bucket_count(bucket_count), current_scope_id(0), outlog(log_stream) 
    {
        current_scope = new scope_table(bucket_count, ++current_scope_id, nullptr);
        cout << "New ScopeTable with ID "<< current_scope->get_unique_id()<<" created"<<endl<<endl;
        outlog << "New ScopeTable with ID " << current_scope->get_unique_id() << " created" << endl <<endl;
        
    }

    
    void enter_scope() {
    scope_table* new_scope = new scope_table(bucket_count, ++current_scope_id, current_scope); 
    current_scope = new_scope; 
    cout << "New ScopeTable with ID"<< current_scope->get_unique_id()<<" created"<<endl<<endl;
    outlog << "New ScopeTable with ID " << current_scope->get_unique_id() << " created" << endl<<endl;
    
    
    
    }

    void exit_scope(){
        if (current_scope == nullptr){
            return;
        }
        cout << "ScopeTable with ID"<< current_scope->get_unique_id()<<" removed"<<endl;
        outlog << "ScopeTable with ID " << current_scope->get_unique_id() << " removed" << endl;
        scope_table* parent_scope = current_scope->get_parent_scope();
        delete current_scope;
        current_scope = parent_scope;   
    }
    

    
    bool insert(symbol_info* symbol) { //inserting a new symbol 
        if (current_scope == nullptr) {
            return false;
        }
        
        return current_scope->insert_in_scope(symbol);
    }
    
	
    int getCurrentScopeID(){
        return current_scope->get_unique_id();
    }

   
    void print_all_scopes(ofstream& outlog){
        outlog<<"################################"<<endl<<endl;
        scope_table *temp = current_scope;
        while (temp != NULL)
        {   int id= temp->get_unique_id();
            temp->print_scope_table(outlog,id); //Printing all scopes by calling print_scope_table
            temp = temp->get_parent_scope();
        }
        outlog<<"################################"<<endl<<endl;
    }

};
