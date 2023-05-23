# bash script to generate C++ canonical class files
​
# SRC_DIR=./src
# INC_DIR=./includes
SRC_DIR=./
INC_DIR=./
​
CLASS_EXT=".cpp"
HEADER_EXT=".hpp"
​
function check_overwrite
{
	if [[ -f $1 ]]
	then
		printf "\033[31;1mFile $1 already exists\nOverwrite ? [y/N]\033[0m\n"
		read ans
		if [ "$ans" == "n" ] || [ "$ans" == "N" ] || [ -z "$ans" ]
		then
			return 1
		fi
	fi
	return 0
}
​
function gen_class_header
{
	name=$1
	header_filename="${INC_DIR}/${name}${HEADER_EXT}"
​
	check_overwrite $header_filename
	if [[ $? -eq 1 ]]
	then
		return 1
	fi
​
	printf "\e[32;1m+++ Generating ${name} Header -- $header_filename\e[0m\n"
	mkdir -p $INC_DIR
	up_name=$(echo "${name}" | tr '[:lower:]' '[:upper:]')
​
​
​
	cat >> $header_filename << EOF
#ifndef ${up_name}_HPP
# define ${up_name}_HPP
namespace ft
{

class ${name}{
	public:
	    //Constructor
		${name}();
		${name}( int var );
		${name}( const ${name}& copy );
	
	    //Destructor
		~${name}();
	
		${name} & operator=( const ${name}& assign ); // Assignement Operator
	
		int		getVar() const;
		void	setVar( int input );
	
	private:
		int	_var;
};

}//Namespace ft

#endif 

EOF
}
​
function gen_class_file
{
	name=$1
	class_filename=${SRC_DIR}/${name}${CLASS_EXT}
​
	check_overwrite $class_filename
	if [[ $? -eq 1 ]]
	then
		return 1
	fi
​
	printf "\e[32;1m+++ Generating $name Class -- $class_filename\e[0m\n"
	mkdir -p $SRC_DIR
​
​
	cat >> $class_filename << EOF
#include "${name}.hpp"

namespace ft
{

//Constructor
${name}::${name}() 
{
	_var = 0;
}
${name}::${name}( int var ) : _var(var) 
{
}
${name}::${name}( const ${name}& copy ) 
{
	operator=(copy);
}
//Destructor
${name}::~${name}() {
}
${name} & ${name}::operator=( const ${name}& assign ) {
    if (this != &assign)
	    _var = assign.getVar();
	return *this;
}

int	${name}::getVar() const {
	return _var;
}
void	${name}::setVar( int input ) {
	_var = input;
}
//Private

}	// Nammespace ft

EOF
}
​
if [[ $# -eq 0 ]]
then
	read -p "Enter class name : " ARG
else
	ARG=$1
fi
if [[ -z $ARG ]]
then
	echo "Please provide a non-empty name."
	exit 1
fi
gen_class_header $ARG
gen_class_file $ARG