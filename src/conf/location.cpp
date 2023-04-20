/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:49:31 by emadriga          #+#    #+#             */
/*   Updated: 2023/04/20 18:55:46 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "location.hpp"

namespace ft
{
//Public
//Constructor
location::location()
	: _methods(0x1), _autoindex(false), _root("/"), _client_max_body_size(1024), _index("index.html"), _return("")
{}

//Destructor
location::~location()
{}

void location::set_methods(uint16_t methods){
	_methods = methods;
}
void location::set_autoindex(bool autoindex){
	_autoindex = autoindex;
}
void location::set_root(std::string root){
	_root = root;
}
void location::set_client_max_body_size(size_t client_max_body_size){
	_client_max_body_size = client_max_body_size;
}
void location::set_index(std::string index){
	_index = index;
}
void location::set_return(std::string return_){
	_return = return_;
}

const uint16_t & location::get_methods(){
	return _methods;
}
const bool &  location::get_autoindex(){
	return _autoindex;
}
const std::string &  location::get_root(){
	return _root;
}
const size_t &  location::get_client_max_body_size(){
	return _client_max_body_size;
}
const std::string &  location::get_index(){
	return _index;
}
const std::string &  location::get_return(){
	return _return;
}


//Private

}	// Nammespace ft




