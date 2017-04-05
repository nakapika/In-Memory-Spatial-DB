#include <iostream>
#include <vector>
#include <string.h>
#include "query-processing.h"
#include "catalog.h"

using namespace std;
int get_geom_type_from_string(string geom) {
    if(geom.compare("POINT") == 0) return 1;
    if(geom.compare("RECTANGLE") == 0) return 2;
    cout << "Invalid Parameter for geometry type.\n"; 
    return -1;
}

bool is_param_sufficient(vector<string> tokens, int required_params) {
    if(tokens.size() < required_params) {
        cout << "Insufficient Parameters\n";   
        return false;
    }
    return true;
}

vector<string> split(string str, string sep) {
    char* cstr = const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current = strtok(cstr, sep.c_str());
    while(current != NULL) {
        arr.push_back(current);
        current = strtok(NULL, sep.c_str());
    }
    return arr;
}

vector<vector<string> > get_predicates_from_string(string predicates) {
    vector<string> left_params = split(predicates, "|");
    vector<vector<string> > predicate_vector;
    for(int i=1; i<= left_params.size(); i++) {
        predicate_vector.push_back(split(left_params[i], ":"));   
    }
    return predicate_vector;
}

int main() {
    while(1) {
        string query, cmd;
        Catalog catalog = Catalog::getInstance();
        cout << "\nPlease, enter your query: ";
        getline (cin, query);
        vector<string> query_tokens = split(query, " ");            
        if(query_tokens[0].compare("LOAD") == 0) {            
            if(is_param_sufficient(query_tokens, 6)) { 
                int collection_structure = 2;
                //loadData(query_tokens[1], query_tokens[2], get_geom_type_from_string(query_tokens[3]), query_tokens[4], collection_structure);                 
                cout << "Loaded " << query_tokens[3] << " data collection into " << query_tokens[1] << "." << query_tokens[2] <<
                 " from " << query_tokens[4]; 
            }
        }  else  if(query_tokens[0].compare("CREATE") == 0) {
            if(is_param_sufficient(query_tokens, 3)) {
                if(query_tokens[1].compare("SPATIAL-INDEX")) {
                    //Class name unknown.
                } else if(query_tokens[1].compare("DATA-INDEX")) {
                    //Class name unknown.
                } else {
                    cout << "Invalid index type.\n";                             
                }

            }      
        } else if(query_tokens[0].compare("SELECT") == 0) {    
            string query_param = query.substr(7);
            int left_param_end = query_param.find("]"); 
            string left_branch = query_param.substr(1, left_param_end-1);            
            
            // QueryTree query = new QueryTree();
            vector<string> collection_details = split(left_branch.substr(0, left_branch.find("|")), " ");
            if(collection_details[0] == "POINT") {
                // query.setLeftPoints(catalog.getPointCollectionByName(collection_details[1], collection_details[2]));
            } else {
                // query.setLeftRectangles(catalog.getRectangleCollectionByName(collection_details[1], collection_details[2]));
            }
            vector<vector<string> > left_filter_param = get_predicates_from_string(left_branch);
            // query.setLeftFilter(left_filter_param);


        } else {
            cout << "Invalid command\n";        
        }
    }
    return 0;
}
