#include "../general.hpp"
#include "../responses/responses.hpp"


#define TEMP_ROOT_PATH "../test_files" 


void method_get(struct s_request_info request_struct)
{
	std::string content = return_content(200, request_struct.path);

	std::cout << content << std::endl;		//TODO	Find out how to return this.
}

