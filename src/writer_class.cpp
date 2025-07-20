#include "product.h"

#include <cstdio>

#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>

class writer : public writer_interface {
	
public:
        // destructor closes log-file
        ~writer(){
                if (output.is_open()) {
                        output.close();
                        std::cout << "closing " << file_name << std::endl;
                }
        }
	void init_writer(std::string file_name, int default_importance) override {
		this->file_name = file_name;
		this->default_importance = default_importance;
		return;
	}
	void change_default_importance (int new_importance) override {
		this->default_importance = new_importance;
		return;
	}

	void msg(std::string msg, int importance){
	
		if(importance < default_importance) return;
		
		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	
		output << msg << std::endl;
		output << "message importance: " << importance << std::endl;
		output << std::ctime(&end_time) << std::endl;
		
		return;
	}
	
	void msg_default (std::string msg_def) override {
		msg(msg_def,default_importance);
		return;
	}
	
	// opens file by sended name 
	// I made it keep write if file already exists, but it could be changed
	void open_file(std::string f_name){
		f_name += ".txt";
		output.open(f_name, std::ios::app);
		if(output.is_open()) std::cout << "openning OK\n";
		else std::cout << "openning FALSE\n";
		return;
	}
	
private:
        // log-file name
	std::string file_name;
	// def imp 
	int default_importance;
	// file-stream manager
	std::ofstream output;
};

std::shared_ptr<writer_interface> create_writer(std::string file_name, int default_importance){
	std::shared_ptr<writer> new_writer_to_return = std::make_shared<writer>();
	new_writer_to_return->init_writer(file_name, default_importance);
	new_writer_to_return->open_file(file_name);
	return new_writer_to_return; 
};

 
