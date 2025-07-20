
#include <iostream>
#include <sstream>
#include "product.h"
#include <mutex>
#include <thread>

#include <string> 

int main(int argc, char** argv) {
	
	// check if we've got file name
	std::string file_name;
	if (argc < 2) {
		file_name = "default_output";
		std::cout << "no output filename -> set to default\n";
	}else{
		while(*argv[1] != '\0'){
			file_name += *(argv[1]);
			++(argv[1]);
		}
	}
	
	// check if we've got default importnace
	int default_importance;
	std::string default_importance_string;
	if (argc < 3) {
		default_importance = imp_lvl_1;
		std::cout << "no default importance -> set to default\n";
	}else{
		default_importance = atoi(argv[2]);
	}
	
	//std::cout << "init: " << file_name << "\t" << default_importance << std::endl;
	
	std::shared_ptr<writer_interface> msg_printer = create_writer(file_name, imp_lvl_1);
	
	std::string message_txt;		// message buffer
	std::string importance_txt;		// importance buffer
	int importance;
	char symb;						// char buffer to add in message
	std::mutex locker;				// mutex threads manager
	do {
		std::cout << "Print your message\n";
		std::cout << "Print \"stop\" if you want to close na app\n";
	
		std::cin >> message_txt;
		std::cin.get(symb);
		
		while(symb != '\n'){
			message_txt.push_back(symb);
			std::cin.get(symb);
		}
		
		if(message_txt == "stop") break;
		
		std::cout << "Print importance\n";
		std::cin.get(symb);
		
		while(symb != '\n'){
			importance_txt.push_back(symb);
			std::cin.get(symb);
		}
		
		// get first number from importance_txt
		if(importance_txt.length() > 0){
			std::stringstream ss;
			ss << importance_txt;
			ss >> importance;
		} else importance = 0;
		
		// defualt importance 
		if (importance == 0){
			std::cout << "No valid importance value!\n";
			std::thread write_thread([&](std::string msg){
			      locker.lock();
			      msg_printer->msg_default(msg);
			      locker.unlock();},
			          message_txt);
                        write_thread.detach();
		}
		// user importance
		else{
			std::thread write_thread([&](std::string msg, int imp){
			      locker.lock();
			      msg_printer->msg(msg,imp);
			      locker.unlock();},
			          message_txt, importance);
			write_thread.detach();
		}
		
		// clear buffers for next step
		message_txt.clear();
		importance_txt.clear();
	        
	        std::cout << std::endl;
	        
	} while (true);
		
	return 0;
}
