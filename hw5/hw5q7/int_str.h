#include <string>

using namespace std;

class int_str  {
	public:
		int_str (int &other_variable);
		int_str (string &other_formula);
		int_str (int &other_variable, string &other_formula);
		int_str ( ){};
		~int_str ( ){};
		//istream& operator>> (istream &go, int_str &uni);
		
		bool integer_store ( );
		bool string_store ( );
		bool both_store ( );
		int variable_get ( );
		string formula_get ( );
		//void clearer ( );
	private:
		int variable;
		string formula;
};
